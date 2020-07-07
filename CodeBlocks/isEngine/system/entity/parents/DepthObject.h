#ifndef DepthOBJECT_H_INCLUDED
#define DepthOBJECT_H_INCLUDED

namespace is
{
////////////////////////////////////////////////////////////
/// Class for manage the depth of drawing object
////////////////////////////////////////////////////////////
class DepthObject
{
public:
    enum Depth
    {
        VERY_BIG_DEPTH = 99999,
        BIG_DEPTH = 999,
        NORMAL_DEPTH = 0,
        SMALL_DEPTH = -999,
        VERY_SMALL_DEPTH = -99999,
    };

    DepthObject(int depth) :
        m_depth(depth)
    {}

    virtual void setDepth(int val)
    {
        m_depth = val;
    }

    virtual int getDepth() const
    {
        return m_depth;
    }

protected:
    int m_depth;
};
}
#endif // DepthOBJECT_H_INCLUDED
