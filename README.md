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

When the device is powered up, and plugged into an ethernet network, it will put it's IP as 192.168.0.200.  
  
Display:
  * The LCD will display will state "Cannot See Server" if it can't access the specified server with the associated service running.  

  Alternatively...

  * The LCD will display "Service x on" 

When button 0 is pressed, it will send a signal to the server to stop the service.  The display will read "Disabling service x..." and eventual report "Service x off"

When button 1 is pressed, it will send a signal to the server to query the internet to check that it's still got network connectivity.  

You can add more buttons and modify the service code easily!  But it's in another repo and written in a higher level language for obvious reasons :)

## Resources

[tut on ethernet](http://nathanhein.com/2013/02/getting-arduino-online-with-an-enc28j60/)


