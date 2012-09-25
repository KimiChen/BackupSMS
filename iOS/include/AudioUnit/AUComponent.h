/*
	File:		AUComponent.h

	Contains:	AudioUnit Interfaces

	Version:	Mac OS X

	Copyright:	© 2002-2004 by Apple Computer, Inc., all rights reserved.

	Bugs?:		For bug reports, consult the following page on
				the World Wide Web:

					http://developer.apple.com/bugreporter/
*/

#ifndef __AUCOMPONENT__
#define __AUCOMPONENT__

#include <Availability.h>
#if !defined(__COREAUDIO_USE_FLAT_INCLUDES__)
	#include <AudioUnit/AudioComponent.h>
	#include <CoreAudio/CoreAudioTypes.h>
#else
	#include <Components.h>
	#include <CoreAudioTypes.h>
#endif

#if PRAGMA_ONCE
#pragma once
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if PRAGMA_IMPORT
#pragma import on
#endif

#if !__LP64__
	#if PRAGMA_STRUCT_ALIGN
		#pragma options align=mac68k
	#elif PRAGMA_STRUCT_PACKPUSH
		#pragma pack(push, 2)
	#elif PRAGMA_STRUCT_PACK
		#pragma pack(2)
	#endif
#endif

//-----------------------------------------------------------------------------
//	An audio unit is of type ComponentInstance, defined by the Component Manager.
//-----------------------------------------------------------------------------
typedef AudioComponentInstance AudioUnit;


//-----------------------------------------------------------------------------
//	Audio unit component types and subtypes
//-----------------------------------------------------------------------------

enum
{
	kAudioUnitType_Output					= 'auou',
	kAudioUnitSubType_GenericOutput			= 'genr',
#if !TARGET_OS_IPHONE
	kAudioUnitSubType_HALOutput				= 'ahal',
	kAudioUnitSubType_DefaultOutput			= 'def ',
	kAudioUnitSubType_SystemOutput			= 'sys ',
#else
	kAudioUnitSubType_RemoteIO				= 'rioc',
#endif


	kAudioUnitType_MusicDevice				= 'aumu',
#if !TARGET_OS_IPHONE
	kAudioUnitSubType_DLSSynth				= 'dls ',
#endif

	kAudioUnitType_MusicEffect				= 'aumf',

	kAudioUnitType_FormatConverter			= 'aufc',
	kAudioUnitSubType_AUConverter			= 'conv',
	kAudioUnitSubType_TimePitch				= 'tmpt',
#if !TARGET_OS_IPHONE
	kAudioUnitSubType_Varispeed				= 'vari',
	kAudioUnitSubType_DeferredRenderer		= 'defr',
	kAudioUnitSubType_Splitter				= 'splt',
	kAudioUnitSubType_Merger				= 'merg',
#endif
	
	kAudioUnitType_Effect					= 'aufx',
#if !TARGET_OS_IPHONE
	kAudioUnitSubType_Delay					= 'dely',
	kAudioUnitSubType_LowPassFilter			= 'lpas',
	kAudioUnitSubType_HighPassFilter		= 'hpas',
	kAudioUnitSubType_BandPassFilter		= 'bpas',
	kAudioUnitSubType_HighShelfFilter		= 'hshf',
	kAudioUnitSubType_LowShelfFilter		= 'lshf',
	kAudioUnitSubType_ParametricEQ			= 'pmeq',
	kAudioUnitSubType_GraphicEQ				= 'greq',
	kAudioUnitSubType_PeakLimiter			= 'lmtr',
	kAudioUnitSubType_DynamicsProcessor		= 'dcmp',
	kAudioUnitSubType_MultiBandCompressor	= 'mcmp',
	kAudioUnitSubType_MatrixReverb			= 'mrev',
	kAudioUnitSubType_SampleDelay			= 'sdly',
	kAudioUnitSubType_Pitch					= 'tmpt',
	kAudioUnitSubType_AUFilter				= 'filt',
	kAudioUnitSubType_NetSend				= 'nsnd',
	kAudioUnitSubType_Distortion			= 'dist',
	kAudioUnitSubType_RogerBeep				= 'rogr',
#else
	kAudioUnitSubType_AUiPodEQ				= 'ipeq',
#endif
	
