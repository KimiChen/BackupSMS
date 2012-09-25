/*
 * Copyright (c) 2000-2007 Apple Inc. All rights reserved.
 */
/*
 * Copyright (c) 1992 NeXT Computer, Inc.
 *
 */

#ifndef	_ARM_SIGNAL_
#define	_ARM_SIGNAL_ 1

#include <sys/appleapiopts.h>

#ifndef _ANSI_SOURCE

#ifdef __APPLE_API_OBSOLETE

#if !defined(_POSIX_C_SOURCE) || defined(_DARWIN_C_SOURCE)

#define __need_struct_sigcontext
#include <arm/_structs.h>

typedef int sig_atomic_t;

#endif /* (_POSIX_C_SOURCE && !_DARWIN_C_SOURCE) */

#endif /* __APPLE_API_OBSOLETE */

#endif /* _ANSI_SOURCE */

#endif	/* _ARM_SIGNAL_ */

