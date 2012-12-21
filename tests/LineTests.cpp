#include <stdio.h>
#include <stdlib.h>

#include "MathGeoLib.h"
#include "myassert.h"
#include "TestRunner.h"

Line RandomLineContainingPoint(const float3 &pt);
LineSegment RandomLineSegmentContainingPoint(const float3 &pt);

void TestLineLineClosestPoint()
{
	float3 pt = float3::RandomBox(rng, -float3(SCALE,SCALE,SCALE), float3(SCALE,SCALE,SCALE));
	float3 pt2 = float3::RandomBox(rng, -float3(SCALE,SCALE,SCALE), float3(SCALE,SCALE,SCALE));
	Line a = RandomLineContainingPoint(pt);
	Line b = RandomLineContainingPoint(pt2);

	float d, d2;
	float3 closestPointA = a.ClosestPoint(b, &d, &d2);
	assert(closestPointA.Equals(a.GetPoint(d), 1e-2f));
	float3 closestPointB = b.GetPoint(d2);
	float D, D2;
	float3 closestPointB2 = b.ClosestPoint(a, &D, &D2);
	assert(EqualAbs(d, D2, 1e-2f));
	assert(EqualAbs(D, d2, 1e-2f));
	assert(closestPointB.Equals(closestPointB2, 1e-2f));
	float3 closestPointA2 = a.GetPoint(D2);
	assert(closestPointA.Equals(closestPointA2, 1e-2f));

	assert(closestPointA.Distance(closestPointB) <= pt.Distance(pt2));
	assert(EqualAbs(a.Distance(b), closestPointA.Distance(closestPointB)));
}

void TestLineLineSegmentClosestPoint()
{
	float3 pt = float3::RandomBox(rng, -float3(SCALE,SCALE,SCALE), float3(SCALE,SCALE,SCALE));
	float3 pt2 = float3::RandomBox(rng, -float3(SCALE,SCALE,SCALE), float3(SCALE,SCALE,SCALE));
	Line a = RandomLineContainingPoint(pt);
	LineSegment b = RandomLineSegmentContainingPoint(pt2);

	float d, d2;
	float3 closestPointA = a.ClosestPoint(b, &d, &d2);
	assert(closestPointA.Equals(a.GetPoint(d), 1e-2f));
	float3 closestPointB = b.GetPoint(d2);
	float D, D2;
	float3 closestPointB2 = b.ClosestPoint(a, &D, &D2);
	assert(EqualAbs(d, D2));
	assert(EqualAbs(D, d2));
	assert(closestPointB.Equals(closestPointB2, 1e-2f));
	float3 closestPointA2 = a.GetPoint(D2);
	assert(closestPointA.Equals(closestPointA2, 1e-2f));

	assert(closestPointA.Distance(closestPointB) <= pt.Distance(pt2));
	assert(EqualAbs(a.Distance(b), closestPointA.Distance(closestPointB)));

	assert(closestPointA.Distance(closestPointB) <= closestPointA.Distance(b.a));
	assert(closestPointA.Distance(closestPointB) <= closestPointA.Distance(b.b));
	assert(closestPointA.Distance(closestPointB) <= a.Distance(b.a));
	assert(closestPointA.Distance(closestPointB) <= a.Distance(b.b));
}

void AddLineTests()
{
	AddRandomizedTest("Line-Line ClosestPoint", TestLineLineClosestPoint);
	AddRandomizedTest("Line-LineSegment ClosestPoint", TestLineLineSegmentClosestPoint);
}
