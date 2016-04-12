#!/usr/bin/python

# always divide the datum into 2 sub sequences.
def merge_sort(datum):

    mid = int(len(datum)/2)
    if mid == 0:
        return datum
    # if in the 'if' loop, it may need to create them first.
    left = merge_sort(datum[:mid])
    right = merge_sort(datum[mid:])
    # so i need not to create a local variable, result, just return it.
    return merge(left, right)

# comparison, and merging
def merge(left, right):
    result = []
    k1 = 0
    k2 = 0
    while k1 < len(left) and k2 < len(right):
        if left[k1] < right[k2]:
            result.append(left[k1])
            k1 += 1
        else:
            result.append(right[k2])
            k2 += 1
    while k1 < len(left):
        result.append(left[k1])
        k1 += 1
    while k2 < len(right):
        result.append(right[k2])
        k2 += 1
    return result

if __name__ == "__main__":
    print merge_sort([10, 8, 15, 66, 23, 89, 55, 77, 27, 68])
