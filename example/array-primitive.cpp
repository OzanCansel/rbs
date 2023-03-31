#include <iostream>
#include <rbs/rbs.hpp>
#include "helper.hpp"

int main()
{
    rbs::stream bes { rbs::endian::big    };
    rbs::stream les { rbs::endian::little };

    short numbers[] { 0x0102 , 0x0304 , 0x0506 , 0x0708 };

    bes << numbers;
    les << numbers;

    print( "little -> numbers" , bes );
    print( "big    -> numbers" , les );
}