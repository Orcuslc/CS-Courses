#include "curve.h"
#include "extra.h"
#ifdef WIN32
#include <windows.h>
#endif
#include <GL/gl.h>
using namespace std;

namespace
{
    // Approximately equal to.  We don't want to use == because of
    // precision issues with floating point.
    inline bool approx( const Vector3f& lhs, const Vector3f& rhs )
    {
        const float eps = 1e-8f;
        return ( lhs - rhs ).absSquared() < eps;
    }

    
}

inline unsigned nChoosek(unsigned n, unsigned k) {
    if(k > n) return 0;
    if(k*2 > n) k = n-k;
    if(k == 0) return 1;
    unsigned res = n;
    for(unsigned i = 2; i <= k; i++) {
        res *= (n-i+1);
        res /= i;
    }
    return res;
}

inline float Berstein(unsigned n, unsigned i, GLfloat t) {
    return nChoosek(n, i)*pow(t, i)*pow((1-t), n-i);
}

inline float dBerstein(unsigned n, unsigned i, GLfloat t) {
    if(i == 0) return n*pow(1-t, n-1);
    if(i == n) return n*pow(t, n-1);
    return nChoosek(n, i)*pow(t, i-1)*pow(1-t, n-i-1)*(i*(1-t)+(n-i)*t);
}

Curve evalBezier( const vector< Vector3f >& P, unsigned steps )
{
    // Check
    if( P.size() < 4 || P.size() % 3 != 1 )
    {
        cerr << "evalBezier must be called with 3n+1 control points." << endl;
        exit( 0 );
    }
    // TODO:
    // You should implement this function so that it returns a Curve
    // (e.g., a vector< CurvePoint >).  The variable "steps" tells you
    // the number of points to generate on each piece of the spline.
    // At least, that's how the sample solution is implemented and how
    // the SWP files are written.  But you are free to interpret this
    // variable however you want, so long as you can control the
    // "resolution" of the discretized spline curve with it.

    // Make sure that this function computes all the appropriate
    // Vector3fs for each CurvePoint: V,T,N,B.
    // [NBT] should be unit and orthogonal.

    // Also note that you may assume that all Bezier curves that you
    // receive have G1 continuity.  Otherwise, the TNB will not be
    // be defined at points where this does not hold.

    unsigned n = P.size()-1;
    vector<GLfloat> timePoints(steps);
    for(unsigned i = 0; i < steps; i++) timePoints[i] = i*1.0/(float)steps;
    Curve Bezier(steps);
    Vector3f B0(-1.34, 2.034, 1.21); // random B0;
    B0.normalize();
    for(unsigned i = 0; i < steps; i++) {
        Vector3f V, T, N, B;
        for(unsigned j = 0; j <= n; j++) 
            V += P[j]*Berstein(n, j, timePoints[i]);
        for(unsigned j = 0; j <= n; j++) 
            T += P[j]*dBerstein(n, j, timePoints[i]);
        T.normalize();
        N = Vector3f::cross(B0, T).normalized();
        B = Vector3f::cross(T, N).normalized();
        B0 = B;
        Bezier[i].V = V;
        Bezier[i].T = T;
        Bezier[i].N = N;
        Bezier[i].B = B;
    }
    return Bezier;
}

inline Vector4f splineBasis(GLfloat t) {
    return Vector4f(1, t, t*t, pow(t, 3));
}

inline Vector4f dsplineBasis(GLfloat t) {
    return Vector4f(0, 1, 2*t, 3*t*t);
}

