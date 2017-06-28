#include <gtest/gtest.h>
#include <utility>
#include <iostream>

#include <strategy/create.hpp>
#include <strategy/delete.hpp>

#include <common/tools/unused.hpp>

template <class T>
T* prototype(const T value){
    T* result = reinterpret_cast<T*>(malloc(sizeof(T)));
    new (result) T { value };
    return result;
}

template <template <class T> class CreateStrategy>
struct CreaterInt:
        public CreateStrategy<int>{
    using Type = int;

    void switch_prototype(int* (*newPrototype)(int)){
        CreateStrategy<int>* currentStrategy = this;
        currentStrategy->setPrototype(newPrototype);
    }
};


TEST(CLASS_PROVIDE_STRATEGY, choose_strategy)
{
    int *newInt = CreaterInt<strategy::NewCreate>::create(1);
    int *mallocInt = CreaterInt<strategy::MallocCreate>::create(2);

    CreaterInt<strategy::PrototypCreate> creater;
    creater.setPrototype(prototype);
    int* byPrototype = creater.create(3);


    EXPECT_EQ(*newInt, 1);
    EXPECT_EQ(*mallocInt, 2);
    EXPECT_EQ(*byPrototype, 3);

    delete newInt;
    delete mallocInt;
    delete byPrototype;
}

TEST(CLASS, compile_only_use_prototype){
    CreaterInt<strategy::NewCreate> creater;
    common::unused(creater);

    CreaterInt<strategy::PrototypCreate> createrPrototype;
    createrPrototype.setPrototype(prototype);

    createrPrototype.switch_prototype(prototype);
}

