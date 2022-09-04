#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <algorithm>
#include <rbs/stream.hpp>
#include "helper.hpp"

TEST_CASE( "write a char" )
{
    rbs::be_stream ss;

    ss.write( char( 0x05 ) );
    REQUIRE( size( ss ) == 1 );
    REQUIRE( nth_byte( ss , 0 ) == 0x05 );
}

TEST_CASE( "write two chars" )
{
    rbs::be_stream ss;

    ss.write( char( 0x05 ) );
    ss.write( char( 0x06 ) );

    REQUIRE( size( ss ) == 2 );
    REQUIRE( nth_byte( ss , 0 ) == 0x05 );
    REQUIRE( nth_byte( ss , 1 ) == 0x06 );
}

TEST_CASE( "write a be short" )
{
    rbs::be_stream ss;

    ss.write( short( 0xABCD ) );

    REQUIRE( size( ss ) == 2 );
    REQUIRE( nth_byte( ss , 0 ) == 0xAB );
    REQUIRE( nth_byte( ss , 1 ) == 0xCD );
}

TEST_CASE( "write a be int" )
{
    rbs::be_stream ss;

    ss.write( 0x12345678 );

    REQUIRE( size( ss ) == 4 );
    REQUIRE( nth_byte( ss , 0 ) == 0x12 );
    REQUIRE( nth_byte( ss , 1 ) == 0x34 );
    REQUIRE( nth_byte( ss , 2 ) == 0x56 );
    REQUIRE( nth_byte( ss , 3 ) == 0x78 );
}

TEST_CASE( "write a be float" )
{
    union 
    {
        float        value;
        std::uint8_t data[ sizeof( float ) ];
    } mem;

    mem.value = 2342.23421f;

    rbs::be_stream ss;

    ss << mem.value;

    if ( rbs::endian::native != rbs::endian::big )
        std::reverse(
            std::begin( mem.data ) ,
            std::end( mem.data )
        );

    REQUIRE( size( ss ) == 4  );
    REQUIRE( nth_byte( ss , 0 ) == mem.data[ 0 ] );
    REQUIRE( nth_byte( ss , 1 ) == mem.data[ 1 ] );
    REQUIRE( nth_byte( ss , 2 ) == mem.data[ 2 ] );
    REQUIRE( nth_byte( ss , 3 ) == mem.data[ 3 ] );
}

TEST_CASE( "write a be double" )
{
    union 
    {
        double       value;
        std::uint8_t data[ sizeof( double ) ];
    } mem;

    mem.value = 2342.23421;

    rbs::be_stream ss;

    ss << mem.value;

    if ( rbs::endian::native != rbs::endian::big )
        std::reverse(
            std::begin( mem.data ) ,
            std::end( mem.data )
        );

    REQUIRE( size( ss ) == 8  );
    REQUIRE( nth_byte( ss , 0 ) == mem.data[ 0 ] );
    REQUIRE( nth_byte( ss , 1 ) == mem.data[ 1 ] );
    REQUIRE( nth_byte( ss , 2 ) == mem.data[ 2 ] );
    REQUIRE( nth_byte( ss , 3 ) == mem.data[ 3 ] );
    REQUIRE( nth_byte( ss , 4 ) == mem.data[ 4 ] );
    REQUIRE( nth_byte( ss , 5 ) == mem.data[ 5 ] );
    REQUIRE( nth_byte( ss , 6 ) == mem.data[ 6 ] );
    REQUIRE( nth_byte( ss , 7 ) == mem.data[ 7 ] );
}

TEST_CASE( "write a le short" )
{
    rbs::le_stream ss;

    ss.write( short( 0xABCD ) );

    REQUIRE( size( ss ) == 2 );
    REQUIRE( nth_byte( ss , 0 ) == 0xCD );
    REQUIRE( nth_byte( ss , 1 ) == 0xAB );
}

