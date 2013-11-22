/*
 * UtilityMacros.h
 *
 * Created: 11/3/2013 1:01:17 AM
 *  Author: Compaq_Administrator
 */


#ifndef UTILITY_MACROS_H_
#define UTILITY_MACROS_H_

#define DO_PRAGMA(x) _Pragma (#x)
#define TODO(x) DO_PRAGMA(message ("TODO - " #x))

#define XSTR(x) STR(x)
#define STR(x) #x

#endif /* UTILITY_MACROS_H_ */