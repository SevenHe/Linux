#!/usr/bin/python2.7

def cal(s):
	result = 0
	for c in s:
		result += ord(c)
	return result

if __name__ == "__main__":
	while True:
		try:
			get = raw_input("Input: ") 
			result = cal(get)
			print result
		except:
			break
