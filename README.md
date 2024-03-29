# rbs
`rbs` is raw binary serialization library. It doesn't append, prepend or insert any additional bytes. It just serializes/deserializes memory footprint of the types to/from `std::streambuf&` which you provide by its constructors. If nothing is provided it instantiates a standalone `boost::asio::streambuf` buffer and uses it. It is also __endian-aware__ so it can provide portability across different platforms.

- Header only library
- Usable with `find_package( rbs REQUIRED )` if it is installed to the system
- Needs C++17 or higher
- Only `Boost.Asio` and `Boost.Pfr` dependency

## Examples
All examples use `helper.hpp` to print bytes. Here its content is :
``` C++
#pragma once

#include <iostream>
#include <iomanip>
#include <string_view>
#include <boost/asio/buffers_iterator.hpp>
#include <rbs/stream.hpp>

inline void print( std::string_view prefix , rbs::stream<true>& ss )
{
    std::cout << prefix << " | ";

    for ( auto it  = buffers_begin( ss.buf().data() );
               it != buffers_end( ss.buf().data() );
               ++it )
        std::cout << std::setw( 2 )
                  << std::setfill( '0' )
                  << std::hex
                  << std::uint32_t( std::uint8_t( *it ) )
                  << ' ';

    std::cout << std::endl;
}
```

