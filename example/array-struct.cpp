#include <iostream>
#include <rbs/rbs.hpp>
#include "helper.hpp"

struct foo
{
    short x;
    short y;
};

template<auto... Args>
inline rbs::stream<Args...>& operator<<( rbs::stream<Args...>& ss , const foo& x )
{
    return ss << x.x << x.y;
}

int main()
{
    rbs::be_stream bes;
    rbs::le_stream les;

    foo foos[]
    {
        { 0x01 , 0x02 } ,
        { 0x03 , 0x04 } ,
        { 0x05 , 0x06 } ,
        { 0x07 , 0x08 }
    };

    bes << foos;
    les << foos;

    print( "little -> foos" , bes );
    print( "big    -> foos" , les );
}