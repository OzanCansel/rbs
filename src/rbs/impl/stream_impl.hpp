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

template<endian E>
stream<E>::stream()
    :   m_opt_buf { std::in_place_t {} }
    ,   m_buffer { *m_opt_buf }
{}

template<endian E>
stream<E>::stream( buffer& buf )
    :   m_buffer { buf }
{}

template<endian E>
template<typename T>
void stream<E>::write( const T& val )
{
    static_assert(
        impl::suitable_to_rw_v<T> ,
        "T must be primitive type"
    );

    if ( E == endian::native )
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

template<endian E>
template<typename T>
void stream<E>::read( T& val )
{
    static_assert(
        impl::suitable_to_rw_v<T> ,
        "T must be primitive type"
    );

    if ( E == endian::native )
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

template<endian E>
typename stream<E>::buffer& stream<E>::buf()
{
    return m_buffer;
}

template<endian E>
const typename stream<E>::buffer& stream<E>::buf() const
{
    return m_buffer;
}

template<endian E , typename T , typename = std::enable_if_t<impl::suitable_to_rw_v<T>>>
inline stream<E>& operator<<( stream<E>& ss , const T& val )
{
    ss.write( val );

    return ss;
}

template<endian E , typename T , typename = std::enable_if_t<impl::suitable_to_rw_v<T>>>
inline stream<E>& operator>>( stream<E>& ss , T& val )
{
    ss.read( val );

    return ss;
}

}