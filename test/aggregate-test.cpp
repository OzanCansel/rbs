#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <rbs/aggregate.hpp>
#include "helper.hpp"

struct coordinate
{
    int x;
    int y;
    int z;
};

template<>
struct rbs::aggregate_serializable<coordinate> : std::true_type
{};

TEST_CASE( "Aggregate operator<< | three fields aggregate type" )
{
    rbs::be_stream bes;

    coordinate c { 1 , 2 , 3 };

    bes << c;

    REQUIRE( size( bes ) == 12 );
    REQUIRE( nth_byte( bes , 3  ) == 0x01 );
    REQUIRE( nth_byte( bes , 7  ) == 0x02 );
    REQUIRE( nth_byte( bes , 11 ) == 0x03 );
}

TEST_CASE( "Aggregate operator>> | three fields aggregate type" )
{
    boost::asio::streambuf buffer;

    buffer.sputc( 0x00 );
    buffer.sputc( 0x00 );
    buffer.sputc( 0x00 );
    buffer.sputc( 0x01 );
    buffer.sputc( 0x00 );
    buffer.sputc( 0x00 );
    buffer.sputc( 0x00 );
    buffer.sputc( 0x02 );
    buffer.sputc( 0x00 );
    buffer.sputc( 0x00 );
    buffer.sputc( 0x00 );
    buffer.sputc( 0x03 );

    rbs::be_stream bes { buffer };

    coordinate c;

    bes >> c;

    REQUIRE( c.x == 1 );
    REQUIRE( c.y == 2 );
    REQUIRE( c.z == 3 );
}