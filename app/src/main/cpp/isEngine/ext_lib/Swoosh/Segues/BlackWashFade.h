#pragma once
#include "../Swoosh/Segue.h"
#include "../Swoosh/Ease.h"

using namespace swoosh;

class BlackWashFade : public Segue {
private:
    sf::RectangleShape whiteout;

public:
  virtual void onDraw(sf::RenderTexture& surface) {
    double elapsed = getElapsed().asMilliseconds();
    double duration = getDuration().asMilliseconds();
    double alpha = ease::wideParabola(elapsed, duration, 1.0);

    if (elapsed <= duration * 0.5) {
      surface.clear(this->getLastActivityBGColor());
      this->drawLastActivity(surface);
    }
    else {
      surface.clear(this->getNextActivityBGColor());
      this->drawNextActivity(surface);
    }

    whiteout.setSize(sf::Vector2f((float)surface.getSize().x, (float)surface.getSize().y));
    whiteout.setFillColor(sf::Color(0, 0, 0, (sf::Uint8)(alpha*255)));
    surface.draw(whiteout);
  }

  BlackWashFade(sf::Time duration, Activity* last, Activity* next) : Segue(duration, last, next) { /* ... */ }
  virtual ~BlackWashFade() { ; }
};
