#ifndef SDM_H_INCLUDED
#define SDM_H_INCLUDED

#include "../entity/MainObject.h"
#include <list>

namespace is
{
////////////////////////////////////////////////////////////
/// class that automatically updates and displays objects in
/// a scene. It also allows you to manage the display depth
/// of objects in a scene.
////////////////////////////////////////////////////////////
class SDM
{
public:
    /// Scene objects container
    std::list<std::shared_ptr<MainObject>> m_SDMsceneObjects;

    /// Allow to get object in container by his name
    MainObject* SDMgetObject(std::string name)
    {
        // update scene objects
        for (std::list<std::shared_ptr<MainObject>>::iterator it = m_SDMsceneObjects.begin();
            it != m_SDMsceneObjects.end(); ++it)
        {
            if (is::instanceExist(*it))
            {
                if (it->get()->getName() == name)
                {
                    return it->get();
                }
            }
        }
        return nullptr;
    }

    //////////////////////////////////////////////////////
    /// \brief Allow to add object in SDM container
    ///
    /// \param obj object (MainObject) of the scene to add
    /// \param callStepFunction lets tell SDM if it can use the object's Step function
    /// \param callDrawFunction lets tell SDM if it can use the object's Draw function
    //////////////////////////////////////////////////////
    template <class T>
    void SDMaddSceneObject(std::shared_ptr<T> obj, bool callStepFunction = true, bool callDrawFunction = true, std::string name = "null")
    {
        obj->m_SDMcallStep = callStepFunction;
        obj->m_SDMcallDraw = callDrawFunction;
        if (name != "null") obj->setName(name);
        m_SDMsceneObjects.push_back(obj);
        m_SDMsortArray = true;
    }

    //////////////////////////////////////////////////////
    /// \brief Allow to add SFML Sprite in SDM container
    ///
    /// \param spr SFML Sprite to add
    /// \param name of sprite which will be used to identify it in the container in order to be able to access it
    /// \param depth display depth
    //////////////////////////////////////////////////////
    virtual void SDMaddSprite(sf::Sprite spr, std::string name, int depth = DepthObject::NORMAL_DEPTH)
    {
        std::shared_ptr<MainObject> obj(new MainObject(spr));
        obj->setName(name);
        obj->setDepth(depth);
        m_SDMsceneObjects.push_back(obj);
        m_SDMsortArray = true;
    }

    /// change the display depth of an object by his name
    template <class T>
    void SDMsetObjDepth(std::string name, int depth)
    {
        if (auto obj = SDMgetObject(name); obj != nullptr)
        {
            obj->setDepth(depth);
            m_SDMsortArray = true;
        }
        else is::showLog("ERROR: Can't change depth because object <" + name + "> not found !");
    }

    /// change the display depth of an object
    void SDMsetObjDepth(MainObject *obj, int depth)
    {
        if (obj->getDepth() != depth)
        {
            obj->setDepth(depth);
            m_SDMsortArray = true;
        }
    }

protected:
    bool m_SDMsortArray = false;
};
}

#endif // SDM_H_INCLUDED
