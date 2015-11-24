#!/usr/bin/env python
# -*- coding: utf-8 -*-

import sys, time
import random
from socket import *

NETCONSOLE_PORT = 6666

sock = socket(AF_INET, SOCK_DGRAM)
sock.bind(('', 0))
sock.setsockopt(SOL_SOCKET, SO_BROADCAST, 1)

levels = ['ERROR', 'WARN', 'INFO']
sources = ['Robot', 'Subsystem', 'CommandOne', 'CommandTwo']
start_time = time.clock()


def send_log(msg, level='INFO', source='Robot'):
    timestamp = time.clock() - start_time
    data = '{} [{}] {} - {}\n'.format(timestamp, level, source, msg)
    sock.sendto(bytes(data, 'utf-8'), ('<broadcast>', NETCONSOLE_PORT))

send_log('Starting log test...', level='START')

try:
    while True:
        send_log('hello world', level=random.choice(levels), source=random.choice(sources))
        time.sleep(.2)
except KeyboardInterrupt:
    print('exiting...')
    send_log('Exiting log test...', level='STATE')
