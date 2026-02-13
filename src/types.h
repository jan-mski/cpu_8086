#pragma once

#define REPEAT_2(x) \
    x, x
#define REPEAT_4(x) \
    REPEAT_2(x), REPEAT_2(x)
#define REPEAT_6(x) \
    REPEAT_4(x), REPEAT_2(x)
#define REPEAT_8(x) \
    REPEAT_6(x), REPEAT_2(x)
#define REPEAT_12(x) \
    REPEAT_6(x), REPEAT_6(x)
#define REPEAT_16(x) \
    REPEAT_12(x), REPEAT_4(x)
#define REPEAT_20(x) \
    REPEAT_16(x), REPEAT_4(x)
#define REPEAT_56(x) \
    REPEAT_20(x), REPEAT_20(x), REPEAT_16(x)
#define REPEAT_136(x) \
    REPEAT_56(x), REPEAT_56(x), REPEAT_20(x), REPEAT_4(x)

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef int int32_t;
