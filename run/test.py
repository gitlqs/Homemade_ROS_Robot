#!/usr/bin/python2
import os
import sys
import time


def prepare():
    os.system('sudo chmod 666 /dev/ttyACM0')
    os.system('sudo chmod 666 /dev/ttyUSB0')
    

def roscore():
    os.system('gnome-terminal -- /bin/bash -c \'roscore\'')

def bringup():
    os.system('gnome-terminal -- /bin/bash -c \'./sequence/bringup.sh\'')

if __name__ == '__main__':
    prepare()
    roscore()
    time.sleep(5)
    bringup()