	kAudioUnitType_Mixer					= 'aumx',
	kAudioUnitSubType_MultiChannelMixer		= 'mcmx',
#if !TARGET_OS_IPHONE
	kAudioUnitSubType_StereoMixer			= 'smxr',
	kAudioUnitSubType_3DMixer				= '3dmx',
	kAudioUnitSubType_MatrixMixer			= 'mxmx',
#else
	kAudioUnitSubType_AU3DMixerEmbedded		= '3dem',
#endif

	kAudioUnitType_Panner					= 'aupn',
#if !TARGET_OS_IPHONE
	kAudioUnitSubType_SphericalHeadPanner	= 'sphr',
	kAudioUnitSubType_VectorPanner			= 'vbas',
	kAudioUnitSubType_SoundFieldPanner		= 'ambi',
	kAudioUnitSubType_HRTFPanner			= 'hrtf',
#endif

	kAudioUnitType_OfflineEffect			= 'auol',

	kAudioUnitType_Generator				= 'augn',
#if !TARGET_OS_IPHONE
	kAudioUnitSubType_ScheduledSoundPlayer	= 'sspl',
	kAudioUnitSubType_AudioFilePlayer		= 'afpl',
	kAudioUnitSubType_NetReceive			= 'nrcv',
#endif

	kAudioUnitManufacturer_Apple			= 'appl'
};

//-----------------------------------------------------------------------------
//	Render flags
//-----------------------------------------------------------------------------

enum
{
								/* these are obsolete, were never implemented: */
								/*	kAudioUnitRenderAction_Accumulate			= (1 << 0) */
								/*	kAudioUnitRenderAction_UseProvidedBuffer	= (1 << 1) */
	kAudioUnitRenderAction_PreRender		= (1 << 2),
	kAudioUnitRenderAction_PostRender		= (1 << 3),
	kAudioUnitRenderAction_OutputIsSilence	= (1 << 4),
		/* Provides hint on return from Render(). if set, the buffer contains all zeroes */
	kAudioOfflineUnitRenderAction_Preflight	= (1 << 5),
	kAudioOfflineUnitRenderAction_Render	= (1 << 6),
	kAudioOfflineUnitRenderAction_Complete	= (1 << 7),
		// this flag is set if on the post-render call an error was returned by the AUs render
		// in this case, the error can be retrieved through the lastRenderError property
		// and the ioData handed to the post-render notification will be invalid.
	kAudioUnitRenderAction_PostRenderError	= (1 << 8)
};

typedef UInt32							AudioUnitRenderActionFlags;

//-----------------------------------------------------------------------------
//	Errors
//-----------------------------------------------------------------------------

enum
{
	kAudioUnitErr_InvalidProperty			= -10879,
	kAudioUnitErr_InvalidParameter			= -10878,
	kAudioUnitErr_InvalidElement			= -10877,
	kAudioUnitErr_NoConnection				= -10876,
	kAudioUnitErr_FailedInitialization		= -10875,
	kAudioUnitErr_TooManyFramesToProcess	= -10874,
	kAudioUnitErr_IllegalInstrument			= -10873,
	kAudioUnitErr_InstrumentTypeNotFound	= -10872,
	kAudioUnitErr_InvalidFile				= -10871,
	kAudioUnitErr_UnknownFileType			= -10870,
	kAudioUnitErr_FileNotSpecified			= -10869,
	kAudioUnitErr_FormatNotSupported		= -10868,
	kAudioUnitErr_Uninitialized				= -10867,
	kAudioUnitErr_InvalidScope				= -10866,
	kAudioUnitErr_PropertyNotWritable		= -10865,
	kAudioUnitErr_CannotDoInCurrentContext	= -10863,
		/*
			Same error code, but different calling context,
			as kAUGraphErr_CannotDoInCurrentContext	
		*/
	kAudioUnitErr_InvalidPropertyValue		= -10851,
	kAudioUnitErr_PropertyNotInUse			= -10850,
	kAudioUnitErr_Initialized				= -10849,
		/* Indicates the operation cannot be performed because the audio unit is initialized. */
	kAudioUnitErr_InvalidOfflineRender		= -10848,
	kAudioUnitErr_Unauthorized				= -10847
};


