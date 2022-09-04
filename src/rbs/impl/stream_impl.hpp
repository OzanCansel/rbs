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
stream<E , OwnsBuffer>::stream( std::ios& os )
    :   stream<E , OwnsBuffer> { *os.rdbuf() }
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
        } mem;

        mem.value = val;

        std::reverse(
            std::begin( mem.data ) ,
            std::end( mem.data )
        );

        m_buffer.sputn(
            reinterpret_cast<char*>( &mem.data ) ,
            sizeof( T )
        );
    }
}

template<endian E , bool OwnsBuffer>
template<typename T>
void stream<E , OwnsBuffer>::read( T& val )
{
    static_assert(
        impl::suitable_to_rw_v<T> ,
        "T must be a primitive type"
    );

    if constexpr ( E == endian::native )
    {
        m_buffer.sgetn(
            reinterpret_cast<char*>( &val ) ,
            sizeof( T )
        );
    }
    else
    {
        auto beg = reinterpret_cast<char*>( &val );

        m_buffer.sgetn(
            beg ,
            sizeof( T )
        );

        std::reverse(
            beg ,
            beg + sizeof( val )
        );
    }
}

template<endian E , bool OwnsBuffer , typename T>
inline
std::enable_if_t<impl::suitable_to_rw_v<T> , stream<E , OwnsBuffer>&>
operator<<( stream<E , OwnsBuffer>& ss , const T& val )
{
    ss.write( val );

    return ss;
}

template<endian E , bool OwnsBuffer , typename T>
inline
std::enable_if_t<impl::suitable_to_rw_v<T> , stream<E , OwnsBuffer>&>
operator>>( stream<E , OwnsBuffer>& ss , T& val )
{
    ss.read( val );

    return ss;
}

}