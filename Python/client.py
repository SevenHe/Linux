#!/usr/bin/python
"""
The core program in the client
"""

import socket, struct, time, random
from hashlib import *
import sys, re
#import multiprocessing
import urllib2
import logging     # for real

# for development debug
# import cgitb
import traceback

# To-do list:
#   optimize the code: the structure.
#   prompt: do not make the passwd literal and let users specify the
#            different args.
#   translatable;
#   check: if the port is in use, just change it or make use to specify it
#           manually; more stronger exception handles.
#   addition: get the time and flow from site; save the information as encrypted
#           maybe need to redirect the std descriptors
#   check updates.
#   there are also some bugs in the log level, it is not resolved for now.
#
#   final test: the window OS or other platform test;
#                and the GUI to be added.
#
# ~~~~~Asynchronized socket----asyncore????~~~~~~~
#configure the encrypted rules when not logging in , in the html file.
#to close the socket and get the information of the httpconnection.

# Features
UNLIMITED_RETRY = True
DEBUG = False 
SALT = ''

# Specified the place.
# some log settings.
LOGFILE = '/tmp/.dclogs'
CONFILE = './.client-conf'
RUNNER = logging.getLogger('Executor')
DEBUGGER = logging.getLogger('Debugger')
CHECKER = logging.getLogger('Checker')
FORMATTER = logging.Formatter("%(levelname)s - %(name)s: %(message)s")
StreamHandler = logging.StreamHandler()
StreamHandler.setLevel(logging.NOTSET)
StreamHandler.setFormatter(FORMATTER)
DEBUGGER.addHandler(StreamHandler)

class ChallengeException(Exception):
    """
    Send challenge exception.
    To be filled.
    """
    def __init__(self):
        pass

class LoginException(Exception):
    """
    The login exception.
    Also to be continued.
    """
    def __init__(self):
        pass

