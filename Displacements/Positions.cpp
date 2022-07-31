#include "Displacements.h"

using namespace BSPStructs;

void Displacements::GenerateDispSurf(
	const DispInfo* pDisp, const DispVert* dispVerts,
	const Vector corners[4],
	Vector* pVerts
)
{
	int postSpacing = (1 << pDisp->power) + 1;
	float ooInt = 1.0f / (float)(postSpacing - 1);

	Vector edgeInt[2];
	edgeInt[0] = corners[1] - corners[0];
	edgeInt[0] *= ooInt;

	edgeInt[1] = corners[2] - corners[3];
	edgeInt[1] *= ooInt;

	for (int i = 0; i < postSpacing; i++) {
		Vector endPts[2];
		endPts[0] = edgeInt[0] * i + corners[0];
		endPts[1] = edgeInt[1] * i + corners[3];

		Vector seg, segInt;
		seg = endPts[1] - endPts[0];
		segInt = seg * ooInt;

		for (int j = 0; j < postSpacing; j++) {
			int ndx = i * postSpacing + j;

			const DispVert* pDispVert = dispVerts + ndx;

			pVerts[ndx] = endPts[0] + (segInt * j);
			pVerts[ndx] += pDispVert->vec * pDispVert->dist;
		}
	}
}