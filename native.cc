#include"native.h"
#include<iostream>
#include<v8.h>

Napi::FunctionReference NativeModule::constructor;
Napi::FunctionReference NativeModule::jsGcBackRef;

Napi::Object NativeModule::Init(Napi::Env env, Napi::Object exports) {
  Napi::Function func =
      DefineClass(env,
                  "NativeModule",
                  {InstanceMethod("initialize",
                                  &NativeModule::initialize)});

  constructor = Napi::Persistent(func);
  constructor.SuppressDestruct();

  exports.Set("NativeModule", func);
  return exports;
}

NativeModule::NativeModule (const Napi::CallbackInfo& info)
    : Napi::ObjectWrap<NativeModule>(info) {
  jsGcBackRef = Napi::Persistent(info[0].As<Napi::Function>());
}

void NativeModule::gc_callback(v8::Isolate* isolate, v8::GCType type, v8::GCCallbackFlags flags, void* data) {
  jsGcBackRef.Call({});
}

void NativeModule::initialize(const Napi::CallbackInfo& info) {
  v8::Isolate* isolate = v8::Isolate::GetCurrent();
  isolate->AddGCEpilogueCallback(NativeModule::gc_callback);
}