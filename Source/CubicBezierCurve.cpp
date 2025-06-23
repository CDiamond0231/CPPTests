//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//             Cubic Bezier Curve (cpp)
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

#include <thread>
#include "CubicBezierCurve.h"


// Dimensions of our console map
#define MAP_WIDTH  90
#define MAP_HEIGHT 25

// World coordinate range for mapping to console grid
#define WORLD_MIN_X -2.0f
#define WORLD_MAX_X 12.0f
#define WORLD_MIN_Y -2.0f
#define WORLD_MAX_Y 12.0f


// @brief Evaluates a point on a Cubic Bezier curve at a given time 't'.
// The curve is defined by four control points: 
//      _pointStart, _controlPoint1, _controlPoint2, _endPoint (p0, p1, p2, p3).
// @return The Vector3 point on the Bezier curve at parameter 't'.
// Math for this came from: https://blog.maximeheckel.com/posts/cubic-bezier-from-math-to-motion/
Vector3 GetPointOnCubicBezierCurve(const Vector3& _pointStart, const Vector3& _tangentPoint1,
                                    const Vector3& _tangentPoint2, const Vector3& _endPoint,
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

    // Calculate the coefficients.
    float tSqr = _t * _t;
    float invertedT = 1.0f - _t;
    float invertedTSqr = invertedT * invertedT;

    float b0 = invertedTSqr * invertedT;    // (1-t)^3
    float b1 = 3.0f * invertedTSqr * _t;    // 3 * (1-t)^2 * t
    float b2 = 3.0f * invertedT * tSqr;     // 3 * (1-t) * t^2
    float b3 = tSqr * _t;                   // t^3

    // Apply the formula: B(t) = b0*P0 + b1*P1 + b2*P2 + b3*P3
    Vector3 result = (_pointStart * b0)
        + (_tangentPoint1 * b1)
        + (_tangentPoint2 * b2)
        + (_endPoint * b3);

    return result;
}


// @brief This function chains multiple Cubic Bezier curves to interpolate an arbitrary number of points.
// Math functionality came from: https://apoorvaj.io/cubic-bezier-through-four-points/
Vector3 GetPointOnInterpolatedBezierSpline(const std::vector<Vector3>& _points, float _globalTime)
{
    size_t numPoints = _points.size();
    if (numPoints == 0)
    {
        std::cerr << "Error: Cannot interpolate an empty set of points." << std::endl;
        return Vector3();
    }
    if (numPoints == 1)
    {
        return _points[0];
    }

    if (_globalTime < 0.0f)
    {
        _globalTime = 0.0f;
    }
    else if (_globalTime > 1.0f)
    {
        _globalTime = 1.0f;
    }

    if (_globalTime == 0.0f)
    {
        return _points[0];
    }
    if (_globalTime == 1.0f)
    {
        return _points[numPoints - 1];
    }

    size_t numSegments = numPoints - 1;
    float segmentSplit = _globalTime * numSegments;
    size_t segmentIndex = (size_t)segmentSplit;

    if (segmentIndex >= numSegments)
    {
        segmentIndex = numSegments - 1;
    }

    float localT = segmentSplit - segmentIndex;

    const Vector3& nowPoint = _points[segmentIndex];
    const Vector3& nextPoint = _points[segmentIndex + 1];

    Vector3 tangentPoint1;
    if (segmentIndex == 0)
    {
        tangentPoint1 = (_points[1] - _points[0]);
    }
    else
    {
        tangentPoint1 = (_points[segmentIndex + 1] - _points[segmentIndex - 1]) * 0.5f;
    }

    Vector3 tangentPoint2;
    if ((segmentIndex + 1) == (numPoints - 1))
    {
        tangentPoint2 = (_points[numPoints - 1] - _points[numPoints - 2]);
    }
    else
    {
        tangentPoint2 = (_points[segmentIndex + 2] - _points[segmentIndex]) * 0.5f;
    }

    Vector3 C0 = nowPoint;
    Vector3 C1 = nowPoint + (tangentPoint1 * 0.33f);
    Vector3 C2 = nextPoint - (tangentPoint2 * 0.33f);
    Vector3 C3 = nextPoint;

    return GetPointOnCubicBezierCurve(C0, C1, C2, C3, localT);
}


// @brief Clears the console screen using ANSI escape codes
void ClearConsole()
{
    // ANSI escape codes:
    //      \033[2J     - clears screen,
    //      \033[H      - moves cursor to home (top-left)
    std::cout << "\033[2J\033[H";
    std::cout.flush();
}