TEST_CASE( "write a le int" )
{
    rbs::le_stream ss;

    ss.write( 0x12345678 );

    REQUIRE( size( ss ) == 4 );
    REQUIRE( nth_byte( ss , 0 ) == 0x78 );
    REQUIRE( nth_byte( ss , 1 ) == 0x56 );
    REQUIRE( nth_byte( ss , 2 ) == 0x34 );
    REQUIRE( nth_byte( ss , 3 ) == 0x12 );
}

TEST_CASE( "write a le float" )
{
    union 
    {
        float        value;
        std::uint8_t data[ sizeof( float ) ];
    } mem;

    mem.value = 2342.23421f;

    rbs::le_stream ss;

    ss << mem.value;

    if ( rbs::endian::native != rbs::endian::little )
        std::reverse(
            std::begin( mem.data ) ,
            std::end( mem.data )
        );

    REQUIRE( size( ss ) == 4  );
    REQUIRE( nth_byte( ss , 0 ) == mem.data[ 0 ] );
    REQUIRE( nth_byte( ss , 1 ) == mem.data[ 1 ] );
    REQUIRE( nth_byte( ss , 2 ) == mem.data[ 2 ] );
    REQUIRE( nth_byte( ss , 3 ) == mem.data[ 3 ] );
}

TEST_CASE( "write a le double" )
{
    union 
    {
        double       value;
        std::uint8_t data[ sizeof( double ) ];
    } mem;

    mem.value = 2342.23421;

    rbs::le_stream ss;

    ss << mem.value;

    if ( rbs::endian::native != rbs::endian::little )
        std::reverse(
            std::begin( mem.data ) ,
            std::end( mem.data )
        );

    REQUIRE( size( ss ) == 8  );
    REQUIRE( nth_byte( ss , 0 ) == mem.data[ 0 ] );
    REQUIRE( nth_byte( ss , 1 ) == mem.data[ 1 ] );
    REQUIRE( nth_byte( ss , 2 ) == mem.data[ 2 ] );
    REQUIRE( nth_byte( ss , 3 ) == mem.data[ 3 ] );
    REQUIRE( nth_byte( ss , 4 ) == mem.data[ 4 ] );
    REQUIRE( nth_byte( ss , 5 ) == mem.data[ 5 ] );
    REQUIRE( nth_byte( ss , 6 ) == mem.data[ 6 ] );
    REQUIRE( nth_byte( ss , 7 ) == mem.data[ 7 ] );
}

TEST_CASE( "write a native short" )
{
    union 
    {
        short        value;
        std::uint8_t data[ sizeof( short ) ];
    } mem;

    mem.value = 0x1234;

    rbs::nt_stream ss;

    ss << mem.value;

    REQUIRE( size( ss ) == 2 );
    REQUIRE( nth_byte( ss , 0 ) == mem.data[ 0 ] );
    REQUIRE( nth_byte( ss , 1 ) == mem.data[ 1 ] );
}

TEST_CASE( "write a native int" )
{
    union 
    {
        int        value;
        std::uint8_t data[ sizeof( int ) ];
    } mem;

    mem.value = 0x12345678;

    rbs::nt_stream ss;

    ss << mem.value;

    REQUIRE( size( ss ) == 4 );
    REQUIRE( nth_byte( ss , 0 ) == mem.data[ 0 ] );
    REQUIRE( nth_byte( ss , 1 ) == mem.data[ 1 ] );
    REQUIRE( nth_byte( ss , 2 ) == mem.data[ 2 ] );
    REQUIRE( nth_byte( ss , 3 ) == mem.data[ 3 ] );
}

