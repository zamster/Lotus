#ifndef FMath_H
#define FMath_H

#include <math.h>
#include <string.h>
#include <float.h>

namespace FxMath
{
	const unsigned int UIntMax = ~0;
	const int IntMin = 0x80000000;
	const int IntMax = 0x7FFFFFFF;
	const float FloatMax = FLT_MAX;
	
	const float Pi = acos(-1.0f);
	const float TwoPi = Pi * 2;
	const float HalfPi = Pi / 2;

	const float Eps = 1e-6;
	const float NaN = *(float *)&UIntMax;
	
	// -------------------------------------------------------------------------------------------------
	// 向量
	// -------------------------------------------------------------------------------------------------

	class vector3f
	{
	public:
		float x, y, z;
		
		vector3f() : x( 0.0f ), y( 0.0f ), z( 0.0f ) 
		{ 
		}

		explicit vector3f( const float x, const float y, const float z ) : x( x ), y( y ), z( z ) 
		{
		}
		
		bool operator==( const vector3f &v ) const
		{
			return (x > v.x - FxMath::Eps && x < v.x + FxMath::Eps && 
			y > v.y - FxMath::Eps && y < v.y + FxMath::Eps &&
			z > v.z - FxMath::Eps && z < v.z + FxMath::Eps);
			
		}

		bool operator!=( const vector3f &v ) const
		{
			return (x < v.x - FxMath::Eps || x > v.x + FxMath::Eps || 
			y < v.y - FxMath::Eps || y > v.y + FxMath::Eps ||
			z < v.z - FxMath::Eps || z > v.z + FxMath::Eps);
			
		}
		
		vector3f &operator=( const vector3f &v )
		{
			x = v.x;
			y = v.y;
			z = v.z;
			return *this;
		}
		
		vector3f operator-() const
		{
			return vector3f( -x, -y, -z );
		}

		vector3f operator+( const vector3f &v ) const
		{
			return vector3f( x + v.x, y + v.y, z + v.z );
		}

		vector3f &operator+=( const vector3f &v )
		{
			return *this = *this + v;
		}

		vector3f operator-( const vector3f &v ) const 
		{
			return vector3f( x - v.x, y - v.y, z - v.z );
		}

		vector3f &operator-=( const vector3f &v )
		{
			return *this = *this - v;
		}

		vector3f operator*( const float f ) const
		{
			return vector3f( x * f, y * f, z * f );
		}

		vector3f &operator*=( const float f )
		{
			return *this = *this * f;
		}

		vector3f operator/( const float f ) const
		{
			return vector3f( x / f, y / f, z / f );
		}

		vector3f &operator/=( const float f )
		{
			return *this = *this / f;
		}

		//点积
		float operator*( const vector3f &v ) const
		{
			return ( x * v.x + y * v.y + z * v.z );
		}

		//叉积
		vector3f crossProduct( const vector3f &v ) const
		{
			return vector3f( y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x );
		}

		//求模
		float length() const 
		{
			return sqrtf( *this * *this );
		}
		
		//正规化
		vector3f normalized() const
		{
			float l = length();

			if( l != 0 ) return vector3f( x / l, y / l, z / l );
			else return vector3f( 0, 0, 0 );
		}
		
		vector3f toRotation() const
		{
			// Assumes that the unrotated view vector is (0, 0, -1)
			vector3f v;
			
			if( y != 0 ) v.x = atan2( y, sqrtf( x*x + z*z ) );
			if( z != 0 ) v.y = atan2( -x, -z );

			return v;
		}

		vector3f lerp( const vector3f &v, float f ) const
		{
			return vector3f( x + (v.x - x) * f, y + (v.y - y) * f, z + (v.z - z) * f ); 
		}
	};


	class vector4f
	{
	public:
		
		float x, y, z, w;


		vector4f() : x( 0 ), y( 0 ), z( 0 ), w( 0 )
		{
		}
		
