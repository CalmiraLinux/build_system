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

void log_msg(const char *msg, const char *color = "==> \033[1m") {
    std::cout << color << msg << "\033[0m\n";
    
    std::fstream fp(log_file);
    if(!fp.is_open()) {
        std::cout << "\033[1m\033[31mOpen file '" << log_file <<
            "': error!\n\033[0m";
        return;
    }
    out << msg << std::endl;
}

std::string *files_list(const char* section) {}