// @brief Convert world coordinates to console grid coordinates
Vector3 WorldToConsole(const Vector3& _worldPoint)
{
    // Normalise coordinates to [0, 1] range
    float normalisedX = (_worldPoint.GetX() - WORLD_MIN_X) / (WORLD_MAX_X - WORLD_MIN_X);
    float normalisedY = (_worldPoint.GetY() - WORLD_MIN_Y) / (WORLD_MAX_Y - WORLD_MIN_Y);

    // Scale to map dimensions
    int consoleX = (int)std::round(normalisedX * (MAP_WIDTH - 1));
    int consoleY = (int)std::round(normalisedY * (MAP_HEIGHT - 1));

    // Ensuring Clamped values
    if (consoleX > MAP_WIDTH - 1)
    {
        consoleX = MAP_WIDTH - 1;
    }
    else if (consoleX < 0)
    {
        consoleX = 0;
    }

    if (consoleY > MAP_HEIGHT - 1)
    {
        consoleY = MAP_HEIGHT - 1;
    }
    else if (consoleY < 0)
    {
        consoleY = 0;
    }

    // Invert Y-axis because console 0,0 is top-left
    Vector3 result = Vector3((float)consoleX, (float)(MAP_HEIGHT - 1 - consoleY));
    return result;
}



// @brief Renders a path in console for every point in the given path using Bezier Curve
void DrawConsoleInterpolatationOverTime(const Vector3& _pointStart, const Vector3& _tangentPoint1,
                                        const Vector3& _tangentPoint2, const Vector3& _endPoint)
{
    const int numFrames = 60;  // Number of "frames" in the animation
    const int delayMS = 60;     // Delay between frames in milliseconds

    // Create a character buffer for the map
    std::vector<std::string> mapBuffer(MAP_HEIGHT, std::string(MAP_WIDTH, ' '));

    // Draw the border
    for (int x = 0; x < MAP_WIDTH; ++x)
    {
        mapBuffer[0][x] = '-';
        mapBuffer[MAP_HEIGHT - 1][x] = '-';
    }

    for (int y = 0; y < MAP_HEIGHT; ++y)
    {
        mapBuffer[y][0] = '|';
        mapBuffer[y][MAP_WIDTH - 1] = '|';
    }

    // Corners
    mapBuffer[0][0] = '+';
    mapBuffer[0][MAP_WIDTH - 1] = '+';
    mapBuffer[MAP_HEIGHT - 1][0] = '+';
    mapBuffer[MAP_HEIGHT - 1][MAP_WIDTH - 1] = '+';

    // Set the interpolation points on the console grid
    std::vector<Vector3> consoleInterpolationPoints;
    consoleInterpolationPoints.push_back( WorldToConsole(_pointStart) );
    consoleInterpolationPoints.push_back( WorldToConsole(_tangentPoint1) );
    consoleInterpolationPoints.push_back( WorldToConsole(_tangentPoint2) );
    consoleInterpolationPoints.push_back( WorldToConsole(_endPoint) );

    // History of points to draw the path
    std::vector<Vector3> pathHistory;

    for (int i = 0; i <= numFrames; ++i)
    {
        float t = (float)i / numFrames;
        Vector3 currentWorldPoint = GetPointOnCubicBezierCurve(_pointStart, _tangentPoint1, _tangentPoint2, _endPoint, t);
        pathHistory.push_back(currentWorldPoint);

        ClearConsole();

        // Clears the Map within borders
        for (int x = 1; x < MAP_WIDTH - 1; ++x)
        {
            for (int y = 1; y < MAP_HEIGHT - 1; ++y)
            {
                mapBuffer[y][x] = ' ';
            }
        }

        // Draw the 'interpolation' points (marked with their index)
        for (int pathPointIndex = 0; pathPointIndex < 4; ++pathPointIndex)
        {
            Vector3 consoleInterpPoint = consoleInterpolationPoints[pathPointIndex];
            char pointChar = (pathPointIndex < 10) ? ('0' + (char)pathPointIndex) : '*';
            mapBuffer[(int)consoleInterpPoint.GetY()][(int)consoleInterpPoint.GetX()] = pointChar;
        }

        // Draw the traced path ('.')
        for (const Vector3& historyPoint : pathHistory)
        {
            Vector3 consoleHistPoint = WorldToConsole(historyPoint);
            int col = (int)consoleHistPoint.GetX();
            int row = (int)consoleHistPoint.GetY();

            // Only draw if it's not on a control point or current point
            if (mapBuffer[row][col] == ' ')
            {
                mapBuffer[row][col] = '.';
            }
        }

        // Draw the current point
        Vector3 currentConsolePoint = WorldToConsole(currentWorldPoint);
        int playerX = (int)currentConsolePoint.GetX();
        int playerY = (int)currentConsolePoint.GetY();
        if (mapBuffer[playerY][playerX] == '.')
        {
            mapBuffer[playerY][playerX] = 'P';
        }

        // Print
        for (const auto& rowStr : mapBuffer)
        {
            std::cout << rowStr << std::endl;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(delayMS));
    }
}


