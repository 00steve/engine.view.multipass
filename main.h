#ifndef __MAIN_H__
#define __MAIN_H__


#include "gl_core_4_3.h"
#include "multipass.h"
#include <windows.h>


//#include <GL/gl.h>

/*  To use this exported function of dll, include this header
 *  in your project.
 */

#ifdef BUILD_DLL
    #define DLL_EXPORT __declspec(dllexport)
#else
    #define DLL_EXPORT __declspec(dllimport)
#endif





#ifdef __cplusplus
extern "C"
{
#endif

    DLL_EXPORT View* Build();
#ifdef __cplusplus
}
#endif

#endif // __MAIN_H__
