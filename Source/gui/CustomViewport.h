#include <juce_gui_basics/juce_gui_basics.h>

using ViewportDragPosition = juce::AnimatedPosition<juce::AnimatedPositionBehaviours::ContinuousWithMomentum>;

class CustomViewport : public juce::Viewport
{
  struct ViewportHelpers
  {
      ViewportHelpers() = delete;

    static bool wouldScrollOnEvent (const Viewport* vp, const juce::MouseInputSource& src)
      {
          if (vp != nullptr)
          {
              switch (vp->getScrollOnDragMode())
              {
                  case Viewport::ScrollOnDragMode::all:           return true;
                  case Viewport::ScrollOnDragMode::nonHover:      return ! src.canHover();
                  case Viewport::ScrollOnDragMode::never:         return false;
              }
          }

          return false;
      }
  };
  
public:
    CustomViewport()
    {
        juce::Desktop::getInstance().addGlobalMouseListener(this);
    }

    ~CustomViewport() override
    {
        juce::Desktop::getInstance().removeGlobalMouseListener(this);
    }
  
protected:
    
  void mouseDrag(const juce::MouseEvent& e) override
  {
      if (e.source.isTouch() && sources.size() == 2)
      {
          if (!isDragging)
          {
              // Initialize the drag operation
              isDragging = true;
              originalViewPos = this->getViewPosition();
              
              // Record the start position for both fingers
              startPos1 = sources[0]->getScreenPosition().toFloat();
              startPos2 = sources[1]->getScreenPosition().toFloat();
          }
          else
          {
              // Calculate the current positions and the average offset
              auto currentPos1 = sources[0]->getScreenPosition().toFloat();
              auto currentPos2 = sources[1]->getScreenPosition().toFloat();
              
              auto averageStartPos = (startPos1 + startPos2) * 0.5f;
              auto averageCurrentPos = (currentPos1 + currentPos2) * 0.5f;
              auto averageOffset = averageCurrentPos - averageStartPos;
              
              // Apply the average movement to the viewport's position
              auto newViewPos = originalViewPos - juce::Point<int>(averageOffset.x, averageOffset.y);
              this->setViewPosition(newViewPos);
          }
      }
      else
      {
          isDragging = false;
         juce::Viewport::mouseDrag(e);
      }
  }
  
    void mouseDown(const juce::MouseEvent& event) override
    {
        addSource(event.source);
    }

    void mouseUp(const juce::MouseEvent& event) override
    {
        removeSource(event.source);
    }

private:
    std::vector<std::shared_ptr<juce::MouseInputSource>> sources;
  ViewportDragPosition offsetX, offsetY;
  juce::Point<float> startPos1, startPos2;
  bool isDragging = false;
  juce::Point<int> originalViewPos;

    void addSource(const juce::MouseInputSource& source)
    {
        for (auto& s : sources)
        {
            if (s->getIndex() == source.getIndex())
                return;
        }

        sources.push_back(std::make_shared<juce::MouseInputSource>(source));
    }

    void removeSource(const juce::MouseInputSource& source)
    {
        for (auto it = sources.begin(); it != sources.end(); ++it)
        {
            if ((*it)->getIndex() == source.getIndex())
            {
                sources.erase(it);
                return;
            }
        }
    }
};
