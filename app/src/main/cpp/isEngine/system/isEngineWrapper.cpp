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
    aabb.left   = position.x - origin.x;
    aabb.top    = position.y - origin.y;
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

RectangleShape::RectangleShape() : Shape(RoundedRectangle(32.f, 32.f, 0.f)) {is::setVector2(ObjectWrapper::m_size, 32.f, 32.f);}

CircleShape::CircleShape() : Shape(smk::Shape::Circle(32.f)) {is::setVector2(m_size, 32.f, 32.f);}

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

Clock::Clock() : m_startTime(seconds(0.018f)) {}
const Time Clock::getElapsedTime()
{
    return m_startTime;
}
Time Clock::restart()
{
    return m_startTime;
}

void Sound::setVolume(float volume)
{
    SetVolume(1.f / volume);
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

////////////////////////////////////////////////////////////
//              Time Operator and Function
////////////////////////////////////////////////////////////
const Time Time::Zero;

// functions
Time seconds(float amount)
{
    // Special case: allows the SMK timer to have the same behavior as that of the SFML Pong example
    if (amount > 0.09f && amount < 0.101f)
    {
        sf::Clock dTime;
        amount = dTime.getElapsedTime().asSeconds() - 0.01f;
    }
    return Time(static_cast<Int64>(amount * 1000000));
}
Time milliseconds(Int32 amount) {return Time(static_cast<Int64>(amount) * 1000);}
Time microseconds(Int64 amount) {return Time(amount);}

// operator
inline bool operator ==(Time left, Time right) {return left.asMicroseconds() == right.asMicroseconds();}

inline bool operator !=(Time left, Time right) {return left.asMicroseconds() != right.asMicroseconds();}

inline bool operator <(Time left, Time right) {return left.asMicroseconds() < right.asMicroseconds();}

inline bool operator >(Time left, Time right) {return left.asMicroseconds() > right.asMicroseconds();}

inline bool operator <=(Time left, Time right){return left.asMicroseconds() <= right.asMicroseconds();}

inline bool operator >=(Time left, Time right){return left.asMicroseconds() >= right.asMicroseconds();}

inline Time operator -(Time right) {return microseconds(-right.asMicroseconds());}

inline Time operator +(Time left, Time right) {return microseconds(left.asMicroseconds() + right.asMicroseconds());}

inline Time& operator +=(Time& left, Time right) {return left = left + right;}

inline Time operator -(Time left, Time right) {return microseconds(left.asMicroseconds() - right.asMicroseconds());}

inline Time& operator -=(Time& left, Time right) {return left = left - right;}

inline Time operator *(Time left, float right) {return seconds(left.asSeconds() * right);}

inline Time operator *(Time left, Int64 right) {return microseconds(left.asMicroseconds() * right);}

inline Time operator *(float left, Time right) {return right * left;}

inline Time operator *(Int64 left, Time right) {return right * left;}

inline Time& operator *=(Time& left, float right) {return left = left * right;}

inline Time& operator *=(Time& left, Int64 right) {return left = left * right;}

inline Time operator /(Time left, float right) {return seconds(left.asSeconds() / right);}

inline Time operator /(Time left, Int64 right) {return microseconds(left.asMicroseconds() / right);}

inline Time& operator /=(Time& left, float right) {return left = left / right;}

inline Time& operator /=(Time& left, Int64 right) {return left = left / right;}

inline float operator /(Time left, Time right) {return left.asSeconds() / right.asSeconds();}

inline Time operator %(Time left, Time right) {return microseconds(left.asMicroseconds() % right.asMicroseconds());}

inline Time& operator %=(Time& left, Time right) {return left = left % right;}
}
#endif
