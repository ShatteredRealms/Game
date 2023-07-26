#pragma once

#include <filesystem>
#include <functional>
#include <sstream>
#include <string>
#include <string_view>

#include "defines.h"

bool launch_debugger();

namespace Kb3d {

    class KBUSD_API IEnvironment
    {
    public:
        IEnvironment() {}
        virtual ~IEnvironment() {}
        virtual std::string GetVar(std::string&) = 0;
        virtual std::string GetVar(const char*) = 0;
    };

    class KBUSD_API WindowsEnvironment : public IEnvironment
    {
    public:
        WindowsEnvironment() {}
        ~WindowsEnvironment() {}
        std::string GetVar(std::string& environmentVariable);
        std::string GetVar(const char* environmentVariable);
    };

    class KBUSD_API CargoFilesystem
    {
    public:
        CargoFilesystem(Kb3d::IEnvironment& env, bool useAppDataOverride);

        std::string AppDataAsString();
        std::filesystem::path AppDataAsPath();

        std::filesystem::path StringAsPath(std::string& str);
        std::string PathAsString(std::filesystem::path& path);

    private:
        std::filesystem::path _appdata;
        Kb3d::IEnvironment& _env;
        bool _useAppDataOverride = false;
    };
}


