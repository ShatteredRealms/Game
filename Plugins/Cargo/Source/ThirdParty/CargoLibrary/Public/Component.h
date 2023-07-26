#pragma once

#include "defines.h"

namespace Kb3d {

	class Mesh;

	class KBUSD_API Component
	{
	public:
		Component(Mesh*);
		Component(Component*);
		~Component();
		Mesh* GetMesh();

	private:
		Mesh* _m;
	};
}

