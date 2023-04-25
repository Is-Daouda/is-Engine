/*
  is::Engine (Infinity Solutions Engine)
  Copyright (C) 2018-2023 Is Daouda <isdaouda.n@gmail.com>

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

#ifndef ISENGINESDLWRAPPER_H_INCLUDED
#define ISENGINESDLWRAPPER_H_INCLUDED

#include "isEngineWrapper.h"

#if defined(IS_ENGINE_SDL_2)

#if defined(__ANDROID__)
#include <jni.h>
#include <android/native_activity.h>
#endif

#if defined(IS_ENGINE_HTML_5)
#include <emscripten.h>
#endif

#include <exception>
#include <string>
#include <iostream>
#include <vector>
#include <chrono>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

namespace is
{
extern SDL_Window *IS_ENGINE_SDL_window;
extern SDL_Renderer *IS_ENGINE_SDL_renderer;
extern SDL_DisplayMode IS_ENGINE_SDL_displayMode; // Used to determine the size of a window

/// Allows to use touch functions
extern bool IS_ENGINE_MOBILE_OS;

/// Allow to avoid bug
static bool IS_ENGINE_SDL_closeWindow = false;

/// These variables are used to store the scale of the screen in order to
/// resize the images on Android (Sprite, Text, ...)
extern float IS_ENGINE_SDL_screenXScale, IS_ENGINE_SDL_screenYScale;

/// Max SDL Sound Channel
static const short IS_ENGINE_SDL_CHANNEL_MAX = 60;

/// Allow to avoid duplicates
extern short IS_ENGINE_SDL_channel[IS_ENGINE_SDL_CHANNEL_MAX];

/// Class that allows to manage touchdowns
class TouchData
{
public:
    bool m_SDLtouchDown;
    int m_SDLtouchX;
    int m_SDLtouchY;
};

/// Maximum number of fingers to have on the screen
static const short IS_ENGINE_SDL_TOUCH_ID_COUNT_MAX = 2;

/// Stores the different fingers used on the screen
extern TouchData IS_ENGINE_SDL_touchData[IS_ENGINE_SDL_TOUCH_ID_COUNT_MAX];

/// Allows to enable SDL_FINGERMOTION event
extern bool IS_ENGINE_SDL_enableFINGERMOTION;

/// The last fingers id
extern short IS_ENGINE_SDL_touchIdLast;

/// Count the number of fingers on the screen
extern short IS_ENGINE_SDL_touchIdCount;

/// Allows to initialize the resources of the SDL library
bool SDL2initLib();

/// Allows to free the resources of the SDL library at the end of the program
void SDL2freeLib();
}

namespace sf
{
class Color
{
public:
    int r, g, b, a;
    Color(): r(255), g(255), b(255), a(255) {}

    Color(int red, int green, int blue, int alpha): r(red), g(green), b(blue), a(alpha) {}
    Color(int red, int green, int blue): r(red), g(green), b(blue), a(255) {}

    static Color White; ///< White
    static Color Black; ///< Black
    static Color Grey; ///< Grey
    static Color Red; ///< Red
    static Color Green; ///< Green
    static Color Blue; ///< Blue
    static Color Yellow; ///< Yellow
    static Color Magenta; ///< Magenta
    static Color Cyan; ///< Cyan
    static Color Transparent; ///< Transparent

    void operator =(const Color &color)
    {
        r = color.r;
        g = color.g;
        b = color.b;
        a = color.a;
    }
};

class Texture
{
public:
    Texture() {}

    Texture(const std::string& filename) {loadSurface(filename);}

    ~Texture();

    const Vector2u& getSize() const noexcept
    {
        return m_size;
    }

    bool loadFromFile(const std::string& filename)
    {
        return loadSurface(filename);
    }

    SDL_Surface* getSDLSurface() const {return m_SDLsurface;}

    const std::string &getFileName() const noexcept
    {
        return m_filename;
    }
/*
    void loadFromImage()  {functionNotSupported("Texture", "loadFromImage", "loadSFMLTexture");}
    void loadFromMemory() {functionNotSupported("Texture", "loadFromMemory", "loadSFMLTexture");}
    void loadFromStream() {functionNotSupported("Texture", "loadFromStream", "loadSFMLTexture");}
*/
private:
    SDL_Surface *m_SDLsurface = NULL;
    Vector2u m_size;
    std::string m_filename = "";
    bool loadSurface(const std::string& filePath);
};

