# configuration read from the config file
# decode()--convert the bytes to str
# encode()--covert the str to bytes

from socket import *
import configparser

config = configparser.ConfigParser()
config.read('server.config')

serverName = config['ubuntu']['Name']
serverPort = config['ubuntu']['Port']

clientSocket = socket(AF_INET, SOCK_STREAM)
clientSocket.connect((serverName, int(serverPort)))
msg = input('Please input a sentence:')
clientSocket.send(msg.encode())
rcv_msg = (clientSocket.recv(1024)).decode()
print("Get:" + rcv_msg)

clientSocket.close()
print("Client is closed...")