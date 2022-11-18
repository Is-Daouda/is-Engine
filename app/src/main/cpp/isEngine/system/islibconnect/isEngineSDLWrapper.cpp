/*
  is::Engine (Infinity Solutions Engine)
  Copyright (C) 2018-2022 Is Daouda <isdaouda.n@gmail.com>

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
*/

#include "isEngineSDLWrapper.h"

#if defined(IS_ENGINE_SDL_2)

namespace is
{
SDL_Window *IS_ENGINE_SDL_window = NULL;
SDL_Renderer *IS_ENGINE_SDL_renderer = NULL;
SDL_DisplayMode IS_ENGINE_SDL_displayMode;

float IS_ENGINE_SDL_screenXScale(1.f);
float IS_ENGINE_SDL_screenYScale(1.f);

short IS_ENGINE_SDL_channel[IS_ENGINE_SDL_CHANNEL_MAX] = {-1};

TouchData IS_ENGINE_SDL_touchData[IS_ENGINE_SDL_TOUCH_ID_COUNT_MAX];
bool IS_ENGINE_SDL_enableFINGERMOTION = true;
short IS_ENGINE_SDL_touchIdLast = 0;
short IS_ENGINE_SDL_touchIdCount = 0;

std::vector<sf::Font*> IS_ENGINE_SDL_AUTO_GENERATE_FONT;

bool SDL2initLib()
{
    if (IS_ENGINE_SDL_window == NULL || IS_ENGINE_SDL_renderer == NULL)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "init Windows / Renderer : %s\n", SDL_GetError());
        return false;
    }

    if (SDL_GetCurrentDisplayMode( 0, &IS_ENGINE_SDL_displayMode) != 0)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Display Mode : %s\n", SDL_GetError());
    }

    SDL_SetRenderDrawBlendMode(IS_ENGINE_SDL_renderer, SDL_BLENDMODE_BLEND);

    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags))
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "init Image : %s\n", IMG_GetError());
        return false;
    }

    if (TTF_Init() < 0)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "init Font : %s\n", TTF_GetError());
        return false;
    }

    // On Android, the use of .wav type music files is not yet supported
#if !defined(__ANDROID__)
    int audioFlags = MIX_INIT_OGG;
    if ((Mix_Init(audioFlags) & audioFlags) != audioFlags)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "init Mix : %s\n", Mix_GetError());
        return false;
    }
#endif

    int const frequency =
#if defined(IS_ENGINE_HTML_5)
    EM_ASM_INT_V({
        var context;
        try
        {
            context = new AudioContext();
        }
        catch(e)
        {
            context = new webkitAudioContext();
        }
        return context.sampleRate;
    });
#else
        22050; //44100;
#endif
    if (Mix_OpenAudio(frequency, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "init OpenAudio : %s\n", Mix_GetError());
    }
    Mix_AllocateChannels(IS_ENGINE_SDL_CHANNEL_MAX);
    return true;
}

void SDL2freeLib()
{
    for (unsigned int _I(0); _I < IS_ENGINE_SDL_AUTO_GENERATE_FONT.size(); _I++)
    {
        delete IS_ENGINE_SDL_AUTO_GENERATE_FONT[_I];
        IS_ENGINE_SDL_AUTO_GENERATE_FONT[_I] = 0;
    }
    Mix_CloseAudio();
    Mix_Quit();

    SDL_DestroyWindow(IS_ENGINE_SDL_window);
    is::IS_ENGINE_SDL_window = NULL;
    SDL_DestroyRenderer(IS_ENGINE_SDL_renderer);
    is::IS_ENGINE_SDL_renderer = NULL;

    TTF_Quit();
    IMG_Quit();
}
}

namespace sf
{
int SoundBuffer::SDL_sndChannel = 0; // Represents the channel of each sound

sf::Color Color::White       = sf::Color(255, 255, 255, 255);
sf::Color Color::Black       = sf::Color(0, 0, 0, 255);
sf::Color Color::Grey        = sf::Color(127, 127, 127, 255);
sf::Color Color::Red         = sf::Color(255, 0, 0, 255);
sf::Color Color::Green       = sf::Color(0, 255, 0, 255);
sf::Color Color::Blue        = sf::Color(0, 0, 255, 255);
sf::Color Color::Yellow      = sf::Color(255, 255, 0, 255);
sf::Color Color::Magenta     = sf::Color(255, 0, 255, 255);
sf::Color Color::Cyan        = sf::Color(0, 255, 255, 255);
sf::Color Color::Transparent = sf::Color(0, 0, 0, 0);

Texture::~Texture()
{
    if (m_SDLsurface != NULL)
    {
        SDL_FreeSurface(m_SDLsurface);
        m_SDLsurface = NULL;
    }
}

bool Texture::loadSurface(const std::string& filePath)
{
    m_filename = filePath;
    m_SDLsurface = IMG_Load(m_filename.c_str());
    if (m_SDLsurface != NULL)
    {
        m_size.x = m_SDLsurface->w;
        m_size.y = m_SDLsurface->h;
    }
    else
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Texture : %s\n \"%s\"", SDL_GetError(), m_filename.c_str());
        return false;
    }
    return true;
}

Font::~Font()
{
    if (m_SDLfont != NULL)
    {
        TTF_CloseFont(m_SDLfont);
        m_SDLfont = NULL;
    }
}

bool Font::loadFont(const std::string& filename)
{
    m_filename = filename;
    m_SDLfont = TTF_OpenFont(m_filename.c_str(), m_size);
    if (m_SDLfont == NULL)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Font : %s \"%s\"\n", TTF_GetError(), filename.c_str());
        return false;
    }
    return true;
}

Transformable::Transformable()
{
    is::setVector2(m_size, 0.f, 0.f);
    is::setVector2(m_scale, 1.f, 1.f);
    is::setVector2(m_origin, 0.f, 0.f);
}

Transformable::Transformable(Texture &texture) :
    m_texture(&(texture))
{
    is::setVector2(m_size, m_texture->getSize().x, m_texture->getSize().y);
    is::setVector2(m_scale, 1.f, 1.f);
    is::setVector2(m_origin, 0.f, 0.f);
}

void Transformable::setRotation(float angle)
{
    m_rotation = static_cast<float>(fmod(angle, 360));
    if (m_rotation < 0)
        m_rotation += 360.f;
}

void Transformable::setColor(int r, int g, int b, int a)
{
    m_color.r = r;
    m_color.g = g;
    m_color.b = b;
    if (a >= 0 && a <= 255) m_color.a = a;

}

const SDL_Color& Transformable::getSDLColor(bool getAlpha)
{
    m_SDLcolor.r = m_color.r;
    m_SDLcolor.g = m_color.g;
    m_SDLcolor.b = m_color.b;
    m_SDLcolor.a = ((getAlpha) ? m_color.a : 0);
    return m_SDLcolor;
}

SDLTexture::~SDLTexture()
{
    if (m_SDLtexture != NULL)
    {
        SDL_DestroyTexture(m_SDLtexture);
        m_SDLtexture = NULL;
    }
    if (m_SDLoutlineTexture != NULL)
    {
        SDL_DestroyTexture(m_SDLoutlineTexture);
        m_SDLoutlineTexture = NULL;
    }
}

