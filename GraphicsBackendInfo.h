#pragma once


#include "Assert.h"
//
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


struct GraphicsBackendInfo
{
    ssq::sqstring    name; // Win32/Linux/etc

    GraphicsBackendInfo()
#if defined(WIN32) || defined(WIN32)
    : name       (_SC("GDI"))
#else
    : name       (_SC("Unknown"))
#endif
    {}

    GraphicsBackendInfo( const GraphicsBackendInfo &) = default;
    GraphicsBackendInfo( GraphicsBackendInfo &&) = default;

    GraphicsBackendInfo& operator=( const GraphicsBackendInfo &) = default;
    GraphicsBackendInfo& operator=( GraphicsBackendInfo &&) = default;

    ssq::sqstring getName() const { return name; }

    static ssq::Class exposeToSquirrel(ssq::Table /* VM */ & vm, const ssq::sqstring &className = _SC("GraphicsBackendInfo"))
    {
        auto cls = vm.addClass( className.c_str()
                              , []( )
                                {
                                    return new GraphicsBackendInfo();
                                }
                              , false // release
                              );

        //cls.addVar(_SC("name"), &GraphicsBackendInfo::name);
        cls.addFunc(_SC("getName"), &GraphicsBackendInfo::getName);

        return cls;
    }


}; // struct GraphicsBackendInfo



} // namespace dotnut



