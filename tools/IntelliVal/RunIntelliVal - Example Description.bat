@echo off

rem IntelliVal.exe 
rem     [Binary directory (ex: --bin=../bin)]
rem     [Source directory (ex: --src=../src)]
rem     [PlugIn manager name (ex: --mgr=XXManager)]
rem     [PlugIn manager NOM name (ex: --nom=XXManager.xml)]
rem     [Output file's extension: h or cs (ex: --outext=cs)]
rem         [If 'cs' then: C# project name (ex: --csproj=XXGUI)]
rem     [Schema Registry Data usage: y or n (ex: --schreg=y)]
rem         [If 'y' then: Schema Registry Data file path under Binary directory (ex: --srpath=SchemaRegistryData.xml)]
rem     [Option: Enable writing function for Type Dispatching: y or n (ex: --tdspc=y)]

rem Example: header file, without schema registry data
IntelliVal.exe --bin=../bin --src=../src --mgr=PlugInManagerWithoutSchemaRegistry --nom=PlugInManagerWithoutSchemaRegistry.xml --outext=h --schreg=n --tdspc=y

rem Example: header file, with schema registry data
IntelliVal.exe --bin=../bin --src=../src --mgr=PlugInManagerWithSchemaRegistry --nom=PlugInManagerWithSchemaRegistry.xml --outext=h --schreg=y --srpath=SchemaRegistryData.xml --tdspc=y

rem Example: cs file, without schema registry data
IntelliVal.exe --bin=../bin --src=../src --mgr=PlugInManagerWithoutSchemaRegistry --nom=PlugInManagerWithoutSchemaRegistry.xml --outext=cs --csproj=GUIProject --schreg=n --tdspc=y

rem Example: cs file, with schema registry data
IntelliVal.exe --bin=../bin --src=../src --mgr=PlugInManagerWithSchemaRegistry --nom=PlugInManagerWithSchemaRegistry.xml --outext=cs --csproj=GUIProject --schreg=y --srpath=SchemaRegistryData.xml --tdspc=y

pause