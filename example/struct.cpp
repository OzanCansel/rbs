#include <iostream>
#include <rbs/stream.hpp>
#include "helper.hpp"

struct coordinate
{
    float x;
    float y;
    float z;
};

template<auto... Args>
inline rbs::stream<Args...>& operator<<( rbs::stream<Args...>& ss , const coordinate& coord )
{
    return ss << coord.x << coord.y << coord.z;
}

int main()
{
    rbs::be_stream bes;
    rbs::le_stream les;

    coordinate coord { 1.0f , 2.0f , 3.0f };

    bes << coord;
    les << coord;

    print( "little -> coordinate" , bes );
    print( "big    -> coordinate" , les );
}