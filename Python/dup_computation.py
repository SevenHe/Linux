#!/usr/bin/python
import sys


inputs = raw_input()
count = 0
temp_c = ''
last = ''
final = ''
if len(inputs) < 1024:
    for char in inputs:
        if 'a' <= char <= 'z':
            char = char.upper()
        if 'A' <= char <= 'Z':
            if temp_c == '':
                temp_c = char
                count = 1
            elif temp_c != '0':
                if temp_c == char:
                    count += 1
                else:
                    final += "%s%d" % (temp_c, count)
                    last = temp_c
                    temp_c = char
                    count = 1

if last != '':
    final += "%s%d" % (temp_c, count)

if final != '':
    print final
