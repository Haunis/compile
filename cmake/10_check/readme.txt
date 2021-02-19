添加环境检查

1.添加CheckFunctionExists.cmake宏
include (${CMAKE_ROOT}/Modules/CheckFunctionExists.cmake)

2.用check_function_exists命令测试是否能在链接阶段找到pow函数
check_function_exists(pow HAVE_POW)