		explicit vector4f( const float x, const float y, const float z, const float w )	: x( x ), y( y ), z( z ), w( w )
		{
		}

		explicit vector4f( vector3f v ) : x( v.x ), y( v.y ), z( v.z ), w( 1.0f )
		{
		}

		vector4f& operator/=( const float value) 
		{
			x /= value;
			y /= value;
			z /= value;
			w /= value;
			return *this;
		}
	};


	// -------------------------------------------------------------------------------------------------
	// 四元数
	// -------------------------------------------------------------------------------------------------

	class quaternion
	{
	public:	
		
		float x, y, z, w;

		quaternion() : x( 0.0f ), y( 0.0f ), z( 0.0f ), w( 0.0f ) 
		{ 
		}
		
		explicit quaternion( const float x, const float y, const float z, const float w ) :	x( x ), y( y ), z( z ), w( w )
		{
		}
		
		quaternion( const float eulerX, const float eulerY, const float eulerZ )
		{
			quaternion roll( sinf( eulerX / 2 ), 0, 0, cosf( eulerX / 2 ) );
			quaternion pitch( 0, sinf( eulerY / 2 ), 0, cosf( eulerY / 2 ) );
			quaternion yaw( 0, 0, sinf( eulerZ / 2 ), cosf( eulerZ / 2 ) );
			
			// Order: y * x * z
			*this = pitch * roll * yaw;
		}

		quaternion operator*( const quaternion &q ) const
		{
			return quaternion(
			y * q.z - z * q.y + q.x * w + x * q.w,
			z * q.x - x * q.z + q.y * w + y * q.w,
			x * q.y - y * q.x + q.z * w + z * q.w,
			w * q.w - (x * q.x + y * q.y + z * q.z) );
		}

		quaternion &operator*=( const quaternion &q )
		{
			return *this = *this * q;
		}

		quaternion slerp( const quaternion &q, const float t ) const
		{
			float		omega, cosom, sinom, scale0, scale1;
			quaternion	q1 = q, res;

			// Calc cosine
			cosom = x * q.x + y * q.y + z * q.z + w * q.w;

			// Adjust signs (if necessary)
			if( cosom < 0 ) {
				cosom = -cosom; 
				q1.x = -q.x;
				q1.y = -q.y;
				q1.z = -q.z;
				q1.w = -q.w;
			} 

			// Calculate coefficients
			if( (1 - cosom) > FxMath::Eps ) {
				// Standard case (Slerp)
				omega = acosf( cosom );
				sinom = sinf( omega );
				scale0 = sinf( (1 - t) * omega ) / sinom;
				scale1 = sinf( t * omega ) / sinom;
			} 
			else {        
				// Quaternions very close, so do linear interpolation
				scale0 = 1 - t;
				scale1 = t;
			}
			
			// Calculate final values
			res.x = x * scale0 + q1.x * scale1;
			res.y = y * scale0 + q1.y * scale1;
			res.z = z * scale0 + q1.z * scale1;
			res.w = w * scale0 + q1.w * scale1;

			return res;
		}

		quaternion inverted() const
		{
			float len = x * x + y * y + z * z + w * w;
			if( len > 0 )
			{
				float invLen = 1.0f / len;
				return quaternion( -x * invLen, -y * invLen, -z * invLen, w * invLen );
			}
			else return quaternion();
		}
	};


	// -------------------------------------------------------------------------------------------------
	// 矩阵
	// -------------------------------------------------------------------------------------------------

	class matrix4f
	{
	private:

		matrix4f( bool )
		{
			
		}

	public:
		
		union
		{
			float c[4][4];	// Column major order for OpenGL: c[column][row]
			float x[16];
		};
		
		// --------------
		// Static methods
		// --------------
		static matrix4f TransMat( float x, float y, float z )
		{
			matrix4f m;
			
			m.c[3][0] = x;
			m.c[3][1] = y;
			m.c[3][2] = z;
			
			return m;
		}

