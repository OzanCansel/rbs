#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <algorithm>
#include <rbs/serialize_util.hpp>
#include "helper.hpp"

TEST_CASE( "serialize_be with std::streambuf&" )
{
    rbs::be_stream ss;

    ss << 0x01020304;

    boost::asio::streambuf buffer;

    rbs::serialize_be( 0x01020304 , buffer );

    for ( auto i = 0; i < size( ss ); ++i )
        REQUIRE( nth_byte( ss , i ) == nth_byte( buffer , i ) );
}

TEST_CASE( "serialize_le with std::streambuf&" )
{
    rbs::le_stream ss;

    ss << 0x01020304;

    boost::asio::streambuf buffer;

    rbs::serialize_le( 0x01020304 , buffer );

    for ( auto i = 0; i < size( ss ); ++i )
        REQUIRE( nth_byte( ss , i ) == nth_byte( buffer , i ) );
}

TEST_CASE( "serialize_nt with std::streambuf&" )
{
    rbs::nt_stream ss;

    ss << 0x01020304;

    boost::asio::streambuf buffer;

    rbs::serialize_nt( 0x01020304 , buffer );

    for ( auto i = 0; i < size( ss ); ++i )
        REQUIRE( nth_byte( ss , i ) == nth_byte( buffer , i ) );
}

TEST_CASE( "serialize_be with std::ios&" )
{
    rbs::be_stream ss;

    ss << 0x01020304;

    boost::asio::streambuf buffer;

    std::ostream os { &buffer };

    rbs::serialize_be( 0x01020304 , os );

    for ( auto i = 0; i < size( ss ); ++i )
        REQUIRE( nth_byte( ss , i ) == nth_byte( buffer , i ) );
}

TEST_CASE( "serialize_le with std::ios&" )
{
    rbs::le_stream ss;

    ss << 0x01020304;

    boost::asio::streambuf buffer;

    std::ostream os { &buffer };

    rbs::serialize_le( 0x01020304 , os );

    for ( auto i = 0; i < size( ss ); ++i )
        REQUIRE( nth_byte( ss , i ) == nth_byte( buffer , i ) );
}

TEST_CASE( "serialize_nt with std::ios&" )
{
    rbs::nt_stream ss;

    ss << 0x01020304;

    boost::asio::streambuf buffer;

    std::ostream os { &buffer };

    rbs::serialize_nt( 0x01020304 , os );

    for ( auto i = 0; i < size( ss ); ++i )
        REQUIRE( nth_byte( ss , i ) == nth_byte( buffer , i ) );
}