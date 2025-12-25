#ifndef RESULT_H
#define RESULT_H

typedef enum {
    CS_SUCCESS = 0,
    CS_NULL_POINTER = 1,
    CS_ALLOCATION_FAILED = 2,
    CS_OUT_OF_BOUNDS = 3,
} CsResult;

#endif // RESULT_H
