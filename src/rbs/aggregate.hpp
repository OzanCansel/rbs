#pragma once

#include <type_traits>
#include <boost/pfr.hpp>
#include "rbs/stream.hpp"

namespace rbs
{

namespace impl
{

template<typename T , std::size_t... Idx , auto... Args>
inline void aggregate_serialize(
    stream<Args...>& ss ,
    const T& value ,
    std::index_sequence<Idx...>
)
{
    ( operator<<( ss , boost::pfr::get<Idx>( value ) ) , ... );
}

template<typename T , std::size_t... Idx , auto... Args>
inline void aggregate_deserialize(
    stream<Args...>& ss ,
    T& value ,
    std::index_sequence<Idx...>
)
{
    ( operator>>( ss , boost::pfr::get<Idx>( value ) ) , ... );
}

}

template<typename T>
struct aggregate_serializable : std::false_type
{};

template<typename T>
static constexpr bool aggregate_serializable_v = aggregate_serializable<T>::value;

template<typename T , auto... Args>
inline
std::enable_if_t<aggregate_serializable_v<T> , stream<Args...>&>
operator<<( stream<Args...>& ss , const T& aggr )
{
    static_assert(
        std::is_aggregate_v<T> ,
        "T should be an aggregate type."
    );

    constexpr int n_elems = boost::pfr::tuple_size<T>::value;

    impl::aggregate_serialize(
        ss ,
        aggr ,
        std::make_index_sequence<n_elems>()
    );

    return ss;
}

template<typename T , auto... Args>
inline
std::enable_if_t<aggregate_serializable_v<T> , stream<Args...>&>
operator>>( stream<Args...>& ss , T& aggr )
{
    static_assert(
        std::is_aggregate_v<T> ,
        "T should be an aggregate type."
    );

    constexpr int n_elems = boost::pfr::tuple_size<T>::value;

    impl::aggregate_deserialize(
        ss ,
        aggr ,
        std::make_index_sequence<n_elems>()
    );

    return ss;
}

}