#include "rbs/stream.hpp"
#include <algorithm>
#include <type_traits>

namespace rbs
{

namespace impl
{
    template<typename T>
    struct suitable_to_rw :
           std::integral_constant<
               bool ,
               std::is_arithmetic_v<T> || std::is_enum_v<T>
           >
    {};

    template<typename T>
    constexpr auto suitable_to_rw_v = suitable_to_rw<T>::value;
}

template<endian E , bool OwnsBuffer>
stream<E , OwnsBuffer>::stream()
    :   m_buffer { impl::conditional_buffer<OwnsBuffer>::buf() }
{
    static_assert( OwnsBuffer );
}

template<endian E , bool OwnsBuffer>
stream<E , OwnsBuffer>::stream( std::streambuf& b )
    :   m_buffer { b }
{
    static_assert( !OwnsBuffer );
}

template<endian E , bool OwnsBuffer>
stream<E , OwnsBuffer>::stream( std::ios& ios )
    :   stream<E , OwnsBuffer> { *ios.rdbuf() }
{}

template<endian E , bool OwnsBuffer>
template<typename T>
void stream<E , OwnsBuffer>::write( const T& val )
{
    static_assert(
        impl::suitable_to_rw_v<T> ,
        "T must be a primitive type"
    );

    if constexpr ( E == endian::native )
    {
        m_buffer.sputn(
            reinterpret_cast<const char*>( &val ) ,
            sizeof( T )
        );
    }
    else
    {
        union raw
        {
            T    value;
            char data[ sizeof( T ) ];
        } memory;

        memory.value = val;

        std::reverse(
            std::begin( memory.data ) ,
            std::end( memory.data )
        );

        m_buffer.sputn(
            reinterpret_cast<char*>( &memory.data ) ,
            sizeof( T )
        );
    }
}

template<endian E , bool OwnsBuffer>
template<typename T>
void stream<E , OwnsBuffer>::write( const T* src , std::size_t n )
{
    static_assert(
        impl::suitable_to_rw_v<T> ,
        "T must be a primitive type"
    );

    if constexpr ( E == endian::native )
    {
        m_buffer.sputn(
            reinterpret_cast<const char*>( src ) ,
            sizeof( T ) * n
        );
    }
    else
    {
        union raw
        {
            T    value;
            char data[ sizeof( T ) ];
        };

        std::unique_ptr<raw[]> src_corrected {
            new raw[ n ]
        };

        std::copy(
            src ,
            src + n ,
            reinterpret_cast<T*>( src_corrected.get() )
        );

        for ( std::size_t i = 0; i < n; ++i )
            std::reverse(
                std::begin( src_corrected[ i ].data ) ,
                std::end( src_corrected[ i ].data )
            );

        m_buffer.sputn(
            reinterpret_cast<char*>( src_corrected.get() ) ,
            sizeof( T ) * n
        );
    }
}

template<endian E , bool OwnsBuffer>
template<typename T>
void stream<E , OwnsBuffer>::read( T& value )
{
    static_assert(
        impl::suitable_to_rw_v<T> ,
        "T must be a primitive type"
    );

    if constexpr ( E == endian::native )
    {
        m_buffer.sgetn(
            reinterpret_cast<char*>( &value ) ,
            sizeof( T )
        );
    }
    else
    {
        auto beginning = reinterpret_cast<char*>( &value );

        m_buffer.sgetn(
            beginning ,
            sizeof( T )
        );

        std::reverse(
            beginning ,
            beginning + sizeof( value )
        );
    }
}

template<endian E , bool OwnsBuffer>
template<typename T>
void stream<E , OwnsBuffer>::read( T* dst , std::size_t n )
{
    m_buffer.sgetn(
        reinterpret_cast<char*>( dst ) ,
        sizeof( T ) * n
    );

    if constexpr ( E != endian::native )
        for ( std::size_t i = 0; i < n; ++i )
            std::reverse(
                reinterpret_cast<char*>( dst ) + i * sizeof( T ) ,
                reinterpret_cast<char*>( dst ) + i * sizeof( T ) + sizeof( T )
            );
}

template<endian E , bool OwnsBuffer , typename T>
inline
std::enable_if_t<impl::suitable_to_rw_v<T> , stream<E , OwnsBuffer>&>
operator<<( stream<E , OwnsBuffer>& ss , const T& value )
{
    ss.write( value );

    return ss;
}

template<typename T>
void print();

template<endian E , bool OwnsBuffer , typename T , std::size_t N>
inline
std::enable_if_t<impl::suitable_to_rw_v<T> , stream<E , OwnsBuffer>&>
operator<<( stream<E , OwnsBuffer>& ss , const T(&src)[N] )
{
    ss.template write<T>( src , N );

    return ss;
}

template<endian E , bool OwnsBuffer , typename T>
inline
std::enable_if_t<impl::suitable_to_rw_v<T> , stream<E , OwnsBuffer>&>
operator>>( stream<E , OwnsBuffer>& ss , T& value )
{
    ss.read( value );

    return ss;
}

template<endian E , bool OwnsBuffer , typename T , std::size_t N>
inline
std::enable_if_t<impl::suitable_to_rw_v<T> , stream<E , OwnsBuffer>&>
operator>>( stream<E , OwnsBuffer>& ss , T(&src)[ N ] )
{
    ss.template read<T>( src , N );

    return ss;
}

}