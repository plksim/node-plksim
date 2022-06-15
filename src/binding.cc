#include <napi.h>

#include <plksim/version.hh>

#include "samples.hh"

using namespace Napi;

Object Init(Env env, Object exports) {
  exports.Set("nativeVersion", String::New(env, plksim::version));
  exports.Set("sampleMeshSvg", Function::New(env, sampleMeshSvg));

  return exports;
}

NODE_API_MODULE(addon, Init);