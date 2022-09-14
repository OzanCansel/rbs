#include <iostream>
#include <rbs/serialize_util.hpp>
#include "helper.hpp"

int main()
{
    boost::asio::streambuf buffer;

    rbs::serialize_be( 0x01020304 , buffer );
    rbs::serialize_le( 0x01020304 , buffer );
    rbs::serialize_nt( 0x01020304 , buffer );

    print( "beint|leint|ntint" , buffer );
}