#pragma once

namespace common {

template <typename... Args>
__attribute__ ((__always_inline__))
inline void unused(Args&&...)
{}

} // namespace common