void SDLTexture::setTextureRect(IntRect rec)
{
    m_textureRec.left = rec.left;
    m_textureRec.top = rec.top;
    m_textureRec.width = rec.width;
    m_textureRec.height = rec.height;
    is::setVector2(m_size, m_textureRec.width, m_textureRec.height);
}

void Sprite::setTexture(sf::Texture& texture)
{
    m_texture = &texture;
    setSDLTexture();
}

void Sprite::setSDLTexture()
{
    if (m_texture->getSDLSurface() != NULL)
    {
        if (m_SDLtexture != NULL)
        {
            SDL_DestroyTexture(m_SDLtexture);
            m_SDLtexture = NULL;
        }
        m_SDLtexture = SDL_CreateTextureFromSurface(is::IS_ENGINE_SDL_renderer, m_texture->getSDLSurface());
        setTextureRect({0, 0, (int)m_texture->getSize().x, (int)m_texture->getSize().y});
    }
}

Image::~Image()
{
    if (m_texture != nullptr)
    {
        delete m_texture;
        m_texture = nullptr;
    }
}

bool Image::loadFromFile(const std::string& filename)
{
    if (m_texture != nullptr)
    {
        delete m_texture;
        m_texture = nullptr;
    }
    m_texture = new Texture(filename);
    if (m_texture == nullptr) return false;
    if (m_texture->getSDLSurface() != NULL)
    {
        m_SDLtexture = SDL_CreateTextureFromSurface(is::IS_ENGINE_SDL_renderer, m_texture->getSDLSurface());
        setSize(m_texture->getSize().x, m_texture->getSize().y);
    }
    return true;
}

const Uint8* Image::getPixelsPtr() const
{
    int pitch;
    void *pixels;
    SDL_LockTexture(m_SDLtexture, NULL, &pixels, &pitch);
    Uint8 *upixels = (Uint8*) pixels;
    memcpy(pixels, upixels, (pitch / 4) * m_texture->getSize().y);
    SDL_UnlockTexture(m_SDLtexture);
    return upixels;
}

Text::Text(sf::Font& font) :
    SDLTexture()
{
    m_SDLTextureType = IS_ENGINE_SDL_TEXT;
    m_font = &font;
    m_characterSize = m_font->getSize();
    m_style = m_font->m_SDLFontStyle;
    m_outlineFont = m_font;
}

Text::Text(sf::Font& font, const std::string& text) :
    SDLTexture()
{
    m_SDLTextureType = IS_ENGINE_SDL_TEXT;
    m_font = &font;
    m_characterSize = m_font->getSize();
    m_style = m_font->m_SDLFontStyle;
    m_outlineFont = m_font;
    setObjectText(text);
}

Text::Text(sf::Font& font, const std::wstring& text):
    SDLTexture()
{
    m_SDLTextureType = IS_ENGINE_SDL_TEXT;
    m_font = &font;
    m_characterSize = m_font->getSize();
    m_style = m_font->m_SDLFontStyle;
    m_outlineFont = m_font;
    setObjectText(text);
}

Text::~Text()
{
    if (m_SDLtexture != NULL)
    {
        SDL_DestroyTexture(m_SDLtexture);
        m_SDLtexture = NULL;
    }
    if (m_SDLtext != nullptr)
    {
        delete m_SDLtext;
        m_SDLtext = nullptr;
    }
}

void Text::setFont(sf::Font &font)
{
    m_font = &font;
    m_characterSize = m_font->getSize();
    m_style = m_font->m_SDLFontStyle;
    if (m_outlineFont == nullptr) m_outlineFont = m_font;
    setSDLText();
}

void Text::setString(const std::wstring& text)
{
    setObjectText(text);
}

void Text::setString(const wchar_t& text)
{
    m_tempWstring = text;
    setObjectText(m_tempWstring);
}

void Text::setString(const std::string& text)
{
    setObjectText(text);
}

void Text::setString(const char& text)
{
    m_tempString = text;
    setObjectText(m_tempString);
}

void Text::setColor(int r, int g, int b, int a)
{
    if (a >= 0 && a <= 255) m_color.a = a;
    if (m_color.r != r || m_color.g != g || m_color.b != b)
    {
        m_color.r = r;
        m_color.g = g;
        m_color.b = b;
        setSDLText();
    }
}

void Text::setOrigin(float x, float y)
{
    is::setVector2(m_origin, x, y);
}

void Text::setCharacterSize(int size)
{
    if (m_characterSize != size)
    {
        m_characterSize = size;
        setSDLText();
    }
}

void Text::setStyle(Uint32 style)
{
    if (m_style != style)
    {
        m_style = style;
        setSDLText();
    }
}

void Text::setOutlineColor(const Color& color)
{
    if (m_outlineColor.r != color.r || m_outlineColor.g != color.g || m_outlineColor.b != color.b ||
        m_outlineColor.a != color.a)
    {
        m_outlineColor = color;
        setSDLText();
    }
}

void Text::setOutlineThickness(float thickness)
{
    if (m_outlineThickness != thickness)
    {
        m_outlineThickness = thickness;
        setSDLText();
    }
}

void Text::setObjectText(const std::string& text)
{
    if (text != m_string)
    {
        m_string = text;
        if (m_SDLtext != nullptr)
        {
            delete m_SDLtext;
            m_SDLtext = nullptr;
        }
        m_currentCharSize = text.length() + 1;
        m_SDLtext = new char[m_currentCharSize];
        strcpy(m_SDLtext, text.c_str());
        m_SDLtext[m_currentCharSize - 1] = '\0';
        setSDLText();
    }
}

void Text::setObjectText(const std::wstring& text)
{
    if (text != m_wstring)
    {
        m_wstring = text;
        if (m_SDLtext != nullptr)
        {
            delete m_SDLtext;
            m_SDLtext = nullptr;
        }
        m_currentCharSize = text.length() + 1;
        m_SDLtext = new char[m_currentCharSize];
        std::wcstombs(m_SDLtext, text.c_str(), text.size());
        m_SDLtext[m_currentCharSize - 1] = L'\0';
        setSDLText();
    }
}

