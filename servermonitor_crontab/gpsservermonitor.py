#!/usr/bin/python
# -*- coding:utf-8 -*-

import sys
import re
import urllib2
import json
import time
import subprocess

reload(sys)
sys.setdefaultencoding('utf8')


def gps_server_open(test_number, error_number, url, url_timeout=10):
    if (test_number is None) or (error_number is None) or (url is None):
        print 'input argument error.'
        return -1

    test_count = error_count = 0
    while test_count < test_number and error_count < error_number:
        test_count += 1
        print time.time()
        try:
            fl = urllib2.urlopen(url, timeout=url_timeout)
            res = fl.readline()
            print res
        except Exception, e:
            error_count += 1
            print e
        print time.time()

    if test_count >= test_number:
        #ok
        return 0
    else:
        #fail
        return -2


def gps_server_reboot():
    #subprocess.call('bash /home/work/dev/build/city_server/run.sh', shell=True)
    subprocess.call('echo `date` >> /home/zh/gpstest/bb.txt', shell=True)

def gps_server_monitor():
    #url_svr = 'http://172.17.0.2:18079/city?la=31.22&lo=121.48'
    url_svr = 'http://localhost:18079/city?la=31.22&lo=121.48'
    #url_svr = 'http://localhost:18100/city?la=31.22&lo=121.48'
    ret_err = gps_server_open(20, 10, url_svr, 6)
    if ret_err != 0:
        print 'reboot start.'
        gps_server_reboot()
        print 'reboot end.'

    else:
        print 'OK,no boot'


if __name__ == '__main__':
    print 'main start.'
    gps_server_monitor()
    print 'main end.'
