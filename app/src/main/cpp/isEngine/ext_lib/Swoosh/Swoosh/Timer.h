#pragma once
#include <SFML/System.hpp>

namespace swoosh {
  class Timer {
    sf::Clock clock;
    sf::Int32 elapsed;
    bool paused;

  public:
    Timer() {
      paused = true;
      elapsed = 0;
      clock.restart();
    }

    void reset() {
      clock.restart();
      elapsed = 0;
      paused = false;
    }

    void start() {
      if (paused) {
        clock.restart();
      }
      paused = false;
    }

    void pause() {
      if (!paused) {
        elapsed += clock.getElapsedTime().asMilliseconds();
      }
      paused = true;
    }

    bool isPaused() { return paused; }

    sf::Time getElapsed() {
      if (!paused) {
        return sf::milliseconds(elapsed + clock.getElapsedTime().asMilliseconds());
      }
      return sf::milliseconds(elapsed);
    }
  };
}