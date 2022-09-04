#include <rbs/stream.hpp>
#include "helper.hpp"

enum class architecture : std::uint8_t
{
    x86   = 10 ,
    amd64
};

enum class operating_system : std::uint16_t
{
    gnu_linux = 20 ,
    mac ,
    win
};

enum class byte_order
{
    little = 30 ,
    big
};

struct computer
{
    architecture     arch;
    operating_system sys;
    byte_order       endianness;
};

template<auto... Args>
inline rbs::stream<Args...>& operator<<( rbs::stream<Args...>& ss , const computer& comp )
{
    return ss << comp.arch << comp.sys << comp.endianness;
}

int main()
{
    computer my_pc
    {
        architecture::amd64 ,
        operating_system::gnu_linux ,
        byte_order::little
    };

    rbs::le_stream les;

    les << my_pc;

    print( "computer -> little" , les );
}