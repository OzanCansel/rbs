#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_ENABLE_BENCHMARKING

#include "catch.hpp"
#include <rbs/stream.hpp>

TEST_CASE( "stream-write" )
{
    BENCHMARK( "Serialize 1'000'000 float native" )
    {
        rbs::nt_stream ss;

        for ( auto i = 0; i < 1e6; ++i )
            ss << float( i );
    };

    BENCHMARK( "Serialize 1'000'000 short native" )
    {
        rbs::nt_stream ss;

        for ( auto i = 0; i < 1e6; ++i )
            ss << short( i );
    };

    BENCHMARK( "Serialize 1'000'000 char native" )
    {
        rbs::nt_stream ss;

        for ( auto i = 0; i < 1e6; ++i )
            ss << char( i );
    };

    BENCHMARK( "Serialize 1'000'000 float opposite endianness" )
    {
        if constexpr ( rbs::endian::big == rbs::endian::native )
        {
            rbs::le_stream ss;

            for ( auto i = 0; i < 1e6; ++i )
                ss << float( i );
        }
        else
        {
            rbs::be_stream ss;

            for ( auto i = 0; i < 1e6; ++i )
                ss << float( i );
        }
    };

    BENCHMARK( "Serialize 1'000'000 short opposite endianness" )
    {
        if constexpr ( rbs::endian::big == rbs::endian::native )
        {
            rbs::le_stream ss;

            for ( auto i = 0; i < 1e6; ++i )
                ss << short( i );
        }
        else
        {
            rbs::be_stream ss;

            for ( auto i = 0; i < 1e6; ++i )
                ss << short( i );
        }
    };
}