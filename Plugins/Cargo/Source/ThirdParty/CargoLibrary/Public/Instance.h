#pragma once

#include "defines.h"

namespace Kb3d {

	class Xform;
	class Component;

	class KBUSD_API Instance
	{
	public:
		Instance(std::string name, Xform* xForm, Component* component);
		Instance(Instance*);
		~Instance();

		const std::string& GetName();

		Component* GetComponent();
		Xform* GetXform();

		void DumpXform();
		void DumpComponent();

	private:
		std::string name;
		Xform* xf;
		Component* component;
	};
}

