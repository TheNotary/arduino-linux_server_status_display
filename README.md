## Linux Server Status Display

This project displays the status of services running on a linux machine.  You can turn off bandwidth consuming services with buttons!  And you can turn them back on too!  

## Parts

LCD Display

ENC28J60 - Network module with SPI interface (ebay) (HR911105A?)

Arduino Uno - Microcontroller

~12v DC @ 1amp power adapter

Ethernet cable

A standard, run of the mill, home ethernet network.

Computer that can ping and has a web browser

## Wiring

### Ethernet Board

The board to board interface used is SPI, utilizing 6 wires including ground.  

(Ethernet Pins - Yours may differ)
```
pin 1: CLK
pin 2: INT
pin 3: WOL
pin 4: SO
pin 5: SI
pin 6: SCK
pin 7: CS
pin 8: RST
pin 9:  VCC (3 or 5v)
pin 10: GND
```

(Arduino Uno Pins)
[Arduino Uno Pins](http://www.electroschematics.com/wp-content/uploads/2013/01/Arduino-Uno-R3-Pinouts.png)

(Ethernet -> Arduino Uno)
```
SO  -> pin 12
SI  -> pin 11
SCK -> pin 13
CS  -> pin 8
VCC -> 3.3v
GND -> GND
```

### LCD Display

(LCD Pins (says J204A on back... HDsomething... they're all the same I guess...))
```
#1:  vss
#2:  vdd
#3:  v0
#4:  rs
#5:  rw
#6:  e
#7:  d0
#8:  d1
#9:  d2
#10: d3
#11: d4
#12: d5
#13: d6
#14: d7
#15: a (backlight 5v)
#16: k (backlight gnd)
```

(LCD -> Arduino)
```
vss -> GND
vdd -> 5v
v0  -> ((POT middle pin))
rs  -> pin 10
rw  -> GND
e   -> pin 9
.
.
.
d4  -> pin 5
d5  -> pin 4
d6  -> pin 3
d7  -> pin 2
a   -> 5v
k   -> GND
```




## To Deploy

Notice this code utilizes the ether_card library.  

    $ git clone https://github.com/TheNotary/ether_test
    $ cd ether_test
    # modify src/ether_test.ino so IP Address works on home network
    # connect Arduino Uno to dev machine
    $ platformio run

    # Unplug Arduino Uno from dev machine
    # Plug Arduino into home network
    # Power the Arduino Uno


## Device Operation

When the device is powered up, and plugged into an ethernet network, it will be pingable form another computer on the same subnet (192.168.0.0/24).  If you can ping, you should also be able to type it's IP address into a web browser and see the html that's been hardcoded into the source code.  

    # ping 192.168.0.200
    # do http get request to address


## Resources

[tut](http://nathanhein.com/2013/02/getting-arduino-online-with-an-enc28j60/)

