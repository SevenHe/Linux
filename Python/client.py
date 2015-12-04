#!/usr/bin/python
import socket, struct, time, random
from hashlib import md5
import sys, re
import multiprocessing
import urllib2
import logging     # for real

# for development debug
import cgitb
import traceback

# To-do list:
#       optimize the code: the structure.
#       prompt: do not make the passwd literal and let users specify the different args.
#       translatable;
#       check: if the port is in use, just change it or make use to specify it manually; more stronger 
#              exception handles.
#       addition: get the time and flow from site; save the information as encrypted
#
#   final test: the window OS or other platform test;
#                and the GUI to be added.
#
# ~~~~~Asynchronized socket----asyncore????~~~~~~~
#configure the encrypted rules when not logging in , in the html file.
#to close the socket and get the information of the httpconnection.

# Features
UNLIMITED_RETRY = True
EXCEPTION = False
DEBUG = True
SALT = ''

runner = logging.getLogger('Executor')
checker = logging.getLogger('Checker')

class ChallengeException (Exception):
  def __init__(self):
    pass

class LoginException (Exception):
  def __init__(self):
    pass
   
import os
import atexit
class Client:
    def __init__(self):
        self._sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        #self._sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        self._sock.bind(("0.0.0.0", 61440))
        
        self._sock.settimeout(3)
        self._svr = "10.100.61.3" # "auth.jlu.edu.cn"
        self._svr_port = 61440
        self._username = "hech5513"
        self._password = "010178"
        self._host_name = "SEVEN"
        self._host_os = "Kubuntu"
        self._mac = 0xC454442B84C5
        self._client = '/tmp/drcom-daemon.pid'

        self.formatter = logging.Formatter("%(levelname)s - %(name)s: %(message)s")
        self.streamHandler = logging.StreamHandler()

    def _challenge(self, ran):
        # a server test after successing in connection.
        while True:
            t = struct.pack("<H", int(ran)%(0xFFFF))
            self._sock.sendto("\x01\x02"+t+"\x09"+"\x00"*15, (self._svr, self._svr_port))
            try:
                data, address = self._sock.recvfrom(1024)
            except:
                if DEBUG:
                    print '[challenge] timeout, retrying...'
                continue
        
            if address == (self._svr, self._svr_port):
                break
            else:
                continue
        if DEBUG:
            print '[DEBUG] challenge:\n' + data.encode('hex')
            print 'random seed:', str(ran) 
        if data[0] != '\x02':
            raise ChallengeException
        print '[challenge] challenge packet sent.'
        return data[4:8]

    # encrypted flows.
    # very restricted way that you do not need to know.
    def _md5sum(self, msg):
        m = md5()
        m.update(msg)
        return m.digest()
            
    # change it into a ordinal character.
    # and fill the odd bits.
    def _dump(self, n):
        dump_str = '%x' % n
        if len(dump_str) & 1:
            dump_str = '0' + dump_str
        return dump_str.decode('hex')

    # encrypted the pswd with md5.
    def _ror(self, md5):
        pswd = self._password
        ret = [(ord(md5[i]) ^ ord(pswd[i])) for i in range(len(pswd))]
        return ''.join(map(lambda x:chr(((x<<3)&0xFF) + (x>>5)), ret))
        """
        # deprecated
        ret = ''
        for i in range(len(pswd)):
            x = ord(md5[i]) ^ ord(pswd[i])
            ret += chr(((x<<3)&0xFF) + (x>>5))
        return ret
        """
            
    # build the packet.
    # just for user send operation.
    def _keep_alive_package_builder(self, number, random, tail, type=1, first=False):
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
            crc = self._packet_CRC(data+foo)
            data += struct.pack("!I",crc) + foo + '\x00' * 8
        else: #packet type = 1
            data += '\x00' * 16
        return data

    # two bit represents a hexadecimal digit.
    # This place can be simplified.
    def _packet_CRC(self, raw):
        ret = 0
        for i in re.findall('..', raw):
            ret ^= struct.unpack('>h', i)[0]
            ret &= 0xFFFF
        ret = ret * 0x2c7
        return ret

    def _keep_alive2(self):
        #first keep_alive:
        #number = number (mod 7)
        #status = 1: first packet user sended
        #         2: first packet user recieved
        #         3: 2nd packet user sended
        #         4: 2nd packet user recieved
        #   Codes for test
        # a recv after a send.
        tail = ''
        packet = ''
        svr = self._svr
        ran = random.randint(1, 0xFFFF + 10)
