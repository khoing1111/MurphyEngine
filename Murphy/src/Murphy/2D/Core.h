#pragma once

namespace Murphy::M2D
{
    enum PrimitiveType
    {
        Points = 0,    ///< List of individual points
        Lines,         ///< List of individual lines
        LineStrip,     ///< List of connected lines, a point uses the previous point to form a line
        Triangles,     ///< List of individual triangles
        TriangleStrip, ///< List of connected triangles, a point uses the two previous points to form a triangle
        TriangleFan,   ///< List of connected triangles, a point uses the common center and the previous point to form a triangle
        Quads,         ///< List of individual quads (deprecated, don't work with OpenGL ES)
    };
}