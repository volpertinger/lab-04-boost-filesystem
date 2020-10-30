// Copyright 2020 Merzlov Nikolay merzlovnik@mail.ru

#include <boost/filesystem.hpp>
#include <header.hpp>

int main() {
  boost::filesystem::path path ("/home/killoboker/CLionProjects/lab-04-boost-filesystem/misc");
  std::string s_p("/home/killoboker/CLionProjects/lab-04-boost-filesystem/misc");
  Filesystem ss(s_p);
  //run_directory("/home/killoboker/CLionProjects/lab-04-boost-filesystem/misc",set_in);
  return 0;
}
