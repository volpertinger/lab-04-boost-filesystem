// Copyright 2020 Merzlov Nikolay merzlovnik@mail.ru

#include <boost/filesystem.hpp>
#include <iostream>
#include <set>
#include <string>

#ifndef INCLUDE_HEADER_HPP_
#define INCLUDE_HEADER_HPP_

struct File_info {
  std::string directory = "current";
  std::string name;
};

bool operator<(File_info const &lhs, File_info const &rhs) {
  return lhs.name < rhs.name;
}

bool is_correct_account(std::string filename) {
  if (filename.substr(0, 8) != "balance_") return false;
  if (filename.substr(filename.size() - 4, 4) == ".old") return false;
  for (size_t i = 8; i < 16; ++i) {
    if (!(filename[i] >= '0' && filename[i] <= '9')) return false;
  }
  for (size_t i = 17; i < 25; ++i) {
    if (!(filename[i] >= '0' && filename[i] <= '9')) return false;
  }
  return true;
}

void run_directory(boost::filesystem::path path,
                   std::set<std::string> &set_in) {
  for (const auto &current_path : boost::filesystem::directory_iterator{path}) {
    if (is_directory(current_path)) {
      run_directory(current_path, set_in);
    } else {
      if (current_path.path().extension().string() == ".txt" &&
          is_correct_account(current_path.path().stem().string()))
        set_in.emplace(current_path.path().filename().string());
    }
  }
}

void run_directory_(boost::filesystem::path path, std::set<File_info> &set_in) {
  std::string c_d = path.filename().string();
  for (const auto &current_path : boost::filesystem::directory_iterator{path}) {
    if (is_directory(current_path)) {
      c_d = current_path.path().filename().string();
      run_directory_(current_path, set_in);
    } else {
      if (current_path.path().extension().string() == ".txt" &&
          is_correct_account(current_path.path().stem().string())) {
        File_info tmp;
        tmp.name = current_path.path().filename().string();
        tmp.directory = c_d;
        set_in.emplace(tmp);
      }
    }
  }
}

class Filesystem {
  boost::filesystem::path path;
  std::set<File_info> file_info_set;
  std::set<std::string> file_set;

 public:
  Filesystem(std::string &path_) : path(path_) {
    run_directory_(path, file_info_set);
  }
};

#endif  // INCLUDE_HEADER_HPP_
