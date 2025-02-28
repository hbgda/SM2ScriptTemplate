#include "utils.h"

#include <Windows.h>
#include <iostream>
#include <string>

namespace utils {
    void create_console() {
        AllocConsole();
        freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);
        freopen_s((FILE**)stderr, "CONOUT$", "w", stderr);
    }

    void destroy_console() {
        fclose(stdout);
        fclose(stderr);
        FreeConsole();
    }

    void kill_process() {
        destroy_console();
        HANDLE curr_proc = GetCurrentProcess();
        TerminateProcess(curr_proc, NULL);
        CloseHandle(curr_proc);
    }

    std::string get_executable_directory() {
        char buffer[MAX_PATH];
        GetModuleFileNameA(NULL, buffer, MAX_PATH);
        std::string::size_type pos = std::string(buffer).find_last_of("\\/");
        return std::string(buffer).substr(0, pos);
    }

    std::string GetGameExecutable() {
        static std::string executable;
        if (executable.empty()) {
            char buffer[MAX_PATH];
            GetModuleFileNameA(NULL, buffer, MAX_PATH);
            std::string::size_type pos = std::string(buffer).find_last_of("\\/");
            executable = std::string(buffer).substr(pos + 1);
        }
        return executable;
    }
}