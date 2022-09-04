#pragma once

#include <boost/asio/streambuf.hpp>
#include <ios>

namespace rbs
{

namespace impl
{
    template<bool Enabled>
    struct conditional_buffer
    {};

    template<>
    struct conditional_buffer<true>
    {
        using buffer  = boost::asio::streambuf;

        buffer&       buf()       { return m_strbuf; };
        const buffer& buf() const { return m_strbuf; };

        protected:

            buffer m_strbuf;
    };
}

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

template<endian E , bool OwnBuffer>
class stream : public impl::conditional_buffer<OwnBuffer>
{

public:

    inline stream();
    inline stream( std::streambuf& );
    inline stream( std::ios& );

    template<typename T>
    inline void write( const T& );

    template<typename T>
    inline void read( T& );

private:

    std::streambuf& m_buffer;
};

template<bool OwnBuffer>
struct be_stream : stream<endian::big , OwnBuffer>
{
    using stream<endian::big , OwnBuffer>::stream;
};

be_stream()                  -> be_stream<true>;
be_stream( std::streambuf& ) -> be_stream<false>;
be_stream( std::ios& )       -> be_stream<false>;

template<bool OwnBuffer>
struct le_stream : stream<endian::little , OwnBuffer>
{
    using stream<endian::little , OwnBuffer>::stream;
};

le_stream()                  -> le_stream<true>;
le_stream( std::streambuf& ) -> le_stream<false>;
le_stream( std::ios& )       -> le_stream<false>;

template<bool OwnBuffer>
struct nt_stream : stream<endian::native , OwnBuffer>
{
    using stream<endian::native , OwnBuffer>::stream;
};

nt_stream()                  -> nt_stream<true>;
nt_stream( std::streambuf& ) -> nt_stream<false>;
nt_stream( std::ios& )       -> nt_stream<false>;

}

#include "impl/stream_impl.hpp"