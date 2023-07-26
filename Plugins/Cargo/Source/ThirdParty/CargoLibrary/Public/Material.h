#pragma once

#include <string>

#include "defines.h"

namespace Kb3d {

	typedef std::tuple<float, float, float> Color;

	typedef std::tuple<std::string, Color> ColorChannel;
	typedef std::tuple<std::string, float> ValueChannel;

	class KBUSD_API Material
	{
	public:
		Material(std::string name);
		Material(Material*);
		const std::string& GetName();

		ColorChannel BaseColor;
		ValueChannel Metalness;
		ColorChannel Normal;
		float NormalStrength;
		ValueChannel Roughness;
		ValueChannel Height;
		ValueChannel Refraction;
		float Ior;
		ColorChannel EmissionColor;
		float EmissionStrength;
		ValueChannel Opacity;
		ValueChannel ARM; // Set by Utilities.cpp

		static const std::string& FileForColor(const ColorChannel&);
		static const std::string& FileForValue(const ValueChannel&);

		static const Color& ColorForColor(const ColorChannel&);
		static const float ValueForValue(const ValueChannel&);

		size_t GetCombinedFilenameLengths();

		void DumpInfo();

	private:
		std::string _name;
	};
}