bool Text::setSDLText()
{
    if (m_string == "" && m_wstring == L"") return false;

    auto checkFontParam = [this](sf::Font *font, bool normalText)
    {
        if (m_characterSize != font->getSize() ||
            m_style != font->m_SDLFontStyle ||
            (!normalText && m_outlineThickness != font->m_SDLoutlineFontSize))
        {
            bool fontExists(false);
            for (unsigned int _I(0); _I < is::IS_ENGINE_SDL_AUTO_GENERATE_FONT.size(); _I++)
            {
                if (is::IS_ENGINE_SDL_AUTO_GENERATE_FONT[_I]->getFileName() == font->getFileName() &&
                    is::IS_ENGINE_SDL_AUTO_GENERATE_FONT[_I]->getSize() == m_characterSize &&
                    is::IS_ENGINE_SDL_AUTO_GENERATE_FONT[_I]->m_SDLFontStyle == m_style &&
                    is::IS_ENGINE_SDL_AUTO_GENERATE_FONT[_I]->m_SDLoutlineFontSize == m_outlineThickness)
                {
                    if (normalText) m_font = is::IS_ENGINE_SDL_AUTO_GENERATE_FONT[_I];
                    else m_outlineFont = is::IS_ENGINE_SDL_AUTO_GENERATE_FONT[_I];
                    fontExists = true;
                    break;
                }
            }
            if (!fontExists)
            {
                is::IS_ENGINE_SDL_AUTO_GENERATE_FONT.push_back(new Font(font->getFileName(), m_characterSize));
                is::IS_ENGINE_SDL_AUTO_GENERATE_FONT[is::IS_ENGINE_SDL_AUTO_GENERATE_FONT.size() - 1]->m_SDLFontStyle = m_style;
                TTF_SetFontStyle(is::IS_ENGINE_SDL_AUTO_GENERATE_FONT[is::IS_ENGINE_SDL_AUTO_GENERATE_FONT.size() - 1]->getSDLFont(), m_style);
                if (!normalText)
                {
                    is::IS_ENGINE_SDL_AUTO_GENERATE_FONT[is::IS_ENGINE_SDL_AUTO_GENERATE_FONT.size() - 1]->m_SDLoutlineFontSize = m_outlineThickness;
                    TTF_SetFontOutline(is::IS_ENGINE_SDL_AUTO_GENERATE_FONT[is::IS_ENGINE_SDL_AUTO_GENERATE_FONT.size() - 1]->getSDLFont(), m_outlineThickness);
                    m_outlineFont = is::IS_ENGINE_SDL_AUTO_GENERATE_FONT[is::IS_ENGINE_SDL_AUTO_GENERATE_FONT.size() - 1];
                }
                else m_font = is::IS_ENGINE_SDL_AUTO_GENERATE_FONT[is::IS_ENGINE_SDL_AUTO_GENERATE_FONT.size() - 1];
            }
        }
    };
    checkFontParam(m_font, true);
    if (m_outlineThickness > 0.f) checkFontParam(m_outlineFont, false);

    if (m_SDLtext == nullptr) return false;
    m_multiLines = false;
    short line(0), maxCaracter(0), caracter(0);
    char currentStr[100];
    char finalStr[100];
    for (size_t i(0); i < strlen(m_SDLtext); i++)
    {
        if (m_SDLtext[i] != '\n')
        {
            if (m_SDLtext[i] == '.') currentStr[caracter] = '-';
            else if (m_SDLtext[i] == ' ' && m_SDLcontainMultiSpaces) currentStr[caracter] = '_';
            else currentStr[caracter] = m_SDLtext[i];
        }
        caracter++;
        if (m_SDLtext[i] == '\n' || (i == strlen(m_SDLtext) - 1 && m_multiLines))
        {
            currentStr[caracter - 1] = '\0';
            if (caracter > maxCaracter)
            {
                strcpy(finalStr, currentStr);
                maxCaracter = caracter;
                m_multiLines = true;
            }
            caracter = 0;
            line++;
        }
    }

    int w(0), h(0);
    if (line > 0)
    {
        if (TTF_SizeText((m_outlineThickness == 0) ? m_font->getSDLFont() : m_outlineFont->getSDLFont(), finalStr, &w, &h)) {/* allow to show error */}
        w += ((m_characterSize > 30) ? 6 : 0) + m_SDLaddTextRecWSize;
    }

    auto createTexture = [this, &line, &w, &h](SDL_Surface *surface, bool normalText)
    {
        surface = NULL;
        surface = TTF_RenderText_Blended_Wrapped((normalText) ? m_font->getSDLFont() : m_outlineFont->getSDLFont(),
                                                      m_SDLtext,
                                                      (normalText) ? getSDLColor(false) : getSDLOutlineColor(),
                                                      ((line == 0) ? 1280 : w));
        if (surface != NULL)
        {
            SDL_Texture *texture = NULL;
            if (normalText)
            {
                if (m_SDLtexture != NULL)
                {
                    SDL_DestroyTexture(m_SDLtexture);
                    m_SDLtexture = NULL;
                }
                m_SDLtexture = SDL_CreateTextureFromSurface(is::IS_ENGINE_SDL_renderer, surface);
                texture = m_SDLtexture;
            }
            else
            {
                if (m_SDLoutlineTexture != NULL)
                {
                    SDL_DestroyTexture(m_SDLoutlineTexture);
                    m_SDLoutlineTexture = NULL;
                }
                m_SDLoutlineTexture = SDL_CreateTextureFromSurface(is::IS_ENGINE_SDL_renderer, surface);
                texture = m_SDLoutlineTexture;
            }
            if (texture != NULL)
            {
                if (normalText) setSize(surface->w, surface->h);
                {
                    m_SDLoutlineTextureRec.width = surface->w;
                    m_SDLoutlineTextureRec.height = surface->h;
                }
                /*if (m_multiLines)
                {
                    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                        "Text: w: %f h: %f \n<%s> line: %d char: %d\n",
                        m_size.x, m_size.y, finalStr, line, maxCaracter);
                }*/
                SDL_FreeSurface(surface);
                surface = NULL;
            }
            else
            {
                SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Texture Text (\"%s\") : %s\n", m_SDLtext, SDL_GetError());
                return false;
            }
        }
        else
        {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Surface Text (\"%s\") : %s\n", m_SDLtext, TTF_GetError());
            return false;
        }
        return true;
    };

    bool createdSuccessfully = createTexture(m_SDLsurface, true);
    if (m_outlineThickness > 0) createdSuccessfully = createTexture(m_SDLsurface, false);
    return createdSuccessfully;
}

View::View()
{
    setSize(640.f, 480.f);
    setCenter(320.f, 240.f);
}

View::View(const Vector2f& center, const Vector2f& size)
{
    setSize(size.x, size.y);
    setCenter(center.x, center.y);
}

void View::setCenter(float x, float y)
{
    is::setVector2(m_center, x, y);
}

void View::setSize(float width, float height)
{
    is::setVector2(m_size, width, height);
}

const Vector2f& View::getCenter() const noexcept
{
    return m_center;
}

void RectangleShape::draw(View const &view)
{
    SDL_Rect rec;
    SDL_SetRenderDrawColor(is::IS_ENGINE_SDL_renderer, m_color.r, m_color.g, m_color.b, m_color.a);
    rec.x = ((m_position.x - m_origin.x) - (view.getCenter().x - (view.getSize().x / 2.f))) * is::IS_ENGINE_SDL_screenXScale;
    rec.y = ((m_position.y - m_origin.y) - (view.getCenter().y - (view.getSize().y / 2.f))) * is::IS_ENGINE_SDL_screenYScale;
    rec.w = (m_size.x * std::abs(m_scale.x)) * is::IS_ENGINE_SDL_screenXScale;
    rec.h = (m_size.y * std::abs(m_scale.y)) * is::IS_ENGINE_SDL_screenYScale;
    SDL_RenderFillRect(is::IS_ENGINE_SDL_renderer, &rec);

    if (m_outlineThickness > 0.f)
    {
        for (int i(0); i < static_cast<int>(m_outlineThickness); i++)
        {
            SDL_Rect recOutline;
            SDL_SetRenderDrawColor(is::IS_ENGINE_SDL_renderer, m_outlineColor.r, m_outlineColor.g, m_outlineColor.b, m_outlineColor.a);
            recOutline.x = rec.x + i;
            recOutline.y = rec.y + i;
            recOutline.w = rec.w - i * 2;
            recOutline.h = rec.h - i * 2;
            SDL_RenderDrawRect(is::IS_ENGINE_SDL_renderer, &recOutline);
        }
    }
}

