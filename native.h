#include <napi.h>
#include<v8.h>

class NativeModule: public Napi::ObjectWrap<NativeModule> {
  public:
    static Napi::Object Init(Napi::Env env, Napi::Object exports);
    NativeModule(const Napi::CallbackInfo& info);
  
  private:
    static Napi::FunctionReference constructor;
    static Napi::FunctionReference jsGcBackRef;

    static void gc_callback(v8::Isolate* isolate, v8::GCType type, v8::GCCallbackFlags flags, void* data);
    void initialize(const Napi::CallbackInfo& info);
};
