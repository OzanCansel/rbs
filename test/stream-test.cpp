#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <algorithm>
#include <rbs/stream.hpp>
#include "helper.hpp"

struct foo
{
    short val_1;
    char  val_2;

    template<auto... Args>
    friend rbs::stream<Args...>& operator<<( rbs::stream<Args...>& ss , const foo& f )
    {
        return ss << f.val_1 << f.val_2;
    }

    template<auto... Args>
    friend rbs::stream<Args...>& operator>>( rbs::stream<Args...>& ss , foo& f )
    {
        return ss >> f.val_1 >> f.val_2;
    }
};

TEST_CASE( "write a char" )
{
    rbs::stream ss { rbs::endian::big };

    ss.write( char( 0x05 ) );
    REQUIRE( size( ss ) == 1 );
    REQUIRE( nth_byte( ss , 0 ) == 0x05 );
}

TEST_CASE( "write two chars" )
{
    rbs::stream ss { rbs::endian::big };

    ss.write( char( 0x05 ) );
    ss.write( char( 0x06 ) );

    REQUIRE( size( ss ) == 2 );
    REQUIRE( nth_byte( ss , 0 ) == 0x05 );
    REQUIRE( nth_byte( ss , 1 ) == 0x06 );
}

TEST_CASE( "write a be short" )
{
    rbs::stream ss { rbs::endian::big };

    ss.write( short( 0xABCD ) );

    REQUIRE( size( ss ) == 2 );
    REQUIRE( nth_byte( ss , 0 ) == 0xAB );
    REQUIRE( nth_byte( ss , 1 ) == 0xCD );
}

TEST_CASE( "write a be int" )
{
    rbs::stream ss { rbs::endian::big };

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

    rbs::stream ss { rbs::endian::big };

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

    rbs::stream ss { rbs::endian::big };

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
    rbs::stream ss { rbs::endian::little };

    ss.write( short( 0xABCD ) );

    REQUIRE( size( ss ) == 2 );
    REQUIRE( nth_byte( ss , 0 ) == 0xCD );
    REQUIRE( nth_byte( ss , 1 ) == 0xAB );
}

