---
layout: post
title: "daVerb v1.0"
date: 2019-04-25
excerpt: "Using the new DSP module from JUCE to chain effects together"
tags:
- reverb
- daVerb
- JUCE
- DSP Module
- C++
feature: http://i.imgur.com/Ds6S7lJ.png
---

# A Gateway Reverb
<figure>
	<a href="https://ibb.co/PjZ4rzB"><img src="https://i.ibb.co/c3ctyXz/da-Verb-Screenshot.png"></a>
	<figcaption></figcaption>
</figure>

JUCE is fortunate to have two `Reverb` classes.
- A simple [Reverb](https://docs.juce.com/master/classReverb.html) that is very easy to implement, requiring very little code. The implementation still exists in the code, but is commented out for reference.
- The other [DSP::Reverb](https://docs.juce.com/master/classdsp_1_1Reverb.html), is equally simple to implement on its own, but becomes much more difficult to implement with the process managers.
  - `dsp::ProcessSpec` - Works with the prepare method on input only buffer
  - `dsp::ProcessContextReplacing` - Works with the prepare method when both input and output is required for the processing task
  - `dsp::ProcessorChain` - Where you order and organize how you want your modules to work together
  - `dsp::Gain` - A simple gain class, added as another element in the processor chain. `dsp::Convolution`, `dsp::FilterDesign`,  `dsp::Coefficients`, and others are available once all the methods are implemented (`prepare`, `process`, `reset`, `updateParameters`).

## Challenges
- Sending parameters from the Sliders to the Processor was a small issue because of the volatile [deprecations](https://forum.juce.com/t/we-are-removing-audioprocessor-based-parameter-management/26032/6) of parameter handling functions.
