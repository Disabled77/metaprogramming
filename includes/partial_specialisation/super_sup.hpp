#pragma once

namespace partial_specialisation {

template <class T, class U>
struct SameChecker{
    static constexpr bool value = false;
};

template <class T>
struct SameChecker<T, T>{
    static constexpr bool value = true;
};

template <class Super, class Sub>
class SuperSub{
public:
    using True = char;
    class False { char dummy[2];};

    static True Test(const Sub&);
    static False Test(...);

    static Super Maket();
    enum Condition { NotConnection = 0, FirstChildOfSecond = 1, TheSame = 3  };

    static constexpr bool firstChildOfSecond = sizeof(Test(Maket())) == sizeof(Sub) ? true: false;
    static constexpr bool isSame = SameChecker<Super, Sub>::value;

    static constexpr Condition condition = static_cast<Condition>(firstChildOfSecond + isSame);
};

} // namespace partial_specialisation
