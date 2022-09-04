add_executable( primitives primitives.cpp )

target_link_libraries(
    primitives

    PRIVATE

        rbs::rbs
)