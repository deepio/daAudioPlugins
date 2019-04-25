---
layout: post
title: "daFlange v1.0"
date: 2019-04-25
excerpt: "Creating a circular buffer for processing"
tag:
- flanger
- daFlange
- JUCE
- Circular Buffer
- C++
feature: http://i.imgur.com/Ds6S7lJ.png
---

![Moon Homepage](https://i.ibb.co/T433KL5/da-Flange-Screenshot.png)


## Store
The delay buffer is larger than the regular buffer. When there are more values to store than positions left in the delay buffer, the remainder is copied at position zero.
```c++
if (delayBufferLength > bufferLength + mWritePosition)
{
    mDelayBuffer.copyFromWithRamp(channel, mWritePosition, bufferData, bufferLength, inGain, outGain);
} else {
    const int bufferRemaining = delayBufferLength - mWritePosition;
    mDelayBuffer.copyFromWithRamp(channel, mWritePosition, bufferData, bufferRemaining, inGain, outGain);
    mDelayBuffer.copyFromWithRamp(channel, 0, bufferData, bufferLength - bufferRemaining, inGain, outGain);
}
```

## Fetch
Same idea as the store function above, but the read position is back in time so we have the same track playing at two different points in time.
```c++
const int readPosition = static_cast<int> (delayBufferLength + mWritePosition - (mSampleRate * delayTime * 0.001f)) % delayBufferLength;

if (delayBufferLength > bufferLength + readPosition)
{
    buffer.copyFrom(channel, 0, delayBufferData + readPosition, bufferLength);
} else {
    const int bufferRemaining = delayBufferLength - readPosition;
    buffer.copyFrom(channel, 0, delayBufferData + readPosition, bufferRemaining);
    buffer.copyFrom(channel, bufferRemaining, delayBufferData, bufferLength - bufferRemaining);
}
```
## Feedback
Continuously add both buffers together to get a feedback effect, with the same wrap around.
```c++
if (delayBufferLength > bufferLength + mWritePosition)
{
    //Copy the main signal to the delayed singal, and the delayed signal with the main signal gets put out of the speakers,
    // instead of the other way around.
    mDelayBuffer.addFromWithRamp(channel, mWritePosition, dryBuffer, bufferLength, inGain, outGain);
} else {
    const int bufferRemaining = delayBufferLength - mWritePosition;
    mDelayBuffer.addFromWithRamp(channel, bufferRemaining, dryBuffer, bufferRemaining, inGain, outGain);
    mDelayBuffer.addFromWithRamp(channel, 0, dryBuffer, bufferLength - bufferRemaining, inGain, outGain);
}
```

## LFO
The LFO speeds up and slows down the read position of one of the delayed buffer.
```c++
auto cyclesPerSample = (*mParameterTree.getRawParameterValue(INTENSITY_ID) * 1000.0f) / mSampleRate;
angleDelta = cyclesPerSample * 2.0 * MathConstants<double>::pi;
auto currentLFOSample = static_cast<float>(std::sin(currentAngle));
```
