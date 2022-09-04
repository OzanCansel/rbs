#include <boost/asio/buffers_iterator.hpp>
#include <iostream>
#include <iomanip>
#include <rbs/stream.hpp>
#include <string_view>

template<rbs::endian E>
void print( std::string_view prefix , rbs::stream<E>& ss )
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

int main()
{
    rbs::be_stream bes;

    bes << char( 0x1F )
        << short( 0x0102 )
        << int( 0x01020304 )
        << float( 1234.56789f )
        << double( 123456789.123456789 );

    rbs::le_stream les;

    les << char( 0x1F )
        << short( 0x0102 )
        << int( 0x01020304 )
        << float( 1234.56789f )
        << double( 123456789.123456789 );

    rbs::nt_stream nts;

    nts << char( 0x1F )
        << short( 0x0102 )
        << int( 0x01020304 )
        << float( 1234.56789f )
        << double( 123456789.123456789 );

    print( "big_endian   " , bes );
    print( "little_endian" , les );
    print( "native       " , nts );
}