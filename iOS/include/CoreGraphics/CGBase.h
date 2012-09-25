/* CoreGraphics - CGBase.h
 * Copyright (c) 2000-2008 Apple Inc.
 * All rights reserved. */

#ifndef CGBASE_H_
#define CGBASE_H_

#include <stdbool.h>
#include <stddef.h>
#include <float.h>

#  include <Availability.h>

#if defined(CG_BUILDING_CG)
#  define CG_AVAILABLE_STARTING(_mac,_iphone)
#  define CG_AVAILABLE_BUT_DEPRECATED(_mac,_macDep,_iphone,_iphoneDep)
#else /* !defined(CG_BUILDING_CG) */
#  define CG_AVAILABLE_STARTING __OSX_AVAILABLE_STARTING
#  define CG_AVAILABLE_BUT_DEPRECATED __OSX_AVAILABLE_BUT_DEPRECATED
#endif /* !defined(CG_BUILDING_CG) */

#  if defined(_WIN32) || defined(__CYGWIN32__)
#    define __WIN32__ 1
#  endif

#if !defined(CG_EXTERN_C_BEGIN)
#  if defined(__cplusplus)
#    define CG_EXTERN_C_BEGIN
#    define CG_EXTERN_C_END
#  else /* !defined(__cplusplus) */
#    define CG_EXTERN_C_BEGIN
#    define CG_EXTERN_C_END
#  endif /* !defined(__cplusplus) */
#endif /* !defined(CG_EXTERN_C_BEGIN) */

#if !defined(CG_EXTERN)
#    if defined(__cplusplus)
#      define CG_EXTERN extern "C"
#    else /* !defined(__cplusplus) */
#      define CG_EXTERN extern
#    endif /* !defined(__cplusplus) */
#endif /* !defined(CG_EXTERN) */

#if !defined(CG_PRIVATE_EXTERN)
#  if defined(__GNUC__)
#    define CG_PRIVATE_EXTERN __private_extern__
#  else /* !defined(__GNUC__) */
#    define CG_PRIVATE_EXTERN CG_EXTERN
#  endif /* !defined(__GNUC__) */
#endif /* !defined(CG_PRIVATE_EXTERN) */

#if !defined(CG_LOCAL)
#  define CG_LOCAL CG_PRIVATE_EXTERN
#endif

#if !defined(CG_OBSOLETE)
#  if defined(__GNUC__)							\
    && ((__GNUC__ == 3 && __GNUC_MINOR__ >= 1) || __GNUC__ >= 4)
#      define CG_OBSOLETE __attribute__((deprecated))
#  else
#    define CG_OBSOLETE
#  endif
#endif /* !defined(CG_OBSOLETE) */

#if !defined(CG_INLINE)
#  if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
#    define CG_INLINE static inline
#  elif defined(__MWERKS__) || defined(__cplusplus)
#    define CG_INLINE static inline
#  elif defined(__GNUC__)
#    define CG_INLINE static __inline__
#  else
#    define CG_INLINE static    
#  endif
#endif /* !defined(CG_INLINE) */

#if !defined(__GNUC__) && !defined(__MWERKS__)
#  define __attribute__(attribute)
#endif

#if defined(__LP64__) && __LP64__
typedef double CGFloat;
#define CGFLOAT_MIN DBL_MIN
#define CGFLOAT_MAX DBL_MAX
#define CGFLOAT_IS_DOUBLE 1
#else /* !defined(__LP64__) || !__LP64__ */
typedef float CGFloat;
#define CGFLOAT_MIN FLT_MIN
#define CGFLOAT_MAX FLT_MAX
#define CGFLOAT_IS_DOUBLE 0
#endif /* !defined(__LP64__) || !__LP64__ */

#define CGFLOAT_DEFINED 1

#endif /* CGBASE_H_ */