		static matrix4f ScaleMat( float x, float y, float z )
		{
			matrix4f m;
			
			m.c[0][0] = x;
			m.c[1][1] = y;
			m.c[2][2] = z;
			
			return m;
		}

		static matrix4f RotMat( float x, float y, float z )
		{
			// Rotation order: YXZ [* Vector]
			return matrix4f( quaternion( x, y, z ) );
		}

		static matrix4f RotMat( vector3f axis, float angle )
		{
			axis = axis * sinf( angle / 2 );
			return matrix4f( quaternion( axis.x, axis.y, axis.z, cosf( angle / 2 ) ) );
		}
		//默认初始化为单位矩阵
		matrix4f()
		{
			c[0][0] = 1; c[1][0] = 0; c[2][0] = 0; c[3][0] = 0;
			c[0][1] = 0; c[1][1] = 1; c[2][1] = 0; c[3][1] = 0;
			c[0][2] = 0; c[1][2] = 0; c[2][2] = 1; c[3][2] = 0;
			c[0][3] = 0; c[1][3] = 0; c[2][3] = 0; c[3][3] = 1;
		}

		matrix4f( const float *floatArray16 )
		{
			for( unsigned int i = 0; i < 4; ++i )
			{
				for( unsigned int j = 0; j < 4; ++j )
				{
					c[i][j] = floatArray16[i * 4 + j];
				}
			}
		}

		matrix4f( const quaternion &q )
		{
			float wx, wy, wz, xx, yy, yz, xy, xz, zz, x2, y2, z2;

			// Calculate coefficients
			x2 = q.x + q.x;	y2 = q.y + q.y;	z2 = q.z + q.z;
			xx = q.x * x2;	xy = q.x * y2;	xz = q.x * z2;
			yy = q.y * y2;	yz = q.y * z2;	zz = q.z * z2;
			wx = q.w * x2;	wy = q.w * y2;	wz = q.w * z2;


			c[0][0] = 1 - (yy + zz);	c[1][0] = xy - wz;	
			c[2][0] = xz + wy;			c[3][0] = 0;
			c[0][1] = xy + wz;			c[1][1] = 1 - (xx + zz);
			c[2][1] = yz - wx;			c[3][1] = 0;
			c[0][2] = xz - wy;			c[1][2] = yz + wx;
			c[2][2] = 1 - (xx + yy);	c[3][2] = 0;
			c[0][3] = 0;				c[1][3] = 0;
			c[2][3] = 0;				c[3][3] = 1;
		}

		//矩阵和
		matrix4f operator+( const matrix4f &m ) const 
		{
			matrix4f mf( false );
			
			mf.x[0] = x[0] + m.x[0];
			mf.x[1] = x[1] + m.x[1];
			mf.x[2] = x[2] + m.x[2];
			mf.x[3] = x[3] + m.x[3];
			mf.x[4] = x[4] + m.x[4];
			mf.x[5] = x[5] + m.x[5];
			mf.x[6] = x[6] + m.x[6];
			mf.x[7] = x[7] + m.x[7];
			mf.x[8] = x[8] + m.x[8];
			mf.x[9] = x[9] + m.x[9];
			mf.x[10] = x[10] + m.x[10];
			mf.x[11] = x[11] + m.x[11];
			mf.x[12] = x[12] + m.x[12];
			mf.x[13] = x[13] + m.x[13];
			mf.x[14] = x[14] + m.x[14];
			mf.x[15] = x[15] + m.x[15];

			return mf;
		}

		matrix4f &operator+=( const matrix4f &m )
		{
			return *this = *this + m;
		}
		
