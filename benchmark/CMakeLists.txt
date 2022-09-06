add_executable( stream-write-benchmark stream-write-benchmark.cpp catch.hpp )

target_link_libraries(
    stream-write-benchmark

    PUBLIC

        rbs::rbs
)