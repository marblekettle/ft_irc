import socket, select
import sys
import time

PASS = 'PASS pass'
NICK = 'NICK nick'
USER = 'USER nick nduijf localhost :Nicky Duijf'
TCP_IP = '127.0.0.1'
TCP_port = 6667

def Message(msg):
	string = msg + '\r\n'
	byte_str = f'{string}'.encode()
	return (byte_str)

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((TCP_IP, TCP_port))

s.send(Message(PASS))
time.sleep(0.1)
s.send(Message(NICK))
time.sleep(0.1)
s.send(Message(USER))
time.sleep(0.1)
socket_list = [sys.stdin, s]

while 1:
    read_sockets, write_sockets, error_sockets = select.select(socket_list, [], [])
    for sock in read_sockets:
        # incoming message from remote server
        if sock == s:
            data = sock.recv(4096)
            if not data:
                print('\nDisconnected from server')
                sys.exit()
            else:
                message = data.decode()
                sys.stdout.write(message)
                sys.stdout.flush()

        else:
            msg = sys.stdin.readline()
            s.send(Message(msg[:-1]))