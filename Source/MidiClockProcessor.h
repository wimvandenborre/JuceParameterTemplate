
#pragma once
#include "..//Dsp/MidiClockInput.hpp"
#include <JuceHeader.h>

class PolynatorAudioProcessor;

class MidiClockProcessor : public juce::MidiInputCallback {
  
private:
  
  PolynatorAudioProcessor& mainProcessor;
  
public:
  
 
  explicit MidiClockProcessor(PolynatorAudioProcessor& processor);
  
  MidiClockInput midiClockInput;

  long long frameCounterClock = 0;
  std::atomic<float> tempo = 120.0;
  double framesPerClock = 0.0;
  unsigned int framesPerQuarterNote = 0;
  bool isPlaying = 0;
  int modulation_update_counter = 0;
  
  std::unique_ptr<juce::MidiInput> clockMidiInput;
  juce::MidiBuffer  clockMessagesBuffer;
  juce::MidiMessageCollector midiClockCollector;
  float lfoMidiValueOut[4] = { };
  
  void setClockMidiInput(int index);
  void handleIncomingMidiMessage(juce::MidiInput* source, const juce::MidiMessage& message) override;
  void setTempo(float tempoToUse);
  float getTempo();
  void initSampleRateAndTempoDependentConstants(const double sampleRate);
  void processClock(int numFrames);
  
};
