#cmake要求的最低版本
cmake_minimum_required(VERSION 3.6)
project(USE_SO)#项目信息随便指定

#库头文件所在路径
include_directories("${PROJECT_SOURCE_DIR}/lib")

#添加库目录,因为是动态库所以可以不用指定
#link_directories("${PROJECT_SOURCE_DIR}/lib")

#遍历源文件,保存在DIR_SRC变量里
aux_source_directory(. DIR_SRC)


# #链接库方式1:link_libraries()
# #在add_executable()之前直接链接库
# link_libraries(my_power) 
# add_executable(main ${DIR_SRC})


# # 链接库方式2.1:target_link_libraries()
# # 在add_executable()之后链接
# add_executable(main ${DIR_SRC})
# target_link_libraries(main my_power)#libmy_power.so也行


# 链接库方式2.2:target_link_libraries()
# 链接指定路径下so:find_library
add_executable(main ${DIR_SRC})
find_library(MY_POWER libmy_power.so ./lib) #在./lib下寻找libmy_power.so,保存在变量MY_POWER
target_link_libraries(main ${MY_POWER})