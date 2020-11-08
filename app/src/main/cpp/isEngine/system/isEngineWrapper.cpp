#if defined(IS_ENGINE_HTML_5)
#include "isEngineWrapper.h"

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

bool Rect::intersects(Rect const &rec) const
{
    int x1Other = rec.left;
    int x2Other = rec.left + rec.width;
    int y1Other = rec.top;
    int y2Other = rec.top + rec.height;

    int x1 = left;
    int x2 = left + width;
    int y1 = top;
    int y2 = top + height;

    if (y2 <= y1Other) return false;
    if (y1 >= y2Other) return false;
    if (x2 <= x1Other) return false;
    if (x1 >= x2Other) return false;
    return true;
}

bool Rect::intersects(Rect const &rec1, Rect const &rec2) const
{
    return rec1.intersects(rec2);
}

Rect functionGetGlobalBounds(const Vector2f &position, const Vector2f &origin, const Vector2f &size)
{
    Rect aabb;
    aabb.left   = position.x;
    aabb.top    = position.y;
    aabb.width  = size.x;
    aabb.height = size.y;
    return aabb;
}

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

void Shape::setSize(float x, float y)
{
    float xScale = (x * m_scale.x) / m_size.x;
    float yScale = (y * m_scale.y) / m_size.y;
    is::setVector2(m_size, x, y);
    setScale(xScale, yScale);
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
    SetVolume(1.f / volume);
}

Vector2i Mouse::getPosition(RenderWindow &window)
{
    Vector2i position(-1, -1);
    glm::vec2 p1 = window.input().cursor();
    p1 -= window.dimension() * 0.125f;
    is::setVector2(position, p1[0], p1[1]);
    return position;
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
