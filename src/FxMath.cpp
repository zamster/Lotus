#include "FxMath.h"

namespace FxMath
{
	//单位矩阵
	const matrix4f IDENTITY;

	// -------------------------------------------------------------------------------------------------
	// 通用
	// -------------------------------------------------------------------------------------------------

	inline float degToRad( float f ) 
	{
		return f * (FxMath::Pi / 180.0f);
	}

	inline float radToDeg( float f ) 
	{
		return f * (180.0f / FxMath::Pi);
	}

	inline float clamp( float f, float min, float max )
	{
		if( f < min ) f = min;
		if( f > max ) f = max;

		return f;
	}

	inline float minf( float a, float b )
	{
		return a < b ? a : b;
	}

	inline float maxf( float a, float b )
	{
		return a > b ? a : b;
	}

	
	// -------------------------------------------------------------------------------------------------
	//RayPicking
	// -------------------------------------------------------------------------------------------------
	inline bool rayTriangleIntersection( const vector3f &rayOrig, const vector3f &rayDir, const vector3f &vert0, const vector3f &vert1, const vector3f &vert2, vector3f &intsPoint )
	{
		// Idea: Tomas Moeller and Ben Trumbore
		// in Fast, Minimum Storage Ray/Triangle Intersection 
		
		// Find vectors for two edges sharing vert0
		vector3f edge1 = vert1 - vert0;
		vector3f edge2 = vert2 - vert0;

		// Begin calculating determinant - also used to calculate U parameter
		vector3f pvec = rayDir.crossProduct( edge2 );

		// If determinant is near zero, ray lies in plane of triangle
		float det = edge1 * pvec;


		// *** Culling branch ***
		/*if( det < FxMath::Eps )return false;

		// Calculate distance from vert0 to ray origin
		vector3f tvec = rayOrig - vert0;

		// Calculate U parameter and test bounds
		float u = tvec * pvec;
		if (u < 0 || u > det ) return false;

		// Prepare to test V parameter
		vector3f qvec = tvec.crossProduct( edge1 );

		// Calculate V parameter and test bounds
		float v = rayDir * qvec;
		if (v < 0 || u + v > det ) return false;

		// Calculate t, scale parameters, ray intersects triangle
		float t = (edge2 * qvec) / det;*/


		// *** Non-culling branch ***
		if( det > -FxMath::Eps && det < FxMath::Eps ) return 0;
		float inv_det = 1.0f / det;

		// Calculate distance from vert0 to ray origin
		vector3f tvec = rayOrig - vert0;

		// Calculate U parameter and test bounds
		float u = (tvec * pvec) * inv_det;
		if( u < 0.0f || u > 1.0f ) return 0;

		// Prepare to test V parameter
		vector3f qvec = tvec.crossProduct( edge1 );

		// Calculate V parameter and test bounds
		float v = (rayDir * qvec) * inv_det;
		if( v < 0.0f || u + v > 1.0f ) return 0;

		// Calculate t, ray intersects triangle
		float t = (edge2 * qvec) * inv_det;


		// Calculate intersection point and test ray length and direction
		intsPoint = rayOrig + rayDir * t;
		vector3f vec = intsPoint - rayOrig;
		if( vec * rayDir < 0 || vec.length() > rayDir.length() ) return false;

		return true;
	}

	// -------------------------------------------------------------------------------------------------
	//rayAABBIntersection
	// -------------------------------------------------------------------------------------------------
	inline bool rayAABBIntersection( const vector3f &rayOrig, const vector3f &rayDir, const vector3f &mins, const vector3f &maxs )
	{
		// SLAB based optimized ray/AABB intersection routine
		// Idea taken from http://ompf.org/ray/
		
		float l1 = (mins.x - rayOrig.x) / rayDir.x;
		float l2 = (maxs.x - rayOrig.x) / rayDir.x;
		float lmin = minf( l1, l2 );
		float lmax = maxf( l1, l2 );

		l1 = (mins.y - rayOrig.y) / rayDir.y;
		l2 = (maxs.y - rayOrig.y) / rayDir.y;
		lmin = maxf( minf( l1, l2 ), lmin );
		lmax = minf( maxf( l1, l2 ), lmax );
		
		l1 = (mins.z - rayOrig.z) / rayDir.z;
		l2 = (maxs.z - rayOrig.z) / rayDir.z;
		lmin = maxf( minf( l1, l2 ), lmin );
		lmax = minf( maxf( l1, l2 ), lmax );

		if( (lmax >= 0.0f) & (lmax >= lmin) )
		{
			// Consider length
			const vector3f rayDest = rayOrig + rayDir;
			vector3f rayMins( minf( rayDest.x, rayOrig.x), minf( rayDest.y, rayOrig.y ), minf( rayDest.z, rayOrig.z ) );
			vector3f rayMaxs( maxf( rayDest.x, rayOrig.x), maxf( rayDest.y, rayOrig.y ), maxf( rayDest.z, rayOrig.z ) );
			return 
			(rayMins.x < maxs.x) && (rayMaxs.x > mins.x) &&
			(rayMins.y < maxs.y) && (rayMaxs.y > mins.y) &&
			(rayMins.z < maxs.z) && (rayMaxs.z > mins.z);
		}
		else
		return false;
	}

	// -------------------------------------------------------------------------------------------------
	//nearestDistToAABB
	// -------------------------------------------------------------------------------------------------
	inline float nearestDistToAABB( const vector3f &pos, const vector3f &mins, const vector3f &maxs )
	{
		const vector3f center = (mins + maxs) / 2.0f;
		const vector3f extent = (maxs - mins) / 2.0f;
		
		vector3f nearestVec;
		nearestVec.x = maxf( 0, fabsf( pos.x - center.x ) - extent.x );
		nearestVec.y = maxf( 0, fabsf( pos.y - center.y ) - extent.y );
		nearestVec.z = maxf( 0, fabsf( pos.z - center.z ) - extent.z );
		
		return nearestVec.length();
	}

}
