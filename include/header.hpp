// Copyright 2020 Merzlov Nikolay merzlovnik@mail.ru

#include <boost/filesystem.hpp>
#include <iostream>
#include <set>
#include <string>

#ifndef INCLUDE_HEADER_HPP_
#define INCLUDE_HEADER_HPP_

struct File_info {
  std::string broker;
  std::string name_full;
  std::string account;
  std::string date;
  int count;
  File_info(std::string broker_, std::string name_full_, std::string account_,
            std::string date_, int count_)
      : broker(broker_),
        name_full(name_full_),
        account(account_),
        date(date_),
        count(count_) {}
};

bool operator<(File_info const &lhs, File_info const &rhs) {
  if (lhs.broker == rhs.broker) return lhs.name_full < rhs.name_full;
  return lhs.broker < rhs.broker;
}

bool operator==(File_info const &lhs, File_info const &rhs) {
  return (lhs.name_full == rhs.name_full && lhs.broker == rhs.broker);
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

std::string get_account(std::string filename) { return filename.substr(8, 8); }

std::string get_date(std::string filename) { return filename.substr(17, 8); }

void run_directory(boost::filesystem::path path, std::set<File_info> &set_in) {
  std::string c_d = path.filename().string();
  for (const auto &current_path : boost::filesystem::directory_iterator{path}) {
    if (is_directory(current_path)) {
      c_d = current_path.path().filename().string();
      run_directory(current_path, set_in);
    } else {
      if (current_path.path().extension().string() == ".txt" &&
          is_correct_account(current_path.path().stem().string())) {
        std::string current_filename = current_path.path().filename().string();
        File_info tmp(c_d, current_filename, get_account(current_filename),
                      get_date(current_filename), 1);
        set_in.emplace(tmp);
      }
    }
  }
}

class Filesystem {
  boost::filesystem::path path;
  std::set<File_info> file_info_set;
  std::set<File_info> sorted_set;

 public:
  Filesystem(std::string &path_) : path(path_) {
    run_directory(path, file_info_set);
  }

  void print_files_set() {
    for (auto &file : file_info_set)
      std::cout << file.broker << " " << file.name_full << " " << file.count
                << std::endl;
  }

  void print_sorted_set() {
    for (auto &file : sorted_set)
      std::cout << "broker:" << file.broker << " account:" << file.account
                << " files:" << file.count << " lastdate:" << file.date
                << std::endl;
  };

  void make_sorted() {
    std::string current_account = file_info_set.begin()->account;
    std::string c_name;
    std::string c_b;
    int counter = 0;
    for (auto &file : file_info_set) {
      if (file.account == current_account) {
        ++counter;
        c_name = file.name_full;
        c_b = file.broker;
      } else {
        File_info tmp(c_b, c_name, current_account, get_date(c_name), counter);
        sorted_set.emplace(tmp);
        current_account = file.account;
        counter = 0;
      }
    }
  }

  void print() {
    print_files_set();
    make_sorted();
    std::cout << "-------------------------------------------------------------"
              << std::endl;
    print_sorted_set();
  }
};

#endif  // INCLUDE_HEADER_HPP_
