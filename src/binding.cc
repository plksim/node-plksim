#include <napi.h>
#include <plksim/version.hh>

using namespace Napi;

namespace plksim {

Value NativeVersionGetter(const CallbackInfo& info) {
  return String::New(info.Env(), VERSION);
}

Object Init(Env env, Object exports) {
  PropertyDescriptor nativeVersion = PropertyDescriptor::Accessor<NativeVersionGetter>("nativeVersion");

  exports.DefineProperties({nativeVersion});

  return exports;
}

NODE_API_MODULE(addon, Init);

} // namespace plksim