class Font
{
public:
    Font() {}

    Font(const std::string& filename, int size): m_size(size) {loadFont(filename);}

    ~Font();

    int m_SDLoutlineFontSize = 0;
    Uint32 m_SDLFontStyle = TTF_STYLE_NORMAL;

    void setSDLFontSize(int size) {m_size = size;}

    const std::string& getFileName() const noexcept {return m_filename;}

    int getSize() const {return m_size;}

    bool loadFromFile(const std::string& filename) {return loadFont(filename);}

    TTF_Font* getSDLFont() const {return m_SDLfont;}

/*  void loadFromMemory() {functionNotSupported("Font", "loadFromMemory", "loadSFMLFont");}
    void loadFromStream() {functionNotSupported("Font", "loadFromStream", "loadSFMLFont");}
*/
private:
    TTF_Font *m_SDLfont = NULL;
    int m_size = 20;
    std::string m_filename = "";

    bool loadFont(const std::string& filename);
};
}

namespace is
{
/// auto generate font container
/// Allows to store fonts that will be used to manipulate the
/// size of texts
extern std::vector<sf::Font*> IS_ENGINE_SDL_AUTO_GENERATE_FONT;
}

namespace sf
{
class Transformable
{
public:
    Transformable();

    Transformable(Texture &texture);

    void setPosition(float x, float y)
    {
        is::setVector2(m_position, x, y);
    }

    void setPosition(const Vector2f &v)
    {
        setPosition(v.x, v.y);
    }

    void move(const Vector2f &v)
    {
        move(v.x, v.y);
    }

    void move(float x, float y)
    {
        setPosition(m_position.x + x, m_position.y + y);
    }

    void setScale(float x, float y)
    {
        is::setVector2(m_scale, x, y);
    }

    void setScale(const Vector2f &v)
    {
        setScale(v.x, v.y);
    }

    void scale(float x, float y)
    {
        is::setVector2(m_scale, m_scale.x + x, m_scale.y + y);
    }

    void scale(const Vector2f &v)
    {
        setScale(v.x, v.y);
    }

    virtual void setSize(float x, float y)
    {
        is::setVector2(m_size, x, y);
        m_textureRec.width = x;
        m_textureRec.height = y;
    }

    virtual void setSize(const Vector2f &size)
    {
        setSize(size.x, size.y);
    }

    void setOrigin(float x, float y)
    {
        is::setVector2(m_origin, x, y);
    }

    void setOrigin(const Vector2f &v)
    {
        setOrigin(v.x, v.y);
    }

    void setRotation(float angle);

    void rotate(float angle)
    {
        setRotation(m_rotation + angle);
    }

    virtual void setColor(int r, int g, int b, int a);

    virtual void setColor(Color const &color)
    {
        setColor(color.r, color.g, color.b, color.a);
    }

    virtual void setFillColor(Color const &color)
    {
        setColor(color.r, color.g, color.b, color.a);
    }

    virtual const Vector2f& getPosition() const noexcept {return m_position;}

    virtual const Vector2f& getScale() const noexcept {return m_scale;}

    virtual const Vector2f& getSize() const noexcept {return m_size;}

    virtual const Vector2f& getOrigin() const noexcept {return m_origin;}

    virtual float getRotation() const {return m_rotation;}

    virtual Rect getGlobalBounds() const {return functionGetGlobalBounds(m_position, m_origin, m_size);}

    virtual const Color& getColor() const noexcept {return m_color;}

    virtual const Color& getFillColor() const noexcept {return getColor();}

    Texture* getTexture() const {return m_texture;}

    virtual const Rect getTextureRect() const noexcept {return m_textureRec;}

