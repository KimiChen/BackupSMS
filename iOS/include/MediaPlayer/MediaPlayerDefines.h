//
//  MediaPlayerDefines.h
//  MediaPlayer
//
//  Copyright 2008 Apple, Inc. All rights reserved.
//

#ifdef __cplusplus
#define MP_EXTERN		extern "C" __attribute__((visibility ("default")))
#else
#define MP_EXTERN	        extern __attribute__((visibility ("default")))
#endif

#define	MP_EXTERN_CLASS	__attribute__((visibility("default")))