# ~~TO-DO~~ compact the duplicate code into a method to get better feeling.
        packet = self._keep_alive_package_builder(0, self._dump(ran), '\x00'*4, 1, True)
        self._sock.sendto(packet, (svr, self._svr_port))
        data, address = self._sock.recvfrom(1024)
        
        ran += random.randint(1, 10)   
        packet = self._keep_alive_package_builder(1, self._dump(ran), '\x00'*4, 1, False)
        self._sock.sendto(packet, (svr, self._svr_port))
        data, address = self._sock.recvfrom(1024)
        tail = data[16:20]
        
        
        ran += random.randint(1, 10)   
        packet = self._keep_alive_package_builder(2, self._dump(ran), tail, 3, False)
        self._sock.sendto(packet, (svr, self._svr_port))
        data, address = self._sock.recvfrom(1024)
        tail = data[16:20]
        print "[keep-alive2] keep-alive2 loop was in daemon."
        
        i = 1
        # ~~TO-DO~~ cut the codes.
        while True:
            try:
                time.sleep(5)
                ran += random.randint(1,10)   
                packet = self._keep_alive_package_builder(2, self._dump(ran), tail, 1, False)
                #print 'DEBUG: keep_alive2,packet 4\n',packet.encode('hex')
                self._sock.sendto(packet, (svr, self._svr_port))
                data, address = self._sock.recvfrom(1024)
                tail = data[16:20]
                #print 'DEBUG: keep_alive2,packet 4 return\n',data.encode('hex')
        
                ran += random.randint(1,10)   
                packet = self._keep_alive_package_builder(2, self._dump(ran), tail, 3, False)
                #print 'DEBUG: keep_alive2,packet 5\n',packet.encode('hex')
                self._sock.sendto(packet, (svr, self._svr_port))
                data, address = self._sock.recvfrom(1024)
                tail = data[16:20]
                #print 'DEBUG: keep_alive2,packet 5 return\n',data.encode('hex')
                i = i+1
                i = i % (0xFF)
        
                # ~~TO-DO~~ this can be optimized to adjust the relogin process.
                check_online = urllib2.urlopen('http://10.100.61.3')
                foo = check_online.read()
                if 'login.jlu.edu.cn' in foo:
                    print '[keep_alive] offline.relogin...'
                    break
                #MODIFIED END
                """ 
                if i % 10 == 0:
                check_online = urllib2.urlopen('http://10.100.61.3')
                foo = check_online.read()
                if 'login.jlu.edu.cn' in foo:
                print '[keep_alive] offline.relogin...'
                break;
                """
            except:
                pass
        
    
    def _checksum(self, s):
        ret = 1234
        for i in re.findall('....', s):
            ret ^= int(i[::-1].encode('hex'), 16)
        ret = (1968 * ret) & 0xffffffff
        return struct.pack('<I', ret)
        """
        import binascii
        binascii.b2a_hex(i[::-1])
        """

    # take care of your args!
    def _mkpkt(self, SALT):
        data = '\x03\01\x00'+chr(len(self._username)+20)
        data += self._md5sum('\x03\x01'+SALT+self._password)
        data += self._username.ljust(36, '\x00')
        data += '\x00\x00'
        data += self._dump(int(data[4:10].encode('hex'),16)^self._mac).rjust(6,'\x00')
        data += self._md5sum("\x01" + self._password + SALT+ '\x00'*4)
        data += '\x01\x31\x8c\x31\x4e' + '\00'*12
        data += self._md5sum(data + '\x14\x00\x07\x0b')[:8] + '\x01'+'\x00'*4
        data += self._host_name.ljust(71, '\x00')
        data += '\x01' + self._host_os.ljust(128, '\x00')
        data += '\x6d\x00\x00'+chr(len(self._password))
        data += self._ror(self._md5sum('\x03\x01'+SALT+self._password))
        data += '\x02\x0c'
        data += self._checksum(data+'\x01\x26\x07\x11\x00\x00'+self._dump(self._mac))
        data += "\x00\x00" + self._dump(self._mac)
        return data

    # ~~TO-DO~~ optimize the codes.
    def _login(self):
        global SALT
 
        i = 0
        while True:
            try:
                try:
                    SALT = self._challenge(time.time()+random.randint(0xF, 0xFF))
                except ChallengeException:
                    if DEBUG:
                        print 'challenge packet exception'
                    continue
                print '[INFO]: make client packets.'
                packet = self._mkpkt(SALT)
                self._sock.sendto(packet, (self._svr, self._svr_port))
                data, address = self._sock.recvfrom(1024)
            except:
                print "[login] recvfrom timeout,retrying..."
                traceback.print_exc() 
                continue
            print '[login] packet sent.'
            if address == (self._svr, self._svr_port):
                if data[0] == '\x05' and i >= 5 and UNLIMITED_RETRY == False:
                    print '[login] wrong password, retried ' + str(i) +' times.'
                    sys.exit(1)
                elif data[0] == '\x05' and i < 5:
                    print "[login] wrong password."
                    i = i + 1
                    time.sleep(i*1.555)
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

    # Deprecated
    def _keep_alive1(self, tail):
        foo = struct.pack('!H', int(time.time())%0xFFFF)
        data = '\xff' + self_md5sum('\x03\x01'+SALT+self._password) + '\x00\x00\x00'
        data += tail
        data += foo + '\x00\x00\x00\x00'
        print '[keep_alive1] keep_alive1,sent'
        self._sock.sendto(data, (svr, self._svr_port))
        try:
            data, address = self._sock.recvfrom(1024)
            print '[keep_alive1] keep_alive1,server received'
        except:
            print '[keep_alive1] Timeout!'
            pass

    def _daemonize(self):
        try:
            pid = os.fork()
            if pid > 0:
                return 1 
        except OSError:
            runner.error('Start the DrCOM daemon client failed.')
            sys.exit(1)
        else:
            # Configure the child processes environment
            os.chdir("/")
            os.setsid()
            os.umask(0)

        try:
            pid = os.fork()
            if self._client > 0:
                return 1
        except OSError:
            runner.error('Start the DrCOM daemon client failed.')
            sys.exit(1)

        #There should be some redirections ,likewise some logs.

        # The reason does not close the file is that it will be removed at the end.
        atexit.register(self._delpid)
        pid = str(os.getpid())
        file(self._client, 'w+').write("%s\n" % pid)

    def _run(self):