Curve evalBspline( const vector< Vector3f >& P, unsigned steps )
{
    // Check
    if( P.size() < 4 )
    {
        cerr << "evalBspline must be called with 4 or more control points." << endl;
        exit( 0 );
    }

    // TODO:
    // It is suggested that you implement this function by changing
    // basis from B-spline to Bezier.  That way, you can just call
    // your evalBezier function.
    Matrix4f basis(1, -3, 3, -1,
                   4, 0, -6, 3,
                   1, 3,  3, -3,
                   0, 0, 0, 1);
    basis /= 6.0;
    vector<GLfloat> timePoints(steps);
    for(unsigned i = 0; i < steps; i++) {
        timePoints[i] = 1.0/(double)steps*i;
    }
    Curve Bspline;
    Vector3f T1 = -0.5*P[0]+0.5*P[2];
    Vector3f B0(1.2324, 0.0, 1.0);
    if(Vector3f::dot(T1, B0) < 1e-4) {
        B0.y() = 1.0;
    }
    B0.normalize();
    for(unsigned int i = 0; i < P.size()-3; i++) {
        Vector3f V, T, N, B;
        for(unsigned j = 0; j < steps; j++) {
            Vector4f bV = basis*splineBasis(timePoints[j]);
            Vector4f bT = basis*dsplineBasis(timePoints[j]);
            V = bV[0]*P[i]+bV[1]*P[i+1]+bV[2]*P[i+2]+bV[3]*P[i+3];
            T = bT[0]*P[i]+bT[1]*P[i+1]+bT[2]*P[i+2]+bT[3]*P[i+3];
            T.normalize();
            N = Vector3f::cross(B0, T);
            B = Vector3f::cross(T, N);
            B0 = B;
            CurvePoint c = {V, T, N, B};
            Bspline.push_back(c);
        }
    }
    return Bspline;
}

Curve evalCircle( float radius, unsigned steps )
{
    // This is a sample function on how to properly initialize a Curve
    // (which is a vector< CurvePoint >).
    
    // Preallocate a curve with steps+1 CurvePoints
    Curve R( steps+1 );

    // Fill it in counterclockwise
    for( unsigned i = 0; i <= steps; ++i )
    {
        // step from 0 to 2pi
        float t = 2.0f * M_PI * float( i ) / steps;

        // Initialize position
        // We're pivoting counterclockwise around the y-axis
        R[i].V = radius * Vector3f( cos(t), sin(t), 0 );
        
        // Tangent vector is first derivative
        R[i].T = Vector3f( -sin(t), cos(t), 0 );
        
        // Normal vector is second derivative
        R[i].N = Vector3f( -cos(t), -sin(t), 0 );

        // Finally, binormal is facing up.
        R[i].B = Vector3f( 0, 0, 1 );
    }

    return R;
}

void drawCurve( const Curve& curve, float framesize )
{
    // Save current state of OpenGL
    glPushAttrib( GL_ALL_ATTRIB_BITS );

    // Setup for line drawing
    glDisable( GL_LIGHTING ); 
    glColor4f( 1, 1, 1, 1 );
    glLineWidth( 1 );
    
    // Draw curve
    glBegin( GL_LINE_STRIP );
    for( unsigned i = 0; i < curve.size(); ++i )
    {
        glVertex( curve[ i ].V );
    }
    glEnd();

    glLineWidth( 1 );

    // Draw coordinate frames if framesize nonzero
    if( framesize != 0.0f )
    {
        Matrix4f M;

        for( unsigned i = 0; i < curve.size(); ++i )
        {
            M.setCol( 0, Vector4f( curve[i].N, 0 ) );
            M.setCol( 1, Vector4f( curve[i].B, 0 ) );
            M.setCol( 2, Vector4f( curve[i].T, 0 ) );
            M.setCol( 3, Vector4f( curve[i].V, 1 ) );

            glPushMatrix();
            glMultMatrixf( M );
            glScaled( framesize, framesize, framesize );
            glBegin( GL_LINES );
            glColor3f( 1, 0, 0 ); glVertex3d( 0, 0, 0 ); glVertex3d( 1, 0, 0 );
            glColor3f( 0, 1, 0 ); glVertex3d( 0, 0, 0 ); glVertex3d( 0, 1, 0 );
            glColor3f( 0, 0, 1 ); glVertex3d( 0, 0, 0 ); glVertex3d( 0, 0, 1 );
            glEnd();
            glPopMatrix();
        }
    }
    
    // Pop state
    glPopAttrib();
}

