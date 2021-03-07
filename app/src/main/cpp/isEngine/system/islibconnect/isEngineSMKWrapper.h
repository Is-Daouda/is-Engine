/*
  is::Engine (Infinity Solution Engine)
  Copyright (C) 2018-2021 Is Daouda <isdaouda.n@gmail.com>

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

#ifndef ISENGINESMKWRAPPER_H_INCLUDED
#define ISENGINESMKWRAPPER_H_INCLUDED

#include "isEngineWrapper.h"

#if defined(IS_ENGINE_HTML_5)
#include <smk/Audio.hpp>
#include <smk/Font.hpp>
#include <smk/Input.hpp>
#include <smk/Rectangle.hpp>
#include <smk/Shape.hpp>
#include <smk/Sound.hpp>
#include <smk/SoundBuffer.hpp>
#include <smk/Sprite.hpp>
#include <smk/Text.hpp>
#include <smk/Texture.hpp>
#include <smk/Vibrate.hpp>
#include <smk/Framebuffer.hpp>
#include <smk/Window.hpp>

namespace sf
{
class Color;
void setObjectWrapperColor(Color &color, float red, float green, float blue, float alpha);

class Color
{
public:
    float r, g, b, a;
    Color(): r(1.f), g(1.f), b(1.f), a(1.f) {}

    Color(float red, float green, float blue, float alpha): r(1.f), g(1.f), b(1.f), a(1.f)
    {
        setObjectWrapperColor(*this, red, green, blue, alpha);
    }
    Color(float red, float green, float blue): r(1.f), g(1.f), b(1.f), a(1.f)
    {
        setObjectWrapperColor(*this, red, green, blue, a);
    }

    static glm::vec4 RGBA(float red, float green, float blue, float alpha) {return {red, green, blue, alpha};}
    static glm::vec4 RGB(float red, float green, float blue) {return {red, green, blue, 1.f};}

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

    void operator =(const glm::vec4 &color)
    {
        r = color[0];
        g = color[1];
        b = color[2];
        a = color[3];
    }
    void operator =(const Color &color)
    {
        r = color.r;
        g = color.g;
        b = color.b;
        a = color.a;
    }
};

class Texture : public smk::Texture
{
public:
    Texture(): smk::Texture() {}
    Texture(const std::string& filename);

    const Vector2u& getSize() const noexcept
    {
        return m_size;
    }
/*
    void loadFromImage()  {functionNotSupported("Texture", "loadFromImage", "loadSFMLTexture");}
    void loadFromFile()   {functionNotSupported("Texture", "loadFromFile", "loadSFMLTexture");}
    void loadFromMemory() {functionNotSupported("Texture", "loadFromMemory", "loadSFMLTexture");}
    void loadFromStream() {functionNotSupported("Texture", "loadFromStream", "loadSFMLTexture");}
*/
private:
    Vector2u m_size;
};

class View : public smk::View
{
public:
    View(const Vector2f& center, const Vector2f& size);
    View(const FloatRect& rectangle);
    View();

    void setCenter(float x, float y)
    {
        is::setVector2(m_center, x, y);
        SetCenter(x, y);
    }
    void setCenter(const Vector2f& center)
    {
        setCenter(center.x, center.y);
    }
    void setSize(float width, float height)
    {
        is::setVector2(m_size, width, height);
        SetSize(m_size.x, m_size.y);
    }
    void setSize(const Vector2f& size)
    {
        setSize(size.x, size.y);
    }

    const Vector2f& getSize() const noexcept {return m_size;}
    const Vector2f& getCenter() const noexcept {return m_center;}

private:
    sf::Vector2f m_size;
    sf::Vector2f m_center;
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

class Event {};

class RenderWindow : public smk::Window, public ViewManager
{
public:
    RenderWindow(): smk::Window() {}
    RenderWindow(int width, int height, const std::string& title):
        smk::Window(width, height, title)
    {
        is::setVector2(m_size, width, height);
    }

