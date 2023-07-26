#pragma once

#include <vector>
#include <tuple>

#include "defines.h"

#include "GeomSubset.h"


namespace Kb3d {
	class GeomSubset;

	typedef std::tuple<float, float, float> Vertex;
	typedef std::tuple<float, float, float> Normal;
	typedef std::tuple<float, float> Uv;

	typedef std::vector<Vertex> VertexArray;
	typedef std::vector<Uv> UvArray;
	typedef std::vector<int> FaceArray;
	typedef std::vector<int> FaceCountArray;
	typedef std::vector<Normal> NormalArray;
	typedef std::vector<GeomSubset*> GeomSubsetArray;
	typedef std::vector<int> SmoothingGroupsArray;

	class KBUSD_API Mesh
	{
	public:
		Mesh() {};
		Mesh(Mesh*);
		~Mesh();

#if defined(KBUSDFRONT)
		bool are_normals_mismatched();
		bool are_uvs_mismatched();
		void reverse_faces();
#endif
		VertexArray vertices;
		NormalArray normals;
		UvArray uvs;
		FaceArray faces;
		FaceCountArray faceCounts;

		SmoothingGroupsArray smoothingGroups;
		GeomSubsetArray subsets;
	};

}

