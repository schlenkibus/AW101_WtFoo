# AW 101 Framework

Modular Synthesizer Executable Example and signal processing library + port audio wrapper



Playground features: 

modular signal processing

real time edit and playback

audio output

dynamic web interface

hardware abstraction layer

- IODevice (ESP8266)



## Install

These instructions are basic; you can use any method to do this work. The important part is making sure that you follow the checklist below before publishing the repository.

```sh
git clone https://github.com/schlenkibus/AW101_WtFoo
cd AW101_WtFoo
mkdir build && cd build
cmake ../CMakeLists.txt
make install
```



## Prerequisites

In order to run the Hardware Server a WiFi access point called: AW101_BASE needs to be running. The BasicIO Device assumes 'aaaaaaaa' as the password for that WiFi. 
The IP for the WiFi device has to be `101.101.101.101` netmask: `255.255.255.0`

This way the Hardware Abstraction Layer can listen to new devices.

## Running

```
./ModularPlaygroundExample --docroot=../../../examples/ModularPlayground/resources --hal-enable=true --http-listen=101.101.101.101:8090 --module-path=../FancyModules/ --hardware-path=../../firmware/IODevice/
```

`hal-enable` starts the Hardware Abstraction Layer opens welcome hall and loads HW plugins

`hardware-path` and `module-path`point to directorys that contain plugins (.so) shared librarys that register DSPModules or HardwareDevices. See README inside HAL / ModularPlaygroundExample 

## Dependencies

#### libDSP

- libuuid

  

#### libAudio

- libDSP

- portaudio




#### HAL

- simple-websocket-server
- libDSP



#### IODevice

- simple-websocket-server
- libDSP
- HAL

- arduino toolchain for ESP8266

  

#### ModularPlaygroundExample

- libDSP
- libAudio
- [Wt](https://github.com/emweb/wt)
- HAL



All projects require an C++ 17 compliant compiler