    virtual const SDL_Color& getSDLColor(bool getAlpha);

protected:
    SDL_Color m_SDLcolor;
    Rect m_textureRec;
    Texture *m_texture = nullptr;
    float m_rotation = 0.f;
    Vector2f m_position;
    Vector2f m_scale;
    Vector2f m_size;
    Vector2f m_origin;
    Color m_color;
};

/// Class that allows to create SDL textures in order to use it to
/// create SFML Sprites, Image and Texts.
/// On SDL texts are created using textures and surfaces
class SDLTexture : public Transformable
{
public:
    SDL_RendererFlip m_SDLFlip = SDL_FLIP_NONE;
    bool m_multiLines = false;
    bool m_circleShape = true;
    Rect m_SDLoutlineTextureRec;

    enum SDLTextureType
    {
        IS_ENGINE_SDL_SPRITE,
        IS_ENGINE_SDL_TEXT
    };

    SDLTextureType m_SDLTextureType = IS_ENGINE_SDL_SPRITE;

    SDLTexture() : Transformable() {}

    SDLTexture(Texture &texture) : Transformable(texture) {}

    ~SDLTexture();

    void setTextureRect(IntRect rec);

    SDL_Texture* getSDLTexture() const {return m_SDLtexture;}

    SDL_Texture* getSDLOutlineTexture() const {return m_SDLoutlineTexture;}

protected:
    SDL_Texture *m_SDLtexture = NULL;
    SDL_Texture *m_SDLoutlineTexture = NULL;
};

class Sprite : public SDLTexture
{
public:
    Sprite() : SDLTexture() {}
    virtual ~Sprite() {}
    Sprite(Texture &texture) : SDLTexture(texture) {setSDLTexture();}

    //-->Sprite(RenderTexture &renderTexture) : Transformable(renderTexture) {setSDLTexture();}

    void setTexture(sf::Texture& texture);

protected:
    void setSDLTexture();
};

class Image : public SDLTexture
{
public:
    Image() : SDLTexture() {}

    ~Image();

    bool loadFromFile(const std::string& filename);

    const Uint8* getPixelsPtr() const;
};

class Text : public SDLTexture
{
public:
    enum Style
    {
        Regular       = TTF_STYLE_NORMAL, ///< Regular characters, no style
        Bold          = TTF_STYLE_BOLD, ///< Bold characters
        Italic        = TTF_STYLE_ITALIC, ///< Italic characters
        Underlined    = TTF_STYLE_UNDERLINE, ///< Underlined characters
        StrikeThrough = TTF_STYLE_STRIKETHROUGH ///< Strike through characters
    };

    bool m_SDLcontainMultiSpaces = false;
    short m_SDLaddTextRecWSize = 3;
    Text(): SDLTexture() {m_SDLTextureType = IS_ENGINE_SDL_TEXT;}

    Text(sf::Font& font);

    Text(sf::Font& font, const std::string& text);

    Text(sf::Font& font, const std::wstring& text);

    ~Text();

    void setFont(sf::Font &font);

    void setString(const std::wstring& text);

    void setString(const wchar_t& text);

    void setString(const std::string& text);

    void setString(const char& text);

    void setColor(int r, int g, int b, int a);

    void setOrigin(float x, float y);

    void setColor(Color const &color)
    {
        setColor(color.r, color.g, color.b, color.a);
    }

    void setFillColor(Color const &color)
    {
        setColor(color.r, color.g, color.b, color.a);
    }

    void setCharacterSize(int size);

    void setStyle(Uint32 style);

    void setOutlineColor(const Color& color);

    void setOutlineThickness(float thickness);

    Font *getFont() const {return m_font;}

    const std::string &getString() const noexcept
    {
        return m_string;
    }

    const std::wstring &getWString() const noexcept
    {
        return m_wstring;
    }

    int getCharacterSize() {return m_characterSize;}

    Uint32 getStyle() const {return m_style;}

    const Color& getOutlineColor() const {return m_outlineColor;}

    float getOutlineThickness() const {return m_outlineThickness;}

private:
    SDL_Surface *m_SDLsurface = NULL;
    Font *m_font = nullptr;

    SDL_Surface *m_SDLoutlineSurface = NULL;
    Font *m_outlineFont = nullptr;
    SDL_Color m_SDLoutlineColor;