TEST_CASE( "write a native float" )
{
    union 
    {
        float        value;
        std::uint8_t data[ sizeof( float ) ];
    } mem;

    mem.value = 2342.23421f;

    rbs::nt_stream ss;

    ss << mem.value;

    REQUIRE( size( ss ) == 4 );
    REQUIRE( nth_byte( ss , 0 ) == mem.data[ 0 ] );
    REQUIRE( nth_byte( ss , 1 ) == mem.data[ 1 ] );
    REQUIRE( nth_byte( ss , 2 ) == mem.data[ 2 ] );
    REQUIRE( nth_byte( ss , 3 ) == mem.data[ 3 ] );
}

TEST_CASE( "write a native double" )
{
    union 
    {
        double       value;
        std::uint8_t data[ sizeof( double ) ];
    } mem;

    mem.value = 2342.23421;

    rbs::nt_stream ss;

    ss << mem.value;

    REQUIRE( size( ss ) == 8 );
    REQUIRE( nth_byte( ss , 0 ) == mem.data[ 0 ] );
    REQUIRE( nth_byte( ss , 1 ) == mem.data[ 1 ] );
    REQUIRE( nth_byte( ss , 2 ) == mem.data[ 2 ] );
    REQUIRE( nth_byte( ss , 3 ) == mem.data[ 3 ] );
    REQUIRE( nth_byte( ss , 4 ) == mem.data[ 4 ] );
    REQUIRE( nth_byte( ss , 5 ) == mem.data[ 5 ] );
    REQUIRE( nth_byte( ss , 6 ) == mem.data[ 6 ] );
    REQUIRE( nth_byte( ss , 7 ) == mem.data[ 7 ] );
}

TEST_CASE( "stream<E>::buffer as reference" )
{
    rbs::nt_stream::buffer buffer;
    rbs::nt_stream ss { buffer };

    ss << 1;

    REQUIRE( buffer_size( buffer.data() ) == 4 );
}

TEST_CASE( "Read char" )
{
    rbs::nt_stream::buffer buffer;

    buffer.sputc( 0xAB );

    rbs::be_stream ss { buffer };

    std::uint8_t val;

    ss >> val;

    REQUIRE( val == 0xAB );
}

TEST_CASE( "Read be short" )
{
    rbs::be_stream::buffer buffer;

    buffer.sputc( 0x0B );
    buffer.sputc( 0xCD );

    rbs::be_stream ss { buffer };

    short val;

    ss >> val;

    REQUIRE( val == 0x0BCD );
}

TEST_CASE( "Read be int" )
{
    rbs::be_stream::buffer buffer;

    buffer.sputc( 0x01 );
    buffer.sputc( 0x23 );
    buffer.sputc( 0x45 );
    buffer.sputc( 0x67 );

    rbs::be_stream ss { buffer };

    int val;

    ss >> val;

    REQUIRE( val == 0x01234567 );
}

TEST_CASE( "Read be float" )
{
    char endian_converted[ sizeof( float ) ];
    union
    {
        float val { 1234.5678f };
        char  data[ sizeof( float ) ];
    } memory;

    rbs::be_stream::buffer buffer;

    std::copy(
        std::begin( memory.data ) ,
        std::end( memory.data ) ,
        std::begin( endian_converted )
    );

    if ( rbs::endian::native != rbs::endian::big )
        std::reverse(
            std::begin( endian_converted ) ,
            std::end( endian_converted )
        );
    
    buffer.sputn( endian_converted , sizeof( endian_converted ) );

    rbs::be_stream ss { buffer };

    float value;

    ss >> value;

    REQUIRE( value == memory.val );
}

TEST_CASE( "Read be double" )
{
    char endian_converted[ sizeof( double ) ];
    union
    {
        double val { 1234.5678 };
        char   data[ sizeof( double ) ];
    } memory;

    rbs::be_stream::buffer buffer;

    std::copy(
        std::begin( memory.data ) ,
        std::end( memory.data ) ,
        std::begin( endian_converted )
    );

    if ( rbs::endian::native != rbs::endian::big )
        std::reverse(
            std::begin( endian_converted ) ,
            std::end( endian_converted )
        );
    
    buffer.sputn( endian_converted , sizeof( endian_converted ) );

    rbs::be_stream ss { buffer };

    double value;

    ss >> value;

    REQUIRE( value == memory.val );
}

