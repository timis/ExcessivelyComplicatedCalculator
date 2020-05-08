#include <napi.h>

using namespace Napi;

Value Add(const CallbackInfo &args){
    Env env = args.Env();
    if(args.Length() < 2){
        TypeError::New(env,"Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Null();
    }       

    if(!args[0].IsNumber() || !args[1].IsNumber()){
        TypeError::New(env, "Wrong argument types").ThrowAsJavaScriptException();
        return env.Null();
    }
    double arg0 = args[0].As<Number>().DoubleValue();
    double arg1 = args[1].As<Number>().DoubleValue();
    double val = arg0+arg1;
    Number num = Number::New(env,val);
    return num;
}

Value Minus(const CallbackInfo &args){
    Env env = args.Env();
    if(args.Length() < 2){
        TypeError::New(env,"Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Null();
    }       

    if(!args[0].IsNumber() || !args[1].IsNumber()){
        TypeError::New(env, "Wrong argument types").ThrowAsJavaScriptException();
        return env.Null();
    }
    double arg0 = args[0].As<Number>().DoubleValue();
    double arg1 = args[1].As<Number>().DoubleValue();
    double val = arg0-arg1;
    Number num = Number::New(env,val);
    return num;
}

Value Times(const CallbackInfo &args){
    Env env = args.Env();
    if(args.Length() < 2){
        TypeError::New(env,"Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Null();
    }       

    if(!args[0].IsNumber() || !args[1].IsNumber()){
        TypeError::New(env, "Wrong argument types").ThrowAsJavaScriptException();
        return env.Null();
    }
    double arg0 = args[0].As<Number>().DoubleValue();
    double arg1 = args[1].As<Number>().DoubleValue();
    double val = arg0*arg1;
    Number num = Number::New(env,val);
    return num;
}

Value Divide(const CallbackInfo &args){
    Env env = args.Env();
    if(args.Length() < 2){
        TypeError::New(env,"Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Null();
    }       

    if(!args[0].IsNumber() || !args[1].IsNumber()){
        TypeError::New(env, "Wrong argument types").ThrowAsJavaScriptException();
        return env.Null();
    }

    if(args[1].As<Number>().DoubleValue() == 0.0){
        TypeError::New(env, "Cannot divide by 0").ThrowAsJavaScriptException();
        return env.Null();
    }
    double arg0 = args[0].As<Number>().DoubleValue();
    double arg1 = args[1].As<Number>().DoubleValue();
    double val = arg0/arg1;
    Number num = Number::New(env,val);
    return num;
}
    
Value Mod(const CallbackInfo &args){
    Env env = args.Env();
    if(args.Length() < 2){
        TypeError::New(env,"Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Null();
    }       

    if(!args[0].IsNumber() || !args[1].IsNumber()){
        TypeError::New(env, "Wrong argument types").ThrowAsJavaScriptException();
        return env.Null();
    }

    if(args[1].As<Number>().Int32Value() == 0){
        TypeError::New(env, "Cannot modulo by 0").ThrowAsJavaScriptException();
        return env.Null();
    }
    int arg0 = args[0].As<Number>().Int32Value();
    int arg1 = args[1].As<Number>().Int32Value();
    int val = arg0%arg1;
    Number num = Number::New(env,val);
    return num;
}

Value FileLength(const CallbackInfo &args){
    Env env = args.Env();
    if(args.Length() != 1){
        TypeError::New(env,"Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Null();
    }       

    if(!args[0].IsBuffer()){
        TypeError::New(env, "Wrong argument type").ThrowAsJavaScriptException();
        return env.Null();
    }

    Buffer<char>  arg0 = args[0].As<Buffer<char>>();
    // int val = arg0%arg1;
    Number num = Number::New(env,arg0.Length());
    return num;
}

// void FileLength(const CallbackInfo<Value> &args){
//     Env env = args.Env();
//     if(args.Length() != 1){
//         TypeError::New(env,"Wrong number of arguments").ThrowAsJavaScriptException();
//         return env.Null();
//     }       

//     if(!args[0].IsNumber()){
//         TypeError::New(env, "Wrong argument types").ThrowAsJavaScriptException();
//         return env.Null();
//     }

//     size_t byteLength = args[0].As<ArrayBuffer>()->Externalize().ByteLength();
//     // int val = args[0].As<Int32>()->Value() / args[1].As<Int32>()->Value();
//     Local<Number> num = Number::New(isolate,byteLength);
//     args.GetReturnValue().Set(num);
// }



Object Initialize(Env env, Object exports){
    exports.Set(String::New(env,"add"), Function::New(env,Add));
    exports.Set(String::New(env,"minus"), Function::New(env,Minus));
    exports.Set(String::New(env,"times"), Function::New(env,Times));
    exports.Set(String::New(env,"divide"), Function::New(env,Divide));
    exports.Set(String::New(env,"mod"), Function::New(env,Mod));
    exports.Set(String::New(env,"length"), Function::New(env, FileLength));
    return exports;
    // NODE_SET_METHOD(exports,"add",Add);
    // NODE_SET_METHOD(exports,"minus",Minus);
    // NODE_SET_METHOD(exports, "times", Times);
    // NODE_SET_METHOD(exports, "divide", Divide);
    // NODE_SET_METHOD(exports, "mod", Mod);
    // NODE_SET_METHOD(exports,"length",FileLength);
}

NODE_API_MODULE(addon, Initialize)
// NODE_MODULE(NODE_GYP_MODULE_NAME, Initialize)
// #include <napi.h>

// String Method(const CallbackInfo& info) {
//   Env env = info.Env();
//   return String::New(env, "world");
// }

// Object Init(Env env, Object exports) {
//   exports.Set(String::New(env, "hello"),
//               Function::New(env, Method));
//   return exports;
// }

// NODE_API_MODULE(hello, Init)