# can add some handler or log code into the method or place here.
        while True:
            try:
                package_tail = self._login()
            except LoginException:
                continue
            self._keep_alive2()

    def _delpid(self):
        os.remove(self._client)

    # Get the accoutn information for further features
    import httplib
    def info(self):
        c = httplib.HTTPConnection(self._svr, 80, timeout=10)
        c.request("GET", "")
        r = c.getresponse()
        if r.status != 200:
            return None
        inf = r.read()
        account_data = dict()
        account_data["flux"] = int(inf[inf.index("flow='")+6:inf.index("';fsele=")])
        account_data["time"] = int(inf[inf.index("time='")+6:inf.index("';flow")])
        return account_data

    # The further feature is to use the 'spawnl()' for the Windows OS.
    def start(self):
        self.streamHandler.setFormatter(self.formatter)
        runner.addHandler(self.streamHandler)
        try:
            pf = file(self._client, 'r')
            pid = int(pf.read().strip())
            pf.close()
        except IOError:
            pid = None
        
        if not pid:
           runner.warn("Pid file %s already exists, Daemon already running?\nYou may want to use 'check' option." % self._client)
           return 2

        self._daemonize()
        self._run()

        """
        # Deprecated
        self._client = multiprocessing.Process(name="DrCOM Client", target=self._keep_alive)
        self._client.daemon = True
        self._client.start()
        """

    def stop(self):
        pass

    # Thers is no " con ? .. : .." in python.
    def check(self):
        self.streamHandler.setFormatter(self.formatter)
        checker.addHandler(self.streamHandler)
        checker.debug('Check is starting...')
        try:
            pf = file(self._client, 'r')
            pid = int(pf.read().strip)
            pf.close()
        except IOError:
            pid = None

        if pid:
            checker.warn('You have not started the client.')
            return 12
        else:
            checker.info("Daemon pid:", pid)
            checker.info("Daemon status:", 'Running' if os.kill(pid, 0) else 'Deactived')
            return 11
            
    # write configs to a hidden file for startup with no logging in.
    def config(self):
        pass

    # print useful information about account and server.
    def print_info(self):
        print "Connect to the server:", self._svr, "..."

# import select -- asychronized socket.
# threading.create(client.keep_alive())??
"""
def main():
    client = Client()
    client.print_info()
    while True:
        try:
            package_tail = client.login()
        except LoginException:
            continue
        client.keep_alive()


if __name__ == "__main__":
    cgitb.enable(format="text")
    main()
"""

""" 
    def stop(self):
    # Get the pid from the pidfile
    try:
    pf = file(self.pidfile,'r')
    pid = int(pf.read().strip())
    pf.close()
    except IOError:
    pid = None
    
    if not pid:
    message = "pidfile %s does not exist. Daemon not running?\n"
    sys.stderr.write(message % self.pidfile)
    return # not an error in a restart
    
    # Try killing the daemon process       
    try:
    while 1:
    os.kill(pid, SIGTERM)
    time.sleep(0.1)
    except OSError, err:
    err = str(err)
    if err.find("No such process") > 0:
    if os.path.exists(self.pidfile):
    os.remove(self.pidfile)
    else:
    print str(err)
    sys.exit(1)
    
    def restart(self):
    self.stop()
    self.start()
"""
