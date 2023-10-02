#pragma once


#include "Assert.h"
//
#include "GraphicsBackendInfo.h"

#include "marty_simplesquirrel/simplesquirrel.h"

#include <simplesquirrel/simplesquirrel.hpp>

#include <cstdint>
#include <string>
#include <exception>
#include <stdexcept>
#include <functional>
#include <utility>
#include <algorithm>


namespace dotnut {


struct SystemInfo
{
    ssq::sqstring          kernel    ; // WinNT/Linux/etc
    ssq::sqstring          osName      ; // Windows/Debian/Ubuntu/etc. Or distName?
    ssq::sqstring          versionStr; //
    ssq::sqstring          platform  ; //

    GraphicsBackendInfo    graphicsBackendInfo;

    SystemInfo()
#if defined(WIN32) || defined(WIN32)
    : kernel     (_SC("WinNT"))
    , osName     (_SC("GenericWindows"))
    , versionStr (_SC("Unknown"))
  #if defined(_MSC_VER)
    #if defined(_M_IX86)
    , platform   (_SC("x86"))
    #elif defined(_M_ARM)
    , platform   (_SC("arm"))
    #elif defined(_M_ARM64)
    , platform   (_SC("arm64"))
    #elif defined(_M_ARM64EC)
    , platform   (_SC("arm64ec"))
    #elif defined(_M_AMD64)
    , platform   (_SC("x64"))
    #elif defined()
    , platform   (_SC("Unknown"))
    #endif
  #else // not MSVC
    #if defined(_WIN64)
    , platform   (_SC("x64"))
    #else
    , platform   (_SC("x86"))
    #endif
  #endif
    , graphicsBackendInfo()
#else
    : kernel     (_SC("Unknown"))
    , osName     (_SC("Unknown"))
    , versionStr (_SC("Unknown"))
    , platform   (_SC("Unknown"))
    , graphicsBackendInfo()
#endif
    {}

    SystemInfo( const SystemInfo &) = default;
    SystemInfo( SystemInfo &&) = default;

    SystemInfo& operator=( const SystemInfo &) = default;
    SystemInfo& operator=( SystemInfo &&) = default;


    static ssq::Class exposeToSquirrel(ssq::Table /* VM */ & vm, const ssq::sqstring &className = _SC("SystemInfo"))
    {
        auto cls = vm.addClass( className.c_str()
                              , []( )
                                {
                                    return new SystemInfo();
                                }
                              , false // release
                              );

        cls.addVar(_SC("kernel"         ), &SystemInfo::kernel);
        cls.addVar(_SC("os"             ), &SystemInfo::osName);
        cls.addVar(_SC("osVer"          ), &SystemInfo::versionStr);
        cls.addVar(_SC("versionStr"     ), &SystemInfo::versionStr);
        cls.addVar(_SC("platform"       ), &SystemInfo::platform);
        cls.addVar(_SC("graphicsBackend"), &SystemInfo::graphicsBackendInfo);
        //cls.addVar(_SC(""), &SystemInfo::);

        return cls;
    }



};



} // namespace dotnut


