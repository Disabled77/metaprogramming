#include <gtest/gtest.h>

#include <common/tools/unused.hpp>

template <bool isPolymorphic>
struct PolymorphicCondtition;

template <>
struct PolymorphicCondtition<true>{
    static constexpr bool polymorph = true;
};

template <>
struct PolymorphicCondtition<false>{
    static constexpr bool polymorph = false;
};

template <class T, bool isPolymorphic>
struct NiftyContainer {

    void doSomething(){
        doSomethingImpl(PolymorphicCondtition<isPolymorphic>{});
    }

private:
    void doSomethingImpl(PolymorphicCondtition<true>){
        this->some_function_which_didnt_ever_exist();
        std::cout<<"polymorphic actions"<<std::endl;
    }
    void doSomethingImpl(PolymorphicCondtition<false>){
       std::cout<<"non polymorphic actions"<<std::endl;
    }

};


TEST(PARTICAL_CLASS_SPECIALISATION, simple_check)
{

    NiftyContainer<int, false> problem3;
    problem3.doSomething();

    NiftyContainer<int, true> problem2;
    common::unused(problem2);
}



