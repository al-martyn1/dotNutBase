#pragma once


#include "Assert.h"
//
#include "GraphicsBackendInfo.h"
#include "SystemInfo.h"

#include "marty_simplesquirrel/simplesquirrel.h"

#include <simplesquirrel/simplesquirrel.hpp>

#include <cstdint>
#include <string>
#include <exception>
#include <stdexcept>
#include <functional>
#include <utility>
#include <algorithm>


namespace dotNut {


struct System
{
    SystemInfo        info;

    std::function<void(const ssq::sqstring&)> printHandler; // = []{};

    static
    ssq::sqstring objectToStringHelper(ssq::Object &o)
    {
        if (o.isNull())
        {
            return _SC("<NULL>");
        }

        if (o.isEmpty())
        {
            return _SC("<EMPTY>");
        }

        ssq::Type t = o.getType();
        switch(t)
        {
            case ssq::Type::INTEGER:         [[fallthrough]];
            case ssq::Type::FLOAT:           [[fallthrough]];
            case ssq::Type::STRING:          [[fallthrough]];
            case ssq::Type::BOOL:
                                             return marty_simplesquirrel::fromObjectConvertHelper<ssq::sqstring>(o, _SC("prnObj"));

            case ssq::Type::NULLPTR:         return _SC("<NULLPTR>");
            case ssq::Type::TABLE:           return _SC("<TABLE>");
            case ssq::Type::ARRAY:           return _SC("<ARRAY>");
            case ssq::Type::USERDATA:        return _SC("<USERDATA>");
            case ssq::Type::CLOSURE:         return _SC("<CLOSURE>");
            case ssq::Type::NATIVECLOSURE:   return _SC("<NATIVECLOSURE>");
            case ssq::Type::GENERATOR:       return _SC("<GENERATOR>");
            case ssq::Type::USERPOINTER:     return _SC("<USERPOINTER>");
            case ssq::Type::THREAD:          return _SC("<THREAD>");
            case ssq::Type::FUNCPROTO:       return _SC("<FUNCPROTO>");
            case ssq::Type::CLASS:           return _SC("<CLASS>");
            case ssq::Type::INSTANCE:        return _SC("<INSTANCE>");
            case ssq::Type::WEAKREF:         return _SC("<WEAKREF>");
            case ssq::Type::OUTER:           return _SC("<OUTER>");

            default: {}
        }

        throw ssq::TypeException("bad cast", ssq::typeToStr(ssq::Type::STRING), ssq::typeToStr(t));
    
    }

    void smpPrint(ssq::Object val) const
    {
        if (printHandler)
        {
            printHandler(objectToStringHelper(val));
        }
    }
    
    void smpPrintLn(ssq::Object val) const
    {
        if (printHandler)
        {
            printHandler(objectToStringHelper(val));
            printHandler(_SC("\n"));
        }
    }

    SystemInfo getInfo() const { return info; }
    

    static ssq::Class exposeToSquirrel(ssq::Table /* VM */ & vm, const ssq::sqstring &className = _SC("System"))
    {
        auto cls = vm.addClass( className.c_str()
                              , [=]( )
                                {
                                    return new System();
                                }
                              , false // release
                              );

        //cls.addVar(_SC("info"         ), &System::info);

        cls.addFunc( _SC("getSysInfo") , &System::getInfo);

        // operators override
        cls.addFunc( _SC("smpprint"  ) , &System::smpPrint);
        cls.addFunc( _SC("smpprintln") , &System::smpPrintLn);

        return cls;
    }


}; // System


} // namespace dotNut {

