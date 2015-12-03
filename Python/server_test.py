import socket

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.bind(("0.0.0.0", 61441))

server = "10.100.61.3"
username = "hech5513"
pswd = "010178"
mac = 0xC454442B84C5
import urllib2
import gzip
import StringIO
f = urllib2.urlopen("http://" + server)
auth_handler = urllib2.HTTPBasicAuthHandler()
auth_handler.add_password(None, uri="http://" + server + ":61440", user=username, passwd=pswd)
opener = urllib2.build_opener(auth_handler)
urllib2.install_opener(opener)
import sys
import os
# os.getcwd()
type = sys.getfilesystemencoding()
f = urllib2.urlopen("http://" + server)
print f.code

with open("/home/seven/Code/Markups/drcom.html", 'w') as html:
    html.write(f.read().decode('gb2312').encode(type))
    f.close()
with open("/home/seven/Code/Markups/drcom.html", 'r') as html:
    print html.read()

"""
# This is useful when the html has been gizpped.
f = StringIO.StringIO(f.read())
gzipper = gzip.GzipFile(fileobj=f)
html = f.readlines()
print html
"""
"""
# This is the best way to adjust the system.
import sys
type = sys.getfilesystemencoding()
print (f.read()).decode('gb2312').encode(type)
"""
