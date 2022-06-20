#include <napi.h>

#include <plksim/version.hh>

#include "samples.hh"

using namespace Napi;

namespace node_plksim {

Object init(Env env, Object exports) {
  exports.Set("nativeVersion", String::New(env, plksim::version));
  exports.Set("sampleMeshSvg", Function::New(env, sampleMeshSvg));

  return exports;
}

NODE_API_MODULE(addon, init);

} // namespace node_plksim