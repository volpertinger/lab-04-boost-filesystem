// Copyright 2020 Merzlov Nikolay merzlovnik@mail.ru

#include <boost/filesystem.hpp>
#include <header.hpp>

int main(int argc, char *argv[]) {
  std::string path;
  if (argc > 2) {
    std::cerr << "To much arguments" << std::endl;
    return 1;
  }
  if (argc == 2) path = argv[1];
  if (argc == 1) std::getline(std::cin, path);
  if (argc == 0) path = "../";
  Filesystem fs(path);
  fs.print();
  return 0;
}
