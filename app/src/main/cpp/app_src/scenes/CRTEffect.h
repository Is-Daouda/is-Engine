#ifndef CRTEFFECT_H_INCLUDED
#define CRTEFFECT_H_INCLUDED

#include "../config/GameConfig.h"

class CRTEffect
{
public:
    SDL_Texture* m_renderTarget;
    SDL_Texture* m_crtTexture;

    CRTEffect(sf::RenderWindow &window)
    {
        const int SCANLINE_SPACING = 2;
        m_renderTarget = SDL_CreateTexture(is::IS_ENGINE_SDL_renderer, SDL_PIXELFORMAT_RGBA8888,
                                       SDL_TEXTUREACCESS_TARGET, is::GameConfig::WINDOW_WIDTH, is::GameConfig::WINDOW_HEIGHT);
        if (!m_renderTarget) {
            std::cerr << "SDL_CreateTexture (renderTarget) Error: " << SDL_GetError() << std::endl;
            exit(1);
        }

        m_crtTexture = SDL_CreateTexture(is::IS_ENGINE_SDL_renderer, SDL_PIXELFORMAT_RGBA8888,
                                     SDL_TEXTUREACCESS_TARGET, is::GameConfig::WINDOW_WIDTH, is::GameConfig::WINDOW_HEIGHT);
        if (!m_crtTexture) {
            std::cerr << "SDL_CreateTexture (crtTexture) Error: " << SDL_GetError() << std::endl;
            exit(1);
        }

        SDL_SetTextureBlendMode(m_crtTexture, SDL_BLENDMODE_BLEND);
        SDL_SetRenderTarget(is::IS_ENGINE_SDL_renderer, m_crtTexture);
        SDL_SetRenderDrawColor(is::IS_ENGINE_SDL_renderer, 0, 0, 0, 0);
        SDL_RenderClear(is::IS_ENGINE_SDL_renderer);

        SDL_SetRenderDrawColor(is::IS_ENGINE_SDL_renderer, 0, 0, 0, 50);
        for (int y = 0; y < is::GameConfig::WINDOW_HEIGHT ; y += SCANLINE_SPACING) {
            SDL_RenderDrawLine(is::IS_ENGINE_SDL_renderer, 0, y, is::GameConfig::WINDOW_WIDTH, y);
        }

        SDL_SetRenderTarget(is::IS_ENGINE_SDL_renderer, nullptr);
    }

    ~CRTEffect()
    {
        SDL_DestroyTexture(m_crtTexture);
        SDL_DestroyTexture(m_renderTarget);
    }

    void startCRT()
    {
        SDL_SetRenderTarget(is::IS_ENGINE_SDL_renderer, m_renderTarget);
    }

    void endCRT()
    {
        SDL_SetRenderTarget(is::IS_ENGINE_SDL_renderer, nullptr);
        SDL_SetTextureBlendMode(m_renderTarget, SDL_BLENDMODE_BLEND);

        SDL_RenderCopy(is::IS_ENGINE_SDL_renderer, m_renderTarget, nullptr, nullptr);

        SDL_SetTextureAlphaMod(m_crtTexture, 255);
        SDL_RenderCopy(is::IS_ENGINE_SDL_renderer, m_crtTexture, nullptr, nullptr);
    }
};

#endif // CRTEFFECT_H_INCLUDED
