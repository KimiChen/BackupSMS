/*
     File:      AudioUnit/AudioComponent.h
 
     Contains:  
 
     Version:   Mac OS X
 
     Copyright: (c) 2007 by Apple Inc., all rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
*/

#ifndef __AUDIOCOMPONENT_H__
#define __AUDIOCOMPONENT_H__

/*
	This file is designed to preserve binary compatibility with existing Leopard API while removing the dependency
	on the Component Mgr on the embedded platform.
	
	It also defines equivalent API in common use for finding and open audio components (such as audio units and audio codecs)
*/

#include <Availability.h>
#if !defined(__COREAUDIO_USE_FLAT_INCLUDES__)
	#include <CoreAudio/CoreAudioTypes.h>
	#include <CoreFoundation/CoreFoundation.h>
#else
    #include <CoreAudioTypes.h>
	#include <CoreFoundation.h>
#endif

	// these are defined with binary compatibility in mind for the use of these objects in API calls
	
#pragma pack(push, 4)
typedef struct AudioComponentDescription {
	OSType              componentType;          /* A unique 4-byte code indentifying the command set */
	OSType              componentSubType;       /* Particular flavor of this instance */
	OSType              componentManufacturer;  /* Vendor identification */
	UInt32              componentFlags;         /* should be set to zero */
	UInt32              componentFlagsMask;     /* should be set to zero */
} AudioComponentDescription;
#pragma pack(pop)

typedef struct OpaqueAudioComponent *	AudioComponent;

#if TARGET_OS_IPHONE
	typedef struct OpaqueAudioComponentInstance *	AudioComponentInstance;
#else
	typedef struct ComponentInstanceRecord *	AudioComponentInstance;
#endif


#ifdef __cplusplus
extern "C" {
#endif

// finds the next component matching AudioComponentDescription after the specified AudioComponent
extern AudioComponent 
AudioComponentFindNext (AudioComponent inComponent, const AudioComponentDescription * inDesc) 
	__OSX_AVAILABLE_STARTING(__MAC_10_6,__IPHONE_2_0);

// the number of AudioComponenents that match the specified AudioComponentDescription
extern UInt32
AudioComponentCount (const AudioComponentDescription * inDesc)
	__OSX_AVAILABLE_STARTING(__MAC_10_6,__IPHONE_2_0);

// returns the generic name of the AudioComponent
extern OSStatus 
AudioComponentCopyName (AudioComponent inComponent, CFStringRef *outName)
	__OSX_AVAILABLE_STARTING(__MAC_10_6,__IPHONE_2_0);

// returns the class description of the AudioComponent
extern OSStatus 
AudioComponentGetDescription(AudioComponent inComponent, AudioComponentDescription *outDesc)
	__OSX_AVAILABLE_STARTING(__MAC_10_6,__IPHONE_2_0);

// returns the version of the audio component in the form of 0xMMMMmmDD (Major, Minor, Dot)
extern OSStatus 
AudioComponentGetVersion(AudioComponent inComponent, UInt32 *outVersion)
	__OSX_AVAILABLE_STARTING(__MAC_10_6,__IPHONE_2_0);

// creates a new instance of the specified AudioComponent.
extern OSStatus 
AudioComponentInstanceNew(AudioComponent inComponent, AudioComponentInstance *outInstance)
	__OSX_AVAILABLE_STARTING(__MAC_10_6,__IPHONE_2_0);

// disposes the specified instance
extern OSStatus 
AudioComponentInstanceDispose(AudioComponentInstance inInstance)
	__OSX_AVAILABLE_STARTING(__MAC_10_6,__IPHONE_2_0);

// retrieves the class object assosciated with the instance
extern AudioComponent 
AudioComponentInstanceGetComponent (AudioComponentInstance inInstance)
	__OSX_AVAILABLE_STARTING(__MAC_10_6,__IPHONE_2_0);

#ifdef __cplusplus
}
#endif


#endif // __AUDIOCOMPONENT_H__