    void setFramerateLimit(float fps) {LimitFrameRate(fps);}
    void setSize(const Vector2u& size) {is::setVector2(m_size, size.x, size.y);}
/*
    void setTitle(const String& text) {functionNotSupported("RenderWindow", "setTitle");}
*/
    void setView(const View& view)
    {
        m_view = view;
        SetView(m_view);
    }

    void clear(sf::Color const &color)
    {
        is::clear(*this, color);
    }

    void clear()
    {
        is::clear(*this);
    }

    template<class T1>
    void draw(T1 &obj)
    {
        is::draw(*this, obj);
    }

    template<class T1>
    void draw(T1 *obj)
    {
        is::draw(this, obj);
    }

    void display()
    {
        is::display(*this);
    }
    void close() {is::closeApplication();}
/*
    bool pollEvent(Event &event)
    {
        functionNotSupported("RenderWindow", "pollEvent");
        return false;
    }
*/
};

class RenderTexture;
static void createRenderTexture(RenderTexture &renderTexture, unsigned int width, unsigned int height);

class RenderTexture : public smk::Framebuffer, public ViewManager
{
public:
    RenderTexture(): smk::Framebuffer(0, 0)
    {
        m_texture = static_cast<Texture*>(&color_texture);
    }

    RenderTexture(unsigned int width, unsigned int height):
        smk::Framebuffer(width, height)
    {
        m_texture = static_cast<Texture*>(&color_texture);
    }

    bool create(unsigned int width, unsigned int height)
    {
        createRenderTexture(*this, width, height);
        is::setVector2(m_size, width, height);
        return true;
    }

    template<class T1>
    void clear(T1 &color)
    {
        is::clear(*this, color);
    }

    template<class T1>
    void draw(T1 &obj)
    {
        is::draw(*this, obj);
    }

    template<class T1>
    void draw(T1 *obj)
    {
        is::draw(this, obj);
    }
/*
    void display() {functionNotSupported("RenderTexture", "display");}

    const Texture& getTexture() const
    {
        functionNotSupported("RenderTexture", "getTexture");
        return *m_texture;
    }
*/
private:
    Texture *m_texture = nullptr;
};

void createRenderTexture(RenderTexture &renderTexture, unsigned int width, unsigned int height)
{
    renderTexture = sf::RenderTexture(width, height);
}

template <class T>
class ObjectWrapper : public T
{
public:
    ObjectWrapper()
    {
        is::setVector2(m_size, 0.f, 0.f);
        is::setVector2(m_scale, 1.f, 1.f);
    }

    explicit ObjectWrapper(smk::Transformable shape) : T(shape) {is::setVector2(m_scale, 1.f, 1.f);}

    ObjectWrapper(Texture &texture) :
        T(texture),
        m_texture(&(texture))
    {
        is::setVector2(m_size, texture.width(), texture.height());
        is::setVector2(m_scale, 1.f, 1.f);
    }
    ObjectWrapper(RenderTexture &renderTexture) :
        T(renderTexture),
        m_renderTexture(&(renderTexture))
    {
        is::setVector2(m_size, renderTexture.getSize().x, renderTexture.getSize().y);
        is::setVector2(m_scale, 1.f, 1.f);
    }