void CircleShape::draw(View const &view)
{
    auto drawCircle = [this, &view](sf::Color const &color, int size)
    {
        SDL_SetRenderDrawColor(is::IS_ENGINE_SDL_renderer, color.r, color.g, color.b, color.a);
        for (int w = 0; w < size * 2; w++)
        {
            for (int h = 0; h < size * 2; h++)
            {
                int dx = size - w; // horizontal offset
                int dy = size - h; // vertical offset
                if ((dx * dx + dy * dy) <= (size * size))
                {
                    SDL_RenderDrawPoint(is::IS_ENGINE_SDL_renderer,
                                        ((m_position.x - m_origin.x) - (view.getCenter().x - (view.getSize().x / 2.f))) * is::IS_ENGINE_SDL_screenXScale + dx,
                                        ((m_position.y - m_origin.y) - (view.getCenter().y - (view.getSize().y / 2.f))) * is::IS_ENGINE_SDL_screenYScale + dy);
                }
            }
        }
    };
    if (m_outlineThickness > 0.f) drawCircle(m_outlineColor, m_size.x);
    drawCircle(m_color, m_size.x - static_cast<int>(m_outlineThickness));
}

bool Keyboard::isKeyPressed(Key key)
{
    const Uint8 *state = SDL_GetKeyboardState(NULL);

    // These keys have the same ID
    if (key == Return) key = Enter;
    if (key == Numpad0) key = Num0;
    if (key == Numpad1) key = Num1;
    if (key == Numpad2) key = Num2;
    if (key == Numpad3) key = Num3;
    if (key == Numpad4) key = Num4;
    if (key == Numpad5) key = Num5;
    if (key == Numpad6) key = Num6;
    if (key == Numpad7) key = Num7;
    if (key == Numpad8) key = Num8;
    if (key == Numpad9) key = Num9;
    if (key == Numpad9) key = Num9;
    if (key == BackSpace) key = Backspace;
    if (key == BackSlash) key = Backslash;
    if (key == SemiColon) key = Semicolon;

    switch (key)
    {
    case A: if(state[SDL_SCANCODE_A]) return true; break;
    case B: if(state[SDL_SCANCODE_B]) return true; break;
    case C: if(state[SDL_SCANCODE_C]) return true; break;
    case D: if(state[SDL_SCANCODE_D]) return true; break;
    case E: if(state[SDL_SCANCODE_E]) return true; break;
    case F: if(state[SDL_SCANCODE_F]) return true; break;
    case G: if(state[SDL_SCANCODE_G]) return true; break;
    case H: if(state[SDL_SCANCODE_H]) return true; break;
    case I: if(state[SDL_SCANCODE_I]) return true; break;
    case J: if(state[SDL_SCANCODE_J]) return true; break;
    case K: if(state[SDL_SCANCODE_K]) return true; break;
    case L: if(state[SDL_SCANCODE_L]) return true; break;
    case M: if(state[SDL_SCANCODE_M]) return true; break;
    case N: if(state[SDL_SCANCODE_N]) return true; break;
    case O: if(state[SDL_SCANCODE_O]) return true; break;
    case P: if(state[SDL_SCANCODE_P]) return true; break;
    case Q: if(state[SDL_SCANCODE_Q]) return true; break;
    case R: if(state[SDL_SCANCODE_R]) return true; break;
    case S: if(state[SDL_SCANCODE_S]) return true; break;
    case T: if(state[SDL_SCANCODE_T]) return true; break;
    case U: if(state[SDL_SCANCODE_U]) return true; break;
    case V: if(state[SDL_SCANCODE_V]) return true; break;
    case W: if(state[SDL_SCANCODE_W]) return true; break;
    case X: if(state[SDL_SCANCODE_X]) return true; break;
    case Y: if(state[SDL_SCANCODE_Y]) return true; break;
    case Z: if(state[SDL_SCANCODE_Z]) return true; break;
    case Num0: if(state[SDL_SCANCODE_0]) return true; break;
    case Num1: if(state[SDL_SCANCODE_1]) return true; break;
    case Num2: if(state[SDL_SCANCODE_2]) return true; break;
    case Num3: if(state[SDL_SCANCODE_3]) return true; break;
    case Num4: if(state[SDL_SCANCODE_4]) return true; break;
    case Num5: if(state[SDL_SCANCODE_5]) return true; break;
    case Num6: if(state[SDL_SCANCODE_6]) return true; break;
    case Num7: if(state[SDL_SCANCODE_7]) return true; break;
    case Num8: if(state[SDL_SCANCODE_8]) return true; break;
    case Num9: if(state[SDL_SCANCODE_9]) return true; break;
    case Escape: if(state[SDL_SCANCODE_ESCAPE]) return true; break;
    case LControl: if(state[SDL_SCANCODE_LCTRL]) return true; break;
    case LShift: if(state[SDL_SCANCODE_LSHIFT]) return true; break;
    case LAlt: if(state[SDL_SCANCODE_LALT]) return true; break;
    //case LSystem: if(state[SDL_SCANCODE_LEFT_SUPER]) return true; break;
    case RControl: if(state[SDL_SCANCODE_RCTRL]) return true; break;
    case RShift: if(state[SDL_SCANCODE_RSHIFT]) return true; break;
    case RAlt: if(state[SDL_SCANCODE_RALT]) return true; break;
    //case RSystem: if(state[SDL_SCANCODE_RIGHT_SUPER]) return true; break;
    case Menu: if(state[SDL_SCANCODE_MENU]) return true; break;
    case LBracket: if(state[SDL_SCANCODE_LEFTBRACKET]) return true; break;
    case RBracket: if(state[SDL_SCANCODE_RIGHTBRACKET]) return true; break;
    case Semicolon: if(state[SDL_SCANCODE_SEMICOLON]) return true; break;
    case Comma: if(state[SDL_SCANCODE_COMMA]) return true; break;
    case Period: if(state[SDL_SCANCODE_PERIOD]) return true; break;
    case Slash: if(state[SDL_SCANCODE_SLASH]) return true; break;
    case Backslash: if(state[SDL_SCANCODE_BACKSLASH]) return true; break;
    case Equal: if(state[SDL_SCANCODE_EQUALS]) return true; break;
    case Space: if(state[SDL_SCANCODE_SPACE]) return true; break;
    case Enter:
    // case Return: same value as Enter
        if(state[SDL_SCANCODE_RETURN]) return true;
    break;
    case Backspace: if(state[SDL_SCANCODE_BACKSPACE]) return true; break;
    case Tab: if(state[SDL_SCANCODE_TAB]) return true; break;
    case PageUp: if(state[SDL_SCANCODE_PAGEUP]) return true; break;
    case PageDown: if(state[SDL_SCANCODE_PAGEDOWN]) return true; break;
    case End: if(state[SDL_SCANCODE_END]) return true; break;
    case Home: if(state[SDL_SCANCODE_HOME]) return true; break;
    case Insert: if(state[SDL_SCANCODE_INSERT]) return true; break;
    case Delete: if(state[SDL_SCANCODE_DELETE]) return true; break;
    //case Add: if(state[SDL_SCANCODE_KP_ADD]) return true; break;
    //case Subtract: if(state[SDL_SCANCODE_KP_SUBTRACT]) return true; break;
    case Multiply: if(state[SDL_SCANCODE_KP_MULTIPLY]) return true; break;
    case Divide: if(state[SDL_SCANCODE_KP_DIVIDE]) return true; break;
    case Left: if(state[SDL_SCANCODE_LEFT]) return true; break;
    case Right: if(state[SDL_SCANCODE_RIGHT]) return true; break;
    case Up: if(state[SDL_SCANCODE_UP]) return true; break;
    case Down: if(state[SDL_SCANCODE_DOWN]) return true; break;
    /*
    case Numpad0: if(state[SDL_SCANCODE_0]) return true; break;
    case Numpad1: if(state[SDL_SCANCODE_1]) return true; break;
    case Numpad2: if(state[SDL_SCANCODE_2]) return true; break;
    case Numpad3: if(state[SDL_SCANCODE_3]) return true; break;
    case Numpad4: if(state[SDL_SCANCODE_4]) return true; break;
    case Numpad5: if(state[SDL_SCANCODE_5]) return true; break;
    case Numpad6: if(state[SDL_SCANCODE_6]) return true; break;
    case Numpad7: if(state[SDL_SCANCODE_7]) return true; break;
    case Numpad8: if(state[SDL_SCANCODE_8]) return true; break;
    case Numpad9: if(state[SDL_SCANCODE_9]) return true; break;
    */
    case F1: if(state[SDL_SCANCODE_F1]) return true; break;
    case F2: if(state[SDL_SCANCODE_F2]) return true; break;
    case F3: if(state[SDL_SCANCODE_F3]) return true; break;
    case F4: if(state[SDL_SCANCODE_F4]) return true; break;
    case F5: if(state[SDL_SCANCODE_F5]) return true; break;
    case F6: if(state[SDL_SCANCODE_F6]) return true; break;
    case F7: if(state[SDL_SCANCODE_F7]) return true; break;
    case F8: if(state[SDL_SCANCODE_F8]) return true; break;
    case F9: if(state[SDL_SCANCODE_F9]) return true; break;
    case F10: if(state[SDL_SCANCODE_F10]) return true; break;
    case F11: if(state[SDL_SCANCODE_F11]) return true; break;
    case F12: if(state[SDL_SCANCODE_F12]) return true; break;
    case F13: if(state[SDL_SCANCODE_F13]) return true; break;
    case F14: if(state[SDL_SCANCODE_F14]) return true; break;
    case F15: if(state[SDL_SCANCODE_F15]) return true; break;
    case Pause: if(state[SDL_SCANCODE_PAUSE]) return true; break;
    /*
    case BackSpace: if(state[SDL_SCANCODE_BACKSPACE]) return true; break;
    case BackSlash: if(state[SDL_SCANCODE_BACKSLASH]) return true; break;
    case SemiColon: if(state[SDL_SCANCODE_SEMICOLON]) return true; break;
    */
    default: return false; break;
    }
    return false;
}

