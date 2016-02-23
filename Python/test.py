"""
from multiprocessing import Pool

def prit():
    print "okkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkk"


if __name__  == '__main__':
    pool = Pool(processes=1)
    pool.apply_async(prit)
    print "1"
    print "2"
    print "3"
    for x in range(0, 20):
        print x
"""
"""
import asyncio

@asyncio.coroutine
def test():
    print "Hello World!"
    yield from hello()
    print "Hello again!"

def hello():
    print " is it real"
"""

import threading

def test(a, b):
    print a, b
    for x in range(1, 20):
        print x

def pr():
    t = threading.Thread(target=test, args=['x', 'y'])
    t.start()
    print "ok"
    print "ok"
    print "ok"
    print "ok"
    print "ok"
    print "ok"


pr()

