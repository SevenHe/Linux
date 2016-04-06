#!/usr/bin/python

present = "(A)"
total = raw_input()
total = total.split("\\n")
fools = [0 for x in range(0, len(total))]
count = 0
for dull in total:
    if len(dull) >= 1000:
        continue
    index = dull.find(present)
    if index != -1:
        for i in range(0, index):
            if dull[i] == '(':
                fools[count] += 1
            elif dull[i] == ')':
                fools[count] -= 1
    count += 1

# add the (A) pack
for fool in fools:
    print fool+1
