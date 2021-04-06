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

#include "isEngineSMKWrapper.h"

#if defined(IS_ENGINE_HTML_5)
namespace sf
{
sf::Color Color::White       = sf::Color(1.f, 1.f, 1.f, 1.f);
sf::Color Color::Black       = sf::Color(0.f, 0.f, 0.f, 1.f);
sf::Color Color::Grey        = sf::Color(.5f, .5f, .5f, 1.f);
sf::Color Color::Red         = sf::Color(1.f, 0.f, 0.f, 1.f);
sf::Color Color::Green       = sf::Color(0.f, 1.f, 0.f, 1.f);
sf::Color Color::Blue        = sf::Color(0.f, 0.f, 1.f, 1.f);
sf::Color Color::Yellow      = sf::Color(1.f, 1.f, 0.f, 1.f);
sf::Color Color::Magenta     = sf::Color(1.f, 0.f, 1.f, 1.f);
sf::Color Color::Cyan        = sf::Color(0.f, 1.f, 1.f, 1.f);
sf::Color Color::Transparent = sf::Color(0.f, 0.f, 0.f, 0.f);

/*
Color functionGetColor(Color &color)
{
    if (color.r < 1.f) color.r *= 255;
    if (color.g < 1.f) color.g *= 255;
    if (color.b < 1.f) color.b *= 255;
    if (color.a < 1.f) color.a *= 255;
    return color;
}
*/

void setObjectWrapperColor(Color &color, float red, float green, float blue, float alpha)
{
    if (red   > 255.f) red = 255.f;
    if (red   < 0.f)   red = 0.f;
    if (green > 255.f) green = 255.f;
    if (green < 0.f)   green = 0.f;
    if (blue  > 255.f) blue = 255.f;
    if (blue  < 0.f)   blue = 0.f;
    if (alpha > 255.f) alpha = 255.f;
    if (alpha < 0.f)   alpha = 0.f;

    if (red > 1.f) color.r = red / 255.f; else color.r = red;
    if (green > 1.f) color.g = green / 255.f; else color.g = green;
    if (blue > 1.f) color.b = blue / 255.f; else color.b = blue;
    if (alpha > 1.f) color.a = alpha / 255.f; else color.a = alpha;
}

void Sprite::setTexture(sf::Texture& texture)
{
    SetTexture(texture);
    is::setVector2(m_size, texture.width(), texture.height());
    m_texture = &texture;
}

void Sprite::setTextureRect(IntRect rec)
{
    smk::Rectangle smkRec;
    smkRec.left = rec.left;
    smkRec.top = rec.top;
    smkRec.right = rec.left + rec.width;
    smkRec.bottom = rec.top + rec.height;
    SetTextureRectangle(smkRec);
    is::setVector2(m_size, smkRec.width(), smkRec.height());
}

Texture::Texture(const std::string& filename): smk::Texture(filename)
{
    is::setVector2(m_size, width(), height());
}

void Shape::setSize(float x, float y)
{
    float xScale = (x * m_scale.x) / m_size.x;
    float yScale = (y * m_scale.y) / m_size.y;
    is::setVector2(m_size, x, y);
    setScale(xScale, yScale);
}

void Shape::setPosition(float x, float y)
{
    is::setVector2(m_position, x, y);
    SetPosition((m_position.x + m_size.x / 2.f) - m_origin.x,
                (m_position.y + m_size.y / 2.f) - m_origin.y);
}

void Shape::setOrigin(float x, float y)
{
    is::setVector2(m_origin, x, y);
}

RectangleShape::RectangleShape() : Shape(RoundedRectangle(32.f, 32.f, 0.f))
{
    is::setVector2(ObjectWrapper::m_size, 32.f, 32.f);
    setPosition(0.f, 0.f);
}

CircleShape::CircleShape() : Shape(smk::Shape::Circle(32.f))
{
    is::setVector2(m_size, 32.f, 32.f);
    setPosition(0.f, 0.f);
}

void CircleShape::setRadius(float raduis)
{
    setSize(raduis, raduis);
}

smk::Transformable RectangleShape::RoundedRectangle(float width, float height, float radius)
{
    radius = std::max(radius, 0.f);
    radius = std::min(radius, width * 0.5f);
    radius = std::min(radius, height * 0.5f);

    width = width * 0.5 - radius;
    height = height * 0.5 - radius;
    std::vector<smk::Vertex> v;
    smk::Vertex p0 = {{0.f, 0.f}, {0.f, 0.f}};
    smk::Vertex p1 = {{width + radius, -height}, {0.f, 0.f}};
    smk::Vertex p2 = {{width + radius, height}, {0.f, 0.f}};

    v.push_back(p0);
    v.push_back(p1);
    v.push_back(p2);

    float angle_delta = 2.0 * M_PI / 40.f;  // 0.01f;//radius * 0.01f;

    auto center = glm::vec2(width, radius);
    for (float angle = 0.f; angle < 2.f * M_PI; angle += angle_delta)
    {
        if (angle > 0.75 * 2.f * M_PI) center = glm::vec2(width, -height);
        else if (angle > 0.5 * 2.f * M_PI) center = glm::vec2(-width, -height);
        else if (angle > 0.25 * 2.f * M_PI) center = glm::vec2(-width, +height);
        else center = glm::vec2(+width, +height);

        p1 = p2;
        p2 = {center + radius * glm::vec2(cos(angle), sin(angle)), {0.f, 0.f}};

        v.push_back(p0);
        v.push_back(p1);
        v.push_back(p2);
    }

    p1 = p2;
    p2 = {{width + radius, -height}, {0.f, 0.f}};
    v.push_back(p0);
    v.push_back(p1);
    v.push_back(p2);

    return smk::Shape::FromVertexArray(smk::VertexArray(std::move(v)));
}

Font::Font(const std::string& filename, float line_height) : smk::Font(filename, line_height)
{
    // std::cout << "line h : " << line_height << "\n";
    m_size = line_height;
    // std::cout << "size : " << m_size << "\n";
    m_filename = filename;
}

void Sound::setVolume(float volume)
{
    if (static_cast<int>(volume) >= 0 && static_cast<int>(volume) <= 100) SetVolume(volume / 100.f);
}

Sound::Status Sound::getStatus()
{
    if (m_status != Status::Paused)
    {
        if (!IsPlaying()) m_status = Stopped;
    }
    return m_status;
}

View::View(const Vector2f& center, const Vector2f& size)
{
    setSize(size.x, size.y);
    setCenter(center.x, center.y);
}

View::View()
{
    setSize(640.f, 480.f);
    setCenter(320.f, 240.f);
}

/*
sf::View(const FloatRect& rectangle)
{

}
*/

Vector2i Mouse::getPosition(RenderWindow &window)
{
    Vector2i mousePosition(-1, -1);
    glm::vec2 p1 = window.input().cursor();
    p1 -= window.dimension() * 0.125f;
    is::setVector2(mousePosition, p1[0], p1[1]);

    float addX(0.f), addY(0.f);
    float xDiv(2.95f), yDiv(2.95);
    float const x1(300.f), x2(340.f);
    float const y1(200.f), y2(300.f);

    // x < param
    if (mousePosition.x < 220.f) xDiv = 3.5f;
    if (mousePosition.x < 160.f) xDiv = 4.f;

    // x > param
    if (mousePosition.x > 380.f) xDiv = 3.5f;
    if (mousePosition.x > 440.f) xDiv = 4.f;
    if (mousePosition.x > 500.f) xDiv = 4.5f;
    if (mousePosition.x > 560.f) xDiv = 5.f;
    if (mousePosition.x > 620.f) xDiv = 5.5f;
    if (mousePosition.x > 680.f) xDiv = 6.f;
    if (mousePosition.x > 740.f) xDiv = 6.5f;
    if (mousePosition.x > 800.f) xDiv = 7.f;
    if (mousePosition.x < x1) addX = is::pointDistance(mousePosition.x, 0.f, x1, 0.f) / xDiv;
    if (mousePosition.x > x2) addX = -is::pointDistance(mousePosition.x, 0.f, x2, 0.f) / xDiv;

    // y < param
    if (mousePosition.y < 220.f) yDiv = 3.f;
    if (mousePosition.y < 70.f) yDiv = 3.5f;
    if (mousePosition.y < 10.f) yDiv = 4.f;

    // y > param
    if (mousePosition.y > 360.f) yDiv = 3.5f;
    if (mousePosition.y > 420.f) yDiv = 4.f;
    if (mousePosition.y > 480.f) yDiv = 4.5f;
    if (mousePosition.y > 540.f) yDiv = 5.f;
    if (mousePosition.y > 600.f) yDiv = 5.5f;
    if (mousePosition.y < y1) addY = is::pointDistance(0.f, mousePosition.y, 0.f, y1) / yDiv;
    if (mousePosition.y > y2) addY = -is::pointDistance(0.f, mousePosition.y, 0.f, y2) / yDiv;

    return Vector2i(mousePosition.x + addX, mousePosition.y + addY);
}

Vector2i Touch::getPosition(unsigned int finger, RenderWindow &window)
{
    Vector2i position(-1, -1);
    int _finger(0);
    for (const auto& it : window.input().touches())
    {
        const auto& touch = it.second;
        for (int i = 1; i < touch.data_points.size(); ++i)
        {
            glm::vec2 p = touch.data_points[i - 1].position;
            if (_finger == 0 && finger == 0) is::setVector2(position, p[0], p[1]);
            if (_finger == 1 && finger == 1) is::setVector2(position, p[0], p[1]);
        }
        _finger++;
    }
    return position;
}
}
#endif
