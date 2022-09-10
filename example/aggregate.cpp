#include <iostream>
#include <rbs/rbs.hpp>
#include "helper.hpp"

struct coordinate
{
    float x;
    float y;
    float z;
};

template<>
struct rbs::aggregate_serializable<coordinate> : std::true_type
{};

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