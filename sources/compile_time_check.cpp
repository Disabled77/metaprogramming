#include <gtest/gtest.h>


template <bool noError>
struct CompileTimeError;

template <>
struct CompileTimeError<true>{
    CompileTimeError(...){}
};

#define HAND_MADE_STATIC_CAST(expr, msg){\
    class ERROR_##msg{};\
    void(CompileTimeError<expr != 0>(ERROR_##msg()));\
    }

#define HAND_MADE_STATIC_CAST2(expr, msg){\
    CompileTimeError<expr!=0>(error_message_##msg);\
    }


TEST(COMPILE_TIME_CHECK, simple_check)
{
    HAND_MADE_STATIC_CAST(true, first_check);
    HAND_MADE_STATIC_CAST2(true, second_check);
}



