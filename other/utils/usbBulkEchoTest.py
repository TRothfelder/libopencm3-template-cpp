#!/usr/bin/python

import usb.core
import usb.util
import usb.control
import time
import sys

# find our device
dev = usb.core.find(idVendor=0x16c0, idProduct=0x05dc)

# was it found?
if dev is None:
    print('Device not found')
    sys.exit(1)

# set the active configuration. With no arguments, the first
# configuration will be the active one
dev.set_configuration()

# get an endpoint instance
cfg = dev.get_active_configuration()
intf = cfg[(0,0)]
timeout = 100

epOut = usb.util.find_descriptor(
    intf,
    # match the first OUT endpoint
    custom_match = \
    lambda e: \
        usb.util.endpoint_direction(e.bEndpointAddress) == \
        usb.util.ENDPOINT_OUT)

epIn = usb.util.find_descriptor(
    intf,
    # match the first OUT endpoint
    custom_match = \
    lambda e: \
        usb.util.endpoint_direction(e.bEndpointAddress) == \
        usb.util.ENDPOINT_IN)

assert epOut is not None
assert epIn is not None

count = 1
countMax = 5
while (count <= countMax):
    # write the data
    print("Set LED on")
    dev.ctrl_transfer( 0x40,
    	3,
    	1,	          	# wValue (LED on)
    	0, 	         	# wIndex
    	None)           # No Data

    writeData = "TestTestTestTestTestTestTestTestTestTestTestTestTestTestTestTestTestTestTestTestTestTestTestTestTestTestTest"
    print("Write data:\"" + writeData + "\"" + "\tLength: " + str(len(writeData)))
    epOut.write(writeData, timeout)

    readLength = 0
    while (True):
        try:
            readData = epIn.read(epIn.wMaxPacketSize, timeout);
            print("Read data: " + "".join(map(chr, readData)) + "\tLength: " + str(len(readData)))
            readLength += len(readData)
        except usb.core.USBError as e:
            readData = None
            #print(e.args[1])
            if e.args == (110, 'Operation timed out'):
                break

    print("Set LED off")
    dev.ctrl_transfer( 0x40,
    	3,
    	0,	          	# wValue (LED off)
    	0, 	         	# wIndex
    	None)           # No Data

    print("Sent " + str(len(writeData)) + " bytes of data.")
    print("Received " + str(readLength) + " bytes of data.")
    if (count < countMax):
        print("")
    count += 1
