#include <iostream>

template <std::size_t number>
void print(){
    std::cout<<"any number except zero: "<<number<<std::endl;
}

template <>
void print<0ul>(){
    std::cout<< "zero here"<<std::endl;
}



int main()
{
    print<0>();
    print<1>();
    return 0;
}
