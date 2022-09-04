add_executable( primitives primitives.cpp helper.hpp )

target_link_libraries(
    primitives

    PRIVATE

        rbs::rbs
)

add_executable( struct struct.cpp helper.hpp )

target_link_libraries(
    struct

    PRIVATE

        rbs::rbs
)