		matrix4f &operator=( const matrix4f &m )
		{
			memcpy( c, m.c, 16 * sizeof(float) );
			return *this;
		}
		//矩阵乘
		matrix4f operator*( const matrix4f &m ) const 
		{
			matrix4f mf( false );
			
			mf.x[0] = x[0] * m.x[0] + x[4] * m.x[1] + x[8] * m.x[2] + x[12] * m.x[3];
			mf.x[1] = x[1] * m.x[0] + x[5] * m.x[1] + x[9] * m.x[2] + x[13] * m.x[3];
			mf.x[2] = x[2] * m.x[0] + x[6] * m.x[1] + x[10] * m.x[2] + x[14] * m.x[3];
			mf.x[3] = x[3] * m.x[0] + x[7] * m.x[1] + x[11] * m.x[2] + x[15] * m.x[3];

			mf.x[4] = x[0] * m.x[4] + x[4] * m.x[5] + x[8] * m.x[6] + x[12] * m.x[7];
			mf.x[5] = x[1] * m.x[4] + x[5] * m.x[5] + x[9] * m.x[6] + x[13] * m.x[7];
			mf.x[6] = x[2] * m.x[4] + x[6] * m.x[5] + x[10] * m.x[6] + x[14] * m.x[7];
			mf.x[7] = x[3] * m.x[4] + x[7] * m.x[5] + x[11] * m.x[6] + x[15] * m.x[7];

			mf.x[8] = x[0] * m.x[8] + x[4] * m.x[9] + x[8] * m.x[10] + x[12] * m.x[11];
			mf.x[9] = x[1] * m.x[8] + x[5] * m.x[9] + x[9] * m.x[10] + x[13] * m.x[11];
			mf.x[10] = x[2] * m.x[8] + x[6] * m.x[9] + x[10] * m.x[10] + x[14] * m.x[11];
			mf.x[11] = x[3] * m.x[8] + x[7] * m.x[9] + x[11] * m.x[10] + x[15] * m.x[11];

			mf.x[12] = x[0] * m.x[12] + x[4] * m.x[13] + x[8] * m.x[14] + x[12] * m.x[15];
			mf.x[13] = x[1] * m.x[12] + x[5] * m.x[13] + x[9] * m.x[14] + x[13] * m.x[15];
			mf.x[14] = x[2] * m.x[12] + x[6] * m.x[13] + x[10] * m.x[14] + x[14] * m.x[15];
			mf.x[15] = x[3] * m.x[12] + x[7] * m.x[13] + x[11] * m.x[14] + x[15] * m.x[15];

			return mf;
		}

		void fastMult( const matrix4f &m1, const matrix4f &m2 )
		{
			x[0] = m1.x[0] * m2.x[0] + m1.x[4] * m2.x[1] + m1.x[8] * m2.x[2] + m1.x[12] * m2.x[3];
			x[1] = m1.x[1] * m2.x[0] + m1.x[5] * m2.x[1] + m1.x[9] * m2.x[2] + m1.x[13] * m2.x[3];
			x[2] = m1.x[2] * m2.x[0] + m1.x[6] * m2.x[1] + m1.x[10] * m2.x[2] + m1.x[14] * m2.x[3];
			x[3] = m1.x[3] * m2.x[0] + m1.x[7] * m2.x[1] + m1.x[11] * m2.x[2] + m1.x[15] * m2.x[3];

			x[4] = m1.x[0] * m2.x[4] + m1.x[4] * m2.x[5] + m1.x[8] * m2.x[6] + m1.x[12] * m2.x[7];
			x[5] = m1.x[1] * m2.x[4] + m1.x[5] * m2.x[5] + m1.x[9] * m2.x[6] + m1.x[13] * m2.x[7];
			x[6] = m1.x[2] * m2.x[4] + m1.x[6] * m2.x[5] + m1.x[10] * m2.x[6] + m1.x[14] * m2.x[7];
			x[7] = m1.x[3] * m2.x[4] + m1.x[7] * m2.x[5] + m1.x[11] * m2.x[6] + m1.x[15] * m2.x[7];

			x[8] = m1.x[0] * m2.x[8] + m1.x[4] * m2.x[9] + m1.x[8] * m2.x[10] + m1.x[12] * m2.x[11];
			x[9] = m1.x[1] * m2.x[8] + m1.x[5] * m2.x[9] + m1.x[9] * m2.x[10] + m1.x[13] * m2.x[11];
			x[10] = m1.x[2] * m2.x[8] + m1.x[6] * m2.x[9] + m1.x[10] * m2.x[10] + m1.x[14] * m2.x[11];
			x[11] = m1.x[3] * m2.x[8] + m1.x[7] * m2.x[9] + m1.x[11] * m2.x[10] + m1.x[15] * m2.x[11];

			x[12] = m1.x[0] * m2.x[12] + m1.x[4] * m2.x[13] + m1.x[8] * m2.x[14] + m1.x[12] * m2.x[15];
			x[13] = m1.x[1] * m2.x[12] + m1.x[5] * m2.x[13] + m1.x[9] * m2.x[14] + m1.x[13] * m2.x[15];
			x[14] = m1.x[2] * m2.x[12] + m1.x[6] * m2.x[13] + m1.x[10] * m2.x[14] + m1.x[14] * m2.x[15];
			x[15] = m1.x[3] * m2.x[12] + m1.x[7] * m2.x[13] + m1.x[11] * m2.x[14] + m1.x[15] * m2.x[15];
		}

