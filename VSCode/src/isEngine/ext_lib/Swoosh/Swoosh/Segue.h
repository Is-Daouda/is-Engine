#pragma once
#include "Timer.h"
#include "Activity.h"
#include <SFML/Graphics.hpp>

namespace swoosh {
  class ActivityController;

  class Segue : public Activity {
    friend class ActivityController;

  private:
    sf::Time duration;
    Activity* last;
    Activity* next;
    Timer timer;

    // Hack to make this lib header-only
    void (ActivityController::*setActivityViewFunc)(sf::RenderTexture& surface, swoosh::Activity* activity);
    void (ActivityController::*resetViewFunc)(sf::RenderTexture& surface);

  protected:
    const sf::Time getDuration() const { return duration; }
    const sf::Time getElapsed() { return timer.getElapsed(); }
    const sf::Color getLastActivityBGColor() const { return last->getBGColor();  }
    const sf::Color getNextActivityBGColor() const { return next->getBGColor(); }
    void drawLastActivity(sf::RenderTexture& surface) {
      if (last) {
        (this->getController().*setActivityViewFunc)(surface, last);
        surface.clear(last->getBGColor());
        last->onDraw(surface);
        (this->getController().*resetViewFunc)(surface);
      }
    }

    void drawNextActivity(sf::RenderTexture& surface) {
      (this->getController().*setActivityViewFunc)(surface, next);
      surface.clear(next->getBGColor());
      next->onDraw(surface);
      (this->getController().*resetViewFunc)(surface);
    }

  public:
    virtual void onStart() final { next->onEnter();  last->onLeave(); timer.reset(); }

    virtual void onUpdate(double elapsed) final {
      if (last) last->onUpdate(elapsed);
      next->onUpdate(elapsed);
    }

    void onLeave() final { timer.pause(); }
    void onExit() final { ; }
    void onEnter() final { ; }
    void onResume() final { timer.start(); }
    virtual void onDraw(sf::RenderTexture& surface) = 0;
    void onEnd() final { last->onExit(); }

    Segue() = delete;
    Segue(sf::Time duration, Activity* last, Activity* next) : duration(duration), last(last), next(next), Activity(&next->getController()) { /* ... */ }
    ~Segue() { }
  };
}
