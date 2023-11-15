/*
  ==============================================================================

    MidiClockProcessor.cpp
    Created: 18 Sep 2023 11:33:21am
    Author:  Wim Van den Borre

  ==============================================================================
*/

#include "MidiClockProcessor.h"
#include "..//PluginProcessor.h"

MidiClockProcessor::MidiClockProcessor(PolynatorAudioProcessor& processor)
                                       : mainProcessor(processor)
                                   {
                                         midiClockInput.onTempoChange = [this](const float newTempo) { setTempo(newTempo);};
                                   }

void MidiClockProcessor::setTempo(float tempoToUse)
{
  tempo.store(std::clamp<float>(tempoToUse, 30, 300));
}

float MidiClockProcessor::getTempo()
{
  return tempo.load();
}

void MidiClockProcessor::initSampleRateAndTempoDependentConstants(const double sampleRate)
{
  framesPerClock = (sampleRate / 48.0) * (120.0 / tempo);
  framesPerQuarterNote = static_cast<unsigned int>(framesPerClock * 24);
}

void MidiClockProcessor::setClockMidiInput(int index)
{
    auto midiInputs = juce::MidiInput::getAvailableDevices();

    if (clockMidiInput) {
        clockMidiInput->stop();
        clockMidiInput = nullptr;
    }

    if (index >= 0 && index < midiInputs.size()) {
        auto newInput = juce::MidiInput::openDevice(midiInputs[index].identifier, this);
        if (newInput) {
            newInput->start();
            clockMidiInput = std::move(newInput);
        }
    }
}

void MidiClockProcessor::handleIncomingMidiMessage(juce::MidiInput* source, const juce::MidiMessage& clockMessage)
{
  if (source == clockMidiInput.get())
    {
      if (clockMessage.isMidiStart()) {
        isPlaying = 1;
        auto& lfoDSPArray = mainProcessor.getLFODspArray();
          for (auto& lfo : lfoDSPArray) {
              lfo->start();
          }
      } else if (clockMessage.isMidiStop()) {
        isPlaying = 0;
        //midiClockInput.handleStopMessage();
        auto& lfoDSPArray = mainProcessor.getLFODspArray();
          for (auto& lfo : lfoDSPArray) {
              lfo->stop();
          }
      } else if (clockMessage.isMidiContinue()) {
        isPlaying = 0;
        auto& lfoDSPArray = mainProcessor.getLFODspArray();
          for (auto& lfo : lfoDSPArray) {
              lfo->pause();  // Or whatever name you choose to represent the MIDI continue functionality
          }
      }
      
          if ( clockMessage.isMidiClock())
          {
            midiClockCollector.addMessageToQueue(clockMessage);
          }

    }
}

void MidiClockProcessor::processClock(int numFrames)
{
  
  clockMessagesBuffer.clear();
  midiClockCollector.removeNextBlockOfMessages(clockMessagesBuffer, numFrames);
  
  juce::MidiBuffer::Iterator iterClock(clockMessagesBuffer);
  juce::MidiMessage clockMessage;
  int samplePositionClock;
  
  while (iterClock.getNextEvent(clockMessage, samplePositionClock))
    {

          const auto framePos = static_cast<double>(frameCounterClock) + clockMessage.getTimeStamp();
          midiClockInput.handleTimingMessage(framePos);
          mainProcessor.g_averageBPM = midiClockInput.getBpm();
    }
  frameCounterClock += numFrames;
}

