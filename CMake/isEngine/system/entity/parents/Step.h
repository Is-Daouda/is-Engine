#ifndef STEP_H_INCLUDED
#define STEP_H_INCLUDED

namespace is
{
////////////////////////////////////////////////////////////
/// Provides methods to manage the step of an object mechanism
////////////////////////////////////////////////////////////
class Step
{
public:
    Step() :
        m_step(0)
    {}

    Step(int step) :
        m_step(step)
    {}

    virtual void setStep(int val)
    {
        m_step = val;
    }

    virtual void addStep()
    {
        m_step++;
    }

    virtual void reduceStep()
    {
        m_step--;
    }

    virtual int getStep() const
    {
        return m_step;
    }

protected:
    int m_step;
};
}
#endif // STEP_H_INCLUDED
