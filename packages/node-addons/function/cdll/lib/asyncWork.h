#include <stdlib.h>

// 异步工作结构体
typedef struct
{
  napi_deferred deferred;
  napi_async_work work;
  int result;
} AsyncWork;