    const SDL_Color& getSDLOutlineColor()
    {
        m_SDLoutlineColor.r = m_outlineColor.r;
        m_SDLoutlineColor.g = m_outlineColor.g;
        m_SDLoutlineColor.b = m_outlineColor.b;
        m_SDLoutlineColor.a = m_outlineColor.a;
        return m_SDLoutlineColor;
    }

    std::string m_string = "";
    std::string m_tempString = "";
    std::wstring m_wstring = L"";
    std::wstring m_tempWstring = L"";
    int m_characterSize = 0;
    int m_currentCharSize = 0;
    char *m_SDLtext = nullptr;

    Uint32 m_style;
    Color m_outlineColor;
    int m_outlineThickness = 0;

    void setObjectText(const std::string& text);
    void setObjectText(const std::wstring& text);

    /// Used to create a text with a Texture, Surface and a font.
    bool setSDLText();
};

class View
{
public:
    View();

    View(const Vector2f& center, const Vector2f& size);

    void setCenter(float x, float y);

    void setCenter(const Vector2f& center)
    {
        setCenter(center.x, center.y);
    }

    void setSize(float width, float height);

    void setSize(const Vector2f& size)
    {
        setSize(size.x, size.y);
    }

    const Vector2f& getSize() const noexcept {return m_size;}

    const Vector2f& getCenter() const noexcept;

private:
    sf::Vector2f m_size;
    sf::Vector2f m_center;
};

class Shape : public Transformable
{
public:
    Shape() : Transformable() {}

    void setOutlineColor(const Color& color) {m_outlineColor = color;}

    void setOutlineThickness(float thickness) {m_outlineThickness = thickness;}

    virtual void draw(View const &view) = 0;

    const Color& getOutlineColor() const {return m_outlineColor;}

    float getOutlineThickness() const {return m_outlineThickness;}

protected:
    Color m_outlineColor;
    float m_outlineThickness = 0.f;
};

class RectangleShape : public Shape
{
public:
    RectangleShape() : Shape() {}

    virtual ~RectangleShape() {}

    RectangleShape(float width, float height) : Shape() {setSize(width, height);}

    RectangleShape(const Vector2f &size) : Shape() {setSize(size.x, size.y);}

    void draw(View const &view);
};

class CircleShape : public Shape
{
public:
    CircleShape(): Shape() {}

    CircleShape(float raduis) : Shape() {setRadius(raduis);}

    void setRadius(float raduis) {setSize(raduis, raduis);}

    float getRadius() {return m_size.x;}

    void draw(View const &view);
};

class ViewManager
{
public:
    const View& getView() {return m_view;}

    const View& getDefaultView() {return m_view;}