TEST_CASE( "write a le int" )
{
    rbs::stream ss { rbs::endian::little };

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

    rbs::stream ss { rbs::endian::little };

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

    rbs::stream ss { rbs::endian::little };

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

    rbs::stream ss { rbs::endian::native };

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

    rbs::stream ss { rbs::endian::native };

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

    rbs::stream ss { rbs::endian::native };

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

    rbs::stream ss { rbs::endian::native };

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

TEST_CASE( "write char array" )
{
    char data[ 4 ] { 0x01 , 0x02 , 0x03 ,0x04 };

    rbs::stream ss { rbs::endian::native };

    ss << data;

    REQUIRE( size( ss ) == 4 );
    REQUIRE( nth_byte( ss , 0 ) == data[ 0 ] );
    REQUIRE( nth_byte( ss , 1 ) == data[ 1 ] );
    REQUIRE( nth_byte( ss , 2 ) == data[ 2 ] );
    REQUIRE( nth_byte( ss , 3 ) == data[ 3 ] );
}

TEST_CASE( "write be short array" )
{
    short data[ 4 ] { 0x0102 , 0x0304 , 0x0506 ,0x0708 };

    rbs::stream ss { rbs::endian::big };

    ss << data;

    REQUIRE( size( ss ) == 8 );
    REQUIRE( nth_byte( ss , 0 ) == 0x01 );
    REQUIRE( nth_byte( ss , 1 ) == 0x02 );
    REQUIRE( nth_byte( ss , 2 ) == 0x03 );
    REQUIRE( nth_byte( ss , 3 ) == 0x04 );
    REQUIRE( nth_byte( ss , 4 ) == 0x05 );
    REQUIRE( nth_byte( ss , 5 ) == 0x06 );
    REQUIRE( nth_byte( ss , 6 ) == 0x07 );
    REQUIRE( nth_byte( ss , 7 ) == 0x08 );
}

TEST_CASE( "write le short array" )
{
    short data[ 4 ] { 0x0102 , 0x0304 , 0x0506 ,0x0708 };

    rbs::stream ss { rbs::endian::little };

    ss << data;

    REQUIRE( size( ss ) == 8 );
    REQUIRE( nth_byte( ss , 0 ) == 0x02 );
    REQUIRE( nth_byte( ss , 1 ) == 0x01 );
    REQUIRE( nth_byte( ss , 2 ) == 0x04 );
    REQUIRE( nth_byte( ss , 3 ) == 0x03 );
    REQUIRE( nth_byte( ss , 4 ) == 0x06 );
    REQUIRE( nth_byte( ss , 5 ) == 0x05 );
    REQUIRE( nth_byte( ss , 6 ) == 0x08 );
    REQUIRE( nth_byte( ss , 7 ) == 0x07 );
}

TEST_CASE( "write nt short array" )
{
    union raw
    {
        short val;
        char  data[ sizeof( short ) ];
    };

    short numbers[ 4 ] { 0x0102 , 0x0304 , 0x0506 , 0x0708 };
    raw*  numbers_raw { reinterpret_cast<raw*>( numbers ) };

    rbs::stream ss { rbs::endian::little };

    ss << numbers;

    REQUIRE( size( ss ) == 8 );
    REQUIRE( nth_byte( ss , 0 ) == numbers_raw[ 0 ].data[ 0 ] );
    REQUIRE( nth_byte( ss , 1 ) == numbers_raw[ 0 ].data[ 1 ] );
    REQUIRE( nth_byte( ss , 2 ) == numbers_raw[ 1 ].data[ 0 ] );
    REQUIRE( nth_byte( ss , 3 ) == numbers_raw[ 1 ].data[ 1 ] );
    REQUIRE( nth_byte( ss , 4 ) == numbers_raw[ 2 ].data[ 0 ] );
    REQUIRE( nth_byte( ss , 5 ) == numbers_raw[ 2 ].data[ 1 ] );
    REQUIRE( nth_byte( ss , 6 ) == numbers_raw[ 3 ].data[ 0 ] );
    REQUIRE( nth_byte( ss , 7 ) == numbers_raw[ 3 ].data[ 1 ] );
}

TEST_CASE( "write be custom type array" )
{
    foo foos[ 4 ]
    {
        { 0x01 , 0x02 } ,
        { 0x03 , 0x04 } ,
        { 0x05 , 0x06 } ,
        { 0x07 , 0x08 }
    };


    rbs::stream ss { rbs::endian::big };

    ss << foos;

    REQUIRE( size( ss ) == 12 );
    REQUIRE( nth_byte( ss , 0  ) == 0x00 );
    REQUIRE( nth_byte( ss , 1  ) == 0x01 );
    REQUIRE( nth_byte( ss , 2  ) == 0x02 );
    REQUIRE( nth_byte( ss , 3  ) == 0x00 );
    REQUIRE( nth_byte( ss , 4  ) == 0x03 );
    REQUIRE( nth_byte( ss , 5  ) == 0x04 );
    REQUIRE( nth_byte( ss , 6  ) == 0x00 );
    REQUIRE( nth_byte( ss , 7  ) == 0x05 );
    REQUIRE( nth_byte( ss , 8  ) == 0x06 );
    REQUIRE( nth_byte( ss , 9  ) == 0x00 );
    REQUIRE( nth_byte( ss , 10 ) == 0x07 );
    REQUIRE( nth_byte( ss , 11 ) == 0x08 );
}

TEST_CASE( "write one be short one le short" )
{
    short value_1 { 0x0102 };
    short value_2 { 0x0304 };

    rbs::stream ss { rbs::endian::big };

    ss << value_1;

    ss.byte_order(rbs::endian::little);

    ss << value_2;

    REQUIRE( size( ss ) == 4 );
    REQUIRE( nth_byte( ss , 0 ) == 0x01 );
    REQUIRE( nth_byte( ss , 1 ) == 0x02 );
    REQUIRE( nth_byte( ss , 2 ) == 0x04 );
    REQUIRE( nth_byte( ss , 3 ) == 0x03 );
}

TEST_CASE( "stream<OwnsBuffer>::byte_order test" )
{
    rbs::stream ss { rbs::endian::big };

    REQUIRE(ss.byte_order() == rbs::endian::big );
    ss.byte_order(rbs::endian::little);
    REQUIRE(ss.byte_order() == rbs::endian::little );
}

TEST_CASE( "stream<E>::buffer as reference" )
{
    boost::asio::streambuf buffer;
    rbs::stream ss { buffer , rbs::endian::native };

    ss << 1;

    REQUIRE( buffer_size( buffer.data() ) == 4 );
}

TEST_CASE( "Read char" )
{
    boost::asio::streambuf buffer;

    buffer.sputc( 0xAB );

    rbs::stream ss { buffer , rbs::endian::big };

    std::uint8_t val;

    ss >> val;

    REQUIRE( val == 0xAB );
}

TEST_CASE( "Read be short" )
{
    boost::asio::streambuf buffer;

    buffer.sputc( 0x0B );
    buffer.sputc( 0xCD );

    rbs::stream ss { buffer , rbs::endian::big };

    short val;

    ss >> val;

    REQUIRE( val == 0x0BCD );
}

TEST_CASE( "Read be int" )
{
    boost::asio::streambuf buffer;

    buffer.sputc( 0x01 );
    buffer.sputc( 0x23 );
    buffer.sputc( 0x45 );
    buffer.sputc( 0x67 );

    rbs::stream ss { buffer , rbs::endian::big };

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

    boost::asio::streambuf buffer;

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

    rbs::stream ss { buffer , rbs::endian::big };

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

    boost::asio::streambuf buffer;

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

    rbs::stream ss { buffer , rbs::endian::big };

    double value;

    ss >> value;

    REQUIRE( value == memory.val );
}

TEST_CASE( "Read le short" )
{
    boost::asio::streambuf buffer;

    buffer.sputc( 0xCD );
    buffer.sputc( 0x0B );

    rbs::stream ss { buffer , rbs::endian::little };

    short val;

    ss >> val;

    REQUIRE( val == 0x0BCD );
}

TEST_CASE( "Read le int" )
{
    boost::asio::streambuf buffer;

    buffer.sputc( 0x67 );
    buffer.sputc( 0x45 );
    buffer.sputc( 0x23 );
    buffer.sputc( 0x01 );

    rbs::stream ss { buffer , rbs::endian::little };

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

    boost::asio::streambuf buffer;

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

    rbs::stream ss { buffer , rbs::endian::little };

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

    boost::asio::streambuf buffer;

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

    rbs::stream ss { buffer , rbs::endian::little };

    double value;

    ss >> value;

    REQUIRE( value == memory.val );
}

TEST_CASE( "Read nt short" )
{
    boost::asio::streambuf buffer;

    union
    {
        short val { 0x0123 };
        char  data[ sizeof( short ) ];
    } memory;

    buffer.sputn( memory.data , sizeof( memory.data ) );

    rbs::stream ss { buffer , rbs::endian::native };

    short val;

    ss >> val;

    REQUIRE( val == 0x0123 );
}

TEST_CASE( "Read nt int" )
{
    boost::asio::streambuf buffer;

    union
    {
        int  val { 0x01234567 };
        char data[ sizeof( int ) ];
    } memory;

    buffer.sputn( memory.data , sizeof( memory.data ) );

    rbs::stream ss { buffer , rbs::endian::native };

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

    boost::asio::streambuf buffer;

    buffer.sputn( memory.data , sizeof( memory.data ) );

    rbs::stream ss { buffer , rbs::endian::native };

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

    boost::asio::streambuf buffer;

    buffer.sputn( memory.data , sizeof( memory.data ) );

    rbs::stream ss { buffer , rbs::endian::native };

    double value;

    ss >> value;

    REQUIRE( value == memory.val );
}

TEST_CASE( "Read char array" )
{
    boost::asio::streambuf buffer;

    buffer.sputc( 0x01 );
    buffer.sputc( 0x02 );
    buffer.sputc( 0x03 );

    rbs::stream ss { buffer , rbs::endian::little };

    char val[ 3 ];

    ss >> val;

    REQUIRE( val[ 0 ] == 0x01 );
    REQUIRE( val[ 1 ] == 0x02 );
    REQUIRE( val[ 2 ] == 0x03 );
}

TEST_CASE( "Read be short array" )
{
    boost::asio::streambuf buffer;

    buffer.sputc( 0x01 );
    buffer.sputc( 0x02 );
    buffer.sputc( 0x03 );
    buffer.sputc( 0x04 );
    buffer.sputc( 0x05 );
    buffer.sputc( 0x06 );

    rbs::stream ss { buffer , rbs::endian::big };

    std::uint16_t val[ 3 ];

    ss >> val;

    REQUIRE( val[ 0 ] == 0x0102 );
    REQUIRE( val[ 1 ] == 0x0304 );
    REQUIRE( val[ 2 ] == 0x0506 );
}

TEST_CASE( "Read le short array" )
{
    boost::asio::streambuf buffer;

    buffer.sputc( 0x02 );
    buffer.sputc( 0x01 );
    buffer.sputc( 0x04 );
    buffer.sputc( 0x03 );
    buffer.sputc( 0x06 );
    buffer.sputc( 0x05 );

    rbs::stream ss { buffer , rbs::endian::little };

    short val[ 3 ];

    ss >> val;

    REQUIRE( val[ 0 ] == 0x0102 );
    REQUIRE( val[ 1 ] == 0x0304 );
    REQUIRE( val[ 2 ] == 0x0506 );
}

TEST_CASE( "read be custom type array" )
{
    boost::asio::streambuf buffer;

    buffer.sputc( 0x00 );
    buffer.sputc( 0x01 );
    buffer.sputc( 0x02 );
    buffer.sputc( 0x00 );
    buffer.sputc( 0x03 );
    buffer.sputc( 0x04 );
    buffer.sputc( 0x00 );
    buffer.sputc( 0x05 );
    buffer.sputc( 0x06 );
    buffer.sputc( 0x00 );
    buffer.sputc( 0x07 );
    buffer.sputc( 0x08 );

    rbs::stream ss { buffer , rbs::endian::big };

    foo foos[ 4 ];
    ss >> foos;

    REQUIRE( foos[ 0 ].val_1 == 0x01 );
    REQUIRE( foos[ 0 ].val_2 == 0x02 );
    REQUIRE( foos[ 1 ].val_1 == 0x03 );
    REQUIRE( foos[ 1 ].val_2 == 0x04 );
    REQUIRE( foos[ 2 ].val_1 == 0x05 );
    REQUIRE( foos[ 2 ].val_2 == 0x06 );
    REQUIRE( foos[ 3 ].val_1 == 0x07 );
    REQUIRE( foos[ 3 ].val_2 == 0x08 );
}