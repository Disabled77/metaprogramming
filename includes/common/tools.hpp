#pragma once

#include <boost/type_index.hpp>

namespace common {

template <typename... Args>
__attribute__ ((__always_inline__))
inline void unused(Args&&...)
{}

template <class T>
auto getPrettyTypeName(T value){
    return boost::typeindex::type_id_with_cvr<decltype(value)>().pretty_name();
}

} // namespace common
