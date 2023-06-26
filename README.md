# All Pass Filter VST3
Tested using on Mac OSX 12.5.1, cmake 3.26.3, JUCE v7.0.5

### Minimum Requirements
- JUCE v7.0.0
- Cmake 3.4
- C++ 17

#### Description

This projects implements a simple all pass filter using the JUCE framework.
It takes any audio input and applies a short delay with an inverted phase.

#### How to build
This project uses FRUT (https://github.com/McMartin/FRUT) to build via cmake instead of projucer.
Follow these steps to build:
'''
$ cd AllPassFilter
$ mkdir build && cd build
$ cmake .. -G <generator>
'''
where ``<generator>`` refers to the cmake generator used for the build.
'''
Generators
* Unix Makefiles               = Generates standard UNIX makefiles.
  Ninja                        = Generates build.ninja files.
  Ninja Multi-Config           = Generates build-<Config>.ninja files.
  Watcom WMake                 = Generates Watcom WMake makefiles.
  Xcode                        = Generate Xcode project files.
  CodeBlocks - Ninja           = Generates CodeBlocks project files.
  CodeBlocks - Unix Makefiles  = Generates CodeBlocks project files.
  CodeLite - Ninja             = Generates CodeLite project files.
  CodeLite - Unix Makefiles    = Generates CodeLite project files.
  Eclipse CDT4 - Ninja         = Generates Eclipse CDT 4.0 project files.
  Eclipse CDT4 - Unix Makefiles= Generates Eclipse CDT 4.0 project files.
  Kate - Ninja                 = Generates Kate project files.
  Kate - Unix Makefiles        = Generates Kate project files.
  Sublime Text 2 - Ninja       = Generates Sublime Text 2 project files.
  Sublime Text 2 - Unix Makefiles
                               = Generates Sublime Text 2 project files.
'''

#### How to use
1. After building copy the VST3 file to your local VST3 folder
2. Lauch your DAW/plugin host and load up the AllPassFilter plugin

#### Controls
The AllPassFilter plugin has 2 controls:
- Delay Line Size: controls the delay time
- Delay Line Gain: controls the gain of the delayed signal

#### Notes
The plugin currently only works for mono input, i.e if a stereo signal is fed into it, it will sum it to mono.
