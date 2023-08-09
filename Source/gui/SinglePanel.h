/*
  ==============================================================================

    NewPanel.h
    Created: 25 Jul 2023 5:22:51pm
    Author:  Wim Van den Borre

  ==============================================================================
*/

#pragma once
#include "..//PluginProcessor.h"
#include "../params/SinglePanelParams.h"
//template<typename T>
//using OwnedVector = std::vector<std::unique_ptr<T>>;

//==============================================================================
/*
*/
class SinglePanel  : public juce::Component
{
public:
  
  SinglePanel(SinglePanelParams& newPanelParamsToUse);

  
private:
  
  SinglePanelParams& newPanelParams;

  std::vector<std::unique_ptr<juce::Component>> components;
  std::array<juce::Slider*, 4> sliders;
  std::array<juce::Label, 4> labels;
  std::array<std::unique_ptr<juce::SliderParameterAttachment>, 4> attachments;

  //juce::Label label1;
  //juce::SliderParameterAttachment slider1Attachment {*newPanelParams.slider1Param, slider1};
  //int getiktn{0};

  template<typename T>
  T& addComponent()
  {
      auto component = std::make_unique<T>();
      T* rawPtr = component.get();
      components.emplace_back(std::move(component));
      return *rawPtr;
  }
  
  
  void paint (juce::Graphics&) override;
  void resized() override;
  
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SinglePanel)
  
};
