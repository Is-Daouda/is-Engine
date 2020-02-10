#ifndef DepthOBJECT_H_INCLUDED
#define DepthOBJECT_H_INCLUDED

namespace is
{
////////////////////////////////////////////////////////////
/// \brief Class for manage the depth of drawing object
////////////////////////////////////////////////////////////
class DepthObject
{
public:
    enum Depth
    {
        VERY_BIG_DEPTH,
        BIG_DEPTH,
        NORMAL_DEPTH,
        SMALL_DEPTH,
        VERY_SMALL_DEPTH,
    };

    DepthObject(Depth Depth) :
        m_depth(Depth)
    {}

    virtual void setDepth(Depth val)
    {
        m_depth = val;
    }

    virtual Depth getDepth() const
    {
        return m_depth;
    }

protected:
    Depth m_depth;
};
}
#endif // DepthOBJECT_H_INCLUDED
