//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//             Cubic Bezier Curve (h)
//             Author: Christopher A
//             Date: June 19, 2025
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  Description:
//
//		Please implement the following mathematical function, in the way 
//		you think is best (explain your choice).
//		
//		F(0) = 0
//		F(n) = n + F(n-1)
//		n=1..20
//
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

#ifndef     __CUBIC_BEZIER_CURVE_H_
#define     __CUBIC_BEZIER_CURVE_H_


#include "Vector3.h"


// @brief Evaluates a point on a Cubic Bezier curve at a given time 't'.
// The curve is defined by four control points: 
//      _pointStart, _controlPoint1, _controlPoint2, _endPoint (p0, p1, p2, p3).
// @return The Vector2 point on the Bezier curve at parameter 't'.
Vector3 GetPointOnCubicBezierCurve(const Vector3& _pointStart, const Vector3& _controlPoint1, 
                                    const Vector3& _controlPoint2, const Vector3& _endPoint,
                                    float _t)
{
    if (_t < 0.0f)
    {
        _t = 0.0f;
    }
    else if (_t > 1.0f)
    {
        _t = 1.0f;
    }

    // Calculate the coefficients. Math for this came from: https://blog.maximeheckel.com/posts/cubic-bezier-from-math-to-motion/
    float tSqr = _t * _t;
    float invertedT = 1.0f - _t;
    float invertedTSqr = invertedT * invertedT;

    float b0 = invertedTSqr * invertedT;    // (1-t)^3
    float b1 = 3.0f * invertedTSqr * _t;    // 3 * (1-t)^2 * t
    float b2 = 3.0f * invertedT * tSqr;     // 3 * (1-t) * t^2
    float b3 = tSqr * _t;                   // t^3

    // Apply the formula: B(t) = b0*P0 + b1*P1 + b2*P2 + b3*P3
    Vector3 result = (_pointStart * b0) 
                    + (_controlPoint1 * b1)
                    + (_controlPoint2 * b2)
                    + (_endPoint * b3);

    return result;
}


#endif  //  __CUBIC_BEZIER_CURVE_H_