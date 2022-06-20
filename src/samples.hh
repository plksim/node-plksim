#include <napi.h>

#include <plksim/samples.hh>

#include <string>

using namespace Napi;

namespace node_plksim {

struct SampleMeshSvgAsyncWorker : AsyncWorker {
  SampleMeshSvgAsyncWorker(Napi::Env& env) : AsyncWorker(env), mDeferred(Napi::Promise::Deferred::New(env)) {
  }

  ~SampleMeshSvgAsyncWorker() {
  }

  void Execute() override {
    try {
      mResult = plksim::sampleMeshSvg();
    } catch (std::exception const& ex) {
      SetError(ex.what());
    } catch (...) {
      SetError("unknown");
    }
  }

  void OnOK() override {
    mDeferred.Resolve(String::New(Env(), mResult));
  }

  void OnError(Error const& error) override {
    mDeferred.Reject(error.Value());
  }

  Promise GetPromise() const {
    return mDeferred.Promise();
  }

private:
  Promise::Deferred mDeferred;
  std::string mResult;
};

Value sampleMeshSvg(const CallbackInfo& info) {
  Napi::Env env = info.Env();

  auto* asyncWorker = new SampleMeshSvgAsyncWorker(env);
  auto promise = asyncWorker->GetPromise();

  asyncWorker->Queue();

  return promise;
}

} // namespace node_plksim