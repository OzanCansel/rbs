#pragma once

#include <iostream>
#include <iomanip>
#include <string_view>
#include <boost/asio/buffers_iterator.hpp>
#include <rbs/stream.hpp>

inline void print( std::string_view prefix , boost::asio::streambuf& buffer )
{
    std::cout << prefix << " | ";

    for ( auto it  = buffers_begin( buffer.data() );
               it != buffers_end( buffer.data() );
               ++it )
        std::cout << std::setw( 2 )
                  << std::setfill( '0' )
                  << std::hex
                  << std::uint32_t( std::uint8_t( *it ) )
                  << ' ';

    std::cout << std::endl;
}

template<rbs::endian E>
inline void print( std::string_view prefix , rbs::stream<E , true>& ss )
{
    print( prefix , ss.buf() );
}