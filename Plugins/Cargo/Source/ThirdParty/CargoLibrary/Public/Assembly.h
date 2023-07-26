#pragma once
#include <string>
#include <vector>
#include <tuple>
#include <map>

#include "defines.h"

namespace Kb3d {

	class Instance;
	class Material;

	class KBUSD_API Assembly
	{
	public:
#if defined(KBUSDFRONT)
		Assembly(const std::vector<uint8_t>& buffer);
#else
		Assembly(const std::string& fileName);
		static void PutKeyValue(const char* key, const char* buffer, const int buffer_length);
		static void ClearMemoryMap();
#endif
	private:
		Assembly() {};
	public:
		Assembly(const Assembly&);
		~Assembly();

		std::vector<Instance*> Components;
		std::map<std::string, Material*> Materials;
		const std::string& GetName();
		const std::string& GetKitShortname();

		void SetName(std::string name);
		void SetKitShortname(std::string shortname);

		void DumpInfo() const;

	private:
		const std::string _fileName;
		std::string _name;
		std::string _kitshortname;
		std::string _defaultPrimPath;
		std::string _defaultPath;

#if defined(KBUSDFRONT)
#else
		void parse_usd();
#endif

	};
}

