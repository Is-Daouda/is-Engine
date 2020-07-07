#include "LevelTile.h"

LevelTile::LevelTile(is::GameDisplay *scene, sf::Texture &tex) :
    m_scene(scene),
    m_tileset(tex),
    m_tileExist(false)
{
}

LevelTile::~LevelTile()
{
}

void LevelTile::loadResources(sf::Vector2u tileSize, std::vector<short> const &tiles, unsigned int width, unsigned int height,
                     unsigned int &valX, unsigned int &valY, int step, bool &stop)
{
    unsigned int tempWidth(valX + step);
    unsigned int tempHeight(valY + step);

    if ((valX + step) > width) tempWidth = width;
    if ((valY + step) > height) tempHeight = height;
    if (tempWidth == width && tempHeight == height) stop = true;

    // we define the size of the background and its position
    m_x = valX * tileSize.x;
    m_y = valY * tileSize.y;
    m_aabb.m_left = valX * tileSize.x;
    m_aabb.m_right = tempWidth * tileSize.x;
    m_aabb.m_top = valY * tileSize.y;
    m_aabb.m_bottom = tempHeight * tileSize.y;

    // resize the vertex array so that it can hold the entire level
    m_vertices.setPrimitiveType(sf::Triangles);
    m_vertices.resize(tempWidth * tempHeight * 6);

    // we fill the vertex array, with one quad per tile
    for (unsigned int i = valX; i < tempWidth; ++i)
    {
        for (unsigned int j = valY; j < tempHeight; ++j)
        {
            // we get the current tile number
            int tileNumber = tiles[i + j * width];

            if (tileNumber != 999) // is an empty space
            {
                m_tileExist = true;

                // we deduce its position in the tileset texture
                int tu = tileNumber % (m_tileset.getSize().x / tileSize.x);
                int tv = tileNumber / (m_tileset.getSize().x / tileSize.x);

                // we get a pointer to the triangle to define in the vertex array
                sf::Vertex* quad = &m_vertices[(i + j * tempWidth) * 6];

                // we define its four corners with two triangles
                // 1st triangle
                quad[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
                quad[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
                quad[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);

                // 2nd triangle
                quad[3].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
                quad[4].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);
                quad[5].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);

                // we define its four texture coordinates with two triangles
                // 1st triangle
                quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
                quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
                quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);

                // 2nd triangle
                quad[3].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
                quad[4].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
                quad[5].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
            }
        }
    }

    if (tempHeight == height)
    {
        valY = 0;
        valX = valX + step;
    }
    else valY = valY + step;
}

void LevelTile::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    // we apply the transformation
    states.transform *= getTransform();

    // we apply the texture of tileset
    states.texture = &m_tileset;

    // and we finally draw the vertex array
    target.draw(m_vertices, states);
}

void LevelTile::draw(sf::RenderTexture &surface)
{
    // We draw the object only if it is in the field of vision of the scene view
    if (m_scene->inViewRec(this, false)) surface.draw(*this);
}

bool LevelTile::hasTile() const
{
    return m_tileExist;
}
