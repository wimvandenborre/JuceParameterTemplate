#pragma once

#include "PluginProcessor.h"
#include "gui/SinglePanel.h"
#include "gui/Lfos.h"


class PolynatorAudioProcessorEditor : public juce::AudioProcessorEditor
{
public:
    explicit PolynatorAudioProcessorEditor(PolynatorAudioProcessor&);
    

private:
  
  void paint(juce::Graphics&) override;
    void resized() override;
  
  PolynatorAudioProcessor& aP;
  Parameters& params {aP.parameters};
  

  SinglePanel singlePanel;
  AllLFOVisualizer allLFOs {params.lfos};
  
  
  struct LeftPanel : public juce::Component
    {
      LeftPanel(Parameters& params)
        : voiceDialAttachment {*params.voiceDial, voiceDial},
          gainAttachment {*params.gain, gain},
          enableAttachment {*params.enable, enable}
      {
        setPaintingIsUnclipped(true);
        addAndMakeVisible(voiceDial);
        addAndMakeVisible(gain);
        addAndMakeVisible(enable);
        gainLabel.setText(params.gain->getName(5), juce::dontSendNotification);
        gainLabel.attachToComponent(&gain, false);
      }
    
    
    
    juce::Slider voiceDial, gain;
    juce::ToggleButton enable;
    juce::Label gainLabel;
    juce::SliderParameterAttachment voiceDialAttachment;
    juce::SliderParameterAttachment gainAttachment;
    juce::ButtonParameterAttachment enableAttachment;

      void paint (juce::Graphics& g) override
      {
        //g.setColour(juce::Colours::red); // change to a different color to see clearly
        g.fillRect(getLocalBounds());
        g.setColour(juce::Colours::black);
      }
      
      
      void resized() override
      {
          juce::FlexBox flexBox;

          // Configure the FlexBox layout
          flexBox.flexDirection = juce::FlexBox::Direction::column; // Vertical layout
          flexBox.justifyContent = juce::FlexBox::JustifyContent::flexStart; // Align to the start
          flexBox.alignItems = juce::FlexBox::AlignItems::flexStart; // Align to the start

          float panelWidth = (float) getWidth();
          float panelHeight = (float) getHeight();

          // Add voiceDial with relative size
          juce::FlexItem voiceDialItem(voiceDial);
          voiceDialItem.width = panelWidth * 0.8f; // 50% of the panel's width
          voiceDialItem.height = panelHeight * 0.2f; // 10% of the panel's height
          flexBox.items.add(std::move(voiceDialItem));

          // Add gain with relative size
          juce::FlexItem gainItem(gain);
          gainItem.width = panelWidth * 0.8f; // 50% of the panel's width
          gainItem.height = panelHeight * 0.2f; // 10% of the panel's height
          flexBox.items.add(std::move(gainItem));

          // Add enable with relative size
          juce::FlexItem enableItem(enable);
          enableItem.width = panelWidth * 0.8f; // 20% of the panel's width
          enableItem.height = panelHeight * 0.2f; // 10% of the panel's height
          flexBox.items.add(std::move(enableItem));

          // Perform the layout
          flexBox.performLayout(getLocalBounds());
      }


      
  };


  LeftPanel leftPanel;
  
  
  
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PolynatorAudioProcessorEditor)
  
};
