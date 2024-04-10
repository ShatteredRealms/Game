@echo off
SETLOCAL ENABLEDELAYEDEXPANSION

pushd "..\"
set ROOT_DIR=%CD%
cd "..\go-backend\api"
set PROTOS_DIR=%CD%
REM cd "..\third_party"
REM set PROTOS_THIRD_PARTY_DIR=%CD%
popd

pushd "..\..\go-backend"
echo Pulling latest changes for go-backend
git pull
popd

set TURBOLINK_DIR=%ROOT_DIR%\Plugins\TurboLink
set PROTOC_EXE=%TURBOLINK_DIR%\Source\ThirdParty\protobuf\bin\protoc.exe
set GRPC_CPP_EXE=%TURBOLINK_DIR%\Source\ThirdParty\grpc\bin\grpc_cpp_plugin.exe
set TURBOLINK_PLUGIN_EXE=Z:\wilsimpson\protoc-gen-turbolink\bin\protoc-gen-turbolink.exe
REM set TURBOLINK_PLUGIN_EXE=%ROOT_DIR%\Tools\protoc-gen-turbolink.exe
set PROTO_WARNINGS_CPP=%CD%\proto_warnings_cpp.txt
set PROTO_WARNINGS_H=%CD%\proto_warnings_h.txt
set OUTPUT_DIR=%ROOT_DIR%\Tools\Testing
set OUTPUT_DIR=%TURBOLINK_DIR%\Source\TurboLinkGrpc
if not exist %OUTPUT_DIR% mkdir %OUTPUT_DIR%

for /R "%PROTOS_DIR%" %%a in (*.proto) do (
    set "relPath=%%~a"
    set "relPath=!relPath:%PROTOS_DIR%\=!"
    set "relPath=!relPath:\%%~nxa=!"

    if "!relPath!" == "%%~nxa" (
        Call :CreateProto %%a
        echo Creating proto for '%%a'
    ) else (
        Call :CreateProto %%a !relPath!
    echo Creating proto for '%%a' with a relative path '!relPath!'
    )
)

@REM for /R "%PROTOS_THIRD_PARTY_DIR%\google\api" %%a in (*.proto) do (
@REM     Call :CreateProto %%a google\api
@REM )

@REM for /R "%PROTOS_THIRD_PARTY_DIR%\google\protobuf" %%a in (*.proto) do (
@REM     Call :CreateProto %%a google\protobuf
@REM )


IF EXIST "%OUTPUT_DIR%\Private\pb\" RMDIR /S /Q "%OUTPUT_DIR%\Private\pb\"
mkdir %OUTPUT_DIR%\Private\pb
move "%OUTPUT_DIR%\*.pb.*" "%OUTPUT_DIR%\Private\pb\"
move "%OUTPUT_DIR%\google" "%OUTPUT_DIR%\Private\pb\"
move "%OUTPUT_DIR%\sro" "%OUTPUT_DIR%\Private\pb\"

EXIT /B 0

:CreateProto
    if [%2] == [] (
        set PROTO_CPP=%OUTPUT_DIR%\%~n1.pb.cc
        set PROTO_H=%OUTPUT_DIR%\%~n1.pb.h
    ) else (
        set PROTO_CPP=%OUTPUT_DIR%\%2\%~n1.pb.cc
        set PROTO_H=%OUTPUT_DIR%\%2\%~n1.pb.h
    )
    set PROTO_OUTPUT_DIR=%OUTPUT_DIR%\%2
    
    REM echo "PROTO_CPP: !PROTO_CPP!"
    REM echo "PROTO_H: !PROTO_H!"
    REM echo "PROTO_OUTPUT_DIR: !PROTO_OUTPUT_DIR!"
    REM echo "%PROTOC_EXE%" ^
    REM     --cpp_out="%OUTPUT_DIR%" ^
    REM     --plugin=protoc-gen-grpc="%GRPC_CPP_EXE%" --grpc_out="%OUTPUT_DIR%" ^
    REM     --plugin=protoc-gen-turbolink="%TURBOLINK_PLUGIN_EXE%" --turbolink_out="%OUTPUT_DIR%" ^
    REM     -I "%PROTOS_DIR%" ^
    REM     "%1"

        REM -I "%PROTOS_THIRD_PARTY_DIR%" ^

    @"%PROTOC_EXE%" ^
        --cpp_out="%OUTPUT_DIR%" ^
        --plugin=protoc-gen-grpc="%GRPC_CPP_EXE%" --grpc_out="%OUTPUT_DIR%" ^
        --plugin=protoc-gen-turbolink="%TURBOLINK_PLUGIN_EXE%" --turbolink_out="%OUTPUT_DIR%" ^
        -I "%PROTOS_DIR%" ^
        "%1"

    pushd %PROTO_OUTPUT_DIR%
   
    copy /b "%PROTO_WARNINGS_CPP%"+"!PROTO_CPP!" "!PROTO_CPP!.tmp"
    del /f "!PROTO_CPP!"
    if [%2] == [] (
        rename "!PROTO_CPP!.tmp" "!PROTO_CPP:%OUTPUT_DIR%\=!"
    ) else (
        rename "!PROTO_CPP!.tmp" "!PROTO_CPP:%OUTPUT_DIR%\%2\=!"
    )

    copy /b "%PROTO_WARNINGS_H%"+"!PROTO_H!" "!PROTO_H!.tmp"
    del /f "!PROTO_H!""
    if [%2] == [] (
        rename "!PROTO_H!.tmp" "!PROTO_H:%OUTPUT_DIR%\=!"
    ) else (
        rename "!PROTO_H!.tmp" "!PROTO_H:%OUTPUT_DIR%\%2\=!"
    )
   
   popd 
EXIT /B 0
