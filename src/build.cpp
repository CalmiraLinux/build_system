/*
 * Calmira Build System
 * Copyright (C) 2021, 2022 Michail Krasnov <linuxoid85@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <iostream>
#include <fstream>
#include <toml.hpp>

const char *log_file = "/var/log/build-system.log";
const char *hlp_file = "/usr/share/build_system/help";
const char *conf_file = "/etc/build_system.toml";

bool isfile(const char* file);
toml::value config();
int usage(int code);
void log_msg(const char* msg, const char* color = "\033[1m");
std::vector<std::string> files_list(const char* section);
int files_list_count(const char* section);
std::string path(const char* file, const char* section);
bool check_files(const char* section);
int answer(const char* pkg, const char* mode);
int build(const char* pkg, const char* mode);

bool isfile(const char* file) {
    return true;
}

toml::value config() {
    return toml::parse(conf_file);
}

int usage(int code) {
    std::string line;
    std::ifstream fp(hlp_file);
    if(!fp.is_open()) {
        std::cout << "\033[1m\033[31mOpen file '" << hlp_file <<
            "': error!\n\033[0m";
        return code;
    }
    while(getline(fp, line)) {
        std::cout << line << std::endl;
    }
    return code;
}

void log_msg(const char *msg, const char *color = "\033[1m") {
    std::cout << "==> " << color << msg << "\033[0m\n";
    
    std::fstream fp(log_file);
    if(!fp.is_open()) {
        std::cout << "\033[1m\033[31mOpen file '" << log_file <<
            "': error!\n\033[0m";
        return;
    }
    fp << msg << std::endl;
}

std::vector<std::string> files_list(const char *section) {
    toml::value conf = config();
    const auto sect = toml::find(conf, section);
    const auto pkgs = toml::find<std::vector<std::string>>(sect, "pkgs");
    return pkgs;
}

int files_list_count(const char *section) {
    toml::value conf = config();
    const auto sect = toml::find(conf, section);
    int count = toml::find<int>(sect, "count");
    return count;
}

std::string path(const char* file, const char* section) {
    std::string _dir = "/usr/share/build_system/pkgs/";
    std::string comb = _dir + section + file;
    return comb;
}

bool check_files(const char* section) {
    std::vector<std::string> files = files_list(section);
    int count = files_list_count(section);
    bool ret_code = true;

    for(int i = 0; i <= count; ++i) {
        std::string file = path(files[i], section) + files[i];
        if(!isfile(file.c_str())) {
            std::cout << "package " << files[i] << ": fail\n";
            ret_code = false;
        }
    }
    return ret_code;
}

int answer(const char *pkg, const char *mode) {
    char answ;
    std::cout << "Continue (c), repeat (r) or exit (e/x)? ";
    std::cin >> answ;
    if(answ == "e" || answ == "x") {
        std::cout << "Aborted\n";
        return 1;
    } else if(answ == "c") {
        std::cout << "Continue building...\n";
        return 0;
    } else if(answ == "r") {
        std::cout << "Repeat building package '" << pkg << "'...\n";
        return build(pkg, mode);
    } else {
        std::cout << "Unknown character: '" << answ << "'\n";
        return answ(pkg, mode);
    }
}

/*
 * Work modes:
 * "chroot";
 * "base"
 */
int build(const char* pkg, const char* mode) {
    if(mode == "chroot") {
        std::string command = "./build_chroot.sh " + pkg;
    } else {
        std::string command = "./build.sh " + pkg;
    }
    int code = system(command);
    if(code != 0) {
        std::cout << "\033[1m\033[31m" <<
            "Building package '" << pkg << "' error!\033[0m\n";
        int i = answer(pkg, mode);
        if(i == 1) {
            return i;
        }
    }
    return code;
}
