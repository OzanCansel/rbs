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

if( ${BOOST_PFR_EXISTS} )

    add_executable( aggregate aggregate.cpp )

    target_link_libraries(
        aggregate

        PRIVATE

            rbs::rbs
    )

endif()

add_executable( array-primitive array-primitive.cpp )

target_link_libraries(
    array-primitive

    PRIVATE

        rbs::rbs
)

add_executable( array-struct array-struct.cpp )

target_link_libraries(
    array-struct

    PRIVATE

        rbs::rbs
)

add_executable( serialize-util serialize-util.cpp )

target_link_libraries(
    serialize-util

    PRIVATE

        rbs::rbs
)