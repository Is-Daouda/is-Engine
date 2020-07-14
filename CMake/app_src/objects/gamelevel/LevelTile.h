#ifndef LEVELTILE_H_INCLUDED
#define LEVELTILE_H_INCLUDED

#include "../../../isEngine/system/display/GameDisplay.h"

////////////////////////////////////////////////////////////
/// Represents the level tile map (Background built with tiles)
////////////////////////////////////////////////////////////
class LevelTile : public sf::Drawable, public sf::Transformable, public is::MainObject
{
public:
    LevelTile(is::GameDisplay *scene, sf::Texture &tex);
    virtual ~LevelTile();

    void loadResources(sf::Vector2u tileSize, std::vector<short> const &tiles, unsigned int width, unsigned int height,
              unsigned int &valX, unsigned int &valY, int step, bool &stop);
    void draw(sf::RenderTexture &surface);

    bool hasTile() const;

private:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    is::GameDisplay *m_scene;
    sf::VertexArray m_vertices;
    sf::Texture &m_tileset;
    bool m_tileExist;
};

#endif // LEVELTILE_H_INCLUDED
