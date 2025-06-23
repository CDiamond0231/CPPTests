
#include "CalculateF.h"
#include "CoinObjectPool.h"
#include "CubicBezierCurve.h"
#include "GenericVectorTemplate.h"
#include "HeightMapInterpolation.h"
#include "SlowString.h"
#include "Vector3.h"





int main()
{
    std::vector<Vector3> bezierCurvePathPoints =
    {
        Vector3(0.0f, 0.0f),
        Vector3(9.0f, -1.0f),
        Vector3(10.0f, 10.0f),
        Vector3(2.0f, 8.0f),
    };
    DrawConsoleInterpolatationOverTime(bezierCurvePathPoints[0], bezierCurvePathPoints[1], bezierCurvePathPoints[2], bezierCurvePathPoints[3]);


    std::vector<Vector3> bezierSplinePathPoints =
    {
        Vector3(0.0f, 0.0f),
        Vector3(2.0f, 8.0f),
        Vector3(6.0f, 2.0f),
        Vector3(10.0f, 10.0f),
        Vector3(-1.0f, 4.0f),
        Vector3(7.0f, 0.0f),
        Vector3(2.0f, 11.0f)
    };
    DrawConsoleInterpolatationOverTime(bezierSplinePathPoints);
    return 0;
}


