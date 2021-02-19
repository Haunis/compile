//不是正宗pipe demo,本文是模拟演示android dump
//参考: https://www.jianshu.com/p/c9d6c2839e7f
//编译:g++ -o pipe pipe.cpp -std=c++11 -lpthread

#include <cstdio>
#include <unistd.h>
#include <fcntl.h>
#include <sys/poll.h>

#include <unistd.h>
#include <iostream>
#include <thread>
#include <string>

constexpr int kTimeOut = 5;

int main(int argc, char** argv) {
  
  //1.创建管道
  int pids[2];
  int ret = pipe(pids);//匿名管道,只能在有亲缘关系之间的进程间通信
  
  //2.新线程中延时写入;从pid[1]端写
  std::string src{"Oh, yes !"};
  std::thread t([&]() {
    std::this_thread::sleep_for(std::chrono::seconds(2));
    write(pids[1], src.c_str(), src.length());
    close(pids[1]);
  });
  t.detach();


  nfds_t size = 1;
  struct pollfd fds[size];

  fds[0].fd = pids[0];
  fds[0].events = POLLIN;
  //3.等待数据写入
  ret = poll(fds, size, kTimeOut * 1000);

  if (ret == -1) {
    std::cerr << "failed, baby ~" << std::endl;
    return -1;
  }

  if (ret == 0) {
      std::cout << "time out , baby ~" << std::endl;
      return -1;
  }
  //4.读出数据,从pid[0]端读
  if (fds[0].revents & POLLIN) {
    std::cout << "oh baby, data is coming ... " << std::endl;
    char dst[src.length() + 1];
    read(pids[0], dst, src.length());
    dst[src.length()] = '\0';
    close(pids[0]);
    std::cout << "data received : " << dst << std::endl;
  }

}
