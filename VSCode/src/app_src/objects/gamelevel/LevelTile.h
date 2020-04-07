#ifndef LEVELTILE_H_INCLUDED
#define LEVELTILE_H_INCLUDED

#include "../../../isEngine/system/entity/MainObject.h"

class LevelTile : public sf::Drawable, public sf::Transformable, public is::MainObject
{
public:
    LevelTile(sf::Texture &tex);
    virtual ~LevelTile();

    void load(sf::Vector2u tileSize, std::vector<short> const &tiles, unsigned int width, unsigned int height,
              unsigned int &valX, unsigned int &valY, int step, bool &stop);
    void draw(sf::RenderTexture &surface) {surface.draw(m_sprParent);};

    bool hasTile() const;

private:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

    sf::VertexArray m_vertices;
    sf::Texture &m_tileset;
    bool tileExist;
};

#endif // LEVELTILE_H_INCLUDED
