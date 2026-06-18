
#include <nFramework/nIntegrator/nIntegrator.h>
#include <nFramework/util/util.h>
#include <nFramework/util/IniHandler.h>
#include <filesystem>
#include <Windows.h>
#include <iostream>

using namespace std::filesystem;

static const wchar_t* kIniFile = L"ATS.ini";

static void setWorkingDirectoryToExeDir()
{
    wchar_t exePath[MAX_PATH]{};
    if (GetModuleFileNameW(nullptr, exePath, MAX_PATH) == 0)
        return;
    current_path(std::filesystem::path(exePath).parent_path());
}

static std::wstring resolveSchemaRegistryPath(const std::wstring& binPath,
    const std::wstring& iniPath, const std::wstring& iniXml)
{
    std::filesystem::path p = iniPath.empty()
        ? std::filesystem::path(binPath) / iniXml
        : std::filesystem::path(binPath) / iniPath / iniXml;
    return std::filesystem::absolute(p).wstring();
}

int main()
{
    setWorkingDirectoryToExeDir();

    NIntegrator* nIntegrator = &(NIntegrator::getInstance());
    const std::wstring origPath = current_path().wstring();

    IniHandler iniHandler;
    iniHandler.readIni(kIniFile);

    if (iniHandler.readString(L"nLogger", L"USE") == L"true")
        nIntegrator->activateNLogger();

    if (iniHandler.readString(L"SchemaRegistryData", L"USE") == L"true")
    {
        std::wstring srPath = iniHandler.readString(L"SchemaRegistryData", L"PATH");
        std::wstring srXml = iniHandler.readString(L"SchemaRegistryData", L"XML");
        bool checkDup = iniHandler.readString(L"SchemaRegistryData", L"CheckMsgIDDuplication") == L"true";
        std::wstring srFull = resolveSchemaRegistryPath(origPath, srPath, srXml);
        if (!nIntegrator->setSchemaRegistryData(srFull, checkDup)) {
            std::wcerr << L"SchemaRegistryData load failed: " << srFull << L"\n";
            return 1;
        }
    }

    unsigned int numOfComponents = iniHandler.readUInteger(L"Components", L"Count");

    for (unsigned int cnt = 1; cnt <= numOfComponents; cnt++)
    {
        std::wstring dllIndex = L"Component_" + std::to_wstring(cnt);
        std::wstring power = iniHandler.readString(dllIndex, L"POWER");
        std::wstring dllPath = iniHandler.readString(dllIndex, L"PATH");
        std::wstring dllName = iniHandler.readString(dllIndex, L"DLL");
        std::wstring nomName = iniHandler.readString(dllIndex, L"XML");
        dllPath = dllPath.empty() ? L"" : dllPath + L"\\";
        dllPath = origPath + L"\\" + dllPath;
#ifdef _DEBUG
        dllName += L"d.dll";
#else
        dllName += L".dll";
#endif
        if (power == L"on") {
            current_path(dllPath);
            nIntegrator->plugInComponent(dllName, nomName);
            current_path(origPath);
        }
    }

    for (unsigned int cnt = 1; cnt <= numOfComponents; cnt++)
    {
        std::wstring dllIndex = L"Component_" + std::to_wstring(cnt);
        if (iniHandler.readString(dllIndex, L"POWER") == L"on") {
            auto* mgr = nIntegrator->getUserManager(iniHandler.readString(dllIndex, L"DLL"));
            if (!mgr) {
                std::wcerr << L"Manager load failed: " << iniHandler.readString(dllIndex, L"DLL") << L"\n";
                return 1;
            }
            mgr->start();
        }
    }

    std::wcout << L"ATS ready. Press Enter to exit...\n";
    tcin.get();

    for (unsigned int cnt = 1; cnt <= numOfComponents; cnt++)
    {
        std::wstring dllIndex = L"Component_" + std::to_wstring(cnt);
        if (iniHandler.readString(dllIndex, L"POWER") == L"on") {
            nIntegrator->getUserManager(iniHandler.readString(dllIndex, L"DLL"))->stop();
        }
    }
    for (unsigned int cnt = 1; cnt <= numOfComponents; cnt++)
    {
        std::wstring dllIndex = L"Component_" + std::to_wstring(cnt);
        if (iniHandler.readString(dllIndex, L"POWER") == L"on") {
            nIntegrator->plugOutComponent(iniHandler.readString(dllIndex, L"DLL"));
        }
    }
    return 0;
}
