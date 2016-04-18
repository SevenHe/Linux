#!/usr/bin/python3.4

while True:
    try:
        src = input()
        s, t = src.split(' ')
        # print(s, t)
        si = 0
        found = False
        for i in range(0, len(t)):
            if s[si] == t[i]:
                si += 1
                if si == len(s):
                    found = True
                    break
        if found:
            print("Yes")
        else:
            print("No")
    except:
        break
