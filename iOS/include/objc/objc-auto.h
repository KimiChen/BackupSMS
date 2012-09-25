/*
 * Copyright (c) 2004-2007 Apple Inc. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 * 
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this
 * file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 * 
 * @APPLE_LICENSE_HEADER_END@
 */

#ifndef _OBJC_AUTO_H_
#define _OBJC_AUTO_H_

#import <objc/objc.h>
#include <sys/types.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <AvailabilityMacros.h>
#include <libkern/OSAtomic.h>


/* GC is unsupported on some architectures. */
#if defined(__i386__) || defined(__x86_64__) || defined(__ppc__) || defined(__ppc64__)
    /* GC supported */
#elif defined(__arm__)
    /* GC unsupported */
#   define OBJC_NO_GC 1
#else
#   error unknown architecture
#endif

#ifdef OBJC_NO_GC
#   define OBJC_GC_EXPORT static
#else
#   define OBJC_GC_EXPORT OBJC_EXPORT
#endif


/* Collection utilities */

enum {
    // choose one
    OBJC_RATIO_COLLECTION        = (0 << 0),  // run "ratio" generational collections, then a full
    OBJC_GENERATIONAL_COLLECTION = (1 << 0),  // run fast incremental collection
    OBJC_FULL_COLLECTION         = (2 << 0),  // run full collection.
    OBJC_EXHAUSTIVE_COLLECTION   = (3 << 0),  // run full collections until memory available stops improving
    
    OBJC_COLLECT_IF_NEEDED       = (1 << 3), // run collection only if needed (allocation threshold exceeded)
    OBJC_WAIT_UNTIL_DONE         = (1 << 4), // wait (when possible) for collection to end before returning (when collector is running on dedicated thread)
};

OBJC_GC_EXPORT void objc_collect(unsigned long options);
OBJC_GC_EXPORT BOOL objc_collectingEnabled(void);


/* GC configuration */

/* Tells collector to wait until specified bytes have been allocated before trying to collect again. */
OBJC_GC_EXPORT void objc_setCollectionThreshold(size_t threshold);

/* Tells collector to run a full collection for every ratio generational collections. */
OBJC_GC_EXPORT void objc_setCollectionRatio(size_t ratio);

/* Tells collector to start collecting on dedicated thread */
OBJC_GC_EXPORT void objc_startCollectorThread(void);


// atomic update of a global variable
OBJC_GC_EXPORT BOOL objc_atomicCompareAndSwapGlobal(id predicate, id replacement, volatile id *objectLocation);
OBJC_GC_EXPORT BOOL objc_atomicCompareAndSwapGlobalBarrier(id predicate, id replacement, volatile id *objectLocation);
// atomic update of an instance variable
OBJC_GC_EXPORT BOOL objc_atomicCompareAndSwapInstanceVariable(id predicate, id replacement, volatile id *objectLocation);
OBJC_GC_EXPORT BOOL objc_atomicCompareAndSwapInstanceVariableBarrier(id predicate, id replacement, volatile id *objectLocation);

/* Write barriers.  Used by the compiler.  */
OBJC_GC_EXPORT id objc_assign_strongCast(id val, id *dest);
OBJC_GC_EXPORT id objc_assign_global(id val, id *dest);
OBJC_GC_EXPORT id objc_assign_ivar(id value, id dest, ptrdiff_t offset);
OBJC_GC_EXPORT void *objc_memmove_collectable(void *dst, const void *src, size_t size);

OBJC_GC_EXPORT id objc_read_weak(id *location);
OBJC_GC_EXPORT id objc_assign_weak(id value, id *location);


//
// SPI. The following routines are available as debugging and transitional aides.
//

/* Tells runtime to issue finalize calls on the main thread only. */
OBJC_GC_EXPORT void objc_finalizeOnMainThread(Class cls);


/* ask if object is scheduled for finalization.  Safe only when called from within a finalizer.  */
OBJC_GC_EXPORT BOOL objc_is_finalized(void *ptr);

enum {
    OBJC_CLEAR_RESIDENT_STACK = (1 << 0)
};

/* Stack management */
OBJC_GC_EXPORT void objc_clear_stack(unsigned long options);

//
// Obsolete.  Present only until all uses can be migrated to newer API.
//

OBJC_GC_EXPORT BOOL objc_collecting_enabled(void);
OBJC_GC_EXPORT void objc_start_collector_thread(void);

/* Memory management */
OBJC_EXPORT id objc_allocate_object(Class cls, int extra);

enum {
    OBJC_GENERATIONAL = (1 << 0)
};

OBJC_GC_EXPORT void objc_collect_if_needed(unsigned long options);


/* Non-GC substitutes for everything above. */
#ifdef OBJC_NO_GC

static inline void objc_collect(unsigned long options) { }
static inline BOOL objc_collectingEnabled(void) { return NO; }
static inline void objc_setCollectionThreshold(size_t threshold) { }
static inline void objc_setCollectionRatio(size_t ratio) { }
static inline void objc_startCollectorThread(void) { }

#import <libkern/OSAtomic.h>

static inline BOOL objc_atomicCompareAndSwapGlobal(id predicate, id replacement, volatile id *objectLocation) 
    { return OSAtomicCompareAndSwapPtr((void *)predicate, (void *)replacement, (void * volatile *)objectLocation); }

static inline BOOL objc_atomicCompareAndSwapGlobalBarrier(id predicate, id replacement, volatile id *objectLocation) 
    { return OSAtomicCompareAndSwapPtrBarrier((void *)predicate, (void *)replacement, (void * volatile *)objectLocation); }

static inline BOOL objc_atomicCompareAndSwapInstanceVariable(id predicate, id replacement, volatile id *objectLocation) 
    { return OSAtomicCompareAndSwapPtr((void *)predicate, (void *)replacement, (void * volatile *)objectLocation); }

static inline BOOL objc_atomicCompareAndSwapInstanceVariableBarrier(id predicate, id replacement, volatile id *objectLocation) 
    { return OSAtomicCompareAndSwapPtrBarrier((void *)predicate, (void *)replacement, (void * volatile *)objectLocation); }


static inline id objc_assign_strongCast(id val, id *dest) 
    { return (*dest = val); }

static inline id objc_assign_global(id val, id *dest) 
    { return (*dest = val); }

static inline id objc_assign_ivar(id val, id dest, ptrdiff_t offset) 
    { return (*(id*)((char *)dest+offset) = val); }

static inline void *objc_memmove_collectable(void *dst, const void *src, size_t size) 
    { return memmove(dst, src, size); }

static inline id objc_read_weak(id *location) 
    { return *location; }

static inline id objc_assign_weak(id value, id *location) 
    { return (*location = value); }


static inline void objc_finalizeOnMainThread(Class cls) { }
static inline BOOL objc_is_finalized(void *ptr) { return NO; }
static inline void objc_clear_stack(unsigned long options) { }

static inline BOOL objc_collecting_enabled(void) { return NO; }
static inline void objc_start_collector_thread(void) { }

static inline void objc_collect_if_needed(unsigned long options) { }

#endif

#endif
