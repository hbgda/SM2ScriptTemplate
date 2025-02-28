#pragma once

#include <cstring>
#include <queue>
#include <functional>
#include <mutex>

#include "../scan.h"
#include "../logging.h"
#include "../utils.h"

template<typename T>
struct NativeTypedef;

#define CALL_VIRTUAL(self, index, ret, params, ...) ((ret (*)params)((*(void***)self)[index]))(__VA_ARGS__)

#define DECLARE_NATIVE_FUNC(s, n, r, p)                  \
    namespace Native {                                   \
        namespace s {                                    \
            inline r (*n)p;                              \
        }                                                \
        namespace Initializers {                         \
            namespace s {                                \
                void Init_ ## n();                       \
            }                                            \
        }                                                \
    }                                                    \
    struct Typedef_ ## s ## _ ## n {                     \
        using Type = r (*)p;                             \
    };                                                   \


#define DECLARE_NATIVE_REF(s, n, t)                      \
    namespace Native {                                   \
        namespace s {                                    \
            inline t n;                                  \
        }                                                \
        namespace Initializers {                         \
            namespace s {                                \
                void Init_ ## n();                       \
            }                                            \
        }                                                \
    }                                                    \
    struct Typedef_ ## s ## _ ## n {                     \
        using Type = t;                                  \
    };                                                   \


#define MEMBER(n) Init_ ## n();

#define DECLARE_NATIVE(s, p) \
    namespace Native { \
        namespace Initializers { \
            namespace s { \
                inline void Init() { \
                    p \
                } \
            } \
        } \
    }

#define SCAN_NATIVE(s, n, pt) \
    void Native::Initializers::s::Init_ ## n() { \
        auto res = Scan::Internal::ScanModule(utils::GetGameExecutable().c_str(), pt); \
        if (!res.found) { FATAL("Native::%s::%s not found!", #s, #n); return; } \
        Native::s::n = reinterpret_cast<Typedef_ ## s ## _ ## n::Type>(res.loc); \
        DEBUG(" - Native::%s::%s found at %p", #s, #n, Native::s::n); \
    }

#define SCAN_NATIVE_CALL(s, n, pt) \
    void Native::Initializers::s::Init_ ## n() { \
        auto res = Scan::Internal::ScanModule(utils::GetGameExecutable().c_str(), pt); \
        if (!res.found) { FATAL("Native::%s::%s not found!", #s, #n); return; } \
        int32_t offset; \
        std::memcpy(&offset, res.store, sizeof(res.store)); \
        Native::s::n = reinterpret_cast<Typedef_ ## s ## _ ## n::Type>(res.loc + 5 + offset); \
        DEBUG(" - Native::%s::%s found at %p", #s, #n, Native::s::n); \
    }

#define SCAN_NATIVE_REF(s, n, pt) \
    void Native::Initializers::s::Init_ ## n() { \
        auto res = Scan::Internal::ScanModule(utils::GetGameExecutable().c_str(), pt); \
        if (!res.found) { FATAL("Native::%s::%s not found!", #s, #n); return; } \
        int32_t offset; \
        std::memcpy(&offset, res.store, sizeof(res.store)); \
        Native::s::n = reinterpret_cast<Typedef_ ## s ## _ ## n::Type>(res.loc + 7 + offset); \
        DEBUG(" - Native::%s::%s found at %p", #s, #n, Native::s::n); \
    }

#define SCAN(pt, r, n, p) \
    r (*n) p = nullptr; \
    void Init_ ## n() { \
        auto n ## _res = Scan::Internal::ScanModule(utils::GetGameExecutable().c_str(), pt); \
        if (!n ## _res.found) { FATAL("%s not found!", #n); return; } \
        n = (r (*) p)n ## _res.loc; \
        DEBUG(" - %s found at %p", #n, n); \
    } \

#define SCAN_CALL(pt, r, n, p) \
    r (*n) p = nullptr; \
    void Init_ ## n() { \
        auto n ## _res = Scan::Internal::ScanModule(utils::GetGameExecutable().c_str(), pt); \
        if (!n ## _res.found) { FATAL("%s not found!", #n); return; } \
        int32_t offset; \
        std::memcpy(&offset, n ## _res.store, sizeof(n ## _res.store)); \
        n = (r (*) p)(n ## _res.loc + 5 + offset); \
        DEBUG(" - %s found at %p", #n, n); \
    } \

#define SCAN_REF(pt, t, n) \
    t n = nullptr; \
    void Init_ ## n() { \
        auto n ## _res = Scan::Internal::ScanModule(utils::GetGameExecutable().c_str(), pt); \
        if (!n ## _res.found) { FATAL("%s not found!", #n); return; } \
        int32_t offset; \
        std::memcpy(&offset, n ## _res.store, sizeof(offset)); \
        n = (t)(n ## _res.loc + 7 + offset); \
        DEBUG(" - %s found at %p", #n, n); \
    } \

#define SCAN_NOP(pt, n, b, o) \
    void Init_ ## n() { \
        auto n ## _res = Scan::Internal::ScanModule(utils::GetGameExecutable().c_str(), pt); \
        if (!n ## _res.found) { FATAL("%s not found!", #n); return; } \
        unsigned char* addr = (unsigned char*)n ## _res.loc; \
        DWORD oldProtect; \
        if (!VirtualProtect(addr, b, PAGE_EXECUTE_READWRITE, &oldProtect)) { \
            FATAL("Failed to change memory protection at %p", addr); return; } \
        std::memset(addr, 0x90, b); \
        VirtualProtect(addr, b, oldProtect, &oldProtect); \
        DEBUG(" - NOP'd %d bytes at %p", b, addr); \
        *o = addr; \
    } \

#define SCAN_PATCH(pt, n, b) \
    void Init_ ## n() { \
        auto n ## _res = Scan::Internal::ScanModule(utils::GetGameExecutable().c_str(), pt); \
        if (!n ## _res.found) { FATAL("%s not found!", #n); return; } \
        unsigned char* addr = (unsigned char*)n ## _res.loc; \
        DWORD oldProtect; \
        if (!VirtualProtect(addr, sizeof(b), PAGE_EXECUTE_READWRITE, &oldProtect)) { \
            FATAL("Failed to change memory protection at %p", addr); return; } \
        std::memcpy(addr, b, sizeof(b)); \
        VirtualProtect(addr, sizeof(b), oldProtect, &oldProtect); \
        DEBUG(" - Patched %zu bytes at %p", sizeof(b), addr); \
    } \

#define ADDRESS_PATCH(a, n, b) \
    void Init_ ## n() { \
        unsigned char* target_addr = a; \
        DWORD oldProtect; \
        if (!VirtualProtect(target_addr, sizeof(b), PAGE_EXECUTE_READWRITE, &oldProtect)) { \
            FATAL("Failed to change memory protection at %p", target_addr); return; } \
        std::memcpy(target_addr, b, sizeof(b)); \
        VirtualProtect(target_addr, sizeof(b), oldProtect, &oldProtect); \
        DEBUG(" - Patched %zu bytes at %p", sizeof(b), target_addr); \
    } \

namespace Native {
    void Init();
}