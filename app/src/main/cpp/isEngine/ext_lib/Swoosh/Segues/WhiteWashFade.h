#pragma once
#include "../Swoosh/Segue.h"
#include "../Swoosh/Ease.h"

using namespace swoosh;

class WhiteWashFade : public Segue {
    sf::RectangleShape whiteout;

public:
  virtual void onDraw(sf::RenderTexture& surface) {
    double elapsed = getElapsed().asMilliseconds();
    double duration = getDuration().asMilliseconds();
    double alpha = ease::wideParabola(elapsed, duration, 1.0);

    if (elapsed <= duration * 0.5)
      this->drawLastActivity(surface);
    else
      this->drawNextActivity(surface);

    whiteout.setSize(sf::Vector2f((float)surface.getTexture().getSize().x, (float)surface.getTexture().getSize().y));
    whiteout.setFillColor(sf::Color(255, 255, 255, (sf::Uint8)(alpha*255)));
    surface.draw(whiteout);
  }

  WhiteWashFade(sf::Time duration, Activity* last, Activity* next) : Segue(duration, last, next) { /* ... */ }
  virtual ~WhiteWashFade() { ; }
};