import os
import atexit
class Client:
    """
    DrCOM Client
    """
    def __init__(self):
        self._sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        #self._sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)

        self._sock.settimeout(3)
        self._svr = "10.100.61.3" # "auth.jlu.edu.cn"
        self._svr_port = 61440
        self._username = ""
        self._password = ""
        self._mac = None
        self._client = '/tmp/drcom-daemon.pid'
        self.host_name = ""
        self.host_os = ""

    @property
    def mac(self):
        return int(self._mac)

    @mac.setter
    def mac(self, value):
        if isinstance(value, int):
            if value > 0:
                self._mac = value
            else:
                raise ValueError('Mac is invalid, check it on the "ip.jlu.edu.cn".')
        else:
            raise TypeError('Mac must be a hexadecimal integer.')

    def _challenge(self, ran):
        # a server test after successing in connection.
        while True:
            t = struct.pack("<H", int(ran)%(0xFFFF))
            self._sock.sendto("\x01\x02"+t+"\x09"+"\x00"*15, (self._svr, self._svr_port))
            try:
                data, address = self._sock.recvfrom(1024)
            except:
                if DEBUG:
                    print '[CHALLENGE] Timeout, retrying...'
                continue

            if address == (self._svr, self._svr_port):
                break
            else:
                continue
        if DEBUG:
            print '[DEBUG] Challenge:\n' + data.encode('hex')
            print 'Random seed:', str(ran)
        if data[0] != '\x02':
            raise ChallengeException
        print '[CHALLENGE] Challenge packet sent.'
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
    # Deprecated
    ret = ''
    for i in range(len(pswd)):
        x = ord(md5[i]) ^ ord(pswd[i])
        ret += chr(((x<<3)&0xFF) + (x>>5))
    return ret
    """
            
    # build the packet.
    # just for user send operation.
    def _daemon_packet_poster(self, number, random, tail, type=1, first=False):
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
        self._sock.sendto(data, (self._svr, self._svr_port))
        dgram, address = self._sock.recvfrom(1024)
        return dgram[16:20]

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
        tail = self._daemon_packet_poster(0, self._dump(ran), '\x00'*4, 1, True)
        
        ran += random.randint(1, 10)   
        tail = self._daemon_packet_poster(1, self._dump(ran), '\x00'*4, 1, False)
        
        
        ran += random.randint(1, 10)   
        tail = self._daemon_packet_poster(2, self._dump(ran), tail, 3, False)
        #print "[keep-alive2] keep-alive2 loop was in daemon."
        
        i = 1
        while True:
            try:
                time.sleep(5)
                ran += random.randint(1,10)   
                tail = self._daemon_packet_poster(2, self._dump(ran), tail, 1, False)
                #print 'DEBUG: keep_alive2,packet 4 return\n',data.encode('hex')
        
                ran += random.randint(1,10)   
                tail = self._daemon_packet_poster(2, self._dump(ran), tail, 3, False)
                #print 'DEBUG: keep_alive2,packet 5\n',packet.encode('hex')

                i = i+1
                i = i % (0xFF)
        
                # ~~TO-DO~~ this can be optimized to adjust the relogin process.
                check_online = urllib2.urlopen('http://10.100.61.3')
                foo = check_online.read()
                if 'login.jlu.edu.cn' in foo:
                    print '[LOGIN] Offline.relogin...'
                    break
                #MODIFIED END
            except:
                pass
    """ 
    if i % 10 == 0:
        check_online = urllib2.urlopen('http://10.100.61.3')
    foo = check_online.read()
    if 'login.jlu.edu.cn' in foo:
        print '[keep_alive] offline.relogin...'
    break;
    """
        
    
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
        data += self._dump(int(data[4:10].encode('hex'),16)^self.mac).rjust(6,'\x00')
        data += self._md5sum("\x01" + self._password + SALT+ '\x00'*4)
        data += '\x01\x31\x8c\x31\x4e' + '\00'*12
        data += self._md5sum(data + '\x14\x00\x07\x0b')[:8] + '\x01'+'\x00'*4
        data += self.host_name.ljust(71, '\x00')
        data += '\x01' + self.host_os.ljust(128, '\x00')
        data += '\x6d\x00\x00'+chr(len(self._password))
        data += self._ror(self._md5sum('\x03\x01'+SALT+self._password))
        data += '\x02\x0c'
        data += self._checksum(data+'\x01\x26\x07\x11\x00\x00'+self._dump(self.mac))
        data += "\x00\x00" + self._dump(self.mac)
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
                print '[INFO] Make client packets.'
                packet = self._mkpkt(SALT)
                self._sock.sendto(packet, (self._svr, self._svr_port))
                data, address = self._sock.recvfrom(1024)
            except:
                print "[LOGIN] recvfrom timeout,retrying..."
                traceback.print_exc() 
                continue
            print '[LOGIN] Packet sent.'
            if address == (self._svr, self._svr_port):
                if data[0] == '\x05' and i >= 5 and UNLIMITED_RETRY == False:
                    print '[LOGIN] Wrong password, retried ' + str(i) +' times.'
                    sys.exit(1)
                elif data[0] == '\x05' and i < 5:
                    print "[LOGIN] Wrong password.", self._password
                    i = i + 1
                    time.sleep(i*1.555)
                elif data[0] != '\x04':
                    print "[LOGIN] Server return exception.retry"
                    if DEBUG:
                        print '[LOGIN] Last packet server returned:\n' + data.encode('hex')
                    time.sleep(1)
                    raise LoginException
                    continue
                break
            else:
                if i >= 5 and UNLIMITED_RETRY == False :
                    print '[LOGIN] Packet received error, maybe you are under attacking'
                    sys.exit(1)
                else:
                    i = i + 1
                    print '[LOGIN] Package error, retrying...'
              
        print '[LOGIN] Connection has been established, enjoy!!'
        # To avoid the broken up outputs.
        self._daemonize()
        return data[-22:-6]

    # Deprecated
    def _keep_alive1(self, tail):
        foo = struct.pack('!H', int(time.time())%0xFFFF)
        data = '\xff' + self._md5sum('\x03\x01'+SALT+self._password) + '\x00\x00\x00'
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
                # Exit the first parent process to replace with a child.
                sys.exit(0)
        except OSError:
            RUNNER.error('Start the DrCOM daemon client failed.')
            sys.exit(1)
        else:
            # Configure the child processes environment
            os.chdir("/")
            os.setsid()
            os.umask(0)

        # Second process to indicate it is not a leader.
        try:
            pid = os.fork()
            if pid > 0:
                RUNNER.info('Parent pid is %d', pid)
                sys.exit(0)
        except OSError:
            RUNNER.error('Start the DrCOM daemon client failed.')
            sys.exit(1)

        #There should be some redirections ,likewise some logs.

        # The reason does not close the file is that it will be removed at the end.
        atexit.register(self._delpid)
        pid = str(os.getpid())
        with open(self._client, 'w+') as pf:
            pf.write("%s\n" % pid)

    def _run(self):
# can add some handler or log code into this method or place here.
        try:
            self._sock.bind(("0.0.0.0", 61440))
        except:
            DEBUGGER.debug(sys.exc_info())
            return 3
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

    # 3 for debug
    def put2log(self, msg, level=3):
        # A fragmentary config will be dismissed.  
        # logging.basicConfig(filename=LOGFILE, filemode='a+')
        if level == 3:
            DEBUGGER.debug(msg)

    # The further feature is to use the 'spawnl()' for the Windows OS.
    def start(self):
        StreamHandler.setFormatter(FORMATTER)
        RUNNER.addHandler(StreamHandler)
        try:
            pf = open(self._client, 'r')
            pid = int(pf.read().strip())
            pf.close()
        except IOError:
            pid = None
        
        if pid:
            RUNNER.warn("Pid file %s already exists, Daemon already running?\nYou may want to use 'check' option." % self._client)
            return 2
        else:
            self.print_version_info()
            self.config()
            print "[START] Connect to the server:", self._svr, "..."
        
        self._run()

    """
    # Deprecated
    self._client = multiprocessing.Process(name="DrCOM Client", target=self._keep_alive)
    self._client.daemon = True
    self._client.start()
    """

    def stop(self):
        # Get the pid from the pidfile
        print "[MSG] Stop operation starts......"
        try:
            pf = open(self._client,'r')
            pid = int(pf.read().strip())
            pf.close()
        except IOError:
            pid = None

        # For daemon's not starting, but figure out which is starting or restarting.
        if not pid:
            DEBUGGER.warn('Pid file does not exists, is it running?')
            return 4

        # Try killing the daemon process       
        import signal
        try:
            while 1:
                os.kill(pid, signal.SIGTERM)
                time.sleep(1)
        except OSError, err:
            err = str(err)
            if err.find("No such process") > 0:
                if os.path.exists(self._client):
                    os.remove(self._client)
            else:
                DEBUGGER.error(str(err)) 
        return 5

    # Thers is no " con ? .. : .." in python.
    # The check procedure need to be more accurate.
    # Set level to make it available.
    # --TO-DO~~~ to change the config.
    def check(self):
        CHECKER.setLevel(logging.DEBUG)
        CHECKER.addHandler(StreamHandler)
        CHECKER.debug('Check is starting...')
        CHECKER.debug('Check configuration...')
        try:
            with open(CONFILE, 'rb') as conf:
                users = conf.read().strip().decode('hex').split(',')
                if len(users) < 5:
                    CHECKER.debug('The config file is broken, just delete it and recreate it.')
                    return 12
                else:
                    CHECKER.debug('The config file is ok, next check the process...')
        except IOError:
            CHECKER.warn('You may get into the directory where the client file exists.')
        try:
            pf = file(self._client, 'r')
            pid = int(pf.read().strip())
            pf.close()
        except IOError:
            pid = None

        if not pid:
            CHECKER.warn('You have not started the client, or maybe you have killed the process but the server would reject your connection after a few minutes.')
            return 12
        else:
            import subprocess
            DEVNULL =  open(os.devnull, 'w')
            CHECKER.info("Daemon pid: %d" % pid)
            status = 'Running' if not subprocess.call("lsof " + "-i:61440", shell=True, stdout=DEVNULL) else 'Deactived'
            CHECKER.info("Daemon status: %s" % status)
            return 11

    # For startu up configuration!
    def startup():
        pass
            
    # write configs to a hidden file for startup with no logging in.
    def config(self):
        if os.path.exists(CONFILE):
            print "[CONFIG] Load from file..."
            try:
                with open(CONFILE, 'rb') as conf:
                    users = conf.read().strip().decode('hex').split(',')
                    self._username = users[0]
                    self._password = users[1]
                    self.mac = int(users[2])
                    self.host_os = users[3]
                    self.host_name = users[4]
            except:
                print "[CONFIG] Loading failed, please use 'check' option to determine whether it is ok or not"
                sys.exit(1)
            else:
                print "[CONFIG] Loading is OK."
        else:
            import getpass
            print "[CONFIG] This is your first use, you need to input your information for a connection to the server."
            try:
                self._username = raw_input("Your Account:")
                self._password = getpass.getpass("Your Password[JUST INPUT]:")
                self.mac= int(raw_input("MAC[JUST LIKE:FFFF...]:"), 16)
                self.host_os = raw_input("Host OS[WHATEVER YOU LIKE]:")
                self.host_name = raw_input("Host Name[LIKE ABOVE]:")
                CONFILE = os.path.abspath(CONFILE)
                with open(CONFILE, 'wb+') as conf:
                    conf.write((self._username + '\x2c' + self._password + '\x2c' + str(self.mac) + '\x2c'
                            + self.host_os + '\x2c' + self.host_name).encode('hex'))
            except:
                traceback.print_exc()
                print "[CONFIG] Failed" 
                sys.exit(1)
            else:
                print "[CONFIG] Completed, processing..."
                time.sleep(2)

    # print useful information about account and server.
    def print_version_info(self):
        print "JLU DrCOM Client - - Version 0.9 "
        print "CREATOR - - Seven(sevenhe2015@gmail.com)"

# import select -- asychronized socket.
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

