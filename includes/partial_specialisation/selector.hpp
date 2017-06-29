#pragma once

namespace partial_specialisation {

template <class FirstType, class SecondType, bool chooseFirst>
struct Selector;

template <class FirstType, class SecondType>
struct Selector<FirstType, SecondType, true>{
    static constexpr FirstType value{};
};

template <class FirstType, class SecondType>
struct Selector<FirstType, SecondType, false>{
    static constexpr SecondType value{};
};

} // namespace partial_specialisation
