#pragma once

#include <optional>
#include <boost/asio/streambuf.hpp>

namespace rbs
{

enum class endian
{
#ifdef _WIN32
    little = 0,
    big    = 1,
    native = little
#else
    little = __ORDER_LITTLE_ENDIAN__,
    big    = __ORDER_BIG_ENDIAN__,
    native = __BYTE_ORDER__
#endif
};

template<endian E>
class stream
{

public:

    using buffer  = boost::asio::streambuf;
    using opt_buf = std::optional<buffer>;

    inline stream();
    inline stream( buffer& );

    template<typename T>
    inline void write( const T& );

    template<typename T>
    inline void read( T& );

    inline buffer& buf();
    inline const buffer& buf() const;

private:

    opt_buf m_opt_buf;
    buffer& m_buffer;
};

using be_stream = stream<endian::big>;
using le_stream = stream<endian::little>;
using nt_stream = stream<endian::native>;

}

#include "impl/stream_impl.hpp"