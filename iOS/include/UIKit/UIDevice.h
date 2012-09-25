//
//  UIDevice.h
//  UIKit
//
//  Copyright 2007-2008 Apple Inc. All rights reserved.
//

#import <Foundation/NSObject.h>
#import <UIKit/UIKitDefines.h>

UIKIT_EXTERN NSString *const UIDeviceOrientationDidChangeNotification;

typedef enum {
    UIDeviceOrientationUnknown,
    UIDeviceOrientationPortrait,            // Device oriented vertically, home button on the bottom
    UIDeviceOrientationPortraitUpsideDown,  // Device oriented vertically, home button on the top
    UIDeviceOrientationLandscapeLeft,       // Device oriented horizontally, home button on the right
    UIDeviceOrientationLandscapeRight,      // Device oriented horizontally, home button on the left
    UIDeviceOrientationFaceUp,              // Device oriented flat, face up
    UIDeviceOrientationFaceDown             // Device oriented flat, face down
} UIDeviceOrientation;

#define UIDeviceOrientationIsPortrait(orientation)  ((orientation) == UIDeviceOrientationPortrait || (orientation) == UIDeviceOrientationPortraitUpsideDown)
#define UIDeviceOrientationIsLandscape(orientation) ((orientation) == UIDeviceOrientationLandscapeLeft || (orientation) == UIDeviceOrientationLandscapeRight)

UIKIT_EXTERN_CLASS @interface UIDevice : NSObject {
 @private
    NSInteger _numDeviceOrientationObservers;
    struct {
        unsigned int orientation:3;
        unsigned int batteryState:2;
    } _deviceFlags;
}

+ (UIDevice *)currentDevice;

@property(nonatomic,readonly,retain) NSString    *name;              // e.g. "My iPhone"
@property(nonatomic,readonly,retain) NSString    *model;             // e.g. @"iPhone", @"iPod Touch"
@property(nonatomic,readonly,retain) NSString    *localizedModel;    // localized version of model
@property(nonatomic,readonly,retain) NSString    *systemName;        // e.g. @"iPhone OS"
@property(nonatomic,readonly,retain) NSString    *systemVersion;     // e.g. @"2.0"
@property(nonatomic,readonly) UIDeviceOrientation orientation;       // return current device orientation
@property(nonatomic,readonly,retain) NSString    *uniqueIdentifier;  // a string unique to each device based on various hardware info.

@property(nonatomic,readonly,getter=isGeneratingDeviceOrientationNotifications) BOOL generatesDeviceOrientationNotifications;
- (void)beginGeneratingDeviceOrientationNotifications;      // nestable
- (void)endGeneratingDeviceOrientationNotifications;

@end
