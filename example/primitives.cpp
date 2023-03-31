#include <rbs/stream.hpp>
#include "helper.hpp"

int main()
{
    rbs::stream bes  { rbs::endian::big };

    bes << char( 0x1F )
        << short( 0x0102 )
        << int( 0x01020304 )
        << float( 1234.56789f )
        << double( 123456789.123456789 );

    rbs::stream les { rbs::endian::little };

    les << char( 0x1F )
        << short( 0x0102 )
        << int( 0x01020304 )
        << float( 1234.56789f )
        << double( 123456789.123456789 );

    rbs::stream nts  { rbs::endian::native };

    nts << char( 0x1F )
        << short( 0x0102 )
        << int( 0x01020304 )
        << float( 1234.56789f )
        << double( 123456789.123456789 );

    print( "big_endian   " , bes );
    print( "little_endian" , les );
    print( "native       " , nts );
}