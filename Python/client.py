#!/usr/bin/python
import socket, struct, time
from hashlib import md5
import sys
import urllib2

# To-do list:
#       optimize the code: the structure.
#       prompt: do not make the passwd literal and let users specify the different args.
#       translatable;
#       check: if the port is in use, just change it or make use to specify it manually.
#configure the encrypted rules when not logging in , in the html file.
#to close the socket and get the information of the httpconnection.

class ChallengeException (Exception):
  def __init__(self):
    pass

class LoginException (Exception):
  def __init__(self):
    pass
   
class client:
    def __init__(self):
        self._sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self._sock.bind(("0.0.0.0", 61440))
        
        self._sock.settimeout(3)
        self._SALT = ''
        self._svr = "10.100.61.3" # "auth.jlu.edu.cn"
        self._username = "hech5513"
        self._password = "010178"
        self._host_name = "SEVEN"
        self._host_os = "Kubuntu"
        self._mac = 0xC454442B84C5
        self.UNLIMITED_RETRY = True
        self.EXCEPTION = False
        self.DEBUG = True

    def challenge(self, svr, ran):
        # a server restricted format.
        while True:
            t = struct.pack("<H", int(ran)%(0xFFFF))
            self._sock.sendto("\x01\x02"+t+"\x09"+"\x00"*15, (svr, 61440))
            try:
                data, address = sock.recvfrom(1024)
            except:
                if DEBUG:
                    print '[challenge] timeout, retrying...'
            continue
        
            if address == (svr, 61440):
                break
            else:
                continue
        if DEBUG:
            print '[DEBUG] challenge:\n' + data.encode('hex')
        if data[0] != '\x02':
            raise ChallengeException
        print '[challenge] challenge packet sent.'
        return data[4:8]


# encrypted.
def md5sum(msg):
    m = md5()
    m.update(msg)
    return m.digest()

def dump(n):
    dump_str = '%x' % n
    if len(dump_str) & 1:
         dump_str = '0' + dump_str
    return dump_str.decode('hex')

def ror(md5, pswd):
    ret = ''
    for i in range(len(pswd)):
        x = ord(md5[i]) ^ ord(pswd[i])
        ret += chr(((x<<3)&0xFF) + (x>>5))
    return ret

def keep_alive_package_builder(number, random, tail, type=1, first=False):
    data = '\x07'+ chr(number) + '\x28\x00\x0b' + chr(type)
    if first :
      data += '\x0f\x27'
    else:
      data += '\xdc\02'
    data += random + '\x00' * 6
    data += tail
    data += '\x00' * 4
    #data += struct.pack("!H",0xdc02)
    if type == 3:
      foo = '\x31\x8c\x21\x3e' #CONSTANT
      #CRC
      crc = packet_CRC(data+foo)
      data += struct.pack("!I",crc) + foo + '\x00' * 8
    else: #packet type = 1
      data += '\x00' * 16
    return data

def packet_CRC(raw):
    ret = 0
    for i in re.findall('..', raw):
        ret ^= struct.unpack('>h', i)[0]
        ret &= 0xFFFF
    ret = ret * 0x2c7
    return ret

def keep_alive2():
    #first keep_alive:
    #number = number (mod 7)
    #status = 1: first packet user sended
    #         2: first packet user recieved
    #         3: 2nd packet user sended
    #         4: 2nd packet user recieved
    #   Codes for test
    tail = ''
    packet = ''
    svr = server
    import random
    ran = random.randint(0, 0xFFFF)
    ran += random.randint(1, 10)   
    packet = keep_alive_package_builder(0,dump(ran),'\x00'*4, 1, True)
    sock.sendto(packet, (svr, 61440))
    data, address = sock.recvfrom(1024)
    
    ran += random.randint(1, 10)   
    packet = keep_alive_package_builder(1, dump(ran), '\x00'*4, 1, False)
    sock.sendto(packet, (svr, 61440))
    data, address = sock.recvfrom(1024)
    tail = data[16:20]
    

    ran += random.randint(1, 10)   
    packet = keep_alive_package_builder(2, dump(ran), tail, 3, False)
    sock.sendto(packet, (svr, 61440))
    data, address = sock.recvfrom(1024)
    tail = data[16:20]
    print "[keep-alive2] keep-alive2 loop was in daemon."
    
    i = 1
    while True:
      try:
        time.sleep(5)
        ran += random.randint(1,10)   
        packet = keep_alive_package_builder(2, dump(ran), tail, 1, False)
        #print 'DEBUG: keep_alive2,packet 4\n',packet.encode('hex')
        sock.sendto(packet, (svr, 61440))
        data, address = sock.recvfrom(1024)
        tail = data[16:20]
        #print 'DEBUG: keep_alive2,packet 4 return\n',data.encode('hex')
        
        ran += random.randint(1,10)   
        packet = keep_alive_package_builder(2,dump(ran),tail,3,False)
        #print 'DEBUG: keep_alive2,packet 5\n',packet.encode('hex')
        sock.sendto(packet, (svr, 61440))
        data, address = sock.recvfrom(1024)
        tail = data[16:20]
        #print 'DEBUG: keep_alive2,packet 5 return\n',data.encode('hex')
        i = i+1
        i = i % (0xFF)
        
        check_online = urllib2.urlopen('http://10.100.61.3')
        foo = check_online.read()
        if 'login.jlu.edu.cn' in foo:
          print '[keep_alive2] offline.relogin...'
          break;
        #MODIFIED END
        ''' 
        if i % 10 == 0:
          check_online = urllib2.urlopen('http://10.100.61.3')
          foo = check_online.read()
          if 'login.jlu.edu.cn' in foo:
            print '[keep_alive2] offline.relogin...'
            break;
        '''
      except:
        pass
        
    