    const Vector2u& getSize() const noexcept {return m_size;}

protected:
    Vector2u m_size;
    View m_view;
};

class Keyboard
{
public:
    enum Key
    {
        Unknown = -1,                  ///< Unhandled key
        A = SDLK_a,                    ///< The A key
        B = SDLK_b,                    ///< The B key
        C = SDLK_c,                    ///< The C key
        D = SDLK_d,                    ///< The D key
        E = SDLK_e,                    ///< The E key
        F = SDLK_f,                    ///< The F key
        G = SDLK_g,                    ///< The G key
        H = SDLK_h,                    ///< The H key
        I = SDLK_i,                    ///< The I key
        J = SDLK_j,                    ///< The J key
        K = SDLK_k,                    ///< The K key
        L = SDLK_l,                    ///< The L key
        M = SDLK_m,                    ///< The M key
        N = SDLK_n,                    ///< The N key
        O = SDLK_o,                    ///< The O key
        P = SDLK_p,                    ///< The P key
        Q = SDLK_q,                    ///< The Q key
        R = SDLK_r,                    ///< The R key
        S = SDLK_s,                    ///< The S key
        T = SDLK_t,                    ///< The T key
        U = SDLK_u,                    ///< The U key
        V = SDLK_v,                    ///< The V key
        W = SDLK_w,                    ///< The W key
        X = SDLK_x,                    ///< The X key
        Y = SDLK_y,                    ///< The Y key
        Z = SDLK_z,                    ///< The Z key
        Num0 = SDLK_0,                 ///< The 0 key
        Num1 = SDLK_1,                 ///< The 1 key
        Num2 = SDLK_2,                 ///< The 2 key
        Num3 = SDLK_3,                 ///< The 3 key
        Num4 = SDLK_4,                 ///< The 4 key
        Num5 = SDLK_5,                 ///< The 5 key
        Num6 = SDLK_6,                 ///< The 6 key
        Num7 = SDLK_7,                 ///< The 7 key
        Num8 = SDLK_8,                 ///< The 8 key
        Num9 = SDLK_9,                 ///< The 9 key
        Escape =
#if !defined(__ANDROID__)
                SDLK_ESCAPE            ///< The Escape key
#else
                SDLK_AC_BACK           ///< The Back key Android
#endif
        ,
        LControl = SDLK_LCTRL,         ///< The left Control key
        LShift = SDLK_LSHIFT,          ///< The left Shift key
        LAlt = SDLK_LALT,              ///< The left Alt key
        //LSystem = SDLK_LEFT_SUPER,     ///< The left OS specific key: window (Windows and Linux), apple (MacOS X), ...
        RControl = SDLK_RCTRL,         ///< The right Control key
        RShift = SDLK_RSHIFT,          ///< The right Shift key
        RAlt = SDLK_RALT,              ///< The right Alt key
        //RSystem = SDLK_RIGHT_SUPER,    ///< The right OS specific key: window (Windows and Linux), apple (MacOS X), ...
        Menu = SDLK_MENU,              ///< The Menu key
        LBracket = SDLK_LEFTBRACKET,   ///< The [ key
        RBracket = SDLK_RIGHTBRACKET,  ///< The ] key
        Semicolon = SDLK_SEMICOLON,    ///< The ; key
        Comma = SDLK_COMMA,            ///< The , key
        Period = SDLK_PERIOD,          ///< The . key
        Slash = SDLK_SLASH,            ///< The / key
        Backslash = SDLK_BACKSLASH,    ///< The \ key
        Equal = SDLK_EQUALS,           ///< The = key
        Space = SDLK_SPACE,            ///< The Space key
        Enter = SDLK_RETURN,           ///< The Enter/Return keys
        Backspace = SDLK_BACKSPACE,    ///< The Backspace key
        Tab = SDLK_TAB,                ///< The Tabulation key
        PageUp = SDLK_PAGEUP,          ///< The Page up key
        PageDown = SDLK_PAGEDOWN,      ///< The Page down key
        End = SDLK_END,                ///< The End key
        Home = SDLK_HOME,              ///< The Home key
        Insert = SDLK_INSERT,          ///< The Insert key
        Delete = SDLK_DELETE,          ///< The Delete key
        //Add = SDLK_KP_ADD,             ///< The + key
        //Subtract = SDLK_KP_SUBTRACT,   ///< The - key (minus, usually from numpad)
        Multiply = SDLK_KP_MULTIPLY,   ///< The * key
        Divide = SDLK_KP_DIVIDE,       ///< The / key
        Left = SDLK_LEFT,              ///< Left arrow
        Right = SDLK_RIGHT,            ///< Right arrow
        Up = SDLK_UP,                  ///< Up arrow
        Down = SDLK_DOWN,              ///< Down arrow
        Numpad0 = SDLK_0,              ///< The numpad 0 key
        Numpad1 = SDLK_1,              ///< The numpad 1 key
        Numpad2 = SDLK_2,              ///< The numpad 2 key
        Numpad3 = SDLK_3,              ///< The numpad 3 key
        Numpad4 = SDLK_4,              ///< The numpad 4 key
        Numpad5 = SDLK_5,              ///< The numpad 5 key
        Numpad6 = SDLK_6,              ///< The numpad 6 key
        Numpad7 = SDLK_7,              ///< The numpad 7 key
        Numpad8 = SDLK_8,              ///< The numpad 8 key
        Numpad9 = SDLK_9,              ///< The numpad 9 key
        F1 = SDLK_F1,                  ///< The F1 key
        F2 = SDLK_F2,                  ///< The F2 key
        F3 = SDLK_F3,                  ///< The F3 key
        F4 = SDLK_F4,                  ///< The F4 key
        F5 = SDLK_F5,                  ///< The F5 key
        F6 = SDLK_F6,                  ///< The F6 key
        F7 = SDLK_F7,                  ///< The F7 key
        F8 = SDLK_F8,                  ///< The F8 key
        F9 = SDLK_F9,                  ///< The F9 key
        F10 = SDLK_F10,                ///< The F10 key
        F11 = SDLK_F11,                ///< The F11 key
        F12 = SDLK_F12,                ///< The F12 key
        F13 = SDLK_F13,                ///< The F13 key
        F14 = SDLK_F14,                ///< The F14 key
        F15 = SDLK_F15,                ///< The F15 key
        Pause = SDLK_PAUSE,            ///< The Pause key

