#!/usr/bin/python3.4

def kick_down(a, b):
    a_len = len(a)
    b_len = len(b)
    i = 0
    b_time = 0
    match = 0
    while i < len(b):
        if match == a_len:
            break
        if int(a[match]) + int(b[i]) <= 3:
            match += 1
            i += 1
        else:
            match = 0
            b_time += 1
            i = b_time

    return a_len + b_len - match

a = ""
count = 0
while True:
    try:
        b = input()
        count += 1
        if count & 1:
            a = b
            continue
        forward = kick_down(b, a)
        backward = kick_down(a, b)
        ans = min(forward, backward) 
        print(ans)
    except:
        break

