#! /usr/bin/python3

import re
import os

script_path = os.getcwd()

path = "{}/src".format(script_path)


def get_files(path):
    files = []

    for (dirpath, dirnames, filenames) in os.walk(path):
        for f in filenames:
            files.append(os.path.join(dirpath, f))

        for d in dirnames:
            files.extend(get_files(os.path.join(dirpath, d)))

        break

    return files


def include_gurad(header):
    t = header.replace(path, '').replace('.', '_').replace(
        '/', '_').replace('\\', '_').split('_')
    t = list(filter(lambda s: len(s) > 0, t))
    t.insert(0, 'framework')
    return '_'.join(s.upper() for s in t)


def replace_guard(data, guard):
    new_guard = "#ifndef {0}\n#define {0}\n".format(guard)

    data = re.sub(
        r'#ifndef\s(?P<g>[a-zA-Z_\\]*)\n#define\s\1\n', new_guard, data)
    return data


headers = list(filter(lambda f: f.endswith('.hpp'), get_files(path)))


for header in headers:
    f = open(header, 'r')
    filedata = f.read()
    f.close()

    print(header)

    guard = include_gurad(header)

    newdata = replace_guard(filedata, guard)

    f = open(header, 'w')
    f.write(newdata)
    f.close()
