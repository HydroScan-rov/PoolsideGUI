# PoolsideGUI
GUI software for surface control unit

Documentation is here: https://github.com/hidronautics/PoolsideGUI_docs

## Requirements: 
 - Ubuntu 20.04 and greater
 - Qt 5.12 and greater
 - HIDAPI lib (https://github.com/libusb/hidapi)
 - SFML lib

## Install and run: 
### Linux:

`sudo apt install -y gcc g++ make git cmake cmake-gui qt5-qmake qt5-default libqt5serialport5-dev`

`sudo apt install -y libudev-dev libusb-1.0-0-dev libfox-1.6-dev autotools-dev autoconf automake libtool libsfml*`

`git clone https://github.com/libusb/hidapi.git`

`cd hidapi`

`./bootstrap`

`./configure`

`make`

`sudo make install`
