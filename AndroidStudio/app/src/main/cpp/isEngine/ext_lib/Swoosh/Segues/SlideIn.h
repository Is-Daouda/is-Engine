#pragma once
#include "../Swoosh/Segue.h"
#include "../Swoosh/Ease.h"

using namespace swoosh;

template<int direction>
class SlideIn : public Segue {
    bool fetch;
    sf::Texture tLast, tNext;

public:

  virtual void onDraw(sf::RenderTexture& surface) {
    double elapsed = getElapsed().asMilliseconds();
    double duration = getDuration().asMilliseconds();
    double alpha = ease::linear(elapsed, duration, 1.0);

    if (fetch) {
        this->drawLastActivity(surface);
        surface.display(); // flip and ready the buffer
        tLast = surface.getTexture(); // Make a copy of the source texture
    }

    sf::Sprite left(tLast);

    int lr = 0;
    int ud = 0;

    if (direction == 0) lr = -1;
    if (direction == 1) lr = 1;
    if (direction == 2) ud = -1;
    if (direction == 3) ud = 1;

    if (fetch) {
        surface.clear();
        this->drawNextActivity(surface);
        surface.display(); // flip and ready the buffer
        tNext = surface.getTexture();
    }

    sf::Sprite right(tNext);

    right.setPosition((float)-lr * (1.0f-(float)alpha) * right.getTexture()->getSize().x, (float)-ud * (1.0f-(float)alpha) * right.getTexture()->getSize().y);

    surface.draw(left);
    surface.draw(right);

    fetch = !getController().isOptimizedForPerformance();
  }

  SlideIn(sf::Time duration, Activity* last, Activity* next) : Segue(duration, last, next) {
    /* ... */
  }

  virtual ~SlideIn() { ; }
};
