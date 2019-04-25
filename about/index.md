---
layout: page
title: About the Project
tags: [about, Jekyll, theme, moon]
date: 2019-04-25
comments: false
---

## Objectives
* Learn to use <b>[JUCE](https://juce.com/)</b>, the cross-platform C++ framework
* Create one (or more) working audio plug-in for use in <b>[Logic Pro X](https://www.apple.com/ca/logic-pro/)</b> and <b>[Audacity](https://www.audacityteam.org/)</b>
  * Creating valid <b>[Audio Units (AU)](https://developer.apple.com/library/archive/documentation/MusicAudio/Conceptual/AudioUnitProgrammingGuide/Introduction/Introduction.html)</b> and <b>[Virtual Studio Technology 3 (VST3)](https://www.steinberg.net/en/company/technologies/vst3.html)</b> with JUCE
* One of the audio plug-ins used the built-in DSP modules in JUCE <b>[daVerb](https://github.com/deepio/daAudioPlugins/tree/master/daVerb/Builds/MacOSX/build/Debug)</b>
* And the other one created a circular buffer <b>[daFlange](https://github.com/deepio/daAudioPlugins/tree/master/daFlange/Builds/MacOSX/build/Debug)</b>.

## Project Design

* `daFlange` has a circular buffer that is read at variable speeds via a low frequency oscillator to achieve a flanger effect.
* `daVerb` takes advantage of the relatively recent release of the JUCE DSP module. The `DSP::Reverb` and `DSP::Gain` can be chained together by using the `DSP::ProcessorChain`. This allows any number of classes (including custom filters, convolutions, etc.) to be linked together.

{% capture images %}
    https://i.ibb.co/rQwTmGM/daVerb1.png
    https://i.ibb.co/vsttsSK/da-Flange1.png
{% endcapture %}
{% include gallery images=images caption="Screenshots of daVerb and daFlange." cols=2 %}

* Backgrounds are by [elum3a](https://instagram.com/elum3a) and [byrawpixel](https://instagram.com/byrawpixel) on instagram, and, are free to use from [pixabay.com](https://pixabay.com).

## Challenges
* JUCE can be hard to work with at times:
  * Compiling the application with no errors, and testing it in the Audio Plug-in Host does not mean it will create a valid Audio Units file for Logic Pro X to use. A solution I have found that sometimes fixed this issue was to select any different target plug-in type (MIDI Processor instead of Audio Effects for example) in Projucer, compile the application, switch back to the original target type, recompile, and suddenly the AU will pass the Mac Validation check. I have not yet discovered why this works.
  * A Wealth of tools exist that make developing Audio Plug-ins much easier and faster if you know they exist. For example the `auval` tool that tests/validates AU's, JUCE's `Audio Plug-In Host` that lets you use your plug-ins outside of a Digital Audio Workstation, the `AudioFilePlayer` that can feed input to your plug-ins while in the Plug-In Host.
  * The size of the framework, the classes, the idioms, the Projucer app, it can be very overwhelming, but the `Class Index` is very helpful.
  * Following the tutorials on the JUCE website helps to get a new user started but as the tutorials get more advanced there is less information and less clarity. Tutorial examples also do not always resemble Projects created with JUCE.

<!-- [Install Moon](https://github.com/TaylanTatli/Moon){: .btn} -->
