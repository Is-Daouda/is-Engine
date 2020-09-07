#pragma once
#include "../Swoosh/Segue.h"
#include "../Swoosh/Ease.h"
#include "../Swoosh/EmbedGLSL.h"

using namespace swoosh;

class ZoomFadeInBounce : public Segue {
private:
  sf::Shader shader;
  std::string ZOOM_FADEIN_BOUNCE_FRAG_SHADER;
  sf::Texture tNext, tLast;
  bool fetch;
public:
  virtual void onDraw(sf::RenderTexture& surface) {
    double elapsed = getElapsed().asMilliseconds();
    double duration = getDuration().asMilliseconds();
    double alpha = ease::sinuoidBounceOut(elapsed, duration);

    if (fetch) {
        this->drawLastActivity(surface);
        surface.display(); // flip and ready the buffer
        tLast = surface.getTexture();
   
        surface.clear(sf::Color::Transparent);
        this->drawNextActivity(surface);
        surface.display(); // flip and ready the buffer
        tNext = surface.getTexture();
    }

    sf::Sprite sprite(tNext);

    shader.setUniform("progress", (float)alpha);
    shader.setUniform("texture2", tNext);
    shader.setUniform("texture", tLast);

    sf::RenderStates states;
    states.shader = &shader;

    surface.draw(sprite, states);

    fetch = !getController().isOptimizedForPerformance();
  }

  ZoomFadeInBounce(sf::Time duration, Activity* last, Activity* next) : Segue(duration, last, next) {
    fetch = true;

    ZOOM_FADEIN_BOUNCE_FRAG_SHADER = GLSL
    (
      110,
      uniform sampler2D texture;
      uniform sampler2D texture2;
      uniform float progress;

      vec2 zoom(vec2 uv, float amount) {
        return 0.5 + ((uv - 0.5) * (1.0 - amount));
      }

      void main() {
        gl_FragColor = mix(
          texture2D(texture, zoom(gl_TexCoord[0].xy, smoothstep(0.0, 0.75, progress))),
          texture2D(texture2, gl_TexCoord[0].xy),
          smoothstep(0.55, 1.0, progress)
        );
      }
    );

    shader.loadFromMemory(ZOOM_FADEIN_BOUNCE_FRAG_SHADER, sf::Shader::Fragment);
  }

  virtual ~ZoomFadeInBounce() {; }
};