TEST_CASE( "Read le short" )
{
    rbs::le_stream::buffer buffer;

    buffer.sputc( 0xCD );
    buffer.sputc( 0x0B );

    rbs::le_stream ss { buffer };

    short val;

    ss >> val;

    REQUIRE( val == 0x0BCD );
}

TEST_CASE( "Read le int" )
{
    rbs::le_stream::buffer buffer;

    buffer.sputc( 0x67 );
    buffer.sputc( 0x45 );
    buffer.sputc( 0x23 );
    buffer.sputc( 0x01 );

    rbs::le_stream ss { buffer };

    int val;

    ss >> val;

    REQUIRE( val == 0x01234567 );
}

TEST_CASE( "Read le float" )
{
    char endian_converted[ sizeof( float ) ];
    union
    {
        float val { 1234.5678f };
        char  data[ sizeof( float ) ];
    } memory;

    rbs::le_stream::buffer buffer;

    std::copy(
        std::begin( memory.data ) ,
        std::end( memory.data ) ,
        std::begin( endian_converted )
    );

    if ( rbs::endian::native != rbs::endian::little )
        std::reverse(
            std::begin( endian_converted ) ,
            std::end( endian_converted )
        );
    
    buffer.sputn( endian_converted , sizeof( endian_converted ) );

    rbs::le_stream ss { buffer };

    float value;

    ss >> value;

    REQUIRE( value == memory.val );
}

TEST_CASE( "Read le double" )
{
    char endian_converted[ sizeof( double ) ];
    union
    {
        double val { 1234.5678 };
        char   data[ sizeof( double ) ];
    } memory;

    rbs::le_stream::buffer buffer;

    std::copy(
        std::begin( memory.data ) ,
        std::end( memory.data ) ,
        std::begin( endian_converted )
    );

    if ( rbs::endian::native != rbs::endian::little )
        std::reverse(
            std::begin( endian_converted ) ,
            std::end( endian_converted )
        );
    
    buffer.sputn( endian_converted , sizeof( endian_converted ) );

    rbs::le_stream ss { buffer };

    double value;

    ss >> value;

    REQUIRE( value == memory.val );
}

TEST_CASE( "Read nt short" )
{
    rbs::nt_stream::buffer buffer;

    union
    {
        short val { 0x0123 };
        char  data[ sizeof( short ) ];
    } memory;

    buffer.sputn( memory.data , sizeof( memory.data ) );

    rbs::nt_stream ss { buffer };

    short val;

    ss >> val;

    REQUIRE( val == 0x0123 );
}

TEST_CASE( "Read nt int" )
{
    rbs::nt_stream::buffer buffer;

    union
    {
        int  val { 0x01234567 };
        char data[ sizeof( int ) ];
    } memory;

    buffer.sputn( memory.data , sizeof( memory.data ) );

    rbs::nt_stream ss { buffer };

    int val;

    ss >> val;

    REQUIRE( val == 0x01234567 );
}

TEST_CASE( "Read nt float" )
{
    union
    {
        float val { 1234.5678f };
        char  data[ sizeof( float ) ];
    } memory;

    rbs::nt_stream::buffer buffer;

    buffer.sputn( memory.data , sizeof( memory.data ) );

    rbs::nt_stream ss { buffer };

    float value;

    ss >> value;

    REQUIRE( value == memory.val );
}

TEST_CASE( "Read nt double" )
{
    union
    {
        double val { 1234.5678 };
        char   data[ sizeof( double ) ];
    } memory;

    rbs::nt_stream::buffer buffer;

    buffer.sputn( memory.data , sizeof( memory.data ) );

    rbs::nt_stream ss { buffer };

    double value;

    ss >> value;

    REQUIRE( value == memory.val );
}