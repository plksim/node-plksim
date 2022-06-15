#include <napi.h>

#include <plksim/samples.hh>
#include <plksim/version.hh>

using namespace Napi;

namespace plksim {

Value NativeVersionGetter(const CallbackInfo& info) {
  return String::New(info.Env(), VERSION);
}

String SampleMeshSvgMethod(const Napi::CallbackInfo& info) {
  auto svg = sampleMeshSvg();
  return String::New(info.Env(), svg);
}

Object Init(Env env, Object exports) {
  PropertyDescriptor nativeVersion = PropertyDescriptor::Accessor<NativeVersionGetter>("nativeVersion");
  exports.DefineProperties({nativeVersion});

  exports.Set(String::New(env, "sampleMeshSvg"), //
              Function::New(env, SampleMeshSvgMethod));

  return exports;
}

NODE_API_MODULE(addon, Init);

} // namespace plksim