    ObjectWrapper(smk::Font& font) : T(font)
    {
        is::setVector2(ObjectWrapper::m_size, T::ComputeDimensions().x, T::ComputeDimensions().y);
        is::setVector2(m_scale, 1.f, 1.f);
    }
    ObjectWrapper(smk::Font& font, const std::string& text): T(font, text)
    {
        is::setVector2(m_size, T::ComputeDimensions().x, T::ComputeDimensions().y);
        is::setVector2(m_scale, 1.f, 1.f);
    }
    ObjectWrapper(smk::Font& font, const std::wstring& text): T(font, text)
    {
        is::setVector2(m_size, T::ComputeDimensions().x, T::ComputeDimensions().y);
        is::setVector2(m_scale, 1.f, 1.f);
    }
    void setPosition(float x, float y)
    {
        is::setVector2(m_position, x, y);
        T::SetPosition(m_position.x, m_position.y);
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
        T::SetScale(x, y);
    }
    void setScale(const Vector2f &v)
    {
        setScale(v.x, v.y);
    }
    void scale(float x, float y)
    {
        is::setVector2(m_scale, m_scale.x + x, m_scale.y + y);
        T::SetScale(m_scale.x, m_scale.y);
    }
    void scale(const Vector2f &v)
    {
        setScale(v.x, v.y);
    }
    virtual void setSize(float x, float y)
    {
        is::setVector2(m_size, x, y);
    }
    virtual void setSize(const Vector2f &size)
    {
        setSize(size.x, size.y);
    }
    void setOrigin(float x, float y)
    {
        is::setVector2(m_origin, x, y);
        T::SetCenter(x, y);
    }
    void setOrigin(const Vector2f &v)
    {
        setOrigin(v.x, v.y);
    }
    void setRotation(float angle)
    {
        m_rotation = static_cast<float>(fmod(angle, 360));
        if (m_rotation < 0)
            m_rotation += 360.f;
        T::SetRotation(-m_rotation);
    }
    void rotate(float angle)
    {
        setRotation(m_rotation + angle);
    }
    virtual void setColor(float r, float g, float b, float a)
    {
        setObjectWrapperColor(m_color, r, g, b, a);
        T::SetColor(smk::Color::RGBA(m_color.r, m_color.g, m_color.b, m_color.a));
    }
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
    RenderTexture* getRenderTexture() const {return m_renderTexture;}
    virtual const Rect getTextureRect() const noexcept
    {
        Rect aabb;
        aabb.width = m_size.x;
        aabb.height = m_size.y;
        return aabb;
    }

protected:
    Texture *m_texture = nullptr;
    RenderTexture *m_renderTexture = nullptr;
    float m_rotation = 0.f;
    Vector2f m_position;
    Vector2f m_scale;
    Vector2f m_size;
    Vector2f m_origin;
    Color m_color;
};

class Shape : public ObjectWrapper<smk::Transformable>
{
public:
    Shape(smk::Transformable shape) : ObjectWrapper(shape) {}
    virtual void setSize(float x, float y);
    virtual void setSize(const Vector2f &size)
    {
        setSize(size.x, size.y);
    }
    void setOrigin(float x, float y) {;}
    void setOrigin(const Vector2f &v) {;}
};

class CircleShape : public Shape
{
public:
    CircleShape();
    CircleShape(float raduis) : Shape(smk::Shape::Circle(raduis)) {is::setVector2(m_size, raduis, raduis);}
    void setRadius(float raduis);
    float getRadius() {return m_size.x;}
};

class RectangleShape : public Shape
{
public:
    static smk::Transformable RoundedRectangle(float width, float height, float radius);
    RectangleShape();
    RectangleShape(float width, float height, float raduis = 0.f) : Shape(RoundedRectangle(width, height, raduis))
    {
        is::setVector2(ObjectWrapper::m_size, width, height);
    }
    RectangleShape(const Vector2f &size) : Shape(RoundedRectangle(size.x, size.y, 0.f))
    {
        ObjectWrapper::m_size = size;
        is::setVector2(ObjectWrapper::m_size, size.x, size.y);
    }
};

class Sprite : public ObjectWrapper<smk::Sprite>
{
public:
    Sprite() : ObjectWrapper() {}
    Sprite(Texture &texture) : ObjectWrapper(texture) {}
    Sprite(RenderTexture &renderTexture) : ObjectWrapper(renderTexture) {}

