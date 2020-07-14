#pragma once
#include "../Swoosh/EmbedGLSL.h"
#include "../Swoosh/Segue.h"
#include "../Swoosh/Ease.h"
#include "../Swoosh/Shaders.h"

using namespace swoosh;

class Morph : public Segue {
private:
  glsl::Morph shader;

public:
  virtual void onDraw(sf::RenderTexture& surface) {
    double elapsed = getElapsed().asMilliseconds();
    double duration = getDuration().asMilliseconds();
    double alpha = ease::linear(elapsed, duration, 1.0);

    surface.clear(this->getLastActivityBGColor());
    this->drawLastActivity(surface);

    surface.display(); // flip and ready the buffer
    sf::Texture temp(surface.getTexture()); // Make a copy of the source texture

    surface.clear(this->getNextActivityBGColor());
    this->drawNextActivity(surface);

    surface.display(); // flip and ready the buffer
    sf::Texture temp2(surface.getTexture()); // Make a copy of the source texture

    shader.setAlpha((float)alpha);
    shader.setTexture1(&temp);
    shader.setTexture2(&temp2);
    shader.apply(surface);
  }

  Morph(sf::Time duration, Activity* last, Activity* next) : Segue(duration, last, next) {
    /* ... */
    shader.setStrength(0.1f);
  }

  virtual ~Morph() { }
};
