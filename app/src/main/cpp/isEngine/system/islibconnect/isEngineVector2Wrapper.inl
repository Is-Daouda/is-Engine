#ifndef ISENGINEVECTOR2WRAPPER_INL_INCLUDED
#define ISENGINEVECTOR2WRAPPER_INL_INCLUDED

////////////////////////////////////////////////////////////
//                  Vector2 Operator
////////////////////////////////////////////////////////////
template <typename T>
inline Vector2<T> operator -(const Vector2<T>& right) {return Vector2<T>(-right.x, -right.y);}

template <typename T>
inline Vector2<T>& operator +=(Vector2<T>& left, const Vector2<T>& right)
{
    left.x += right.x;
    left.y += right.y;
    return left;
}

template <typename T>
inline Vector2<T>& operator -=(Vector2<T>& left, const Vector2<T>& right)
{
    left.x -= right.x;
    left.y -= right.y;
    return left;
}

template <typename T>
inline Vector2<T> operator +(const Vector2<T>& left, const Vector2<T>& right) {return Vector2<T>(left.x + right.x, left.y + right.y);}

template <typename T>
inline Vector2<T> operator -(const Vector2<T>& left, const Vector2<T>& right) {return Vector2<T>(left.x - right.x, left.y - right.y);}

template <typename T>
inline Vector2<T> operator *(const Vector2<T>& left, T right) {return Vector2<T>(left.x * right, left.y * right);}

template <typename T>
inline Vector2<T> operator *(T left, const Vector2<T>& right) {return Vector2<T>(right.x * left, right.y * left);}

template <typename T>
inline Vector2<T>& operator *=(Vector2<T>& left, T right)
{
    left.x *= right;
    left.y *= right;
    return left;
}

template <typename T>
inline Vector2<T> operator /(const Vector2<T>& left, T right) {return Vector2<T>(left.x / right, left.y / right);}

template <typename T>
inline Vector2<T>& operator /=(Vector2<T>& left, T right)
{
    left.x /= right;
    left.y /= right;
    return left;
}

template <typename T>
inline bool operator ==(const Vector2<T>& left, const Vector2<T>& right) {return (left.x == right.x) && (left.y == right.y);}

template <typename T>
inline bool operator !=(const Vector2<T>& left, const Vector2<T>& right) {return (left.x != right.x) || (left.y != right.y);}

#endif // ISENGINEVECTOR2WRAPPER_INL_INCLUDED