// @brief Renders a path in console for every point in the given path using Bezier Spline
void DrawConsoleInterpolatationOverTime(std::vector<Vector3>& _pathPoints)
{
    const int numFrames = 150;  // Number of "frames" in the animation
    const int delayMS = 60;     // Delay between frames in milliseconds

    // Create a character buffer for the map
    size_t numPathPoints = _pathPoints.size();
    std::vector<std::string> mapBuffer(MAP_HEIGHT, std::string(MAP_WIDTH, ' '));

    // Draw the border
    for (int x = 0; x < MAP_WIDTH; ++x)
    {
        mapBuffer[0][x] = '-';
        mapBuffer[MAP_HEIGHT - 1][x] = '-';
    }

    for (int y = 0; y < MAP_HEIGHT; ++y)
    {
        mapBuffer[y][0] = '|';
        mapBuffer[y][MAP_WIDTH - 1] = '|';
    }

    // Corners
    mapBuffer[0][0] = '+';
    mapBuffer[0][MAP_WIDTH - 1] = '+';
    mapBuffer[MAP_HEIGHT - 1][0] = '+';
    mapBuffer[MAP_HEIGHT - 1][MAP_WIDTH - 1] = '+';

    // Set the interpolation points on the console grid
    std::vector<Vector3> consoleInterpolationPoints;
    for (const Vector3& point : _pathPoints)
    {
        Vector3 consoleInterpPoint = WorldToConsole(point);
        consoleInterpolationPoints.push_back(consoleInterpPoint);       
    }

    // History of points to draw the path
    std::vector<Vector3> pathHistory;

    for (int i = 0; i <= numFrames; ++i)
    {
        float t = (float)i / numFrames;
        Vector3 currentWorldPoint = GetPointOnInterpolatedBezierSpline(_pathPoints, t);
        pathHistory.push_back(currentWorldPoint);

        ClearConsole();

        // Clears the Map within borders
        for (int x = 1; x < MAP_WIDTH - 1; ++x)
        {
            for (int y = 1; y < MAP_HEIGHT - 1; ++y)
            {
                mapBuffer[y][x] = ' ';
            }
        }       

        // Draw the 'interpolation' points (marked with their index)
        for (int pathPointIndex = 0; pathPointIndex < numPathPoints; ++pathPointIndex)
        {
            Vector3 consoleInterpPoint = consoleInterpolationPoints[pathPointIndex];
            char pointChar = (pathPointIndex < 10) ? ('0' + (char)pathPointIndex) : '*';
            mapBuffer[(int)consoleInterpPoint.GetY()][(int)consoleInterpPoint.GetX()] = pointChar;
        }

        // Draw the traced path ('.')
        for (const Vector3& historyPoint : pathHistory)
        {
            Vector3 consoleHistPoint = WorldToConsole(historyPoint);
            int col = (int)consoleHistPoint.GetX();
            int row = (int)consoleHistPoint.GetY();

            // Only draw if it's not on a control point or current point
            if (mapBuffer[row][col] == ' ')
            {
                mapBuffer[row][col] = '.';
            }
        }

        // Draw the current point
        Vector3 currentConsolePoint = WorldToConsole(currentWorldPoint);
        int playerX = (int)currentConsolePoint.GetX();
        int playerY = (int)currentConsolePoint.GetY();
        if (mapBuffer[playerY][playerX] == '.')
        {
            mapBuffer[playerY][playerX] = 'P';
        }

        // Print
        for (const auto& rowStr : mapBuffer)
        {
            std::cout << rowStr << std::endl;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(delayMS));
    }
}