		matrix4f operator*( const float f ) const
		{
			matrix4f m( *this );
			
			for( unsigned int y = 0; y < 4; ++y )
			{
				for( unsigned int x = 0; x < 4; ++x ) 
				{
					m.c[x][y] *= f;
				}
			}

			return m;
		}
		
		//向量——矩阵乘
		vector3f operator*( const vector3f &v ) const
		{
			return vector3f( v.x * c[0][0] + v.y * c[1][0] + v.z * c[2][0] + c[3][0],
			v.x * c[0][1] + v.y * c[1][1] + v.z * c[2][1] + c[3][1],
			v.x * c[0][2] + v.y * c[1][2] + v.z * c[2][2] + c[3][2] );
		}

		vector4f operator*( const vector4f &v ) const
		{
			return vector4f( v.x * c[0][0] + v.y * c[1][0] + v.z * c[2][0] + c[3][0],
			v.x * c[0][1] + v.y * c[1][1] + v.z * c[2][1] + c[3][1],
			v.x * c[0][2] + v.y * c[1][2] + v.z * c[2][2] + c[3][2],
			v.x * c[0][3] + v.y * c[1][3] + v.z * c[2][3] + c[3][3] );
		}
		
		//变换
		void translate( const float x, const float y, const float z )
		{
			*this = TransMat( x, y, z ) * *this;
		}

		void scale( const float x, const float y, const float z )
		{
			*this = ScaleMat( x, y, z ) * *this;
		}

		void rotate( const float x, const float y, const float z )
		{
			*this = RotMat( x, y, z ) * *this;
		}

		// ---------------
		// Other
		// ---------------
		
		matrix4f transposed() const
		{
			matrix4f m( *this );
			
			for( unsigned int y = 0; y < 4; ++y )
			{
				for( unsigned int x = y + 1; x < 4; ++x ) 
				{
					float tmp = m.c[x][y];
					m.c[x][y] = m.c[y][x];
					m.c[y][x] = tmp;
				}
			}

			return m;
		}

