
#include <nFramework/nIntegrator/nIntegrator.h>
#include <nFramework/util/util.h>
#include <nFramework/util/IniHandler.h>
#include <nFramework/nLineStream/NLineStreamMain.h>
#include <filesystem>
#include <Windows.h>

using namespace std::filesystem;

static const wchar_t* kIniFile = L"LCS.ini";

static void setWorkingDirectoryToExeDir()
{
    wchar_t exePath[MAX_PATH]{};
    if (GetModuleFileNameW(nullptr, exePath, MAX_PATH) == 0)
        return;
    current_path(path(exePath).parent_path());
}

static void waitForShutdown()
{
    HANDLE stdinHandle = GetStdHandle(STD_INPUT_HANDLE);
    if (stdinHandle != nullptr && stdinHandle != INVALID_HANDLE_VALUE) {
        DWORD mode = 0;
        if (GetConsoleMode(stdinHandle, &mode))
            tcin.get();
        else
            Sleep(INFINITE);
    } else {
        Sleep(INFINITE);
    }
}

int main()
{
    setWorkingDirectoryToExeDir();

    NIntegrator* nIntegrator = &(NIntegrator::getInstance());
    nlinelog::INLineLog* lgr = &(nlinelog::NLineLog::getInstance());
    nlinestream::NLineTstream ntcout{ nlinestream::Level::COUT };
    nlinestream::NLineTstream ntcerr{ nlinestream::Level::CERR };
    lgr->enableLevelTag();

    const std::wstring origPath = current_path().wstring();

    tcout << L"SimulatorMain starting\n";

    IniHandler iniHandler;
    if (!iniHandler.readIni(kIniFile)) {
        tcerr << L"Failed to read ini: " << kIniFile << L"\n";
        return 1;
    }

    if (iniHandler.readString(L"nLogger", L"USE") == L"true")
        nIntegrator->activateNLogger();

    if (iniHandler.readString(L"SchemaRegistryData", L"USE") == L"true")
    {
        std::wstring srPath = iniHandler.readString(L"SchemaRegistryData", L"PATH");
        std::wstring srXml = iniHandler.readString(L"SchemaRegistryData", L"XML");
        const bool checkDup = iniHandler.readString(L"SchemaRegistryData", L"CheckMsgIDDuplication") == L"true";
        srPath = srPath.empty() ? L"" : srPath + L"\\";
        srXml = srPath + srXml;
        if (!nIntegrator->setSchemaRegistryData(srXml, checkDup)) {
            tcerr << L"SchemaRegistryData load failed: " << srXml << L"\n";
            return 1;
        }
    }

    const unsigned int numOfComponents = iniHandler.readUInteger(L"Components", L"Count");

    for (unsigned int cnt = 1; cnt <= numOfComponents; cnt++)
    {
        const std::wstring dllIndex = L"Component_" + std::to_wstring(cnt);
        const std::wstring power = iniHandler.readString(dllIndex, L"POWER");
        if (power != L"on")
            continue;

        std::wstring dllPath = iniHandler.readString(dllIndex, L"PATH");
        std::wstring dllName = iniHandler.readString(dllIndex, L"DLL");
        const std::wstring nomName = iniHandler.readString(dllIndex, L"XML");
        dllPath = dllPath.empty() ? L"" : dllPath + L"\\";
        dllPath = origPath + L"\\" + dllPath;
#ifdef _DEBUG
        dllName += L"d.dll";
#else
        dllName += L".dll";
#endif
        tcout << L"Plug-in " << dllName << L" (" << nomName << L")\n";
        current_path(dllPath);
        nIntegrator->plugInComponent(dllName, nomName);
        current_path(origPath);
    }

    if (iniHandler.readString(L"ValidatingComponents", L"USE") == L"true")
        nIntegrator->validateComponentsPluggedIn();

    for (unsigned int cnt = 1; cnt <= numOfComponents; cnt++)
    {
        const std::wstring dllIndex = L"Component_" + std::to_wstring(cnt);
        if (iniHandler.readString(dllIndex, L"POWER") != L"on")
            continue;
        const std::wstring dllKey = iniHandler.readString(dllIndex, L"DLL");
        auto* mgr = nIntegrator->getUserManager(dllKey);
        if (!mgr) {
            tcerr << L"Manager load failed: " << dllKey << L"\n";
            return 1;
        }
        mgr->start();
    }

    tcout << L"LCS ready. Press Enter to exit...\n";
    waitForShutdown();

    for (unsigned int cnt = 1; cnt <= numOfComponents; cnt++)
    {
        const std::wstring dllIndex = L"Component_" + std::to_wstring(cnt);
        if (iniHandler.readString(dllIndex, L"POWER") == L"on") {
            nIntegrator->getUserManager(iniHandler.readString(dllIndex, L"DLL"))->stop();
        }
    }
    for (unsigned int cnt = 1; cnt <= numOfComponents; cnt++)
    {
        const std::wstring dllIndex = L"Component_" + std::to_wstring(cnt);
        if (iniHandler.readString(dllIndex, L"POWER") == L"on") {
            nIntegrator->plugOutComponent(iniHandler.readString(dllIndex, L"DLL"));
        }
    }
    return 0;
}
