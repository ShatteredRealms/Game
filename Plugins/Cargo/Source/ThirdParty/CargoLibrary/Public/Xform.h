#pragma once

#include "defines.h"

namespace Kb3d {

	class KBUSD_API Xform
	{
	public:
		Xform(float mat[4][4]);
		Xform(float *mat);
		Xform(Xform*);
		Xform(const Xform&);
		Xform& operator=(const Xform&);
		float Get(int x, int y);
		const float* data();
	private:
		void copy_mat(const float  mat[4][4]);

		float xform[4][4];
	};

}

