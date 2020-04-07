#pragma once
#include "../Swoosh/Segue.h"
#include "../Swoosh/Ease.h"

using namespace swoosh;

class BlendFadeIn : public Segue {
private:
  sf::Texture tLast, tNext;
  bool fetch;
public:
  virtual void onDraw(sf::RenderTexture& surface) {
    double elapsed = getElapsed().asMilliseconds();
    double duration = getDuration().asMilliseconds();
    double alpha = ease::linear(elapsed, duration, 1.0);

    if (fetch) {
        surface.clear(this->getLastActivityBGColor());
        this->drawLastActivity(surface);
        surface.display(); // flip and ready the buffer
        tLast = surface.getTexture(); // Make a copy of the source texture

        surface.clear(this->getNextActivityBGColor());

        this->drawNextActivity(surface);
        surface.display();
        tNext = surface.getTexture();
    }

    sf::Sprite left(tLast);
    sf::Sprite right(tNext);

    left.setColor(sf::Color(255, 255, 255, (sf::Uint8)((1.0-alpha) * 255.0)));
    right.setColor(sf::Color(255, 255, 255, (sf::Uint8)(alpha * 255.0)));

    surface.draw(left);
    surface.draw(right);

    fetch = !getController().isOptimizedForPerformance();
  }

  BlendFadeIn(sf::Time duration, Activity* last, Activity* next) : Segue(duration, last, next) {
    /* ... */
    fetch = true;
  }

  virtual ~BlendFadeIn() { ; }
};