VideoMode VideoMode::getDesktopMode()
{
    VideoMode videoMode;
    videoMode.width = is::IS_ENGINE_SDL_displayMode.w;
    videoMode.height = is::IS_ENGINE_SDL_displayMode.h;
    return videoMode;
}

RenderWindow::~RenderWindow()
{
    if (m_SDLiconSurface != NULL)
    {
        SDL_FreeSurface(m_SDLiconSurface);
        m_SDLiconSurface = NULL;
    }
}

void RenderWindow::create(VideoMode videoMode, const std::string& title, int style)
{
    is::setVector2(m_size, videoMode.width, videoMode.height);
    m_view.setSize(videoMode.width, videoMode.height);
    m_title = title;
    m_style = style;

    int w, h;
#if defined(__ANDROID__)
    w = is::IS_ENGINE_SDL_displayMode.w;
    h = is::IS_ENGINE_SDL_displayMode.h;
#else
    SDL_GetWindowSize(is::IS_ENGINE_SDL_window, &w, &h);
#endif

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "init SDL Video : %s\n", SDL_GetError());
        is::closeApplication();
    }

    // Allows to calculate the scale of the screen
    is::IS_ENGINE_SDL_screenXScale = w / m_view.getSize().x;
    is::IS_ENGINE_SDL_screenYScale = h / m_view.getSize().y;

    is::IS_ENGINE_SDL_window = SDL_CreateWindow(m_title.c_str(),
#if !defined(__ANDROID__)
            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_size.x, m_size.y, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL
#else
             SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, m_size.x, m_size.y, SDL_WINDOW_OPENGL
#endif
            );
    is::IS_ENGINE_SDL_renderer = SDL_CreateRenderer(is::IS_ENGINE_SDL_window, -1, SDL_RENDERER_ACCELERATED);

    if (!is::SDL2initLib()) is::closeApplication();
}

void RenderWindow::setFramerateLimit(int fps)
{
    // m_windowFrameLimit = 1000 / fps;
    m_windowFrameLimit = (fps * 50) / 60;
}

void RenderWindow::setSize(const Vector2u& size)
{
    is::setVector2(m_size, size.x, size.y);
    SDL_SetWindowSize(is::IS_ENGINE_SDL_window, size.x, size.y);
}

void RenderWindow::setTitle(const std::string& text)
{
    m_title = text;
    SDL_SetWindowTitle(is::IS_ENGINE_SDL_window, m_title.c_str());
}

void RenderWindow::setView(const View& view)
{
    m_view = view;

    // When we change the size of the view we recalculate the scale of the screen
    int w, h;
#if defined(__ANDROID__)
    w = is::IS_ENGINE_SDL_displayMode.w;
    h = is::IS_ENGINE_SDL_displayMode.h;
#else
    SDL_GetWindowSize(is::IS_ENGINE_SDL_window, &w, &h);
#endif

    is::IS_ENGINE_SDL_screenXScale = w / m_view.getSize().x;
    is::IS_ENGINE_SDL_screenYScale = h / m_view.getSize().y;
}

void RenderWindow::setPosition(Vector2i position)
{
    SDL_SetWindowPosition(is::IS_ENGINE_SDL_window, position.x, position.y);
}

void RenderWindow::setPosition(int x, int y)
{
    SDL_SetWindowPosition(is::IS_ENGINE_SDL_window, x, y);
}

void RenderWindow::setVerticalSyncEnabled(bool vsync)
{
    SDL_GL_SetSwapInterval(vsync);
}

void RenderWindow::setIcon(Uint32 width, Uint32 height, const Uint8* pixels)
{
    // This part is automatically managed when we define the icon in the "resource.rc" file
}

void RenderWindow::clear(sf::Color const &color)
{
    SDL_SetRenderDrawColor(is::IS_ENGINE_SDL_renderer, color.r, color.g, color.b, color.a);
    SDL_RenderClear(is::IS_ENGINE_SDL_renderer);
}

