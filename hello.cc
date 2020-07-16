#include <node.h>
#include <windows.h>
#include <stdio.h>

using namespace std;

namespace demo {

using v8::FunctionCallbackInfo;
using v8::Isolate;
using v8::Local;
using v8::NewStringType;
using v8::Object;
using v8::String;
using v8::Value;

__int64 Filetime2Int64(const FILETIME* ftime) {
    LARGE_INTEGER li;
    li.LowPart = ftime->dwLowDateTime;
    li.HighPart = ftime->dwHighDateTime;
    return li.QuadPart;
}

// 计算时间间隔
__int64 CompareFileTime2(FILETIME preTime,FILETIME currTime) {
    return Filetime2Int64(&preTime) - Filetime2Int64(&currTime);
}

string getCPUUsage() {
    // FILETIME preIdleTime;
    // FILETIME preKernelTime;
    // FILETIME preUserTime;
    // GetSystemTimes(&preIdleTime, &preKernelTime, &preUserTime);

    // Sleep(1000);

    FILETIME currIdleTime;
    FILETIME currKernelTime;
    FILETIME currUserTime;
    GetSystemTimes(&currIdleTime, &currKernelTime, &currUserTime);

    __int64 idle = Filetime2Int64(&currIdleTime);
    __int64 kernel = Filetime2Int64(&currKernelTime);
    __int64 user = Filetime2Int64(&currUserTime);
    // float currUtilization = float(100.0 * (kernel + user - idle) / (kernel + user));
    return to_string(idle) + " " + to_string(kernel) + " " + to_string(user);
}

void Method(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();
  string currUtilization = getCPUUsage();
  args.GetReturnValue().Set(String::NewFromUtf8(isolate, currUtilization.c_str(), NewStringType::kNormal).ToLocalChecked());
}

void init(Local<Object> exports) {
  NODE_SET_METHOD(exports, "hello", Method);
}

NODE_MODULE(addon, init)

}  // namespace demo