#include <gtest/gtest.h>

#include <common/tools.hpp>

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


TEST(PARTICAL_CLASS_SPECIALISATION, dont_build_functions_which_doesnt_use)
{

    NiftyContainer<int, false> problem3;
    problem3.doSomething();

    NiftyContainer<int, true> problem2;
    common::unused(problem2);
}

template <class T, bool isPolymorphic>
struct ObjectType;

template <class T>
struct ObjectType<T, true>{
    static constexpr T* value = nullptr;
};

template <class T>
struct ObjectType<T, false>{
    static constexpr T value{};
};

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

TEST(PARTICAL_CLASS_SPECIALISATION, selector)
{
    ObjectType<int, true> objectKeeper1{};
    ObjectType<int, false> objectKeeper2{};
    std::cout<<common::getPrettyTypeName(objectKeeper1.value)<<std::endl;
    std::cout<<common::getPrettyTypeName(objectKeeper2.value)<<std::endl;

    Selector<int, int*, true> selector1{};
    Selector<int, int*, false> selector2{};
    std::cout<<common::getPrettyTypeName(selector1.value)<<std::endl;
    std::cout<<common::getPrettyTypeName(selector2.value)<<std::endl;
}
