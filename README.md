

STM32F4 sample code 
===================
1. hello world
2. reading external accelerometer (ADXL345)
3. adopting external button 


OS version 
==========
```
Distributor ID:IDUbuntu
Description:DescriptionUbuntu 14.04.1 LTS
Release:Release14.04
Codename:Codenametrusty
```

Pre-Build 
=========

* [OpenOCD](http://openocd.sourceforge.net/)
```
    $ git clone git://git.code.sf.net/p/openocd/code openocd
    $ cd openocd
    $ ./bootstrap
    $ ./configure --prefix=/usr/local \
        --enable-stlink
    $ echo -e "all:\ninstall:" > doc/Makefile
    $ make
    $ sudo make install
```
* [GNU Tools for ARM Embedded Processors](https://launchpad.net/gcc-arm-embedded)
```
    $ wget -c -nH -np -m -N -nd -P /tmp https://launchpad.net/gcc-arm-embedded/4.8/4.8-2014-q1-update/+download/gcc-arm-none-eabi-4_8-2014q1-20140314-linux.tar.bz2
    (md5: 72b0d06ae16b303c25fd70b2883d3950)
    $ tar -jxf /tmp/gcc-arm-none-eabi-4_8-2014q1-2014-314-linux.tar.bz2 -C /usr/local && rm /tmp/gcc-arm-none-eabi-4_8-2014q1-20140314-linux.tar.bz

```

If you encounter the problems of missing packages, try to execute the following commands in advance:

```
    $ sudo add-apt-repository ppa:terry.guo/gcc-arm-embedded
    $ sudo apt-get update
```

* [Libraries with prefix TM](https://stm32f4-discovery.com)

* [Makefile was modified from jserv](wiki.csie.ncku.edu.tw)

Make 
====

Make sure your device is plug in the usb
For the seek of convenient, the library needed for single project is contained in each directory
Attension: stub.c is included in adxl345 directory

```
    $ cd /[dir you want]
    $ make && make flash
```

If usart reading is needed..

```
    screen /dev/ttyUSB0 15200 8n1
    (15200 baud, 8-bits per character, no parity, and 1 stop bit)
```
