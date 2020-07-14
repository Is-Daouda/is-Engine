#pragma once
#include "../Swoosh/Segue.h"
#include "../Swoosh/Ease.h"
#include "../Swoosh/EmbedGLSL.h"
#include "../Swoosh/Shaders.h"

using namespace swoosh;

template<int cols, int rows>
class CheckerboardCustom : public Segue {
private:
  glsl::Checkerboard shader;
  sf::Texture tNext, tLast;
  bool fetch;

public:
  virtual void onDraw(sf::RenderTexture& surface) {
    double elapsed = getElapsed().asMilliseconds();
    double duration = getDuration().asMilliseconds();
    double alpha = ease::linear(elapsed, duration, 1.0);

    if (fetch) {
        this->drawLastActivity(surface);
        surface.display(); // flip and ready the buffer
        tLast = surface.getTexture(); // Make a copy of the source texture

        surface.clear(sf::Color::Transparent);

        this->drawNextActivity(surface);
        surface.display(); // flip and ready the buffer
        tNext = surface.getTexture(); // Make a copy of the source texture
    }

    shader.setAlpha((float)alpha);
    shader.setTexture1(&tLast);
    shader.setTexture2(&tNext);
    shader.apply(surface);

    fetch = !getController().isOptimizedForPerformance();
  }

  CheckerboardCustom(sf::Time duration, Activity* last, Activity* next) : Segue(duration, last, next),
    shader(cols, rows) {
    fetch = true;
    shader.setSmoothness(0.005f);
  }

  virtual ~CheckerboardCustom() { ; }
};

using Checkerboard = CheckerboardCustom<10, 10>;