void RenderWindow::draw(SDLTexture &obj)
{
    if (obj.getSDLTexture() == NULL) return;

    SDL_Rect rec;
    SDL_Rect recSrc;
    SDL_Point point;

    // We keep the value of the origin x and y of the object to be drawn.
    // This allows to keep the value of the original variables intact during recalculations.
    float objOriginX((obj.getScale().x < 0.f /*&& static_cast<int>(obj.getOrigin().y) == 0*/ &&
                      static_cast<int>(obj.getOrigin().x) == 0) ? obj.getTextureRect().width : obj.getOrigin().x);
    float objOriginY((obj.getScale().y < 0.f /*&& static_cast<int>(obj.getOrigin().x) == 0*/ &&
                      static_cast<int>(obj.getOrigin().y) == 0) ? obj.getTextureRect().height : obj.getOrigin().y);
    float xOrigin(objOriginX);
    float yOrigin(objOriginY);

    // Image angle
    float rotation(obj.getRotation());

    // Use to stretch the image of the object to make a scale effect
    rec.w = obj.getTextureRect().width * std::abs(obj.getScale().x);
    rec.h = obj.getTextureRect().height * std::abs(obj.getScale().y);

    // Each time the image is scale, the origin of the object is recalculated
    if (std::abs(obj.getScale().x) > 1.001f || std::abs(obj.getScale().x) < 0.999f)
        xOrigin = rec.w / (obj.getTextureRect().width / objOriginX);
    if (std::abs(obj.getScale().y) > 1.001f || std::abs(obj.getScale().y) < 0.999f)
        yOrigin = rec.h / (obj.getTextureRect().height / objOriginY);

    // We do a corresponding flip according to the sign of the variables x scale and y scale
    if (obj.getScale().x < 0.f && obj.getScale().y < 0.f)
    {
        obj.m_SDLFlip = (SDL_RendererFlip)(SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL);
        if (static_cast<int>(obj.getOrigin().x) != static_cast<int>(obj.getTextureRect().width / 2) &&
            static_cast<int>(obj.getOrigin().x) != 0)
            xOrigin += obj.getTextureRect().width;
        if (static_cast<int>(obj.getOrigin().y) != static_cast<int>(obj.getTextureRect().height / 2) &&
            static_cast<int>(obj.getOrigin().y) != 0)
            yOrigin -= obj.getTextureRect().height;
    }
    else if (obj.getScale().x < 0.f)
    {
        obj.m_SDLFlip = SDL_FLIP_HORIZONTAL;
        if (static_cast<int>(obj.getOrigin().x) != static_cast<int>(obj.getTextureRect().width / 2) &&
            static_cast<int>(obj.getOrigin().x) != 0) xOrigin += obj.getTextureRect().width;
    }
    else if (obj.getScale().y < 0.f)
    {
        obj.m_SDLFlip = SDL_FLIP_VERTICAL;
        if (static_cast<int>(obj.getOrigin().y) != static_cast<int>(obj.getTextureRect().height / 2) &&
            static_cast<int>(obj.getOrigin().y) != 0)
            yOrigin -= obj.getTextureRect().height;
    }
    else obj.m_SDLFlip = SDL_FLIP_NONE;

    // Move the object according to the position of the camera
    rec.x = (obj.getPosition().x - xOrigin) - (m_view.getCenter().x - (m_view.getSize().x / 2.f));
    rec.y = (obj.getPosition().y - yOrigin) - (m_view.getCenter().y - (m_view.getSize().y / 2.f));

    // We apply the scale of the screen to the object in order to resize it in relation to the screen
    rec.x *= is::IS_ENGINE_SDL_screenXScale;
    rec.y *= is::IS_ENGINE_SDL_screenYScale;
    rec.w *= is::IS_ENGINE_SDL_screenXScale;
    rec.h *= is::IS_ENGINE_SDL_screenYScale;
    recSrc.x = obj.getTextureRect().left;
    recSrc.y = obj.getTextureRect().top;
    recSrc.w = obj.getTextureRect().width;
    recSrc.h = obj.getTextureRect().height;
    point.x = xOrigin * is::IS_ENGINE_SDL_screenXScale;
    point.y = yOrigin * is::IS_ENGINE_SDL_screenYScale;

    if (obj.getTextureRect().width == obj.getTextureRect().height && rec.w != rec.h &&
        obj.m_circleShape && std::abs(obj.getRotation()) > 0 &&
        std::abs(obj.getScale().x) == std::abs(obj.getScale().y))
    {
        auto redimImg = [this](int &destSize, int &destPos, int &destOrigin, float &origin,
                               int const &srcSize, int const &size, float const &objOrigin)
        {
            destPos += (destSize - srcSize) / 2;
            destSize = srcSize;
            if (std::abs(objOrigin) > 0.f) origin = destSize / (size / objOrigin);
            destOrigin = origin;
        };
        if (rec.w > rec.h) redimImg(rec.w, rec.x, point.x, xOrigin,
                                    rec.h, obj.getTextureRect().width, objOriginX);
        else redimImg(rec.h, rec.y, point.y, yOrigin,
                      rec.w, obj.getTextureRect().height, objOriginY);
    }

    if (obj.m_SDLTextureType == SDLTexture::SDLTextureType::IS_ENGINE_SDL_TEXT)
    {
        if (obj.getSDLOutlineTexture() != NULL)
        {
            SDL_SetTextureBlendMode(obj.getSDLOutlineTexture(), SDL_BLENDMODE_BLEND);
            SDL_SetTextureAlphaMod(obj.getSDLOutlineTexture(), obj.getColor().a);

            SDL_Rect SDLoutlineTextureRec, outlineTextureRecSrc;
            SDLoutlineTextureRec.x = rec.x;
            SDLoutlineTextureRec.y = rec.y;
            SDLoutlineTextureRec.w = obj.m_SDLoutlineTextureRec.width * std::abs(obj.getScale().x);
            SDLoutlineTextureRec.h = obj.m_SDLoutlineTextureRec.height * std::abs(obj.getScale().y);
            SDLoutlineTextureRec.w *= is::IS_ENGINE_SDL_screenXScale;
            SDLoutlineTextureRec.h *= is::IS_ENGINE_SDL_screenYScale;

            outlineTextureRecSrc.x = obj.getTextureRect().left;
            outlineTextureRecSrc.y = obj.getTextureRect().top;
            outlineTextureRecSrc.w = obj.m_SDLoutlineTextureRec.width;
            outlineTextureRecSrc.h = obj.m_SDLoutlineTextureRec.height;

            SDL_RenderCopyEx(is::IS_ENGINE_SDL_renderer, obj.getSDLOutlineTexture(),
                             &outlineTextureRecSrc, &SDLoutlineTextureRec, rotation, &point, obj.m_SDLFlip);
        }
    }
    SDL_SetTextureBlendMode(obj.getSDLTexture(), SDL_BLENDMODE_BLEND);
    SDL_SetTextureAlphaMod(obj.getSDLTexture(), obj.getColor().a);
    SDL_SetTextureColorMod(obj.getSDLTexture(), obj.getColor().r, obj.getColor().g, obj.getColor().b);
    SDL_RenderCopyEx(is::IS_ENGINE_SDL_renderer, obj.getSDLTexture(), &recSrc, &rec, rotation, &point, obj.m_SDLFlip);
}

