#!/usr/bin/python3
#
# Calmira Build System
# Copyright (C) 2021, 2022  Linuxoid85
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.

import os
import sys
import toml
import time
import subprocess

LOG_FILE = "/var/log/build-system.log"
HLP_FILE = "/usr/share/build_system/help"

def usage(code: int) -> int:
    with open(HLP_FILE) as f:
        data = f.read()

    print(data, file = sys.stderr)
    return code

def log_msg(msg: str, color = "\033[1m") -> None:
    print(f"{color}{msg}\033[0m")
    with open(LOG_FILE, 'a') as f:
        lmsg = f"[ {time.ctime()} ] {msg}\n"
        f.write(lmsg)

def config(file: str) -> dict:
    return toml.load(file)

def files_list(section: str) -> list:
    conf = config("/etc/build_system.toml")
    sect = conf.get(section)

    if sect is None:
        raise ValueError

    files = sect.get("pkgs")
    return files

def path(file: str, section: str):
    _dir = "/usr/share/build_system/pkgs/"
    comb = f"{_dir}{section}/{file}"
    return comb

def check_files(section: str) -> bool:
    files = files_list(section)

    data = True
    for file in files:
        pth = path(file, section)
        if not os.path.exists(pth):
            print(f"package '{file}': fail")
            data = False

    return data

def build(pkg: str) -> int:
    command = f"./build.sh {pkg}"
    run = subprocess.run(command, shell = True)
    if run.returncode != 0:
        log_msg(f"Building package '{pkg}' error!")
        answ = input("Continue (c), repeat (r) or exit(e/x)? ")
        ex_lst = ('e', 'E', 'x', 'X')
        if answ in ex_lst:
            print("Aborted.", file = sys.stderr)
            return -1
        elif answ == "c":
            print("Continue building...", file = sys.stderr)
        elif answ == "r":
            print("Repeat building...", file = sys.stderr)
            build(pkg)

    return run.returncode

def build_packages(tp: str) -> int:
    if not check_files(tp):
        return 1
    files = files_list(tp)

    for file in files:
        msg = f"building package '{file}'"
        log_msg(msg)
        run = build(path(file, tp))

        if run == 0:
            log_msg(f"building package '{file}' is OK!")
        else:
            log_msg(f"building package '{file}' is FAIL!")
            log_msg("Aborted building.")
            return run

    return 0

try:
    data = build_packages(sys.argv[1])
except PermissionError:
    print("\033[31m\033[1mPermission error!\033[0m")
    exit(usage(1))
except IndexError:
    print("\033[31m\033[1mUsage error!\033[0m")
    exit(usage(1))
