#include <assert.h>
#include <node_api.h>
#include <stdio.h>
#include <windows.h>
#include "op2p.h"

static napi_value Add(napi_env env, napi_callback_info info)
{
  napi_status status;

  size_t argc = 1;
  napi_value args[2];
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
    printf("Failed to load the DLL\n");
    return 1;
  }

  // Define the function pointer type
  typedef int (*CNewClientFunc)(char*);

  // Get the function address
  CNewClientFunc CNewClient = (CNewClientFunc)GetProcAddress(hLib, "CNewClient");
  if (CNewClient == NULL)
  {
    printf("Failed to get the function address\n");
    FreeLibrary(hLib);
    return 1;
  }

  char* value0;

  // Call the function

  // int res = CNewClient(value0);
  // printf("res: %d\n", res);


  // Free the DLL
  FreeLibrary(hLib);

  return value0;
}

#define DECLARE_NAPI_METHOD(name, func) \
  {name, 0, func, 0, 0, 0, napi_default, 0}

napi_value Init(napi_env env, napi_value exports)
{
  napi_status status;
  napi_property_descriptor addDescriptor = DECLARE_NAPI_METHOD("add", Add);
  status = napi_define_properties(env, exports, 1, &addDescriptor);
  assert(status == napi_ok);
  return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, Init)
