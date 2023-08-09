#pragma once
#include <iostream>
#include <vector>


struct SinglePanelParams
{
    std::vector<juce::AudioParameterInt*> params;
  
  SinglePanelParams()
    {

    for (int i = 1; i <= 4; ++i)
        {
            std::string id = "slider" + std::to_string(i);
            std::string name = "Slider " + std::to_string(i);
            params.push_back(new juce::AudioParameterInt(id, name, 1, 12, 5));
        }
    }

    // Do NOT delete params in destructor, because juce::AudioProcessor takes ownership of them.
};
