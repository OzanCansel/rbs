#pragma once

#include <cstdint>
#include <rbs/stream.hpp>
#include <boost/asio/buffers_iterator.hpp>

template<rbs::endian E , bool OwnsBuffer>
inline std::uint8_t nth_byte( rbs::stream<E , OwnsBuffer>& bs , int idx )
{
    return std::uint8_t( buffers_begin( bs.buf().data() )[ idx ] );
}

template<rbs::endian E , bool OwnsBuffer>
inline int size( rbs::stream<E , OwnsBuffer>& bs )
{
    return buffer_size( bs.buf().data() );
}