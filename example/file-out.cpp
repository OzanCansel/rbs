#include <fstream>
#include <rbs/stream.hpp>

struct coordinate
{
    int x;
    int y;
    int z;
};

template<auto... Args>
rbs::stream<Args...>& operator<<( rbs::stream<Args...>& ss , const coordinate& coord )
{
    return ss << coord.x << coord.y << coord.z;
}

int main()
{
    std::ofstream  of  { "coordinate.bin" };
    rbs::be_stream out { of };

    coordinate c { 1 , 2 , 3 };

    out << c;
}