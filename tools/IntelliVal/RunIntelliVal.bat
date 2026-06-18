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

IntelliVal.exe --bin=../bin --src=../src --mgr=BarManager --nom=BarManager.xml --outext=h --schreg=y --srpath=SchemaRegistryData.xml --tdspc=y
IntelliVal.exe --bin=../bin --src=../src --mgr=CommandManager --nom=CommandManager.xml --outext=h --schreg=y --srpath=SchemaRegistryData.xml --tdspc=y
IntelliVal.exe --bin=../bin --src=../src --mgr=FooManager --nom=FooManager.xml --outext=h --schreg=y --srpath=SchemaRegistryData.xml --tdspc=y
IntelliVal.exe --bin=../bin --src=../src --mgr=NewRoleManager --nom=NewRoleManager.xml --outext=h --schreg=y --srpath=SchemaRegistryData.xml --tdspc=y
IntelliVal.exe --bin=../bin --src=../src --mgr=UIManager --nom=UIManager.xml --outext=h --schreg=y --srpath=SchemaRegistryData.xml --tdspc=y
IntelliVal.exe --bin=../bin --src=../src --mgr=DDSCommunicationManager --nom=DDSCommunicationManager.xml --outext=h --schreg=y --srpath=SchemaRegistryData.xml --tdspc=y
IntelliVal.exe --bin=../bin --src=../src --mgr=RTICommunicationManager --nom=RTICommunicationManager.xml --outext=h --schreg=y --srpath=SchemaRegistryData.xml --tdspc=y
IntelliVal.exe --bin=../bin --src=../src --mgr=TCPCommunicationManager --nom=TCPCommunicationManager.xml --outext=h --schreg=y --srpath=SchemaRegistryData.xml --tdspc=y
IntelliVal.exe --bin=../bin --src=../src --mgr=UDPCommunicationManager --nom=UDPCommunicationManager.xml --outext=h --schreg=y --srpath=SchemaRegistryData.xml --tdspc=y
IntelliVal.exe --bin=../bin --src=../src --mgr=UIManager --nom=UIManager.xml --outext=cs --csproj=MiniProject_GUI --schreg=y --srpath=SchemaRegistryData.xml --tdspc=y
IntelliVal.exe --bin=../bin --src=../src --mgr=UIManager --nom=UIManager.xml --outext=cs --csproj=MiniProject_GUI.Net8 --schreg=y --srpath=SchemaRegistryData.xml --tdspc=y

pause