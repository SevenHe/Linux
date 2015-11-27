#!/usr/bin/python3.4
# if you import the socket.*, you will not get the functions outside the socketobject.
# so you must use "import socket" to get the outside functions,
# and use " from .. import *" get the object

import socket

serverName = socket.gethostname()
serverPort = 9999

from socket import *

serverSocket = socket(AF_INET, SOCK_STREAM)
serverSocket.bind((serverName, serverPort))
serverSocket.listen(1)
print('The server is ready to receive.....')
while 1:
	conSocket, addr = serverSocket.accept()
	msg = (conSocket.recv(1024)).decode()
	print(str(addr) + ":" + str(msg))
	msg += '---from server'
	# return to the client
	conSocket.send(msg.encode())
	conSocket.close()

serverSocket.close():
print('The server is closed')
	
