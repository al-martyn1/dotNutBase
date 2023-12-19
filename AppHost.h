#pragma once


#include "Assert.h"
//
#include "GraphicsBackendInfo.h"
#include "SystemInfo.h"
#include "System.h"

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


struct AppHost
{
    System    sys;

    static ssq::Class exposeToSquirrel(ssq::Table /* VM */ & vm, const ssq::sqstring &className = _SC("AppHost"))
    {
        auto cls = vm.addClass( className.c_str()
                              , []( )
                                {
                                    return new AppHost();
                                }
                              , false // release
                              );

        cls.addVar(_SC("sys"         ), &AppHost::sys);

        return cls;
    }


}; // struct AppHost


} // namespace dotnut {