		float determinant() const
		{
			return 
			c[0][3]*c[1][2]*c[2][1]*c[3][0] - c[0][2]*c[1][3]*c[2][1]*c[3][0] - c[0][3]*c[1][1]*c[2][2]*c[3][0] + c[0][1]*c[1][3]*c[2][2]*c[3][0] +
			c[0][2]*c[1][1]*c[2][3]*c[3][0] - c[0][1]*c[1][2]*c[2][3]*c[3][0] - c[0][3]*c[1][2]*c[2][0]*c[3][1] + c[0][2]*c[1][3]*c[2][0]*c[3][1] +
			c[0][3]*c[1][0]*c[2][2]*c[3][1] - c[0][0]*c[1][3]*c[2][2]*c[3][1] - c[0][2]*c[1][0]*c[2][3]*c[3][1] + c[0][0]*c[1][2]*c[2][3]*c[3][1] +
			c[0][3]*c[1][1]*c[2][0]*c[3][2] - c[0][1]*c[1][3]*c[2][0]*c[3][2] - c[0][3]*c[1][0]*c[2][1]*c[3][2] + c[0][0]*c[1][3]*c[2][1]*c[3][2] +
			c[0][1]*c[1][0]*c[2][3]*c[3][2] - c[0][0]*c[1][1]*c[2][3]*c[3][2] - c[0][2]*c[1][1]*c[2][0]*c[3][3] + c[0][1]*c[1][2]*c[2][0]*c[3][3] +
			c[0][2]*c[1][0]*c[2][1]*c[3][3] - c[0][0]*c[1][2]*c[2][1]*c[3][3] - c[0][1]*c[1][0]*c[2][2]*c[3][3] + c[0][0]*c[1][1]*c[2][2]*c[3][3];
		}

