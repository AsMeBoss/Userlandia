/**********************************************************************************************
*
*   raymath (header only file)
*
*   Some useful functions to work with Vector3, Matrix and Quaternions
*
*   You must:
*       #define RAYMATH_IMPLEMENTATION
*   before you include this file in *only one* C or C++ file to create the implementation.
*
*   Example:
*       #define RAYMATH_IMPLEMENTATION
*       #include "raymath.h"
*
*   You can also use:
*       #define RAYMATH_EXTERN_INLINE       // Inlines all functions code, so it runs faster.
*                                           // This requires lots of memory on system.
*       #define RAYMATH_STANDALONE          // Not dependent on raylib.h structs: Vector3, Matrix.
*
*
*   Copyright (c) 2015 Ramon Santamaria (@raysan5)
*
*   This software is provided "as-is", without any express or implied warranty. In no event
*   will the authors be held liable for any damages arising from the use of this software.
*
*   Permission is granted to anyone to use this software for any purpose, including commercial
*   applications, and to alter it and redistribute it freely, subject to the following restrictions:
*
*     1. The origin of this software must not be misrepresented; you must not claim that you
*     wrote the original software. If you use this software in a product, an acknowledgment
*     in the product documentation would be appreciated but is not required.
*
*     2. Altered source versions must be plainly marked as such, and must not be misrepresented
*     as being the original software.
*
*     3. This notice may not be removed or altered from any source distribution.
*
**********************************************************************************************/

#ifndef RAYMATH_H
#define RAYMATH_H

#ifdef __cplusplus
    #define RMEXTERN extern "C"     // Functions visible from other files (no name mangling of functions in C++)
#else
    #define RMEXTERN extern         // Functions visible from other files
#endif

#define RMDEF RMEXTERN

//----------------------------------------------------------------------------------
// Defines and Macros
//----------------------------------------------------------------------------------
#ifndef PI
    #define PI 3.14159265358979323846
#endif

#ifndef DEG2RAD
    #define DEG2RAD (PI/180.0f)
#endif

#ifndef RAD2DEG
    #define RAD2DEG (180.0f/PI)
#endif

//----------------------------------------------------------------------------------
// Types and Structures Definition
//----------------------------------------------------------------------------------

// Vector2 type
typedef struct Vector2 {
    float x;
    float y;
} Vector2;

// Vector3 type
typedef struct Vector3 {
    float x;
    float y;
    float z;
} Vector3;

// Matrix type (OpenGL style 4x4 - right handed, column major)
typedef struct Matrix {
    float m0, m4, m8, m12;
    float m1, m5, m9, m13;
    float m2, m6, m10, m14;
    float m3, m7, m11, m15;
} Matrix;

// Quaternion type
typedef struct Quaternion {
    float x;
    float y;
    float z;
    float w;
} Quaternion;


//------------------------------------------------------------------------------------
// Functions Declaration to work with Vector3
//------------------------------------------------------------------------------------
RMDEF Vector3 VectorAdd(Vector3 v1, Vector3 v2);              // Add two vectors
RMDEF Vector3 VectorSubtract(Vector3 v1, Vector3 v2);         // Substract two vectors
RMDEF Vector3 VectorCrossProduct(Vector3 v1, Vector3 v2);     // Calculate two vectors cross product
RMDEF Vector3 VectorPerpendicular(Vector3 v);                 // Calculate one vector perpendicular vector
RMDEF float VectorDotProduct(Vector3 v1, Vector3 v2);         // Calculate two vectors dot product
RMDEF float VectorLength(const Vector3 v);                    // Calculate vector lenght
RMDEF void VectorScale(Vector3 *v, float scale);              // Scale provided vector
RMDEF void VectorNegate(Vector3 *v);                          // Negate provided vector (invert direction)
RMDEF void VectorNormalize(Vector3 *v);                       // Normalize provided vector
RMDEF float VectorDistance(Vector3 v1, Vector3 v2);           // Calculate distance between two points
RMDEF Vector3 VectorLerp(Vector3 v1, Vector3 v2, float amount); // Calculate linear interpolation between two vectors
RMDEF Vector3 VectorReflect(Vector3 vector, Vector3 normal);  // Calculate reflected vector to normal
RMDEF void VectorTransform(Vector3 *v, Matrix mat);           // Transforms a Vector3 by a given Matrix
RMDEF Vector3 VectorZero(void);                               // Return a Vector3 init to zero
RMDEF Vector3 VectorMin(Vector3 vec1, Vector3 vec2);          // Return min value for each pair of components
RMDEF Vector3 VectorMax(Vector3 vec1, Vector3 vec2);          // Return max value for each pair of components