//-----------------------------------------------------------------------------
//	Types specific to Audio Unit Services
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Properties, Parameters, Scopes, and Elements
//
//	A value of 0xFFFFFFFF should never be used for a real scope,
//	element, or parameter ID, as this value is reserved for use with the
//	AUParameterListener APIs to do wild card searches.
//
//	Apple reserves the range of 0-1023 for specifying scopes; any custom
//	scope values should lie outside of this range.
//-----------------------------------------------------------------------------

typedef UInt32							AudioUnitPropertyID;
typedef UInt32							AudioUnitParameterID;
typedef UInt32							AudioUnitScope;
typedef UInt32							AudioUnitElement;
typedef	Float32							AudioUnitParameterValue;

//-----------------------------------------------------------------------------
//	Audio unit parameter events
//-----------------------------------------------------------------------------
enum
{
	kParameterEvent_Immediate	= 1,
	kParameterEvent_Ramped		= 2
};

typedef UInt32							AUParameterEventType;

struct AudioUnitParameterEvent
{
	AudioUnitScope			scope;
	AudioUnitElement		element;
	AudioUnitParameterID	parameter;
	
	AUParameterEventType	eventType;
	
	union
	{
		struct
		{
			SInt32						startBufferOffset;
			UInt32						durationInFrames;
			AudioUnitParameterValue		startValue;
			AudioUnitParameterValue		endValue;
		}					ramp;
		
		struct
		{
			UInt32						bufferOffset;
			AudioUnitParameterValue		value;
		}					immediate;		

	}						eventValues;
};

typedef struct AudioUnitParameterEvent	AudioUnitParameterEvent;


//-----------------------------------------------------------------------------
//	The following types are used by functions in the AudioUnitCarbonView.h and 
//	/AudioUnitUtilities.h header files:
//-----------------------------------------------------------------------------

struct AudioUnitParameter
{
	AudioUnit				mAudioUnit;
	AudioUnitParameterID	mParameterID;
	AudioUnitScope			mScope;
	AudioUnitElement		mElement;
};

typedef struct AudioUnitParameter	AudioUnitParameter;

struct AudioUnitProperty
{
	AudioUnit				mAudioUnit;
	AudioUnitPropertyID		mPropertyID;
	AudioUnitScope			mScope;
	AudioUnitElement		mElement;
};

typedef struct AudioUnitProperty	AudioUnitProperty;

//-----------------------------------------------------------------------------

typedef OSStatus
(*AURenderCallback)(	void *							inRefCon,
						AudioUnitRenderActionFlags *	ioActionFlags,
						const AudioTimeStamp *			inTimeStamp,
						UInt32							inBusNumber,
						UInt32							inNumberFrames,
						AudioBufferList *				ioData);

typedef void
(*AudioUnitPropertyListenerProc)(	void *				inRefCon,
									AudioUnit			ci,
									AudioUnitPropertyID	inID,
									AudioUnitScope		inScope,
									AudioUnitElement	inElement);

typedef void
(*AUInputSamplesInOutputCallback)(	void *						inRefCon,
									const AudioTimeStamp *		inOutputTimeStamp,
									Float64						inInputSample,
									Float64						inNumberInputSamples);

//=============================================================================
//	Functions
//=============================================================================