		matrix4f inverted() const
		{
			matrix4f m( false );

			float d = determinant();
			if( d == 0 ) return m;
			d = 1 / d;
			
			m.c[0][0] = d * (c[1][2]*c[2][3]*c[3][1] - c[1][3]*c[2][2]*c[3][1] + c[1][3]*c[2][1]*c[3][2] - c[1][1]*c[2][3]*c[3][2] - c[1][2]*c[2][1]*c[3][3] + c[1][1]*c[2][2]*c[3][3]);
			m.c[0][1] = d * (c[0][3]*c[2][2]*c[3][1] - c[0][2]*c[2][3]*c[3][1] - c[0][3]*c[2][1]*c[3][2] + c[0][1]*c[2][3]*c[3][2] + c[0][2]*c[2][1]*c[3][3] - c[0][1]*c[2][2]*c[3][3]);
			m.c[0][2] = d * (c[0][2]*c[1][3]*c[3][1] - c[0][3]*c[1][2]*c[3][1] + c[0][3]*c[1][1]*c[3][2] - c[0][1]*c[1][3]*c[3][2] - c[0][2]*c[1][1]*c[3][3] + c[0][1]*c[1][2]*c[3][3]);
			m.c[0][3] = d * (c[0][3]*c[1][2]*c[2][1] - c[0][2]*c[1][3]*c[2][1] - c[0][3]*c[1][1]*c[2][2] + c[0][1]*c[1][3]*c[2][2] + c[0][2]*c[1][1]*c[2][3] - c[0][1]*c[1][2]*c[2][3]);
			m.c[1][0] = d * (c[1][3]*c[2][2]*c[3][0] - c[1][2]*c[2][3]*c[3][0] - c[1][3]*c[2][0]*c[3][2] + c[1][0]*c[2][3]*c[3][2] + c[1][2]*c[2][0]*c[3][3] - c[1][0]*c[2][2]*c[3][3]);
			m.c[1][1] = d * (c[0][2]*c[2][3]*c[3][0] - c[0][3]*c[2][2]*c[3][0] + c[0][3]*c[2][0]*c[3][2] - c[0][0]*c[2][3]*c[3][2] - c[0][2]*c[2][0]*c[3][3] + c[0][0]*c[2][2]*c[3][3]);
			m.c[1][2] = d * (c[0][3]*c[1][2]*c[3][0] - c[0][2]*c[1][3]*c[3][0] - c[0][3]*c[1][0]*c[3][2] + c[0][0]*c[1][3]*c[3][2] + c[0][2]*c[1][0]*c[3][3] - c[0][0]*c[1][2]*c[3][3]);
			m.c[1][3] = d * (c[0][2]*c[1][3]*c[2][0] - c[0][3]*c[1][2]*c[2][0] + c[0][3]*c[1][0]*c[2][2] - c[0][0]*c[1][3]*c[2][2] - c[0][2]*c[1][0]*c[2][3] + c[0][0]*c[1][2]*c[2][3]);
			m.c[2][0] = d * (c[1][1]*c[2][3]*c[3][0] - c[1][3]*c[2][1]*c[3][0] + c[1][3]*c[2][0]*c[3][1] - c[1][0]*c[2][3]*c[3][1] - c[1][1]*c[2][0]*c[3][3] + c[1][0]*c[2][1]*c[3][3]);
			m.c[2][1] = d * (c[0][3]*c[2][1]*c[3][0] - c[0][1]*c[2][3]*c[3][0] - c[0][3]*c[2][0]*c[3][1] + c[0][0]*c[2][3]*c[3][1] + c[0][1]*c[2][0]*c[3][3] - c[0][0]*c[2][1]*c[3][3]);
			m.c[2][2] = d * (c[0][1]*c[1][3]*c[3][0] - c[0][3]*c[1][1]*c[3][0] + c[0][3]*c[1][0]*c[3][1] - c[0][0]*c[1][3]*c[3][1] - c[0][1]*c[1][0]*c[3][3] + c[0][0]*c[1][1]*c[3][3]);
			m.c[2][3] = d * (c[0][3]*c[1][1]*c[2][0] - c[0][1]*c[1][3]*c[2][0] - c[0][3]*c[1][0]*c[2][1] + c[0][0]*c[1][3]*c[2][1] + c[0][1]*c[1][0]*c[2][3] - c[0][0]*c[1][1]*c[2][3]);
			m.c[3][0] = d * (c[1][2]*c[2][1]*c[3][0] - c[1][1]*c[2][2]*c[3][0] - c[1][2]*c[2][0]*c[3][1] + c[1][0]*c[2][2]*c[3][1] + c[1][1]*c[2][0]*c[3][2] - c[1][0]*c[2][1]*c[3][2]);
			m.c[3][1] = d * (c[0][1]*c[2][2]*c[3][0] - c[0][2]*c[2][1]*c[3][0] + c[0][2]*c[2][0]*c[3][1] - c[0][0]*c[2][2]*c[3][1] - c[0][1]*c[2][0]*c[3][2] + c[0][0]*c[2][1]*c[3][2]);
			m.c[3][2] = d * (c[0][2]*c[1][1]*c[3][0] - c[0][1]*c[1][2]*c[3][0] - c[0][2]*c[1][0]*c[3][1] + c[0][0]*c[1][2]*c[3][1] + c[0][1]*c[1][0]*c[3][2] - c[0][0]*c[1][1]*c[3][2]);
			m.c[3][3] = d * (c[0][1]*c[1][2]*c[2][0] - c[0][2]*c[1][1]*c[2][0] + c[0][2]*c[1][0]*c[2][1] - c[0][0]*c[1][2]*c[2][1] - c[0][1]*c[1][0]*c[2][2] + c[0][0]*c[1][1]*c[2][2]);
			
			return m;
		}

