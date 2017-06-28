#pragma once
namespace strategy {

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


    template<class... Args>
    T* create(T value) const {
        T* variable = functionPrototype_(value);
        return variable;
    }

    T* (*functionPrototype_)(T);
};

} // namespace strategy