//------------------------------------------------------------------------------------
// Functions Declaration to work with Matrix
//------------------------------------------------------------------------------------
RMDEF float MatrixDeterminant(Matrix mat);                    // Compute matrix determinant
RMDEF float MatrixTrace(Matrix mat);                          // Returns the trace of the matrix (sum of the values along the diagonal)
RMDEF void MatrixTranspose(Matrix *mat);                      // Transposes provided matrix
RMDEF void MatrixInvert(Matrix *mat);                         // Invert provided matrix
RMDEF void MatrixNormalize(Matrix *mat);                      // Normalize provided matrix
RMDEF Matrix MatrixIdentity(void);                            // Returns identity matrix
RMDEF Matrix MatrixAdd(Matrix left, Matrix right);            // Add two matrices
RMDEF Matrix MatrixSubstract(Matrix left, Matrix right);      // Substract two matrices (left - right)
RMDEF Matrix MatrixTranslate(float x, float y, float z);      // Returns translation matrix
RMDEF Matrix MatrixRotate(Vector3 axis, float angle);         // Returns rotation matrix for an angle around an specified axis (angle in radians)
RMDEF Matrix MatrixRotateX(float angle);                      // Returns x-rotation matrix (angle in radians)
RMDEF Matrix MatrixRotateY(float angle);                      // Returns y-rotation matrix (angle in radians)
RMDEF Matrix MatrixRotateZ(float angle);                      // Returns z-rotation matrix (angle in radians)
RMDEF Matrix MatrixScale(float x, float y, float z);          // Returns scaling matrix
RMDEF Matrix MatrixMultiply(Matrix left, Matrix right);       // Returns two matrix multiplication
RMDEF Matrix MatrixFrustum(double left, double right, double bottom, double top, double near, double far);  // Returns perspective projection matrix
RMDEF Matrix MatrixPerspective(double fovy, double aspect, double near, double far);                        // Returns perspective projection matrix
RMDEF Matrix MatrixOrtho(double left, double right, double bottom, double top, double near, double far);    // Returns orthographic projection matrix
RMDEF Matrix MatrixLookAt(Vector3 position, Vector3 target, Vector3 up);  // Returns camera look-at matrix (view matrix)

//------------------------------------------------------------------------------------
// Functions Declaration to work with Quaternions
//------------------------------------------------------------------------------------
RMDEF float QuaternionLength(Quaternion quat);                // Compute the length of a quaternion
RMDEF void QuaternionNormalize(Quaternion *q);                // Normalize provided quaternion
RMDEF void QuaternionInvert(Quaternion *quat);                // Invert provided quaternion
RMDEF Quaternion QuaternionMultiply(Quaternion q1, Quaternion q2);    // Calculate two quaternion multiplication
RMDEF Quaternion QuaternionSlerp(Quaternion q1, Quaternion q2, float slerp); // Calculates spherical linear interpolation between two quaternions
RMDEF Quaternion QuaternionFromMatrix(Matrix matrix);                 // Returns a quaternion for a given rotation matrix
RMDEF Matrix QuaternionToMatrix(Quaternion q);                        // Returns a matrix for a given quaternion
RMDEF Quaternion QuaternionFromAxisAngle(Vector3 axis, float angle);  // Returns rotation quaternion for an angle and axis
RMDEF void QuaternionToAxisAngle(Quaternion q, Vector3 *outAxis, float *outAngle); // Returns the rotation angle and axis for a given quaternion
RMDEF void QuaternionTransform(Quaternion *q, Matrix mat);            // Transform a quaternion given a transformation matrix


#endif  // RAYMATH_H

