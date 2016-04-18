#!/usr/bin/python 

class ListMetaclass(type):
    def __new__(cls, name, bases, attrs):
        attrs['add'] = lambda self, value: self.append(value)
        print "get a class %s" % name
        return type.__new__(cls, name, bases, attrs)

class MyList(list):
    __metaclass__ = ListMetaclass

ml = MyList()
ml.add(1)
ml.add(3)
print ml
ml.name = 'ok'
print ml.name
from types import MethodType

def test(self):
    print 'ok'

MyList.test = MethodType(test, MyList)
ml.test()
