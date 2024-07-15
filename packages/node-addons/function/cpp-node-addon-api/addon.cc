#include <napi.h>
#include <windows.h>
#include <stdio.h>
#include "op2p.h"

// Function to load DLL and call CNewClient
Napi::Value LoadAndCallDLL(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  // Load the DLL
  HMODULE hLib = LoadLibrary("./lib/op2p.dll");
  if (hLib == NULL) {
    Napi::Error::New(env, "Failed to load the DLL").ThrowAsJavaScriptException();
    return env.Null();
  }

  // Define the function pointer type
  typedef int (*CNewClientFunc)(char*);

  // Get the function address
  CNewClientFunc CNewClient = (CNewClientFunc)GetProcAddress(hLib, "CNewClient");
  if (CNewClient == NULL) {
    Napi::Error::New(env, "Failed to get the function address").ThrowAsJavaScriptException();
    FreeLibrary(hLib);
    return env.Null();
  }

  // Call the function
  int res = CNewClient("ss");

  // Free the DLL
  FreeLibrary(hLib);

  // Return the result
  return Napi::Number::New(env, res);
}

// Initialize the module
Napi::Object Init(Napi::Env env, Napi::Object exports) {
  exports.Set(Napi::String::New(env, "loadAndCallDLL"), Napi::Function::New(env, LoadAndCallDLL));
  return exports;
}

NODE_API_MODULE(addon, Init)