### Primitives Serialization
`rbs` is able to serialize [arithmetic types](https://en.cppreference.com/w/cpp/types/is_arithmetic) in regards to [byte order](https://en.cppreference.com/w/cpp/types/endian) of the `stream` class.

``` C++
#include <rbs/stream.hpp>
#include "helper.hpp"

int main()
{
    rbs::stream bes { rbs::endian::big };

    bes << char( 0x1F )
        << short( 0x0102 )
        << int( 0x01020304 )
        << float( 1234.56789f )
        << double( 123456789.123456789 );

    rbs::stream les { rbs::endian::little };

    les << char( 0x1F )
        << short( 0x0102 )
        << int( 0x01020304 )
        << float( 1234.56789f )
        << double( 123456789.123456789 );

    rbs::stream nts { rbs::endian::native };

    nts << char( 0x1F )
        << short( 0x0102 )
        << int( 0x01020304 )
        << float( 1234.56789f )
        << double( 123456789.123456789 );

    print( "big_endian   " , bes );
    print( "little_endian" , les );
    print( "native       " , nts );
}
```
Output :
```console
big_endian    | 1f 01 02 01 02 03 04 44 9a 52 2c 41 9d 6f 34 54 7e 6b 75 
little_endian | 1f 02 01 04 03 02 01 2c 52 9a 44 75 6b 7e 54 34 6f 9d 41 
native        | 1f 02 01 04 03 02 01 2c 52 9a 44 75 6b 7e 54 34 6f 9d 41
```

### Struct Serialization
`rbs` provides a convenient mechanism to serialize/deserialize a struct by overlading `operator<<`, `operator>>` operators.

``` C++
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
    rbs::stream bes { rbs::endian::big    };
    rbs::stream les { rbs::endian::little };

    coordinate coord { 1.0f , 2.0f , 3.0f };

    bes << coord;
    les << coord;

    print( "little -> coordinate" , bes );
    print( "big    -> coordinate" , les );
}
```
Output :
``` console
little -> coordinate | 3f 80 00 00 40 00 00 00 40 40 00 00
big    -> coordinate | 00 00 80 3f 00 00 00 40 00 00 40 40
```

### Aggregate Serialization
`rbs` provides a convenient mechanism to serialize/deserialize an aggregate type automatically. Member of aggregate types will be serialized/deserialized in order they are declared.

``` C++
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
    rbs::stream bes { rbs::endian::big    };
    rbs::stream les { rbs::endian::little };

    coordinate coord { 1.0f , 2.0f , 3.0f };

    bes << coord;
    les << coord;

    print( "little -> coordinate" , bes );
    print( "big    -> coordinate" , les );
}
```
Output :
``` console
little -> coordinate | 3f 80 00 00 40 00 00 00 40 40 00 00 
big    -> coordinate | 00 00 80 3f 00 00 00 40 00 00 40 40
```

### Scoped Enum Serialization
`rbs` is able to serialize [scoped enums](https://en.cppreference.com/w/cpp/language/enum#Scoped_enumerations) in regards to its [underlying_type](https://en.cppreference.com/w/cpp/types/underlying_type).

``` C++
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

    rbs::stream les { rbs::endian::little };

    les << my_pc;

    print( "computer -> little" , les );
}
```
Output :
```console
computer -> little | 0b 14 00 1e 00 00 00 
```

### File Output Example
`rbs` is able to work with standard streams such as [std::ofstream](https://en.cppreference.com/w/cpp/io/basic_ofstream). This example writes serialized `coordinate` object to the `coordinate.bin` file.

``` C++
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
    rbs::stream out { of , rbs::endian::big };

    coordinate c { 1 , 2 , 3 };

    out << c;
}
```
Output :
``` sh
# cat coordinate.bin | hexdump -C
00000000  00 00 00 01 00 00 00 02  00 00 00 03              |............|
```

### Primitive Array Serialization
`rbs` provides built-in mechanism to serialize/deserialize an array which holds primitive types.

``` C++
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
```
Output :
``` console
little -> numbers | 01 02 03 04 05 06 07 08 
big    -> numbers | 02 01 04 03 06 05 08 07
```

### User Defined Type Array Serialization
`rbs` provides built-in mechanism to serialize/deserialize an array which holds user defined types.

``` C++
#include <iostream>
#include <rbs/rbs.hpp>
#include "helper.hpp"

struct foo
{
    short x;
    short y;
};

template<>
struct rbs::aggregate_serializable<foo> : std::true_type
{};

int main()
{
    rbs::stream bes { rbs::endian::big    };
    rbs::stream les { rbs::endian::little };

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
```
Output :
``` console
little -> foos | 00 01 00 02 00 03 00 04 00 05 00 06 00 07 00 08
big    -> foos | 01 00 02 00 03 00 04 00 05 00 06 00 07 00 08 00
```

### Serialize Util Function
`rbs` provides `serialize_be`, `serialize_le`, `serialize_nt` functions for less verbose code snippets.

``` C++
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
```
Output :
``` console
beint|leint|ntint | 01 02 03 04 04 03 02 01 04 03 02 01
```

## How to use ?
### Option 1. Install to the system
- Install `rbs` as system-wide.
```bash
cd $(mktemp -d)
git clone https://github.com/OzanCansel/rbs.git
cd rbs
mkdir build && cd build
cmake ..
sudo cmake --build . --target install -- -j$(nproc)
```

#### Option 1.1.
- Include `rbs` to your cmake project with `find_package( rbs )`
``` cmake
cmake_minimum_required( VERSION 3.10 )
project( my_project )

# Allows you to use rbs
find_package( rbs REQUIRED )

add_executable( my_binary main.cpp )

target_link_libraries( my_binary PRIVATE rbs::rbs )
```

#### Option 1.2.
- It is not obliged to be included by a cmake project. `rbs` is header only so it will be visible after it is installed to the system. So just include it and make sure that you enabled C++17 standard.

### Option 2. Add as a subdirectory
- Add as an subdirectory to your existing cmake project.

```bash
cd already_existing_project
git clone https://github.com/OzanCansel/rbs.git
```
``` cmake
cmake_minimum_required( VERSION 3.10 )
project( already_existing_project )

# Allows you to use rbs
add_subdirectory( rbs EXCLUDE_FROM_ALL )

add_executable( my_binary main.cpp )

target_link_libraries( my_binary PRIVATE rbs::rbs )
```

# LICENSE
[MIT](https://raw.githubusercontent.com/OzanCansel/rbs/master/LICENSE)
