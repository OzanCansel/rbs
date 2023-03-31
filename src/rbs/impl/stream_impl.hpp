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

template<bool OwnsBuffer>
stream<OwnsBuffer>::stream(endian e)
    :   m_endian {e}
    ,   m_buffer { impl::conditional_buffer<OwnsBuffer>::buf() }
{
    static_assert( OwnsBuffer );
}

template<bool OwnsBuffer>
stream<OwnsBuffer>::stream( std::streambuf& b , endian e )
    :   m_endian { e }
    ,   m_buffer { b }
{
    static_assert( !OwnsBuffer );
}

template<bool OwnsBuffer>
stream<OwnsBuffer>::stream( std::ios& ios, endian e )
    :   stream<OwnsBuffer> { *ios.rdbuf(), e }
{}

template<bool OwnsBuffer>
template<typename T>
void stream<OwnsBuffer>::write( const T& val )
{
    static_assert(
        impl::suitable_to_rw_v<T> ,
        "T must be a primitive type"
    );

    if ( m_endian == endian::native )
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

template<bool OwnsBuffer>
template<typename T>
void stream<OwnsBuffer>::write( const T* src , std::size_t n )
{
    static_assert(
        impl::suitable_to_rw_v<T> ,
        "T must be a primitive type"
    );

    if ( m_endian == endian::native )
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

template<bool OwnsBuffer>
template<typename T>
void stream<OwnsBuffer>::read( T& value )
{
    static_assert(
        impl::suitable_to_rw_v<T> ,
        "T must be a primitive type"
    );

    if ( m_endian == endian::native )
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

template<bool OwnsBuffer>
template<typename T>
void stream<OwnsBuffer>::read( T* dst , std::size_t n )
{
    m_buffer.sgetn(
        reinterpret_cast<char*>( dst ) ,
        sizeof( T ) * n
    );

    if ( m_endian != endian::native )
        for ( std::size_t i = 0; i < n; ++i )
            std::reverse(
                reinterpret_cast<char*>( dst ) + i * sizeof( T ) ,
                reinterpret_cast<char*>( dst ) + i * sizeof( T ) + sizeof( T )
            );
}

template<bool OwnsBuffer>
endian stream<OwnsBuffer>::byte_order() const
{
    return m_endian;
}

template<bool OwnsBuffer>
void stream<OwnsBuffer>::byte_order( endian x )
{
    m_endian = x;
}

template<bool OwnsBuffer , typename T>
inline
std::enable_if_t<impl::suitable_to_rw_v<T> , stream<OwnsBuffer>&>
operator<<( stream<OwnsBuffer>& ss , const T& value )
{
    ss.write( value );

    return ss;
}

template<bool OwnsBuffer , typename T , std::size_t N>
inline
std::enable_if_t<impl::suitable_to_rw_v<T> , stream<OwnsBuffer>&>
operator<<( stream<OwnsBuffer>& ss , const T(&src)[N] )
{
    ss.template write<T>( src , N );

    return ss;
}

template<bool OwnsBuffer , typename T , std::size_t N>
inline
std::enable_if_t<!impl::suitable_to_rw_v<T> , stream<OwnsBuffer>&>
operator<<( stream<OwnsBuffer>& ss , const T(&src)[N] )
{
    for ( std::size_t i = 0; i < N; ++i )
        ss << src[ i ];

    return ss;
}

template<bool OwnsBuffer , typename T>
inline
std::enable_if_t<impl::suitable_to_rw_v<T> , stream<OwnsBuffer>&>
operator>>( stream<OwnsBuffer>& ss , T& value )
{
    ss.read( value );

    return ss;
}

template<bool OwnsBuffer , typename T , std::size_t N>
inline
std::enable_if_t<impl::suitable_to_rw_v<T> , stream<OwnsBuffer>&>
operator>>( stream<OwnsBuffer>& ss , T(&src)[ N ] )
{
    ss.template read<T>( src , N );

    return ss;
}

template<bool OwnsBuffer , typename T , std::size_t N>
inline
std::enable_if_t<!impl::suitable_to_rw_v<T> , stream<OwnsBuffer>&>
operator>>( stream<OwnsBuffer>& ss , T(&src)[ N ] )
{
    for ( std::size_t i = 0; i < N; ++i )
        ss >> src[ i ];

    return ss;
}

}