        BackSpace = SDLK_BACKSPACE,    ///< \deprecated Use Backspace instead
        BackSlash = SDLK_BACKSLASH,    ///< \deprecated Use Backslash instead
        SemiColon = SDLK_SEMICOLON,    ///< \deprecated Use Semicolon instead
        Return    = Enter,             ///< \deprecated Use Enter instead

        Underscore = SDLK_UNDERSCORE   ///< \deprecated The Underscore (Only for SDL 2)
    };

    static bool isKeyPressed(Key key);
};

class Event
{
public:
    SDL_Event m_event;

    struct SizeEvent
    {
        unsigned int width;
        unsigned int height;
    };

    struct MouseWheelEvent
    {
        int delta; ///< Number of ticks the wheel has moved (positive is up, negative is down)
    };

    struct KeyEvent
    {
        int code;
    };

    struct TouchEvent
    {
        unsigned int finger;
        int x;
        int y;
    };

    enum EventType
    {
        Closed = SDL_QUIT,
        Resized = SDL_WINDOWEVENT_RESIZED,
        LostFocus = -2,
        GainedFocus = -1,
        MouseButtonPressed = SDL_MOUSEBUTTONDOWN,
        MouseButtonReleased = SDL_MOUSEBUTTONUP,
        MouseWheelMoved = SDL_MOUSEWHEEL,
        KeyPressed = SDL_KEYDOWN,
        KeyReleased = SDL_KEYUP,
        TouchBegan = SDL_FINGERDOWN,
        TouchMoved = SDL_FINGERMOTION,
        TouchEnded = SDL_FINGERUP,
    };

    int type;

    union
    {
        SizeEvent size;
        KeyEvent key;
        TouchEvent touch;
        MouseWheelEvent mouseWheel;
    };
};

class VideoMode
{
public:
    VideoMode() {}

    VideoMode(unsigned int modeWidth, unsigned int modeHeight, unsigned int modeBitsPerPixel = 32):
        width(modeWidth),
        height(modeHeight),
        bitsPerPixel(modeBitsPerPixel)
        {}
    static VideoMode getDesktopMode();

    unsigned int width;
    unsigned int height;
    unsigned int bitsPerPixel;
};

class RenderWindow : public ViewManager
{
public:
    RenderWindow():
        m_title(""),
        m_windowFrameLimit(1000 / 30)
     {}

    ~RenderWindow();

    void create(VideoMode videoMode, const std::string& title, int style = Style::Default);

    void setFramerateLimit(int fps);

    void setSize(const Vector2u& size);

    void setTitle(const std::string& text);

    void setView(const View& view);

    void setPosition(Vector2i position);

    void setPosition(int x, int y);

    void setVerticalSyncEnabled(bool vsync);

    void setIcon(Uint32 width, Uint32 height, const Uint8* pixels);

    void clear(sf::Color const &color);

    void clear() {clear(sf::Color::Black);}

    void draw(SDLTexture &obj);

    void draw(Shape &obj) {obj.draw(m_view);}

    void display();

    void close()
    {
        is::IS_ENGINE_SDL_closeWindow = true;
        m_isOpen = false;
    }

    bool pollEvent(Event &event);

    bool waitEvent(Event &event);

    bool isOpen() const {return m_isOpen;}

    Vector2i getPosition() const;

    Vector2f mapPixelToCoords(const Vector2i& point, const View& view) const;

private:
    SDL_Surface* m_SDLiconSurface = NULL;
    std::string m_title;
    unsigned int m_windowFrameLimit;
    int m_style;
    bool m_isOpen = true;
    float m_tempScreenXScale, m_tempScreenYScale;
    std::chrono::steady_clock::time_point m_timeSinceLastDisplay; ///< The timepoint at which Display() was last called
};

typedef sf::RenderWindow Render;

class SoundBuffer
{
public:
    static int SDL_sndChannel;