		void decompose( vector3f &trans, vector3f &rot, vector3f &scale ) const
		{
			// Getting translation is trivial
			trans = vector3f( c[3][0], c[3][1], c[3][2] );

			// Scale is length of columns
			scale.x = sqrt( c[0][0] * c[0][0] + c[0][1] * c[0][1] + c[0][2] * c[0][2] );
			scale.y = sqrt( c[1][0] * c[1][0] + c[1][1] * c[1][1] + c[1][2] * c[1][2] );
			scale.z = sqrt( c[2][0] * c[2][0] + c[2][1] * c[2][1] + c[2][2] * c[2][2] );

			if( scale.x == 0 || scale.y == 0 || scale.z == 0 ) return;

			// Detect negative scale with determinant and flip one arbitrary axis
			if( determinant() < 0 ) scale.x = -scale.x;

			// Combined rotation matrix YXZ
			//
			// Cos[y]*Cos[z]+Sin[x]*Sin[y]*Sin[z]	Cos[z]*Sin[x]*Sin[y]-Cos[y]*Sin[z]	Cos[x]*Sin[y]	
			// Cos[x]*Sin[z]						Cos[x]*Cos[z]						-Sin[x]
			// -Cos[z]*Sin[y]+Cos[y]*Sin[x]*Sin[z]	Cos[y]*Cos[z]*Sin[x]+Sin[y]*Sin[z]	Cos[x]*Cos[y]

			rot.x = asinf( -c[2][1] / scale.z );
			
			// Special case: Cos[x] == 0 (when Sin[x] is +/-1)
			float f = fabsf( c[2][1] / scale.z );
			if( f > 0.999f && f < 1.001f )
			{
				// Pin arbitrarily one of y or z to zero
				// Mathematical equivalent of gimbal lock
				rot.y = 0;
				
				// Now: Cos[x] = 0, Sin[x] = +/-1, Cos[y] = 1, Sin[y] = 0
				// => m[0][0] = Cos[z] and m[1][0] = Sin[z]
				rot.z = atan2f( -c[1][0] / scale.y, c[0][0] / scale.x );
			}
			// Standard case
			else
			{
				rot.y = atan2f( c[2][0] / scale.z, c[2][2] / scale.z );
				rot.z = atan2f( c[0][1] / scale.x, c[1][1] / scale.y );
			}
		}

		vector4f getCol( unsigned int col ) const
		{
			return vector4f( x[col * 4 + 0], x[col * 4 + 1], x[col * 4 + 2], x[col * 4 + 3] );
		}

		vector4f getRow( unsigned int row ) const
		{
			return vector4f( x[row + 0], x[row + 4], x[row + 8], x[row + 12] );
		}

		vector3f getScale()
		{
			vector3f scale;
			// Scale is length of columns
			scale.x = sqrt( c[0][0] * c[0][0] + c[0][1] * c[0][1] + c[0][2] * c[0][2] );
			scale.y = sqrt( c[1][0] * c[1][0] + c[1][1] * c[1][1] + c[1][2] * c[1][2] );
			scale.z = sqrt( c[2][0] * c[2][0] + c[2][1] * c[2][1] + c[2][2] * c[2][2] );
			return scale;
		}
	};


	// -------------------------------------------------------------------------------------------------
	// 平面
	// -------------------------------------------------------------------------------------------------

	class plane
	{
	public:
		vector3f normal; 
		float dist;

		plane() 
		{ 
			normal.x = 0; normal.y = 0; normal.z = 0; dist = 0; 
		};

		explicit plane( const float a, const float b, const float c, const float d )
		{
			normal = vector3f( a, b, c );
			float len = normal.length();
			normal /= len;	//正规化
			dist = d / len;
		}

		plane( const vector3f &v0, const vector3f &v1, const vector3f &v2 )
		{
			normal = v1 - v0;
			normal = normal.crossProduct( v2 - v0 ).normalized();
			dist = -(normal * v0);
		}
		// ----------------
		// Other operations
		// ----------------
		float distToPoint( const vector3f &v ) const
		{
			return (normal * v) + dist;
		}
	};
	
	inline float degToRad( float f );
	inline float radToDeg( float f );
	inline float clamp( float f, float min, float max );
	inline float minf( float a, float b );
	inline float maxf( float a, float b );
	inline bool rayTriangleIntersection( const vector3f &rayOrig, const vector3f &rayDir, const vector3f &vert0, const vector3f &vert1, const vector3f &vert2, vector3f &intsPoint );
	inline bool rayAABBIntersection( const vector3f &rayOrig, const vector3f &rayDir, const vector3f &mins, const vector3f &maxs );
	inline float nearestDistToAABB( const vector3f &pos, const vector3f &mins, const vector3f &maxs );
};


#endif
