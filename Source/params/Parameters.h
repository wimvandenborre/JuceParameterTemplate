#pragma once

#include <../Modules/shared_plugin_helpers/shared_plugin_helpers.h>
#include "SinglePanelParams.h"
#include "LfoParams.h"

using LFOs = std::vector<LFOParameter>;

struct Parameters
{
  
  static constexpr int numLFOs = 4;
  SinglePanelParams newPanelParams;
  LFOs lfos;

  Parameters()
  {
      for (int i = 0; i < numLFOs; ++i)
      {
          lfos.emplace_back(i);
      }
  }
  
  void add(juce::AudioProcessor& processor) const
  {
    processor.addParameter(gain);
    processor.addParameter(enable);
    processor.addParameter(voiceDial);
    

    for (const auto& lfo : lfos)
    {
        processor.addParameter(lfo.gain);
        processor.addParameter(lfo.speed);
    }

    
    
    for (const auto& param : newPanelParams.params)
    {
        processor.addParameter(param);
    }

  }
  
  //Raw pointers. They will be owned by either the processor or the APVTS (if you use it)
  juce::AudioParameterFloat* gain =
  new juce::AudioParameterFloat({"Gain", 1}, "Gain", 0.f, 1.f, 0.2f);

  juce::AudioParameterBool* enable =
  new juce::AudioParameterBool({"Enable", 1}, "Enable", true);
  
  juce::AudioParameterInt* voiceDial =
  new juce::AudioParameterInt({"VoiceDial", 1 }, "VoiceDialKnop", 1, 8, 3);

};
