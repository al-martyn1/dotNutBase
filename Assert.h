#pragma once

#include <exception>
#include <stdexcept>


//----------------------------------------------------------------------------
/*! \def DOTNUT_ASSERT(expr)
    Проверка условия и аварийный выход (или сообщение с последующим продолжением работы).

    При компиляции под Qt или Win32 будут вызваны соответствующие функции Qt/Windows, отображающие диалог с сообщением об ошибке.

    При компиляции для железа и работе под отладчиком последний должен показать место, где произошел assert.
    \note Не факт что это всегда работает.
*/

#if defined(Q_ASSERT)

    #define DOTNUT_ASSERT( statement )         Q_ASSERT(statement)

#elif defined(WIN32) || defined(_WIN32)

    #include <winsock2.h>
    #include <windows.h>
    #include <crtdbg.h>

    #define DOTNUT_ASSERT( statement )         _ASSERTE(statement)

#else

    #include <cassert>

    #define DOTNUT_ASSERT( statement )         assert(condition) 

#endif


//------------------------------
//! DOTNUT_ASSERT_FAIL срабатывает всегда, и ставится туда, куда, по идее, никогда попадать не должны
#define DOTNUT_ASSERT_FAIL()                   DOTNUT_ASSERT( 0 )
