#pragma once

#include "rbs/stream.hpp"

namespace rbs
{

template<typename T>
inline void serialize_be( const T& val , std::streambuf& );

template<typename T>
inline void serialize_be( const T& val , std::ios& );

template<typename T>
inline void serialize_le( const T& val , std::streambuf& );

template<typename T>
inline void serialize_le( const T& val , std::ios& );

template<typename T>
inline void serialize_nt( const T& val , std::streambuf& );

template<typename T>
inline void serialize_nt( const T& val , std::ios& );

}

#include "rbs/impl/serialize_util_impl.hpp"