#include <nan.h>

namespace __idle__ {

unsigned int idle_times = 0;
uv_idle_t* idle = 0;

void test_idle(uv_idle_t* handle)
{
    // 空转次数减一
    idle_times--;

    // 输出点东西
    printf("还剩 %u 次空转。\n", idle_times);

    // 若空转次数到达，则该空转停止
    if(idle_times == 0)
    {
        idle = 0;

        // 空转停止
        uv_idle_stop(handle);

        // 释放空转句柄
        delete handle;
    }
}

NAN_METHOD(StartIdle)
{
    if(idle != 0)
    {
        return Nan::ThrowError("上一个空转仍在进行。");
    }

    idle_times = Nan::To<unsigned int>(info[0]).FromJust();

    idle = new uv_idle_t();

    // 初始化空转句柄
    uv_idle_init(uv_default_loop(), idle);

    // 将 `test_idle` 函数绑定给空转句柄并开始
    // 即每个空转阶段都会执行 `test_idle` 函数
    uv_idle_start(idle, test_idle);
}

NAN_MODULE_INIT(Init)
{
    Nan::Export(target, "startIdle", StartIdle);
}

NODE_MODULE(reverse, Init)

}
