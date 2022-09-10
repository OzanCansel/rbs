add_executable( stream-test stream-test.cpp helper.hpp catch.hpp )
target_link_libraries( stream-test rbs::rbs )

add_test( NAME stream-test COMMAND stream-test -s )

add_executable( aggregate-test aggregate-test.cpp helper.hpp catch.hpp )
target_link_libraries( aggregate-test rbs::rbs )

add_test( NAME aggregate-test COMMAND aggregate-test -s )