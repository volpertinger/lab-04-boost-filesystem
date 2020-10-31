// Copyright 2020 Merzlov Nikolay merzlovnik@mail.ru

#include <boost/filesystem.hpp>
#include <header.hpp>

int main() {
  std::string s_p(
      "/home/killoboker/CLionProjects/lab-04-boost-filesystem/misc");
  Filesystem ss(s_p);
  ss.print();
  return 0;
}
