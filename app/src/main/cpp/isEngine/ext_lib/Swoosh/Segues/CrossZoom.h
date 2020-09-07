#pragma once
#include "../Swoosh/Segue.h"
#include "../Swoosh/Ease.h"
#include "../Swoosh/EmbedGLSL.h"
#include "../Swoosh/Shaders.h"

using namespace swoosh;

template<int percent_power> // from 0% - 100%
class CrossZoomCustom : public Segue {
private:
  sf::Texture tNext, tLast;
  glsl::CrossZoom shader;
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
        tLast = sf::Texture(surface.getTexture());

        surface.clear(this->getNextActivityBGColor());
        this->drawNextActivity(surface);
        surface.display(); // flip and ready the buffer
        tNext = sf::Texture(surface.getTexture());
    }

    sf::Sprite sprite(tNext);

    shader.setAlpha((float)alpha);
    shader.setPower((float)percent_power / 100.0f);
    shader.setTexture1(&tLast);
    shader.setTexture2(&tNext);
    shader.apply(surface);

    fetch = !getController().isOptimizedForPerformance();
  }

  CrossZoomCustom(sf::Time duration, Activity* last, Activity* next) : Segue(duration, last, next) {
    /* ... */
      fetch = true;
  }

  virtual ~CrossZoomCustom() { ; }
};

using CrossZoom = CrossZoomCustom<40>;
