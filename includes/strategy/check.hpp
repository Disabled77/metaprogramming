#pragma once

#include <iostream>
namespace strategy {

struct ReintrpretCastCheck{

    template <class StartType, class FinalType>
    static bool check(StartType start, FinalType final){
        static_assert(sizeof(start) <= sizeof(final), "final type can't be less then start type");

        return true;
    }

};

} // namespace strategy

