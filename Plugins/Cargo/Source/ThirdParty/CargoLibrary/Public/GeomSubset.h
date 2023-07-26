#pragma once

#include <string>
#include <vector>

#include "defines.h"

namespace Kb3d {

	class KBUSD_API GeomSubset
	{
	public:
		GeomSubset(const std::string& );
		GeomSubset(GeomSubset*);
		~GeomSubset();

		const std::string material;
		std::vector<int> materialIndices;

	};
}

