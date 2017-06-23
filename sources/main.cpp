#include <iostream>
#include <gtest/gtest.h>

template <std::size_t number>
void print(){
    std::cout<<"any number except zero: "<<number<<std::endl;
}

template <>
void print<0ul>(){
    std::cout<< "zero here"<<std::endl;
}



int main(int argc, char **argv){

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

//TEST(MAIN, general)
//{
//   std::cout<<"hello world"<<std::endl;
//}
