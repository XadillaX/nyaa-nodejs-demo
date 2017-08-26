#include <node_api.h>

namespace __first__ {

napi_value echo(napi_env env, napi_callback_info info)
{
    napi_status status;
    
    size_t argc = 1;
    napi_value argv[1];
    status = napi_get_cb_info(env, info, &argc, argv, 0, 0);
    if(status != napi_ok || argc < 1)
    {
        napi_throw_type_error(env, "EBADARGS", "Wrong number of arguments");
        return 0;
    }
    
    return argv[0];
}

void init(napi_env env, napi_value exports, napi_value module, void* priv)
{
    napi_status status;

    // 用于设置 exports 对象的描述结构体
    napi_property_descriptor desc =
        { "echo", 0, echo, 0, 0, 0, napi_default, 0 };

    // 把 "echo" 设置到 exports 去
    status = napi_define_properties(env, exports, 1, &desc);
}

NAPI_MODULE(addon, init)

}