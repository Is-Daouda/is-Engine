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
}
#endif
