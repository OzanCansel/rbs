#pragma once

#include <iostream>
#include <iomanip>
#include <string_view>
#include <boost/asio/buffers_iterator.hpp>
#include <rbs/stream.hpp>

template<rbs::endian E>
inline void print( std::string_view prefix , rbs::stream<E>& ss )
{
    std::cout << prefix << " | ";

    for ( auto it  = buffers_begin( ss.buf().data() );
               it != buffers_end( ss.buf().data() );
               ++it )
        std::cout << std::setw( 2 )
                  << std::setfill( '0' )
                  << std::hex
                  << std::uint32_t( std::uint8_t( *it ) )
                  << ' ';

    std::cout << std::endl;
}