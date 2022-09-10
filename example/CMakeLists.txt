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

add_executable( enum enum.cpp helper.hpp )

target_link_libraries(
    enum

    PRIVATE

        rbs::rbs
)

add_executable( file-out file-out.cpp )

target_link_libraries(
    file-out

    PRIVATE

        rbs::rbs
)

add_executable( aggregate aggregate.cpp )

target_link_libraries(
    aggregate

    PRIVATE

        rbs::rbs
)