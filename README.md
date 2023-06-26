# All Pass Filter VST3

#### Description

This projects implements a simple all pass filter using the JUCE framework.
It takes any audio input and applies a short delay with an inverted phase.

#### How to use
1. Copy the VST3/allpassfilter.vst3 file to your local VST3 folder
2. Lauch your DAW/plugin host and load up the AllPassFilter plugin

#### Controls
The AllPassFilter plugin has 2 controls:
- Delay Line Size: controls the delay time
- Delay Line Gain: controls the gain of the delayed signal

#### Notes
The plugin currently only works for mono input, i.e if a stereo signal is fed into it, it will sum it to mono.
