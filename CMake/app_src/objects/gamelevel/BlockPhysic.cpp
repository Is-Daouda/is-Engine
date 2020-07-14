#include "BlockPhysic.h"

BlockPhysic::BlockPhysic(is::GameDisplay *scene):
    m_scene(scene),
    m_timeCancelCollision(0)
{
}

void BlockPhysic::step(float const &DELTA_TIME)
{
    short const yPrecision(6);
    short const xPrecision(10);
    bool rightCollision(true);
    bool cancelRightCollision(false);
    bool canFollowBloc(true);

    // We call the player object which is in the SDM container
    auto player = static_cast<Player*>(m_scene->SDMgetObject("Player"));

    // If this counter is greater than 0, it cancels all the collisions of the player at
    // the top in order to make the contacts with the blocks softer
    if (m_timeCancelCollision > 0.f) m_timeCancelCollision -= is::getMSecond(DELTA_TIME);
    else m_timeCancelCollision = 0.f;

    // this variables allow to store block temporally
    Block* blockGroundId = nullptr;
    Block* blockId = nullptr;

    // block loop
    WITH(m_scene->m_SDMsceneObjects.size())
    {
        if (is::instanceExist(m_scene->m_SDMsceneObjects[_I]))
        {
            // This allows to know if the object browsed is a Block
            if (m_scene->m_SDMsceneObjects[_I]->getName() == "Block")
            {
                auto currentBlock = static_cast<Block*>(m_scene->m_SDMsceneObjects[_I].get());

                if (currentBlock->getIsActive())
                {
                    // moving blocks
                    if (currentBlock->getType() == Block::BlockType::BLOCK_MOVE_HORIZ ||
                        currentBlock->getType() == Block::BlockType::BLOCK_MOVE_VERTI)
                    {
                        // We check if the moving block touches the Limiter. to change its trajectory
                        for (unsigned int i(0); i < m_scene->m_SDMsceneObjects.size(); i++)
                        {
                            if (is::instanceExist(m_scene->m_SDMsceneObjects[i]))
                            {
                                // This allows to know if the object browsed is a Limiter
                                if (m_scene->m_SDMsceneObjects[i]->getName() == "Limiter")
                                {
                                    if (currentBlock->placeMetting(0 , 0, m_scene->m_SDMsceneObjects[i]))
                                    {
                                        if (!currentBlock->getChangeDir())
                                        {
                                            currentBlock->setSpeed(1.f);
                                            currentBlock->setChangeDir(true);
                                            break;
                                        }
                                    }
                                }
                            }
                        }
                    }

                    // check collision at bottom
                    if (static_cast<int>(m_timeCancelCollision) == 0)
                    {
                        if (player->getY() + static_cast<float>(player->getMaskHeight()) < currentBlock->getY() + (static_cast<float>(yPrecision) + 4.f) &&
                            player->getY() + static_cast<float>(player->getMaskHeight()) > currentBlock->getY() - 2.f)
                        {
                            if (player->placeMetting(0, yPrecision + 10, currentBlock) && player->getVspAcc() > -0.99f)
                            {
                                blockGroundId = currentBlock; // store the block to use it after
                            }
                        }
                    }

                    // execute this instruction only for this block
                    if (currentBlock->getType() == Block::BlockType::BLOCK_NORMAL)
                    {
                        // check collision at right
                        if (player->placeMetting(xPrecision, 0, currentBlock))
                        {
                            if (player->getHsp() > 0.f)
                            {
                                blockId = currentBlock;
                                rightCollision = true;
                            }
                            if (is::instanceExist(blockGroundId))
                            {
                                if (blockGroundId->getMoveHorizontal() && std::abs(blockGroundId->getSpeed()) > 0.f) canFollowBloc = false;
                            }
                        }
                        else if (player->placeMetting(-xPrecision, 0, currentBlock)) // check collision at left
                        {
                            if (player->getHsp() < 0.f)
                            {
                                blockId = currentBlock;
                                rightCollision = false;
                            }
                            if (is::instanceExist(blockGroundId))
                            {
                                if (blockGroundId->getMoveHorizontal() && std::abs(blockGroundId->getSpeed()) > 0.f) canFollowBloc = false;
                            }
                        }
                        else if (player->placeMetting(0, -yPrecision, currentBlock) && player->getVspAcc() < 0.f) // check top collision
                        {
                            player->setY(currentBlock->getY() + 5.f + static_cast<float>(currentBlock->getMaskHeight()));
                            player->setIsJumping(false);
                        }
                    }
                }
            }
        }
    }

    if (player->getIsActive())
    {
        // check if it has collision
        if (is::instanceExist(blockGroundId) && static_cast<int>(m_timeCancelCollision) == 0) player->setOnGround(true);
        else player->setOnGround(false);

        // cancel horizontal collision if this condition is true
        if (cancelRightCollision) blockId = nullptr;

        // This prevents the player from moving when he touches a block on the left or right side
        player->setCanMove(blockId == nullptr);

        // is on ground
        if (player->getOnGround())
        {
            // if player touch the ground after jumping
            if (player->getVspAcc() > 0.f)
            {
                player->setVspAcc(0.f);
            }

            // if player is on horizontal moving bloc
            if (canFollowBloc)
            {
                if (blockGroundId->getMoveHorizontal())
                {
                    player->setX(player->getX() + (blockGroundId->getSpeed() * is::VALUE_CONVERSION) * DELTA_TIME);
                }
                if (blockGroundId->getMoveVertical())
                {
                    player->setY(player->getY() + (blockGroundId->getSpeed() * is::VALUE_CONVERSION) * DELTA_TIME);
                }
            }

            // if player is on vertical moving bloc
            if (is::instanceExist(blockGroundId))
            {
                player->setY(blockGroundId->getY() - static_cast<float>(player->getMaskHeight()));
            }
        }

        // horizontal collision with blocs
        if (is::instanceExist(blockId))
        {
            if (!rightCollision) // put player to the right of the block
            {
                player->setX(blockId->getX() + static_cast<float>(blockId->getMaskWidth()));
                player->setHsp(0.f);
            }
            else  // put player to the left of the block
            {
                player->setX(blockId->getX() - static_cast<float>(player->getMaskWidth()));
                player->setHsp(0.f);
            }
        }
    }
}