    SoundBuffer();

    SoundBuffer(const std::string filename);

    ~SoundBuffer();

    const std::string& getFileName() const noexcept {return m_filename;}

    bool loadFromFile(const std::string& filePath)
    {
        m_filename = filePath;
        return loadSound(m_filename);
    }

/*  void loadFromMemory()  {functionNotSupported("SoundBuffer", "loadFromMemory", "loadSFMLSoundBuffer");}
    void loadFromStream()  {functionNotSupported("SoundBuffer", "loadFromStream", "loadSFMLSoundBuffer");}
    void loadFromSamples() {functionNotSupported("SoundBuffer", "loadFromSamples", "loadSFMLSoundBuffer");}
*/
    Mix_Chunk* getSDLChunk() const {return m_SDLsound;}

    int getSDLChannel() const {return m_channel;}

private:
    Mix_Chunk *m_SDLsound = NULL;
    int m_channel;
    std::string m_filename = "";
    bool loadSound(const std::string& filePath);
    void setChannelId();
};

class Sound : public SoundSource
{
public:
    Sound() : SoundSource() {}

    Sound(SoundBuffer& buffer) :
        SoundSource(),
        m_SDLsoundBuffer(&buffer)
        {}

    Status getStatus();

    void play();

    void setPitch(float speed);

    void pause()
    {
        Mix_Pause(m_SDLsoundBuffer->getSDLChannel());
        m_status = Status::Paused;
    }

    void stop()
    {
        Mix_HaltChannel(m_SDLsoundBuffer->getSDLChannel());
        m_status = Status::Stopped;
    }

    void setLoop(bool loop)
    {
        m_loop = loop;
    }

    void setVolume(float volume);

    void setBuffer(SoundBuffer &soundBuffer)
    {
        m_SDLsoundBuffer = &soundBuffer;
    }

#if !defined(__ANDROID__)
private:
#else
protected:
#endif
    SoundBuffer *m_SDLsoundBuffer = nullptr;
    bool m_loop = false;
};

class Music : public
#if !defined(__ANDROID__)
        SoundSource
#else
        Sound
#endif
{
public:
    Music();

    ~Music();

    Status getStatus();
#if !defined(__ANDROID__)
    void play();

    void setPitch(float speed);

    void pause()
    {
        Mix_PauseMusic();
        m_status = Status::Paused;
    }

    void stop()
    {
        Mix_HaltMusic();
        m_status = Status::Stopped;
    }

    void setLoop(bool loop)
    {
        m_loop = loop;
    }

    void setVolume(float volume);
#endif
    bool openFromFile(const std::string& filePath);
    /*
    bool openFromMemory() {functionNotSupported("Music", "openFromMemory", "loadSFMLMusic");}
    bool openFromStream() {functionNotSupported("Music", "openFromStream", "loadSFMLMusic");}
    */
#if !defined(__ANDROID__)
private:
    Mix_Music *m_music = NULL;
    bool m_loop = false;
#endif
};

class Mouse
{
public:
    enum Button {
        Left = SDL_BUTTON_LEFT,
        Right = SDL_BUTTON_RIGHT,
        Middle = SDL_BUTTON_MIDDLE,
        XButton1 = SDL_BUTTON_X1,
        XButton2 = SDL_BUTTON_X2
    };

    static bool isButtonPressed(Button button);

    static Vector2i getPosition();

    static Vector2i getPosition(const RenderWindow& relativeTo);

    static void setPosition(const Vector2i& position);

    static void setPosition(const Vector2i& position, const RenderWindow& relativeTo);

private:
    static Uint32 getSDLButtonState();
};

class Touch
{
public:
    // define array which will save different touch id
    static bool isDown(unsigned int finger);

    static Vector2i getPosition(unsigned int finger);

    static Vector2i getPosition(unsigned int finger, const RenderWindow& relativeTo);
};
}
#endif

#endif // ISENGINESDLWRAPPER_H_INCLUDED