import re
def checksum(sock):
    ret = 1234
    for i in re.findall('....', sock):
        ret ^= int(i[::-1].encode('hex'), 16)
    ret = (1968 * ret) & 0xffffffff
    return struct.pack('<I', ret)

def mkpkt(salt, usr, pswd, mac):
    data = '\x03\01\x00'+chr(len(usr)+20)
    data += md5sum('\x03\x01'+salt+pswd)
    data += usr.ljust(36, '\x00')
    data += '\x00\x00'
    data += dump(int(data[4:10].encode('hex'),16)^mac).rjust(6,'\x00')
    data += md5sum("\x01" + pswd + salt + '\x00'*4)
    data += '\x01\x31\x8c\x31\x4e' + '\00'*12
    data += md5sum(data + '\x14\x00\x07\x0b')[:8] + '\x01'+'\x00'*4
    data += host_name.ljust(71, '\x00')
    data += '\x01' + host_os.ljust(128, '\x00')
    data += '\x6d\x00\x00'+chr(len(pswd))
    data += ror(md5sum('\x03\x01'+salt+pswd), pswd)
    data += '\x02\x0c'
    data += checksum(data+'\x01\x26\x07\x11\x00\x00'+dump(mac))
    data += "\x00\x00" + dump(mac)
    return data

def login(usr, pswd, svr):
    import random
    global SALT
 
    i = 0
    while True:
        try:
            try:
              salt = challenge(svr, time.time()+random.randint(0xF,0xFF))
            except ChallengeException:
              if DEBUG:
                print 'challenge packet exception'
              continue
            SALT = salt
            packet = mkpkt(salt, usr, pswd, mac)
            sock.sendto(packet, (svr, 61440))
            data, address = sock.recvfrom(1024)
        except:
            print "[login] recvfrom timeout,retrying..."
            continue
        print '[login] packet sent.'
        if address == (svr, 61440):
            if data[0] == '\x05' and i >= 5 and UNLIMITED_RETRY == False:
              print '[login] wrong password, retried ' + str(i) +' times.'
              sys.exit(1)
            elif data[0] == '\x05':
              print "[login] wrong password."
              i = i + 1
              time.sleep(i*1.618)
            elif data[0] != '\x04':
              print "[login] server return exception.retry"
              if DEBUG:
                print '[login] last packet server returned:\n' + data.encode('hex')
              time.sleep(1)
              raise LoginException
              continue
            break
        else:
            if i >= 5 and UNLIMITED_RETRY == False :
              print '[login] packet received error, maybe you are under attacking'
              sys.exit(1)
            else:
              i = i + 1
              print '[login] package error, retrying...'
              
    print '[login] login sent'
    return data[-22:-6]

import httplib
def info(ip):
    c = httplib.HTTPConnection(ip, 80, timeout=10)
    c.request("GET", "")
    r = c.getresponse()
    if r.status != 200:
        return None
    inf = r.read()
    data = dict()
    data["flux"] = int(inf[inf.index("flow='")+6:inf.index("';fsele=")])
    data["time"] = int(inf[inf.index("time='")+6:inf.index("';flow")])
    return data

def keep_alive1(salt, tail, pswd, svr):
    foo = struct.pack('!H', int(time.time())%0xFFFF)
    data = '\xff' + md5sum('\x03\x01'+salt+pswd) + '\x00\x00\x00'
    data += tail
    data += foo + '\x00\x00\x00\x00'
    print '[keep_alive1] keep_alive1,sent'
    sock.sendto(data, (svr, 61440))
    try:
        data, address = sock.recvfrom(1024)
        print '[keep_alive1] keep_alive1,server received'
    except:
        print '[keep_alive1] Timeout!'
        pass
    
def main():
    server = "10.0.0.0"
    username = "test"
    mac = 0xffffffff 
    print "auth svr:"+server+"\nusername:"+username+"\npassword:"+"********"+"\nmac:"+str(hex(mac))
    print "os:MSDOS 8.0"+"\nhostname: localhost" 
    print "DrCOM Auth Client Ver 0.5"
    print "Author: sevenhe2015@gmail.com"
    print "Version feature:\n[1] Auto Anti droping connection\n[2] Stronger exception handling."
    """
    while True:
      try:
        package_tail = login(username, password, server)
      except LoginException:
        continue
      keep_alive2()
    """

if __name__ == "__main__":
    main()



