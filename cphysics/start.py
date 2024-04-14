#!/usr/bin/env python3
import RPi.GPIO as GPIO
import time
import subprocess, os
import signal
GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)
GPIO_switch = 24  # pin 18
GPIO.setup(GPIO_switch,GPIO.IN, pull_up_down=GPIO.PUD_UP)

print ("  Press Ctrl & C to Quit")

try:
    
   run = 0
   while True :
      if GPIO.input(GPIO_switch)==0 and run == 0:
         print ("  Started")
         rpistr = "FilePathExample; ./executable"
         p=subprocess.Popen(rpistr,shell=True, preexec_fn=os.setsid)
         run = 1
         while GPIO.input(GPIO_switch)==0:
             time.sleep(0.1)
      if GPIO.input(GPIO_switch)==0 and run == 1:
         print ("  Stopped ") 
         run = 0
         os.killpg(p.pid, signal.SIGTERM)
         while GPIO.input(GPIO_switch)==0:
             time.sleep(0.1)
       

except KeyboardInterrupt:
  print ("  Quit")
  GPIO.cleanup()
