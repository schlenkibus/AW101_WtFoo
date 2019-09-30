# AW 101 Framework

Modular Synthesizer Executable Example and signal processing library + port audio wrapper



Playground features: 

Basic Modules

Dynamic Module connection at runtime

Plug in support

Web-based User Interface



## Install

These instructions are basic; you can use any method to do this work. The important part is making sure that you follow the checklist below before publishing the repository.

```sh
git clone https://github.com/schlenkibus/AW101_WtFoo
cd AW101_WtFoo
mkdir build && cd build
cmake ../CMakeLists.txt
make install
```

## Running

```
./ModularPlaygroundExample --docroot ../../../examples/ModularPlayground/resources --http-listen localhost:8090
```



## Dependencies

#### libDSP

- libuuid

  

#### libAudio

- libDSP

- portaudio

  

#### ModularPlaygroundExample

- libDSP
- libAudio
- [Wt](https://github.com/emweb/wt)



All projects require an C++ 17 compliant compiler