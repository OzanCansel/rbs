#include <iostream>
#include <rbs/rbs.hpp>
#include "helper.hpp"

int main()
{
    rbs::be_stream bes;
    rbs::le_stream les;

    short numbers[] { 0x0102 , 0x0304 , 0x0506 , 0x0708 };

    bes << numbers;
    les << numbers;

    print( "little -> numbers" , bes );
    print( "big    -> numbers" , les );
}