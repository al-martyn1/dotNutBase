#pragma once


#include "../AppHost.h"
#include "../GraphicsBackendInfo.h"
#include "../System.h"
#include "../SystemInfo.h"


namespace dotnut {

namespace simplesquirrel {

template<typename TVM>
void performBinding(TVM &vm, const std::string &ns="DotNut")
{


    ssq::Table t = marty_simplesquirrel::findOrCreateTable(vm, ns);

    GraphicsBackendInfo::exposeToSquirrel(t, _SC("GraphicsBackendInfo"));
    SystemInfo         ::exposeToSquirrel(t, _SC("SystemInfo"));
    System             ::exposeToSquirrel(t, _SC("System"));
    AppHost            ::exposeToSquirrel(t, _SC("AppHost"));

}


} // namespace simplesquirrel {

} // namespace dotnut