void RenderWindow::display()
{
    SDL_RenderPresent(is::IS_ENGINE_SDL_renderer);
    if (m_windowFrameLimit != 0)
    {
        Uint64 diff = std::chrono::duration_cast<std::chrono::milliseconds>(
                std::chrono::steady_clock::now() - m_timeSinceLastDisplay).count();

        if (diff < 1000 / m_windowFrameLimit)
        {
            SDL_Delay(static_cast<Uint32>(1000 / m_windowFrameLimit - diff));
        }
    }
    m_timeSinceLastDisplay = std::chrono::steady_clock::now();
}

bool RenderWindow::pollEvent(Event &event)
{
    int pollEvenValue = SDL_PollEvent(&event.m_event);
    event.type = event.m_event.type;
    event.key.code = event.m_event.key.keysym.sym;
    if (event.type == sf::Event::MouseButtonPressed || event.type == sf::Event::MouseButtonReleased)
    {
        switch(event.m_event.button.button)
        {
        case SDL_BUTTON_LEFT: event.key.code = sf::Mouse::Left; break;
        case SDL_BUTTON_RIGHT: event.key.code = sf::Mouse::Right; break;
        case SDL_BUTTON_MIDDLE: event.key.code = sf::Mouse::Middle; break;
        case SDL_BUTTON_X1: event.key.code = sf::Mouse::XButton1; break;
        case SDL_BUTTON_X2: event.key.code = sf::Mouse::XButton2; break;
        }
    }
    if (event.type == sf::Event::MouseWheelMoved)
    {
        if (event.m_event.wheel.y > 0) // scroll up
        {
             event.mouseWheel.delta++;
        }
        else if (event.m_event.wheel.y < 0) // scroll down
        {
             event.mouseWheel.delta--;
        }
    }
#if defined(__ANDROID__)
    if (pollEvenValue == 1)
    {
        switch (event.m_event.type)
        {
            case SDL_FINGERDOWN:
            {
                if (is::IS_ENGINE_SDL_touchIdCount < is::IS_ENGINE_SDL_TOUCH_ID_COUNT_MAX)
                {
                    int tempTouchId = is::IS_ENGINE_SDL_touchIdCount;
                    if (is::IS_ENGINE_SDL_touchData[1].m_SDLtouchDown && !is::IS_ENGINE_SDL_touchData[0].m_SDLtouchDown) tempTouchId = 0;
                    is::IS_ENGINE_SDL_touchData[tempTouchId].m_SDLtouchX = (event.m_event.tfinger.x * is::IS_ENGINE_SDL_displayMode.w) / is::IS_ENGINE_SDL_screenXScale;
                    is::IS_ENGINE_SDL_touchData[tempTouchId].m_SDLtouchY = (event.m_event.tfinger.y * is::IS_ENGINE_SDL_displayMode.h) / is::IS_ENGINE_SDL_screenYScale;
                    is::IS_ENGINE_SDL_touchData[tempTouchId].m_SDLtouchDown = true;
                    is::IS_ENGINE_SDL_touchIdCount++;
                    if (is::IS_ENGINE_SDL_touchIdCount == 2) is::IS_ENGINE_SDL_touchIdLast = tempTouchId;
                }
            }
            break;

            case SDL_FINGERMOTION:
            {
                if (is::IS_ENGINE_SDL_enableFINGERMOTION)
                {
                    if (is::IS_ENGINE_SDL_touchIdCount == 1)
                    {
                        int tempTouchId = 0;
                        if (is::IS_ENGINE_SDL_touchData[1].m_SDLtouchDown && !is::IS_ENGINE_SDL_touchData[0].m_SDLtouchDown) tempTouchId = 1;
                        is::IS_ENGINE_SDL_touchData[tempTouchId].m_SDLtouchX = (event.m_event.tfinger.x * is::IS_ENGINE_SDL_displayMode.w) / is::IS_ENGINE_SDL_screenXScale;
                        is::IS_ENGINE_SDL_touchData[tempTouchId].m_SDLtouchY = (event.m_event.tfinger.y * is::IS_ENGINE_SDL_displayMode.h) / is::IS_ENGINE_SDL_screenYScale;
                    }
                    if (is::IS_ENGINE_SDL_touchIdCount == 2)
                    {
                        is::IS_ENGINE_SDL_touchData[is::IS_ENGINE_SDL_touchIdLast].m_SDLtouchX = (event.m_event.tfinger.x * is::IS_ENGINE_SDL_displayMode.w) / is::IS_ENGINE_SDL_screenXScale;
                        is::IS_ENGINE_SDL_touchData[is::IS_ENGINE_SDL_touchIdLast].m_SDLtouchY = (event.m_event.tfinger.y * is::IS_ENGINE_SDL_displayMode.h) / is::IS_ENGINE_SDL_screenYScale;
                    }
                }
            }
            break;

            case SDL_FINGERUP:
            {
                if (is::IS_ENGINE_SDL_touchIdCount > 0)
                {
                    int releaseTouchX = (event.m_event.tfinger.x * is::IS_ENGINE_SDL_displayMode.w) / is::IS_ENGINE_SDL_screenXScale;
                    int releaseTouchY = (event.m_event.tfinger.y * is::IS_ENGINE_SDL_displayMode.h) / is::IS_ENGINE_SDL_screenYScale;

                    int nearTouchId = 0;
                    if (is::IS_ENGINE_SDL_touchIdCount == 2)
                    {
                        float disTouch0 = is::pointDistance(releaseTouchX, releaseTouchY, is::IS_ENGINE_SDL_touchData[0].m_SDLtouchX, is::IS_ENGINE_SDL_touchData[0].m_SDLtouchY);
                        float disTouch1 = is::pointDistance(releaseTouchX, releaseTouchY, is::IS_ENGINE_SDL_touchData[1].m_SDLtouchX, is::IS_ENGINE_SDL_touchData[1].m_SDLtouchY);
                        nearTouchId = ((disTouch0 > disTouch1) ? 1 : 0);
                    }
                    else if (is::IS_ENGINE_SDL_touchData[1].m_SDLtouchDown) nearTouchId = 1;

                    is::IS_ENGINE_SDL_touchData[nearTouchId].m_SDLtouchX = 0;
                    is::IS_ENGINE_SDL_touchData[nearTouchId].m_SDLtouchY = 0;
                    is::IS_ENGINE_SDL_touchData[nearTouchId].m_SDLtouchDown = false;
                    is::IS_ENGINE_SDL_touchIdCount--;
                }
            }
            break;
            case SDL_WINDOWEVENT_RESIZED:
                event.size.width = event.m_event.window.data1;
                event.size.height = event.m_event.window.data2;
            break;
        }
    }
#endif
    if (event.type == 0 || event.type == 512 || event.type == 1024)
        event.type = ((SDL_GetWindowFlags(is::IS_ENGINE_SDL_window) & SDL_WINDOW_INPUT_FOCUS) ? -1 : -2);
    return ((pollEvenValue == 1) ? true : false);
}

bool RenderWindow::waitEvent(Event &event)
{
    while (!pollEvent(event)) continue;
    return true;
}

