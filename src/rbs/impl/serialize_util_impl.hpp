#include "rbs/serialize_util.hpp"

namespace rbs
{

template<typename T>
void serialize_be( const T& val , std::streambuf& buffer )
{
    stream bes { buffer , rbs::endian::big };

    bes << val;
}

template<typename T>
void serialize_be( const T& val , std::ios& buffer )
{
    stream bes { buffer , rbs::endian::big };

    bes << val;
}

template<typename T>
void serialize_le( const T& val , std::streambuf& buffer )
{
    stream les { buffer , rbs::endian::little };

    les << val;
}

template<typename T>
void serialize_le( const T& val , std::ios& buffer )
{
    stream les { buffer , rbs::endian::little };

    les << val;
}

template<typename T>
void serialize_nt( const T& val , std::streambuf& buffer )
{
    stream nts { buffer , rbs::endian::native };

    nts << val;
}

template<typename T>
void serialize_nt( const T& val , std::ios& buffer )
{
    stream nts { buffer , rbs::endian::native };

    nts << val;
}

}