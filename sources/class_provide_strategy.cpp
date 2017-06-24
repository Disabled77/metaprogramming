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
struct Creater{
    using Type = int;
    template <class... Args>
    static Type* create(Args... args){
        return CreateStrategy<Type>::create(args...);
    }
};

template <>
struct Creater<PrototypCreate>{
    using Type = int;
    using PrototypeCreateStrategy = PrototypCreate<Type>;
    using Prototype = decltype(std::declval<PrototypCreate<Type>>().functionPrototype_);

    Creater(Prototype functionPrototype):
        prototypeCreator_(functionPrototype)
    {}

    template <class... Args>
    Type* create(Args... args){
        return prototypeCreator_.create(args...);
    }
    PrototypeCreateStrategy prototypeCreator_;
};



TEST(CLASS_PROVIDE_STRATEGY, choose_strategy)
{
   int *newInt = Creater<NewCreate>::create(1);
   int *mallocInt = Creater<MallocCreate>::create(2);

   Creater<PrototypCreate> creater(prototype);
   int* byPrototype = creater.create(3);


   EXPECT_EQ(*newInt, 1);
   EXPECT_EQ(*mallocInt, 2);
   EXPECT_EQ(*byPrototype, 3);

   delete newInt;
   delete mallocInt;
}
