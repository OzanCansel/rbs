#include "rbs/serialize_util.hpp"

namespace rbs
{

template<typename T>
void serialize_be( const T& val , std::streambuf& buffer )
{
    be_stream bes { buffer };

    bes << val;
}

template<typename T>
void serialize_be( const T& val , std::ios& buffer )
{
    be_stream bes { buffer };

    bes << val;
}

template<typename T>
void serialize_le( const T& val , std::streambuf& buffer )
{
    le_stream les { buffer };

    les << val;
}

template<typename T>
void serialize_le( const T& val , std::ios& buffer )
{
    le_stream les { buffer };

    les << val;
}

template<typename T>
void serialize_nt( const T& val , std::streambuf& buffer )
{
    nt_stream nts { buffer };

    nts << val;
}

template<typename T>
void serialize_nt( const T& val , std::ios& buffer )
{
    nt_stream nts { buffer };

    nts << val;
}

}