#pragma once

#include <cstdint>
#include <rbs/stream.hpp>
#include <boost/asio/buffers_iterator.hpp>

template<bool OwnsBuffer>
inline std::uint8_t nth_byte( rbs::stream<OwnsBuffer>& bs , int idx )
{
    return std::uint8_t( buffers_begin( bs.buf().data() )[ idx ] );
}

inline std::uint8_t nth_byte( boost::asio::streambuf& bs , int idx )
{
    return std::uint8_t( buffers_begin( bs.data() )[ idx ] );
}

template<bool OwnsBuffer>
inline int size( rbs::stream<OwnsBuffer>& bs )
{
    return buffer_size( bs.buf().data() );
}