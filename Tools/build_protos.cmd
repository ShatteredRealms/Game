@echo off
SETLOCAL ENABLEDELAYEDEXPANSION

pushd "..\"
set ROOT_DIR=%CD%
cd "..\go-backend\api"
set PROTOS_DIR=%CD%
cd "..\third_party"
set PROTOS_THIRD_PARTY_DIR=%CD%
popd

set PROTOC_EXE=%ROOT_DIR%\ThirdParty\protobuf\bin\protoc.exe
set GRPC_CPP_EXE=%ROOT_DIR%\ThirdParty\grpc\bin\grpc_cpp_plugin.exe
set PROTO_WARNINGS_CPP=%CD%\proto_warnings_cpp.txt
set PROTO_WARNINGS_H=%CD%\proto_warnings_h.txt
set OUTPUT_DIR=%ROOT_DIR%\Source\SRO\Private\pb
if not exist %OUTPUT_DIR% mkdir %OUTPUT_DIR%

for %%a in ("%PROTOS_DIR%\*.proto") do (
    Call :CreateProto %%a
)

for /R "%PROTOS_THIRD_PARTY_DIR%" %%a in (*.proto) do (
    Call :CreateProto %%a google\api
)

EXIT /B 0

:CreateProto
    set PROTO_CPP="%~n1.pb.cc"
    set PROTO_H="%~n1.pb.h"
    set PROTO_OUTPUT_DIR=%OUTPUT_DIR%\%2
    
    "%PROTOC_EXE%" ^
        --cpp_out="%OUTPUT_DIR%" ^
        --plugin=protoc-gen-grpc="%GRPC_CPP_EXE%" --grpc_out="%OUTPUT_DIR%" ^
        -I "%PROTOS_THIRD_PARTY_DIR%" ^
        -I "%PROTOS_DIR%" ^
        "%1"
      
   pushd %PROTO_OUTPUT_DIR%
   
   copy /b %PROTO_WARNINGS_CPP%+!PROTO_CPP! !PROTO_CPP!.tmp
   del /f !PROTO_CPP!
   rename !PROTO_CPP!.tmp !PROTO_CPP!
   
   copy /b %PROTO_WARNINGS_H%+!PROTO_H! !PROTO_H!.tmp
   del /f !PROTO_H!
   rename !PROTO_H!.tmp !PROTO_H!
   
   popd 
EXIT /B 0