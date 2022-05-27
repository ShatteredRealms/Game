@echo off

:: Default User Variables ################################################################

:: Default gRPC tag
set DEFAULT_TAG=v1.45.0

:: Default UE Path
SET DEFAULT_UE_ROOT=C:\UnrealEngine\

:: User Specific Variables ###############################################################

set /p TAG="Enter gRPC Tag (v1.45.0): "

set /p UE_ROOT="Enter path to Unreal Engine (C:\UnrealEngine\): "

IF "%TAG%" == "" (set TAG=%DEFAULT_TAG%)
IF "%UE_ROOT%" == "" (set UE_ROOT=%DEFAULT_UE_ROOT%)


:: Static Variables #############################################################################

set SCRIPT_FOLDER=%cd%

set GRPC_ROOT=%SCRIPT_FOLDER%\grpc
set GRPC_OUT_ROOT=%SCRIPT_FOLDER%\grpc\generated
set GRPC_INCLUDE_DIR=%GRPC_OUT_ROOT%\include
set GRPC_LIBRARIES_DIR=%GRPC_OUT_ROOT%\lib\Win64
set GRPC_BINARIES_DIR=%GRPC_OUT_ROOT%\bin\Win64

set CMAKE_BUILD_DIR=%GRPC_ROOT%\.build

set REMOTE_ORIGIN=https://github.com/grpc/grpc.git

::#####################################VARS#############################################################################

:GET_UE_ROOT
IF "%UE_ROOT%" == "" (echo "UE_ROOT directory does not exist, please set correct UE_ROOT via SET UE_ROOT=<PATH_TO_UNREAL_ENGINE_FOLDER>" && GOTO ABORT)

:CLEAN
IF EXIST %GRPC_ROOT% (rd /s /q %GRPC_ROOT%)
IF EXIST %GRPC_OUT_ROOT% (rd /s /q %GRPC_OUT_ROOT%)

:CLONE
call git clone --recursive -b %TAG% %REMOTE_ORIGIN% && cd %GRPC_ROOT%

:BUILD_ALL
mkdir %CMAKE_BUILD_DIR% && cd %CMAKE_BUILD_DIR%

::Use "Visual Studio 16 2019" to generate a Visual Studio 2019 x64 solution
call cmake .. -G "Visual Studio 16 2019" -DCMAKE_CXX_STANDARD_LIBRARIES="Crypt32.Lib User32.lib Advapi32.lib" -DCMAKE_BUILD_TYPE=Release -DCMAKE_CONFIGURATION_TYPES=Release -Dprotobuf_BUILD_TESTS=OFF -DgRPC_ZLIB_PROVIDER=package -DZLIB_INCLUDE_DIR="%UE_ROOT%\Engine\Source\ThirdParty\zlib\v1.2.8\include\Win64\VS2015" -DZLIB_LIBRARY_DEBUG="%UE_ROOT%\Engine\Source\ThirdParty\zlib\v1.2.8\lib\Win64\VS2015\Debug\zlibstatic.lib" -DZLIB_LIBRARY_RELEASE="%UE_ROOT%\Engine\Source\ThirdParty\zlib\v1.2.8\lib\Win64\VS2015\Release\zlibstatic.lib" -DgRPC_SSL_PROVIDER=package -DLIB_EAY_LIBRARY_DEBUG="%UE_ROOT%\Engine\Source\ThirdParty\OpenSSL\1.1.1\Lib\Win64\VS2015\Debug\libcrypto.lib" -DLIB_EAY_LIBRARY_RELEASE="%UE_ROOT%\Engine\Source\ThirdParty\OpenSSL\1.1.1\Lib\Win64\VS2015\Release\libcrypto.lib" -DLIB_EAY_DEBUG="%UE_ROOT%\Engine\Source\ThirdParty\OpenSSL\1.1.1\Lib\Win64\VS2015\Debug\libcrypto.lib" -DLIB_EAY_RELEASE="%UE_ROOT%\Engine\Source\ThirdParty\OpenSSL\1.1.1\Lib\Win64\VS2015\Release\libcrypto.lib" -DOPENSSL_INCLUDE_DIR="%UE_ROOT%\Engine\Source\ThirdParty\OpenSSL\1.1.1\include\Win64\VS2015" -DSSL_EAY_DEBUG="%UE_ROOT%\Engine\Source\ThirdParty\OpenSSL\1.1.1\Lib\Win64\VS2015\Debug\libssl.lib" -DSSL_EAY_LIBRARY_DEBUG="%UE_ROOT%\Engine\Source\ThirdParty\OpenSSL\1.1.1\Lib\Win64\VS2015\Debug\libssl.lib" -DSSL_EAY_LIBRARY_RELEASE="%UE_ROOT%\Engine\Source\ThirdParty\OpenSSL\1.1.1\Lib\Win64\VS2015\Release\libssl.lib" -DSSL_EAY_RELEASE="%UE_ROOT%\Engine\Source\ThirdParty\OpenSSL\1.1.1\Lib\Win64\VS2015\Release\libssl.lib"
call cmake --build . --target ALL_BUILD --config Release

:COPY_HEADERS
robocopy %GRPC_ROOT%\include %GRPC_INCLUDE_DIR%\ *.h *.inc *.proto /E > nul
robocopy %GRPC_ROOT%\third_party\protobuf\src\google %GRPC_INCLUDE_DIR%\google *.h *.inc *.proto /E > nul

:COPY_LIBRARIES
robocopy "%CMAKE_BUILD_DIR%\Release" %GRPC_LIBRARIES_DIR% *.lib /R:0 /S > nul
robocopy "%CMAKE_BUILD_DIR%\third_party\cares\cares\lib\Release" %GRPC_LIBRARIES_DIR% *.lib /R:0 /S > nul
robocopy "%CMAKE_BUILD_DIR%\third_party\benchmark\src\Release" %GRPC_LIBRARIES_DIR% *.lib /R:0 /S > nul
robocopy "%CMAKE_BUILD_DIR%\third_party\gflags\Release" %GRPC_LIBRARIES_DIR% *.lib /R:0 /S > nul
robocopy "%CMAKE_BUILD_DIR%\third_party\protobuf\Release" %GRPC_LIBRARIES_DIR% *.lib /R:0 /S > nul

:COPY_BINARIES
robocopy "%CMAKE_BUILD_DIR%\Release" %GRPC_BINARIES_DIR% *.exe /R:0 /S > nul
copy "%CMAKE_BUILD_DIR%\third_party\protobuf\Release\protoc.exe" %GRPC_BINARIES_DIR%\protoc.exe

:REMOVE_USELESS_INCLUDES
IF EXIST %GRPC_INCLUDE_DIR%\grpc++ (rd /s /q %GRPC_INCLUDE_DIR%\grpc++)

:REMOVE_USELESS_LIBRARIES
del %GRPC_LIBRARIES_DIR%\grpc_csharp_ext.lib
del %GRPC_LIBRARIES_DIR%\gflags_static.lib
del %GRPC_LIBRARIES_DIR%\gflags_nothreads_static.lib
del %GRPC_LIBRARIES_DIR%\benchmark.lib

:Finish
cd %SCRIPT_FOLDER%
GOTO GRACEFULEXIT

:ABORT
echo Aborted...
pause

:GRACEFULEXIT
echo Build done!
pause