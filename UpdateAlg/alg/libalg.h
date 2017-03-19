/* 
 * libalg.h 
 */
#ifndef LIB_ALG_H
#define LIB_ALG_H

#ifdef __cplusplus
#define EXPORT extern "C" __declspec (dllexport)
#else
#define EXPORT __declspec (dllexport)
#endif

EXPORT int WINAPI GetMax(int a, int b);

#endif 