#include <gtest/gtest.h>
#include <iostream>

enum class CreateStrategy{ NEW, MALLOC, PROTOTYPE };

struct AnyStruct{
    int value = 1;
    AnyStruct(const AnyStruct& other):
        value { other.value }
    {}
    AnyStruct():
        value { 0 }
    {}
    AnyStruct(AnyStruct && other) = delete;
};

template <CreateStrategy>
struct Create;

template<>
struct Create<CreateStrategy::NEW>{
    template<class T, class... Args>
    static T* create(Args... args){
        return new T { args... };
    }
};

template<>
struct Create<CreateStrategy::MALLOC>{
    template<class T, class... Args>
    static T* create(Args... args){
        T* object = malloc(sizeof(T));
        return new (object) T { args... };
    }
};

template<>
struct Create<CreateStrategy::PROTOTYPE>{
    Create()
}



TEST(CLASS_PROVIDE_STRATEGY, choose_strategy)
{
   int *newInt = Create<CreateStrategy::NEW>::create<int>(1);
   int *mallocInt = Create<CreateStrategy::NEW>::create<int>(2);

   EXPECT_EQ(*newInt, 1);
   EXPECT_EQ(*mallocInt, 2);

   delete newInt;
   delete mallocInt;
}
