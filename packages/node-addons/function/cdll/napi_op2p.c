#include <assert.h>
#include <node_api.h>
#include <stdio.h>
#include <windows.h>
#include "./lib/op2p.h"
#include "./lib/asyncWork.h"

static napi_value NewClient(napi_env env, napi_callback_info info)
{
  napi_status status;

  size_t argc = 1;
  napi_value args[1];
  status = napi_get_cb_info(env, info, &argc, args, NULL, NULL);
  assert(status == napi_ok);

  if (argc < 1)
  {
    napi_throw_type_error(env, NULL, "Wrong number of arguments");
    return NULL;
  }

  // start
  // Load the DLL : HANDLE 代表句柄
  HMODULE hLib = LoadLibrary("./lib/op2p.dll");
  if (hLib == NULL)
  {
    napi_throw_error(env, NULL, "Failed to load the DLL");
    return NULL;
  }

  napi_valuetype valuetype0;
  status = napi_typeof(env, args[0], &valuetype0);
  assert(status == napi_ok);

  if (valuetype0 != napi_string)
  {
    napi_throw_type_error(env, NULL, "Wrong arguments");
    return NULL;
  }

  // Convert the argument to a C string
  size_t str_size;
  size_t str_size_read;
  status = napi_get_value_string_utf8(env, args[0], NULL, 0, &str_size);
  assert(status == napi_ok);

  char *clientConfig = (char *)malloc(str_size + 1);
  status = napi_get_value_string_utf8(env, args[0], clientConfig, str_size + 1, &str_size_read);
  assert(status == napi_ok);

  // Define the function pointer type
  typedef int (*CNewClientFunc)(char *);

  CNewClientFunc CNewClient = (CNewClientFunc)GetProcAddress(hLib, "CNewClient");
  if (CNewClient == NULL)
  {
    napi_throw_error(env, NULL, "Failed to get the function address");
    FreeLibrary(hLib);
    return NULL;
  }

  int res = CNewClient(clientConfig);

  typedef int (*CStartFunc)(int);
  CStartFunc CStart = (CStartFunc)GetProcAddress(hLib, "CStart");
  int sd = CStart(res);

  // Sleep(100000000);

  // FreeLibrary(hLib);
  napi_value result;
  status = napi_create_promise(env, 1, &result);

  return result;
}

// 异步执行函数
void Execute(napi_env env, void *data)
{
  AsyncWork *asyncWork = (AsyncWork *)data;
  // 模拟异步操作，例如计算或 I/O 操作
  asyncWork->result = 42; // 假设异步操作的结果是 42
}

// 异步完成回调函数
void Complete(napi_env env, napi_status status, void *data)
{
  AsyncWork *asyncWork = (AsyncWork *)data;

  napi_value result;
  napi_status create_status = napi_create_int32(env, asyncWork->result, &result);
  assert(create_status == napi_ok);

  // 解决 Promise
  napi_status resolve_status = napi_resolve_deferred(env, asyncWork->deferred, result);
  assert(resolve_status == napi_ok);

  // 清理工作
  napi_delete_async_work(env, asyncWork->work);
  free(asyncWork);
}

// 创建 Promise 的函数
static napi_value CreatePromise(napi_env env, napi_callback_info info)
{
  napi_status status;

  napi_deferred deferred;
  napi_value promise;

  // 创建 Promise
  status = napi_create_promise(env, &deferred, &promise);
  assert(status == napi_ok);

  // 分配异步工作结构体
  AsyncWork *asyncWork = (AsyncWork *)malloc(sizeof(AsyncWork));
  asyncWork->deferred = deferred;

  // 创建异步工作
  napi_value resource_name;
  status = napi_create_string_utf8(env, "AsyncWork", NAPI_AUTO_LENGTH, &resource_name);
  assert(status == napi_ok);

  status = napi_create_async_work(env, NULL, resource_name, Execute, Complete, asyncWork, &asyncWork->work);
  assert(status == napi_ok);

  // 队列异步工作
  status = napi_queue_async_work(env, asyncWork->work);
  assert(status == napi_ok);

  return promise;
}

static napi_value Add(napi_env env, napi_callback_info info)
{
  napi_status status;

  size_t argc = 2;
  napi_value args[2];
  status = napi_get_cb_info(env, info, &argc, args, NULL, NULL);
  assert(status == napi_ok);

  if (argc < 2)
  {
    napi_throw_type_error(env, NULL, "Wrong number of arguments");
    return NULL;
  }

  napi_valuetype valuetype0;
  status = napi_typeof(env, args[0], &valuetype0);
  assert(status == napi_ok);

  napi_valuetype valuetype1;
  status = napi_typeof(env, args[1], &valuetype1);
  assert(status == napi_ok);

  if (valuetype0 != napi_number || valuetype1 != napi_number)
  {
    napi_throw_type_error(env, NULL, "Wrong arguments");
    return NULL;
  }

  napi_create_string_utf8()

  double value0;
  status = napi_get_value_double(env, args[0], &value0);
  assert(status == napi_ok);

  double value1;
  status = napi_get_value_double(env, args[1], &value1);
  assert(status == napi_ok);

  napi_value sum;
  status = napi_create_double(env, value0 + value1, &sum);
  assert(status == napi_ok);

  return sum;
}

#define DECLARE_NAPI_METHOD(name, func) \
  {name, 0, func, 0, 0, 0, napi_default, 0}

napi_value Init(napi_env env, napi_value exports)
{
  napi_status status;
  napi_property_descriptor descriptors[] = {
      DECLARE_NAPI_METHOD("NewClient", NewClient),
      DECLARE_NAPI_METHOD("CreatePromise", CreatePromise),
      DECLARE_NAPI_METHOD("Add", Add)};
  status = napi_define_properties(env, exports, sizeof(descriptors) / sizeof(descriptors[0]), descriptors);
  assert(status == napi_ok);
  return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, Init)
