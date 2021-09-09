#include <array>
#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
using namespace std;
std::string exec(const char* cmd) {
  std::array<char, 128> buffer;
  std::string result;
  std::shared_ptr<FILE> pipe(popen(cmd, "r"), pclose);
  if (!pipe) throw std::runtime_error("popen() failed!");
  while (!feof(pipe.get())) {
    if (fgets(buffer.data(), 128, pipe.get()) != nullptr)
      result += buffer.data();
  }
  return result;
}
int main() {
  try {
    //    system("service call iphonesubinfo 1 >/sdcard/mobvoi/imei.txt");
    auto exec_android = [](const char* cmd) {
      std::array<char, 128> buffer;
      std::string result;
      std::shared_ptr<FILE> pipe(popen(cmd, "r"), pclose);
      if (!pipe) throw std::runtime_error("popen() failed!");
      while (!feof(pipe.get())) {
        if (fgets(buffer.data(), 128, pipe.get()) != nullptr)
          result += buffer.data();
      }
      return result;
    };
    string imei_origin = exec_android("service call iphonesubinfo 1");
    cout << imei_origin << endl;
    int indexes[] = {75,  77,  79,  81,  136, 138, 140, 142,
                     144, 146, 148, 150, 205, 207, 209};
    std::string imei;
    for (int i = 0; i < 15; i++) {
      imei += imei_origin[indexes[i]];
    }
    std::cout << imei << std::endl;
  } catch (exception& e) {
    cout << e.what();
    exit(1);
  }
  return 0;
}