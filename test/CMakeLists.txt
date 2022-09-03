add_executable( stream-test stream-test.cpp helper.hpp catch.hpp )
target_link_libraries( stream-test rbs::rbs )

add_test( NAME stream-test COMMAND stream-test -s )