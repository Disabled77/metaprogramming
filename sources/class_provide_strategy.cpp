#include <gtest/gtest.h>
#include <utility>
#include <iostream>

template<class T>
struct NewCreate{
    template<class... Args>
    static T* create(Args... args){
        return new T { args... };
    }
};

template<class T>
struct MallocCreate{
    template<class... Args>
    static T* create(Args... args){
        T* object = reinterpret_cast<T*>(malloc(sizeof(T)));
        new (object) T { args... };
        return object;
    }
};

template<class T>
struct PrototypCreate{
    PrototypCreate(T* (functionPrototype)(T) = nullptr):
        functionPrototype_ { functionPrototype }
    {}

    void setPrototype(T* (functionPrototype)(T)){
        functionPrototype_ = functionPrototype;
    }

    T* getPrototype() const {
        return functionPrototype_;
    }

    template<class... Args>
    T* create(T value) const {
        T* variable = functionPrototype_(value);
        return variable;
    }

    T* (*functionPrototype_)(T);
};

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
};


TEST(CLASS_PROVIDE_STRATEGY, choose_strategy)
{
    int *newInt = CreaterInt<NewCreate>::create(1);
    int *mallocInt = CreaterInt<MallocCreate>::create(2);

    CreaterInt<PrototypCreate> creater;
    creater.setPrototype(prototype);
    int* byPrototype = creater.create(3);


    EXPECT_EQ(*newInt, 1);
    EXPECT_EQ(*mallocInt, 2);
    EXPECT_EQ(*byPrototype, 3);

    delete newInt;
    delete mallocInt;
    delete byPrototype;
}

TEST(CONVERT, convert_one_class_to_completely_different){
    CreaterInt<NewCreate> classCreator;
    NewCreate<int>* strategyCreator = &classCreator;
    delete(strategyCreator);
    //undefined behaviour!!!
}
