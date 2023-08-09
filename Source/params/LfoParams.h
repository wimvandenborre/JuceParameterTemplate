/*
  ==============================================================================

    LfoParams.h
    Created: 5 Aug 2023 11:31:55am
    Author:  Wim Van den Borre

  ==============================================================================
*/

#pragma once

struct LFOParameter
{
  LFOParameter(int index)
  {
      initGainParam(index);
     initSpeedParam(index);
      //etc
  }
  
  //create a function for initGainParam
  
  void initGainParam(int index)
  {
    // Define a unique parameter ID and name based on the index
    juce::String paramID = "gain" + juce::String(index);
    juce::String paramName = "Gain " + juce::String(index);

    // Define the range, interval, and default value
    int minValue = 0;
    int maxValue = 20;
    int defaultValue = 10;

    // Create the parameter and assign it to 'gain'
    gain = new juce::AudioParameterInt(paramID, paramName, minValue, maxValue, defaultValue);
  }
  
  
  void initSpeedParam(int index)
  {
    // Define a unique parameter ID and name based on the index
    juce::String paramID = "speed" + juce::String(index);
    juce::String paramName = "Speed " + juce::String(index);
    

    // Define the range, interval, and default value
    int minValue = 1;
    int maxValue = 8;
    int defaultValue = 3;
    int versionNumber = 1;

    // Create the parameter

    speed = new juce::AudioParameterInt(juce::ParameterID{paramID, versionNumber}, paramName, minValue, maxValue, defaultValue);

  }
  
  juce::AudioParameterInt* gain;
  juce::AudioParameterInt* speed;
};
