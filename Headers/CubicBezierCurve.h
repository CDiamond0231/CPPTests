//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//             Cubic Bezier Curve (h)
//             Author: Christopher A
//             Date: June 19, 2025
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  Description:
//
//		Please think of an algorithm that given 4 arbitrary points produces a
//      smooth curve that connects all of them. Then write a function that takes
//      5 parameters (4 points and a 'time' parameter between 0 and 1) and returns
//      the point on the curve at an arbitrary 'time'.
// 
//      Now write a function that given an arbitrary number of points smoothly
//      interpolates between them at a given input 'time' parameter between
//      0 and 1.
//
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

#ifndef     __CUBIC_BEZIER_CURVE_H_
#define     __CUBIC_BEZIER_CURVE_H_


#include <vector>
#include "Vector3.h"


// @brief Evaluates a point on a Cubic Bezier curve at a given time 't'.
// The curve is defined by four control points: 
//      _pointStart, _controlPoint1, _controlPoint2, _endPoint (p0, p1, p2, p3).
// @return The Vector3 point on the Bezier curve at parameter 't'.
Vector3 GetPointOnCubicBezierCurve(const Vector3& _pointStart, const Vector3& _tangentPoint1,
                                    const Vector3& _tangentPoint2, const Vector3& _endPoint,
                                    float _t);



// @brief This function chains multiple Cubic Bezier curves to interpolate an arbitrary number of points.
Vector3 GetPointOnInterpolatedBezierSpline(const std::vector<Vector3>& _points, float _globalTime);

// @brief Clears the console screen using ANSI escape codes
void ClearConsole();

// @brief Convert world coordinates to console grid coordinates
Vector3 WorldToConsole(const Vector3& _worldPoint);

// @brief Renders a path in console for every point in the given path using Bezier Curve
void DrawConsoleInterpolatationOverTime(const Vector3& _pointStart, const Vector3& _tangentPoint1,
                                        const Vector3& _tangentPoint2, const Vector3& _endPoint);

// @brief Renders a path in console for every point in the given path using Bezier Spline
void DrawConsoleInterpolatationOverTime(std::vector<Vector3>& _pathPoints);

#endif  //  __CUBIC_BEZIER_CURVE_H_