    void setTexture(sf::Texture& texture);
    void setTextureRect(IntRect rec);
};

class Font : public smk::Font
{
public:
    Font() {}
    Font(const std::string& filename, float line_height);
    const std::string& getFileName() const noexcept {return m_filename;}
    float getSize() const {return m_size;}
/*
    void loadFromFile()   {functionNotSupported("Font", "loadFromFile", "loadSFMLFont");}
    void loadFromMemory() {functionNotSupported("Font", "loadFromMemory", "loadSFMLFont");}
    void loadFromStream() {functionNotSupported("Font", "loadFromStream", "loadSFMLFont");}
*/
private:
    float m_size = 0.f;
    std::string m_filename = "";
};

class Text : public ObjectWrapper<smk::Text>
{
public:
    Text() {}
    Text(sf::Font& font) :
        ObjectWrapper(font)
    {
        m_font = &font;
    }
    Text(sf::Font& font, const std::string& text) :
        ObjectWrapper(font, text)
    {
        m_font = &font;
    }
    Text(sf::Font& font, const std::wstring& text):
        ObjectWrapper(font, text)
    {
        m_font = &font;
    }

    void setString(const std::wstring& text)
    {
        m_wstring = text;
        SetString(text);
        is::setVector2(m_size, ComputeDimensions().x, ComputeDimensions().y);
    }
    void setString(const wchar_t& text)
    {
        m_wstring = text;
        SetString(m_wstring);
        is::setVector2(m_size, ComputeDimensions().x, ComputeDimensions().y);
    }
    void setString(const std::string& text)
    {
        m_string = text;
        SetString(text);
        is::setVector2(m_size, ComputeDimensions().x, ComputeDimensions().y);
    }
    void setString(const char& text)
    {
        m_string = text;
        SetString(m_string);
        is::setVector2(m_size, ComputeDimensions().x, ComputeDimensions().y);
    }
    void setFont(sf::Font &font) {SetFont(font);}

    Font *getFont() const {return m_font;}
    const std::string &getString() const noexcept
    {
        return m_string;
    }
    const std::wstring &getWString() const noexcept
    {
        return m_wstring;
    }
    float getCharacterSize() {return m_font->getSize();}

private:
    Font *m_font = nullptr;
    std::string m_string;
    std::wstring m_wstring;
};

class SoundBuffer : public smk::SoundBuffer
{
public:
    SoundBuffer() {}
    SoundBuffer(const std::string filename):
        smk::SoundBuffer(filename),
        m_filename(filename)
    {}
    const std::string& getFileName() const noexcept {return m_filename;}
/*
    void loadFromFile()    {functionNotSupported("SoundBuffer", "loadFromFile", "loadSFMLSoundBuffer");}
    void loadFromMemory()  {functionNotSupported("SoundBuffer", "loadFromMemory", "loadSFMLSoundBuffer");}
    void loadFromStream()  {functionNotSupported("SoundBuffer", "loadFromStream", "loadSFMLSoundBuffer");}
    void loadFromSamples() {functionNotSupported("SoundBuffer", "loadFromSamples", "loadSFMLSoundBuffer");}
*/
private:
    std::string m_filename = "";
};

class Sound : public smk::Sound, public SoundSource
{
public:
    Sound() {}
    Sound(const SoundBuffer& buffer) :
        smk::Sound(buffer),
        SoundSource()
        {}