extern OSStatus
AudioUnitInitialize(				AudioUnit				ci)						__OSX_AVAILABLE_STARTING(__MAC_10_0,__IPHONE_2_0);


extern OSStatus
AudioUnitUninitialize(				AudioUnit				ci)						__OSX_AVAILABLE_STARTING(__MAC_10_0,__IPHONE_2_0);



extern OSStatus
AudioUnitGetPropertyInfo(			AudioUnit				ci,
									AudioUnitPropertyID 	inID,
									AudioUnitScope			inScope,
									AudioUnitElement		inElement,
									UInt32 *				outDataSize,
									Boolean *				outWritable)			__OSX_AVAILABLE_STARTING(__MAC_10_0,__IPHONE_2_0);

//-----------------------------------------------------------------------------
//	AudioUnitGetProperty
//
//	Set the outData parameter to NULL to determine how much memory to allocate for
//	variable size properties. The ioDataSize parameter must be a pointer to a UInt32
//	value containing the size of the expected result. Upon return, this
//	parameter will contain the size of the data copied.
//-----------------------------------------------------------------------------
extern OSStatus
AudioUnitGetProperty(				AudioUnit				ci,
									AudioUnitPropertyID		inID,
									AudioUnitScope			inScope,
									AudioUnitElement		inElement,
									void *					outData,
									UInt32 *				ioDataSize)				__OSX_AVAILABLE_STARTING(__MAC_10_0,__IPHONE_2_0);


extern OSStatus
AudioUnitSetProperty(				AudioUnit				ci,
									AudioUnitPropertyID		inID,
									AudioUnitScope			inScope,
									AudioUnitElement		inElement,
									const void *			inData,
									UInt32					inDataSize)				__OSX_AVAILABLE_STARTING(__MAC_10_0,__IPHONE_2_0);

extern OSStatus
AudioUnitAddPropertyListener(		AudioUnit						ci,
									AudioUnitPropertyID				inID,
									AudioUnitPropertyListenerProc	inProc,
									void *							inProcUserData)   __OSX_AVAILABLE_STARTING(__MAC_10_0,__IPHONE_2_0);

#if !__LP64__ && !TARGET_OS_IPHONE
// this call is deprecated and replaced by AudioUnitRemovePropertyListenerWithUserData
// this allows apps to use the same function pointer more than once
// you provide the same function ptr and user data as provided when you add a property listener
extern OSStatus
AudioUnitRemovePropertyListener(	AudioUnit						ci,
									AudioUnitPropertyID				inID,
									AudioUnitPropertyListenerProc	inProc)			
											__OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_0,__MAC_10_5, __IPHONE_NA, __IPHONE_NA);
#endif

extern OSStatus
AudioUnitRemovePropertyListenerWithUserData(
									AudioUnit						ci,
									AudioUnitPropertyID				inID,
									AudioUnitPropertyListenerProc	inProc,
									void *							inProcUserData)	__OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_2_0);

extern OSStatus
AudioUnitAddRenderNotify(			AudioUnit				ci,
									AURenderCallback		inProc,
									void *					inProcUserData)			__OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_2_0);


extern OSStatus
AudioUnitRemoveRenderNotify(		AudioUnit				ci,
									AURenderCallback		inProc,
									void *					inProcUserData)			__OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_2_0);

extern OSStatus
AudioUnitGetParameter(				AudioUnit					ci,
									AudioUnitParameterID		inID,
									AudioUnitScope				inScope,
									AudioUnitElement			inElement,
									AudioUnitParameterValue *	outValue)			__OSX_AVAILABLE_STARTING(__MAC_10_0,__IPHONE_2_0);



extern OSStatus
AudioUnitSetParameter(				AudioUnit					ci,
									AudioUnitParameterID		inID,
									AudioUnitScope				inScope,
									AudioUnitElement			inElement,
									AudioUnitParameterValue		inValue,
									UInt32						inBufferOffsetInFrames) __OSX_AVAILABLE_STARTING(__MAC_10_0,__IPHONE_2_0);


