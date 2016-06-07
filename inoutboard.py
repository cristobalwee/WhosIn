###### Sourced in part from https://raw.github.com/paulbarber/raspi-gpio/master/inoutboard.py ######

###### Threading info from https://pymotw.com/2/threading/ #######

#!/usr/bin/python

import bluetooth
import time
import datetime
import threading
import logging

#logging.basicConfig(level=logging.DEBUG, format='[%(levelname)s] (%(threadName)-10s) %(message)s',)

def worker(num):
    i = num
    #logging.debug(users[i])
    print "Looking for " + users[i] + "..."
    result = bluetooth.lookup_name(bids[i], timeout = 2)
    localTime = time.strftime("%I:%M", time.localtime())
    ampm = time.strftime("%p", time.localtime()).lower()
    ret = ''
    if localTime[0] == '0':
        splitTime = localTime.split('0', 1)
        ret = splitTime[1] + ampm
    else:
        ret = localTime + ampm
    times[i] = ret
    if result != None:
        status[i] = "IN"
    else:
        status[i] = "OUT"
    #lock
    data[i] = "%s %s %s %s|\n" % (users[i], status[i], times[i], bids[i])
    #unlock
    #logging.debug('Done')
    print "Done"
    #return

users = ["user1", "user2", "user3", "user4"]
userCount = len(users)
data = [""] * userCount
status = [""] * userCount
times = [""] * userCount
bids = ['D4:F4:6F:32:B0:AF', 'C8:69:CD:6A:F2:21', '78:7E:61:52:32:2B', 'C9:69:CD:6A:D2:21']

while True:
    print "Checking " + time.strftime("%a, %d %b %Y %H:%M:%S", time.gmtime())
    localTime = time.strftime("%I:%M", time.localtime())
    ampm = time.strftime("%p", time.localtime()).lower()
    ret = ''
    if localTime[0] == '0':
        splitTime = localTime.split('0', 1)
        ret = splitTime[1] + ampm
    else:
        ret = localTime + ampm
    #print ret

    threads = []
    for i in range(userCount):
        t = threading.Thread(target=worker, args=(i,))
        threads.append(t)
        t.start()

    time.sleep(5)
    file = open("data.txt", "r+")
    text = file.read()
    arr = text.splitlines()
    newArr = [""] * userCount
    for i in range(0, userCount):
        if status[i] not in arr[i]:
            newArr[i] = data[i]
        else:
            newArr[i] = arr[i] + '\n'
    file.seek(0)
    for i in range(0, userCount):
        file.write(newArr[i])

    file.close()
    #time.sleep(2)
