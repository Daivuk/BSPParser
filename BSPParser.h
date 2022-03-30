#pragma once

#include <cstdint>

#include "FileFormat/Parser.h"

struct BSPTexture
{
	int32_t flags;
	BSPStructs::Vector reflectivity;
	const char* path;
	int32_t width, height;
};

class BSPMap
{
private:
	bool mIsValid = false;

	// Raw data
	uint8_t* mpData;
	size_t mDataSize = 0U;

	// Raw BSP structs
	const BSPStructs::Header* mpHeader;

	const BSPStructs::Vector* mpVertices;
	size_t mNumVertices = 0U;

	const BSPStructs::Plane* mpPlanes;
	size_t mNumPlanes = 0U;

	const BSPStructs::Edge* mpEdges;
	size_t mNumEdges = 0U;

	const int32_t* mpSurfEdges;
	size_t mNumSurfEdges = 0U;

	const BSPStructs::Face* mpFaces;
	size_t mNumFaces = 0U;

	const BSPStructs::TexInfo* mpTexInfos;
	size_t mNumTexInfos = 0U;

	const BSPStructs::TexData* mpTexDatas;
	size_t mNumTexDatas = 0U;

	const int32_t* mpTexDataStringTable;
	size_t mNumTexDataStringTableEntries = 0U;

	const char* mpTexDataStringData;
	size_t mNumTexDataStringDatas = 0U;

	// Triangulated faces
	size_t mNumTris = 0U;

	float* mpPositions;
	float* mpNormals, * mpTangents, * mpBinormals;
	float* mpUVs;
	uint32_t* mpTexIndices;

	template<class LumpDatatype>
	bool ParseLump(const LumpDatatype** pArray, size_t* pLength)
	{
		return BSPParser::ParseLump(
			mpData, mDataSize,
			mpHeader,
			pArray, pLength
		);
	}

	bool IsFaceNodraw(const BSPStructs::Face* pFace) const;

	void FreeAll();

	bool CalcUVs(
		const int32_t texInfoIdx, const float* pos,
		float* pUVs
	) const;

	bool GetSurfEdgeVerts(const int32_t index, float* pVertA, float* pVertB = nullptr) const;

	bool Triangulate();

public:
	BSPMap(const uint8_t* pFileData, const size_t dataSize);
	~BSPMap();

	// Returns whether the BSP was loaded correctly
	bool IsValid() const;

	// Returns relevant texture information for an index in the TexInfo lump
	BSPTexture GetTexture(const uint32_t index) const;

	// Gets the number of triangles in the triangulated BSP data
	size_t GetNumTris() const;

	// Returns a const pointer to the vertex positions as raw float data
	const float* GetVertPositions() const;

	// Returns a const pointer to the triangle normals as raw float data
	const float* GetTriNormals() const;

	// Returns a const pointer to the triangle tangents as raw float data
	const float* GetTriTangents() const;

	// Returns a const pointer to the triangle binormals as raw float data
	const float* GetTriBinormals() const;

	// Returns a const pointer to the vertex UVs as raw float data
	const float* GetVertUVs() const;

	// Returns a const pointer to the triangle TexInfo indices as an array of uint32_t
	const uint32_t* GetTriTextures() const;
};