Vector2i RenderWindow::getPosition() const
{
    int x = 0, y = 0;
    SDL_GetWindowPosition(is::IS_ENGINE_SDL_window, &x, &y);
    return Vector2i(x, y);
}

Vector2f RenderWindow::mapPixelToCoords(const Vector2i& point, const View& view) const
{
    Vector2f pos{static_cast<float>((point.x
#if !defined(__ANDROID__)
            / is::IS_ENGINE_SDL_screenXScale
#endif
            ) + (view.getCenter().x - (view.getSize().x / 2.f))),
            static_cast<float>((point.y
#if !defined(__ANDROID__)
            / is::IS_ENGINE_SDL_screenYScale
#endif
            ) + (view.getCenter().y - (view.getSize().y / 2.f)))};
    return pos;
}

void SoundBuffer::setChannelId()
{
    m_channel = SDL_sndChannel++;
    for (int i(0); i < is::IS_ENGINE_SDL_CHANNEL_MAX; i++)
    {
        if (is::IS_ENGINE_SDL_channel[i] == m_channel)
        {
            m_channel = 0;
            break;
        }
    }
    for (int i(0); i < is::IS_ENGINE_SDL_CHANNEL_MAX; i++)
    {
        if (is::IS_ENGINE_SDL_channel[i] == m_channel) m_channel++; else break;
    }
    is::IS_ENGINE_SDL_channel[m_channel] = m_channel;
}

SoundBuffer::SoundBuffer()
{
    setChannelId();
}

SoundBuffer::SoundBuffer(const std::string filename):
    m_filename(filename)
{
    setChannelId();
    loadSound(m_filename);
}

SoundBuffer::~SoundBuffer()
{
    SDL_sndChannel--;
    is::IS_ENGINE_SDL_channel[m_channel] = -1;
    Mix_FreeChunk(m_SDLsound);
    m_SDLsound = NULL;
}

bool SoundBuffer::loadSound(const std::string& filePath)
{
    m_SDLsound = Mix_LoadWAV(filePath.c_str());
    if (m_SDLsound == NULL)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Can't load SoundBuffer : %s \"%s\"\n", Mix_GetError(), filePath.c_str());
        return false;
    }
    return true;
}

Sound::Status Sound::getStatus()
{
    if (m_status != Status::Paused)
    {
        if (Mix_Playing(m_SDLsoundBuffer->getSDLChannel()) == 0) m_status = Stopped;
    }
    return m_status;
}

void Sound::play()
{
    if (m_status != Status::Paused)
    {
        Mix_PlayChannel(m_SDLsoundBuffer->getSDLChannel(), m_SDLsoundBuffer->getSDLChunk(), ((m_loop) ? -1 : 0));
    }
    else
    {
        Mix_Resume(m_SDLsoundBuffer->getSDLChannel());
    }
    m_status = Status::Playing;
}

void Sound::setPitch(float speed)
{
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "This function is not yet implemented!");
}

void Sound::setVolume(float volume)
{
    if (static_cast<int>(volume) >= 0 && static_cast<int>(volume) <= 100) Mix_VolumeChunk(m_SDLsoundBuffer->getSDLChunk(), volume * MIX_MAX_VOLUME / 100);
}

Music::Music() :
#if !defined(__ANDROID__)
    SoundSource()
{
    Mix_VolumeMusic(MIX_MAX_VOLUME);
#else
    Sound()
{
#endif
}

Music::~Music()
{
#if defined(__ANDROID__)
    if (m_SDLsoundBuffer != nullptr)
    {
        delete m_SDLsoundBuffer;
        m_SDLsoundBuffer = nullptr;
    }
#else
    Mix_FreeMusic(m_music);
    m_music = NULL;
#endif
}

Music::Status Music::getStatus()
{
    if (m_status != Status::Paused)
    {
#if !defined(__ANDROID__)
        if (Mix_PlayingMusic() == 0) m_status = Stopped;
#else
        if (Mix_Playing(m_SDLsoundBuffer->getSDLChannel()) == 0) m_status = Stopped;
#endif
    }
    return m_status;
}

#if !defined(__ANDROID__)
void Music::play()
{
    if (m_status != Status::Paused)
    {
        Mix_PlayMusic(m_music, ((m_loop) ? -1 : 0));
    }
    else
    {
        Mix_ResumeMusic();
    }
    m_status = Status::Playing;
}

void Music::setPitch(float speed)
{
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "This function is not yet implemented!");
}

void Music::setVolume(float volume)
{
    if (static_cast<int>(volume) >= 0 && static_cast<int>(volume) <= 100) Mix_VolumeMusic(volume * MIX_MAX_VOLUME / 100);
}
#endif
bool Music::openFromFile(const std::string& filePath)
{
#if defined(__ANDROID__)
    if (m_SDLsoundBuffer != nullptr)
    {
        delete m_SDLsoundBuffer;
        m_SDLsoundBuffer = nullptr;
    }
    m_SDLsoundBuffer = new SoundBuffer();
    return m_SDLsoundBuffer->loadFromFile(filePath.c_str());
#else
    m_music = Mix_LoadMUS(filePath.c_str());
    if (m_music == NULL)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Can't load Music : %s \"%s\"\n", Mix_GetError(), filePath.c_str());
        return false;
    }
    return true;
#endif
}

bool Mouse::isButtonPressed(Button button)
{
    return (getSDLButtonState() & SDL_BUTTON(button));
}

Vector2i Mouse::getPosition()
{
    int x = 0, y = 0;
#if !defined(IS_ENGINE_HTML_5)
    SDL_GetGlobalMouseState
#else
    SDL_GetMouseState
#endif
        (&x, &y);
    return Vector2i(x, y);
}

Vector2i Mouse::getPosition(const RenderWindow& relativeTo)
{
    return getPosition()
#if !defined(IS_ENGINE_HTML_5)
        - relativeTo.getPosition()
#endif
     ;
}

void Mouse::setPosition(const Vector2i& position)
{
    SDL_WarpMouseGlobal(position.x, position.y);
}

void Mouse::setPosition(const Vector2i& position, const RenderWindow& relativeTo)
{
    SDL_WarpMouseInWindow(is::IS_ENGINE_SDL_window, position.x, position.y);
}

Uint32 Mouse::getSDLButtonState()
{
    return SDL_GetMouseState(NULL, NULL);
}

bool Touch::isDown(unsigned int finger)
{
    if (finger <= is::IS_ENGINE_SDL_TOUCH_ID_COUNT_MAX)
    {
        return is::IS_ENGINE_SDL_touchData[finger].m_SDLtouchDown;
    }
    return false;
}

Vector2i Touch::getPosition(unsigned int finger)
{
    Vector2i pos{0, 0};
    if (finger <= is::IS_ENGINE_SDL_TOUCH_ID_COUNT_MAX)
    {
        pos.x = is::IS_ENGINE_SDL_touchData[finger].m_SDLtouchX;
        pos.y = is::IS_ENGINE_SDL_touchData[finger].m_SDLtouchY;
    }
    return pos;
}

Vector2i Touch::getPosition(unsigned int finger, const RenderWindow& relativeTo)
{
    return getPosition(finger);
}
}
#endif
