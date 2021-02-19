关于c++和c的混合编程,可参考make demo里的示例

nm xxx -i  //xxx是可执行bin文件



readelf:
    参考:http://www.voidcn.com/article/p-hozwsmnk-tp.html
    查看编译后的elf文件信息
    readelf -h main //查看头信息
    readelf -r main //查看重定位信息
