#pragma once

#include "params/Parameters.h"

class PolynatorAudioProcessor : public PluginHelpers::ProcessorBase
{
public:
    PolynatorAudioProcessor();

    void processBlock(juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    juce::AudioProcessorEditor* createEditor() override;

    void getStateInformation(juce::MemoryBlock& destData) override;
    void setStateInformation(const void* data, int sizeInBytes) override;
  
  
  
  Parameters parameters;
  
  
  
private:
  
  
  
};