    void play()
    {
        Play();
        m_status = Status::Playing;
    }
    void pause()
    {
        Stop();
        m_status = Status::Paused;
    }
    void stop()
    {
        Stop();
        m_status = Status::Stopped;
    }
    void setLoop(bool loop)
    {
        SetLoop(loop);
    }
    void setVolume(float volume);
};

class Music : public Sound
{
public:
    explicit Music() {}
    Music(const SoundBuffer& buffer) : Sound(buffer) {}
/*
    void openFromFile()   {functionNotSupported("Music", "openFromFile", "loadSFMLMusic");}
    void openFromMemory() {functionNotSupported("Music", "openFromMemory", "loadSFMLMusic");}
    void openFromStream() {functionNotSupported("Music", "openFromStream", "loadSFMLMusic");}
*/
};

class Keyboard
{
public:
    enum Key
    {
        Unknown = -1,                      ///< Unhandled key
        A = GLFW_KEY_A,                    ///< The A key
        B = GLFW_KEY_B,                    ///< The B key
        C = GLFW_KEY_C,                    ///< The C key
        D = GLFW_KEY_D,                    ///< The D key
        E = GLFW_KEY_E,                    ///< The E key
        F = GLFW_KEY_F,                    ///< The F key
        G = GLFW_KEY_G,                    ///< The G key
        H = GLFW_KEY_H,                    ///< The H key
        I = GLFW_KEY_I,                    ///< The I key
        J = GLFW_KEY_J,                    ///< The J key
        K = GLFW_KEY_K,                    ///< The K key
        L = GLFW_KEY_L,                    ///< The L key
        M = GLFW_KEY_M,                    ///< The M key
        N = GLFW_KEY_N,                    ///< The N key
        O = GLFW_KEY_O,                    ///< The O key
        P = GLFW_KEY_P,                    ///< The P key
        Q = GLFW_KEY_Q,                    ///< The Q key
        R = GLFW_KEY_R,                    ///< The R key
        S = GLFW_KEY_S,                    ///< The S key
        T = GLFW_KEY_T,                    ///< The T key
        U = GLFW_KEY_U,                    ///< The U key
        V = GLFW_KEY_V,                    ///< The V key
        W = GLFW_KEY_W,                    ///< The W key
        X = GLFW_KEY_X,                    ///< The X key
        Y = GLFW_KEY_Y,                    ///< The Y key
        Z = GLFW_KEY_Z,                    ///< The Z key
        Num0 = GLFW_KEY_0,                 ///< The 0 key
        Num1 = GLFW_KEY_1,                 ///< The 1 key
        Num2 = GLFW_KEY_2,                 ///< The 2 key
        Num3 = GLFW_KEY_3,                 ///< The 3 key
        Num4 = GLFW_KEY_4,                 ///< The 4 key
        Num5 = GLFW_KEY_5,                 ///< The 5 key
        Num6 = GLFW_KEY_6,                 ///< The 6 key
        Num7 = GLFW_KEY_7,                 ///< The 7 key
        Num8 = GLFW_KEY_8,                 ///< The 8 key
        Num9 = GLFW_KEY_9,                 ///< The 9 key
        Escape = GLFW_KEY_ESCAPE,          ///< The Escape key
        LControl = GLFW_KEY_LEFT_CONTROL,  ///< The left Control key
        LShift = GLFW_KEY_LEFT_SHIFT,      ///< The left Shift key
        LAlt = GLFW_KEY_LEFT_ALT,          ///< The left Alt key
        LSystem = GLFW_KEY_LEFT_SUPER,     ///< The left OS specific key: window (Windows and Linux), apple (MacOS X), ...
        RControl = GLFW_KEY_RIGHT_CONTROL, ///< The right Control key
        RShift = GLFW_KEY_RIGHT_SHIFT,     ///< The right Shift key
        RAlt = GLFW_KEY_RIGHT_ALT,         ///< The right Alt key
        RSystem = GLFW_KEY_RIGHT_SUPER,    ///< The right OS specific key: window (Windows and Linux), apple (MacOS X), ...
        Menu = GLFW_KEY_MENU,              ///< The Menu key
        LBracket = GLFW_KEY_LEFT_BRACKET,  ///< The [ key
        RBracket = GLFW_KEY_RIGHT_BRACKET, ///< The ] key
        Semicolon = GLFW_KEY_SEMICOLON,    ///< The ; key
        Comma = GLFW_KEY_COMMA,            ///< The , key
        Period = GLFW_KEY_PERIOD,          ///< The . key
        Slash = GLFW_KEY_SLASH,            ///< The / key
        Backslash = GLFW_KEY_BACKSLASH,    ///< The \ key
        Equal = GLFW_KEY_EQUAL,            ///< The = key
        Space = GLFW_KEY_SPACE,            ///< The Space key
        Enter = GLFW_KEY_ENTER,            ///< The Enter/Return keys
        Backspace = GLFW_KEY_BACKSPACE,    ///< The Backspace key
        Tab = GLFW_KEY_TAB,                ///< The Tabulation key
        PageUp = GLFW_KEY_PAGE_UP,         ///< The Page up key
        PageDown = GLFW_KEY_PAGE_DOWN,     ///< The Page down key
        End = GLFW_KEY_END,                ///< The End key
        Home = GLFW_KEY_HOME,              ///< The Home key
        Insert = GLFW_KEY_INSERT,          ///< The Insert key
        Delete = GLFW_KEY_DELETE,          ///< The Delete key
        Add = GLFW_KEY_KP_ADD,             ///< The + key
        Subtract = GLFW_KEY_KP_SUBTRACT,   ///< The - key (minus, usually from numpad)
        Multiply = GLFW_KEY_KP_MULTIPLY,   ///< The * key
        Divide = GLFW_KEY_KP_DIVIDE,       ///< The / key
        Left = GLFW_KEY_LEFT,              ///< Left arrow
        Right = GLFW_KEY_RIGHT,            ///< Right arrow
        Up = GLFW_KEY_UP,                  ///< Up arrow
        Down = GLFW_KEY_DOWN,              ///< Down arrow
        Numpad0 = GLFW_KEY_0,              ///< The numpad 0 key
        Numpad1 = GLFW_KEY_1,              ///< The numpad 1 key
        Numpad2 = GLFW_KEY_2,              ///< The numpad 2 key
        Numpad3 = GLFW_KEY_3,              ///< The numpad 3 key
        Numpad4 = GLFW_KEY_4,              ///< The numpad 4 key
        Numpad5 = GLFW_KEY_5,              ///< The numpad 5 key
        Numpad6 = GLFW_KEY_6,              ///< The numpad 6 key
        Numpad7 = GLFW_KEY_7,              ///< The numpad 7 key
        Numpad8 = GLFW_KEY_8,              ///< The numpad 8 key
        Numpad9 = GLFW_KEY_9,              ///< The numpad 9 key
        F1 = GLFW_KEY_F1,                  ///< The F1 key
        F2 = GLFW_KEY_F2,                  ///< The F2 key
        F3 = GLFW_KEY_F3,                  ///< The F3 key
        F4 = GLFW_KEY_F4,                  ///< The F4 key
        F5 = GLFW_KEY_F5,                  ///< The F5 key
        F6 = GLFW_KEY_F6,                  ///< The F6 key
        F7 = GLFW_KEY_F7,                  ///< The F7 key
        F8 = GLFW_KEY_F8,                  ///< The F8 key
        F9 = GLFW_KEY_F9,                  ///< The F9 key
        F10 = GLFW_KEY_F10,                ///< The F10 key
        F11 = GLFW_KEY_F11,                ///< The F11 key
        F12 = GLFW_KEY_F12,                ///< The F12 key
        F13 = GLFW_KEY_F13,                ///< The F13 key
        F14 = GLFW_KEY_F14,                ///< The F14 key
        F15 = GLFW_KEY_F15,                ///< The F15 key
        Pause = GLFW_KEY_PAUSE,            ///< The Pause key

        BackSpace = GLFW_KEY_BACKSPACE,    ///< \deprecated Use Backspace instead
        BackSlash = GLFW_KEY_BACKSLASH,    ///< \deprecated Use Backslash instead
        SemiColon = GLFW_KEY_SEMICOLON,    ///< \deprecated Use Semicolon instead
        Return    = Enter                  ///< \deprecated Use Enter instead
    };
};

class Mouse
{
public:
    enum Button
    {
        Left = GLFW_MOUSE_BUTTON_LEFT,     ///< The left mouse button
        Right = GLFW_MOUSE_BUTTON_RIGHT,   ///< The right mouse button
        Middle = GLFW_MOUSE_BUTTON_MIDDLE, ///< The middle (wheel) mouse button
    };

    static Vector2i getPosition(RenderWindow &window);
};

class Touch
{
public:
    static Vector2i getPosition(unsigned int finger, RenderWindow &window);
};
}

// Init OpenAL.
static smk::Audio audio;
#endif // defined

#endif // ISENGINESMKWRAPPER_H_INCLUDED
