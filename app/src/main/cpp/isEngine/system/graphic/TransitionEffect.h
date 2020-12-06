#ifndef TRANSITIONEFFECT_H_INCLUDED
#define TRANSITIONEFFECT_H_INCLUDED

#include "../display/GameDisplay.h"
#include "../entity/parents/Type.h"

namespace is
{
class TransitionEffect : public is::MainObject, public is::Type
{
public:
    enum Transition
    {
        FADE_IN,
        FADE_OUT
    };
    TransitionEffect(is::GameDisplay *scene);
    void step(float const &DELTA_TIME);
    void draw(is::Render &render);
    void setType(int type)
    {
        if ((m_type == FADE_OUT && type == FADE_IN) || (m_type == FADE_IN && type == FADE_OUT))
            m_transitionEnd = false;
        m_type = type;
    }
    bool getTransitionEnd(int type) const {return (m_transitionEnd && m_type == type);}
    sf::RectangleShape& getRecTransition() {return m_recTransition;}

private:
    is::GameDisplay *m_scene;
    sf::RectangleShape m_recTransition;
    bool m_transitionEnd;
};
}

#endif // TRANSITIONEFFECT_H_INCLUDED
