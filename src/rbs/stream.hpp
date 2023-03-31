#pragma once

#include <boost/asio/streambuf.hpp>
#include <ios>
#include <cstdint>

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

        buffer&       buf()       { return m_buf; };
        const buffer& buf() const { return m_buf; };

    protected:

        buffer m_buf;
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

template<bool OwnBuffer>
class stream : public impl::conditional_buffer<OwnBuffer>
{
public:

    stream( endian = endian::big );
    stream( std::streambuf& , endian = endian::big );
    stream( std::ios& , endian = endian::big );

    template<typename T>
    void write( const T& );

    template<typename T>
    void write( const T* , std::size_t num_of_elems );

    template<typename T>
    void read( T& );

    template<typename T>
    void read( T* , std::size_t num_of_elems );

    endian byte_order() const;
    void byte_order( endian );

private:

    endian m_endian;
    std::streambuf& m_buffer;
};

stream( endian )                   -> stream<true>;
stream( std::streambuf& , endian ) -> stream<false>;
stream( std::ios& , endian )       -> stream<false>;

}

#include "impl/stream_impl.hpp"