extern OSStatus
AudioUnitScheduleParameters(		AudioUnit						ci,
									const AudioUnitParameterEvent *	inParameterEvent,
									UInt32							inNumParamEvents) __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_2_0);



extern OSStatus
AudioUnitRender(					AudioUnit						ci,
									AudioUnitRenderActionFlags *	ioActionFlags,
									const AudioTimeStamp *			inTimeStamp,
									UInt32							inOutputBusNumber,
									UInt32							inNumberFrames,
									AudioBufferList *				ioData)			__OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_2_0);


extern OSStatus
AudioUnitReset(						AudioUnit			ci,
									AudioUnitScope		inScope,
									AudioUnitElement	inElement)					__OSX_AVAILABLE_STARTING(__MAC_10_0,__IPHONE_2_0);


//-----------------------------------------------------------------------------
//	Selectors for component calls
//-----------------------------------------------------------------------------
enum
{
	kAudioUnitRange							= 0x0000,	// range of selectors for audio units
	kAudioUnitInitializeSelect				= 0x0001,
	kAudioUnitUninitializeSelect			= 0x0002,
	kAudioUnitGetPropertyInfoSelect			= 0x0003,
	kAudioUnitGetPropertySelect				= 0x0004,
	kAudioUnitSetPropertySelect				= 0x0005,
	kAudioUnitAddPropertyListenerSelect		= 0x000A,
	kAudioUnitRemovePropertyListenerSelect	= 0x000B,
	kAudioUnitRemovePropertyListenerWithUserDataSelect = 0x0012,
	kAudioUnitAddRenderNotifySelect			= 0x000F,
	kAudioUnitRemoveRenderNotifySelect		= 0x0010,
	kAudioUnitGetParameterSelect			= 0x0006,
	kAudioUnitSetParameterSelect			= 0x0007,
	kAudioUnitScheduleParametersSelect		= 0x0011,
	kAudioUnitRenderSelect					= 0x000E,
	kAudioUnitResetSelect					= 0x0009
};


#if !TARGET_OS_IPHONE
//-----------------------------------------------------------------------------
//	Fast-dispatch function pointer types
//	
//	For functions where performance may be an issue, a host application may use
//	the kAudioUnitProperty_FastDispatch property to get a function
//	pointer pointing directly to the audio unit's implementation. This
//	avoids the cost of dispatching through the Component Manager. (Audio units
//	are not required to implement this, but should.)
//-----------------------------------------------------------------------------
typedef OSStatus
(*AudioUnitGetParameterProc)(	void *						inComponentStorage,
								AudioUnitParameterID		inID,
								AudioUnitScope				inScope,
								AudioUnitElement			inElement,
								AudioUnitParameterValue *	outValue);
								
typedef OSStatus
(*AudioUnitSetParameterProc)(	void *						inComponentStorage,
								AudioUnitParameterID		inID,
								AudioUnitScope				inScope,
								AudioUnitElement			inElement,
								AudioUnitParameterValue		inValue,
								UInt32						inBufferOffsetInFrames);
								
typedef OSStatus
(*AudioUnitRenderProc)(			void *							inComponentStorage,
								AudioUnitRenderActionFlags *	ioActionFlags,
								const AudioTimeStamp *			inTimeStamp,
								UInt32							inOutputBusNumber,
								UInt32							inNumberFrames,
								AudioBufferList *				ioData);
#endif

#if !__LP64__
	#if PRAGMA_STRUCT_ALIGN
		#pragma options align=reset
	#elif PRAGMA_STRUCT_PACKPUSH
		#pragma pack(pop)
	#elif PRAGMA_STRUCT_PACK
		#pragma pack()
	#endif
#endif

#ifdef PRAGMA_IMPORT_OFF
#pragma import off
#elif PRAGMA_IMPORT
#pragma import reset
#endif

#ifdef __cplusplus
}
#endif

#endif /* __AUCOMPONENT__ */

