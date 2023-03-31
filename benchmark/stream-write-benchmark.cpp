#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_ENABLE_BENCHMARKING

#include "catch.hpp"
#include <rbs/stream.hpp>

TEST_CASE( "stream-write" )
{
    std::vector<short> floats( 1e6 );
    std::vector<short> shorts( 1e6 );
    std::vector<char>  chars( 1e6 );

    BENCHMARK( "Serialize 1'000'000 float native" )
    {
        rbs::stream ss { rbs::endian::native };

        for ( auto i = 0; i < 1e6; ++i )
            ss << float( i );
    };

    BENCHMARK( "Serialize 1'000'000 floats native as bulk" )
    {
        rbs::stream ss { rbs::endian::native };

        ss.write( data( floats ) , size( floats ) );
    };

    BENCHMARK( "Serialize 1'000'000 short native" )
    {
        rbs::stream ss { rbs::endian::native };

        for ( auto i = 0; i < 1e6; ++i )
            ss << short( i );
    };

    BENCHMARK( "Serialize 1'000'000 shorts native as bulk" )
    {
        rbs::stream ss { rbs::endian::native };

        ss.write( data( shorts ) , size( shorts ) );
    };

    BENCHMARK( "Serialize 1'000'000 char native" )
    {
        rbs::stream ss { rbs::endian::native };

        for ( auto i = 0; i < 1e6; ++i )
            ss << char( i );
    };

    BENCHMARK( "Serialize 1'000'000 chars native as bulk" )
    {
        rbs::stream ss { rbs::endian::native };

        ss.write( data( chars ) , size( chars ) );
    };

    BENCHMARK( "Serialize 1'000'000 float opposite endianness" )
    {
        if constexpr ( rbs::endian::big == rbs::endian::native )
        {
            rbs::stream ss { rbs::endian::little };

            for ( auto i = 0; i < 1e6; ++i )
                ss << float( i );
        }
        else
        {
            rbs::stream ss { rbs::endian::big };

            for ( auto i = 0; i < 1e6; ++i )
                ss << float( i );
        }
    };

    BENCHMARK( "Serialize 1'000'000 float opposite endianness as bulk" )
    {
        if constexpr ( rbs::endian::big == rbs::endian::native )
        {
            rbs::stream ss { rbs::endian::little };

            ss.write( data( floats ) , size( floats ) );
        }
        else
        {
            rbs::stream ss { rbs::endian::big };

            ss.write( data( floats ) , size( floats ) );
        }
    };

    BENCHMARK( "Serialize 1'000'000 short opposite endianness" )
    {
        if constexpr ( rbs::endian::big == rbs::endian::native )
        {
            rbs::stream ss { rbs::endian::little };

            for ( auto i = 0; i < 1e6; ++i )
                ss << short( i );
        }
        else
        {
            rbs::stream ss { rbs::endian::big };

            for ( auto i = 0; i < 1e6; ++i )
                ss << short( i );
        }
    };

    BENCHMARK( "Serialize 1'000'000 short opposite endianness as bulk" )
    {
        if constexpr ( rbs::endian::big == rbs::endian::native )
        {
            rbs::stream ss { rbs::endian::little };

            ss.write( data( shorts ) , size( shorts ) );
        }
        else
        {
            rbs::stream ss { rbs::endian::big };

            ss.write( data( shorts ) , size( shorts ) );
        }
    };
}