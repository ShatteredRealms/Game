#pragma once

#include <functional>
#include <sstream>
#include <string>
#include <string_view>

#include "defines.h"

bool launch_debugger();
namespace Kb3d {
	class KBUSD_API Utilities
	{
	public:
		template <typename T>
		static void Replace(T& source, const T& search, const T& replacement)
		{
			if (source.empty() || search.empty()) {
				return;
			}

			size_t pos = 0;
			while ((pos = source.find(search, pos)) != std::wstring::npos) {
				source.replace(pos, search.length(), replacement);
				pos += replacement.length();
			}
		}

		static void Replace(std::wstring& source, const std::string& search, const std::string& replacement)
		{
			std::wstring wsearch = std::wstring(search.cbegin(), search.cend());
			std::wstring wreplacement = std::wstring(replacement.cbegin(), replacement.cend());

			Kb3d::Utilities::Replace(source, wsearch, wreplacement);
		}

		template <typename T>
		static uint8_t* write_datum_to_buffer(uint8_t* buffer_ptr, const T* datum);

		template <typename T>
		static uint8_t* read_datum_from_buffer(uint8_t* buffer_ptr, T* datum);

		template <typename T>
		static uint8_t* write_array_to_buffer(uint8_t* buffer_ptr, const T* data, uint32_t length);

		template <typename T>
		static uint8_t* read_array_from_buffer(uint8_t* buffer_ptr, T* data, uint32_t length);

#if !defined(KBUSDFRONT)
		static void SerializeAssemblyToBuffer(Assembly& assembly, std::vector<uint8_t>& buffer);
		static void SerializeMaterialsToBuffer(Assembly& assembly, std::vector<uint8_t>& buffer);
		static void SerializeComponentsToBuffer(Assembly& assembly, std::vector<uint8_t>& buffer);
#endif

#if defined(KBUSDFRONT)
		static void DeserializeBufferToAssembly(const std::vector<uint8_t>& buffer, Assembly& assembly);
		static void BuildARMTextures(Kb3d::Assembly& assembly);
		static void StartReceivingUnreal(std::function<void(Kb3d::Assembly& assembly)> handler, std::string dcc);
		static void StartReceivingUnreal(std::function<void(Kb3d::Assembly& assembly)> handler, std::string dcc, std::function<void(std::string)> logger);
		static void StartReceivingLoc(std::function<void(Kb3d::Assembly&)>, std::string dcc, std::string& loc);
		static void StartReceivingLoc(std::function<void(Kb3d::Assembly&)>, std::string dcc, std::string& loc, std::function<void(std::string)> logger);
		static void StartReceiving(std::function<void(Kb3d::Assembly&)>, std::string dcc);
		static void StartReceiving(std::function<void(Kb3d::Assembly& assembly)> handler, std::string dcc, std::function<void(std::string)> logger);
		static void StopReceiving();
#endif
		static std::string WstringToString(const std::wstring& wstr);
		static std::wstring StringToWstring(const std::string& str);
	};
}

#ifndef CPPCLI

template<typename T>
void format_helper(std::ostringstream& oss,
	std::string_view& str, const T& value)
{
	std::size_t openBracket = str.find('{');
	if (openBracket == std::string::npos) { return; }
	std::size_t closeBracket = str.find('}', openBracket + 1);
	if (closeBracket == std::string::npos) { return; }
	oss << str.substr(0, openBracket) << value;
	str = str.substr(closeBracket + 1);
}

template<typename... Targs>
std::string formatit(std::string_view str, Targs...args)
{
	std::ostringstream oss;
	(format_helper(oss, str, args), ...);
	oss << str;
	return oss.str();
}

#endif

