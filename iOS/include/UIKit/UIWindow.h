//
//  UIWindow.h
//  UIKit
//
//  Copyright 2005-2008 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <UIKit/UIView.h>
#import <UIKit/UIApplication.h>
#import <UIKit/UIKitDefines.h>

typedef CGFloat UIWindowLevel;

@class UIEvent;

UIKIT_EXTERN_CLASS @interface UIWindow : UIView {
  @package
    id                       _delegate;
    CFTypeRef                _window;
    CGFloat                  _windowLevel;
    id                       _layerContext;
    UIView                  *_lastMouseDownView;
    UIView                  *_lastMouseEnteredView;
    UIResponder             *_firstResponder;
    id                       _fingerInfo;
    UIInterfaceOrientation   _viewOrientation;
    UIView                  *_exclusiveTouchView;
    struct {
        unsigned int delegateWillRotate:1;
        unsigned int delegateDidRotate:1;
        unsigned int delegateWillAnimateFirstHalf:1;
        unsigned int delegateDidAnimationFirstHalf:1;
        unsigned int delegateWillAnimateSecondHalf:1;
        unsigned int autorotatesToPortrait:1;
        unsigned int autorotatesToPortraitUpsideDown:1;
        unsigned int autorotatesToLandscapeLeft:1;
        unsigned int autorotatesToLandscapeRight:1;
        unsigned int dontBecomeKeyOnOrderFront:1;
        unsigned int output:1;
        unsigned int inGesture:1;
        unsigned int trackingStatusBar:1;
        unsigned int resetLevelOnSuspend:1;
        unsigned int cancelScroller:1;
        unsigned int bitsPerComponent:4;
        unsigned int autorotates:1;
        unsigned int isRotating:1;
        unsigned int orderKeyboardInAfterRotating:1;
    } _windowFlags;
}

@property(nonatomic) UIWindowLevel windowLevel;                   // default = 0.0
@property(nonatomic,readonly,getter=isKeyWindow) BOOL keyWindow;
- (void)becomeKeyWindow;                               // override point for subclass. Do not call directly
- (void)resignKeyWindow;                               // override point for subclass. Do not call directly

- (void)makeKeyWindow;
- (void)makeKeyAndVisible;                             // convenience. most apps call this to show the main window and also make it key. otherwise use view hidden property

- (void)sendEvent:(UIEvent *)event;                    // called by UIApplication to dispatch events to views inside the window

- (CGPoint)convertPoint:(CGPoint)point toWindow:(UIWindow *)window;    // can be used to convert to another window
- (CGPoint)convertPoint:(CGPoint)point fromWindow:(UIWindow *)window;  // pass in nil to mean screen
- (CGRect)convertRect:(CGRect)rect toWindow:(UIWindow *)window;
- (CGRect)convertRect:(CGRect)rect fromWindow:(UIWindow *)window;

@end

UIKIT_EXTERN const UIWindowLevel UIWindowLevelNormal;
UIKIT_EXTERN const UIWindowLevel UIWindowLevelAlert;
UIKIT_EXTERN const UIWindowLevel UIWindowLevelStatusBar;

UIKIT_EXTERN NSString *const UIWindowDidBecomeVisibleNotification; // nil
UIKIT_EXTERN NSString *const UIWindowDidBecomeHiddenNotification;  // nil
UIKIT_EXTERN NSString *const UIWindowDidBecomeKeyNotification;     // nil
UIKIT_EXTERN NSString *const UIWindowDidResignKeyNotification;     // nil

// Each notification includes a nil object and a userInfo dictionary containing
// keyboard center beginning and ending values and the keyboard bounds, all in main
// screen coordinates.
UIKIT_EXTERN NSString *const UIKeyboardWillShowNotification;
UIKIT_EXTERN NSString *const UIKeyboardDidShowNotification; 
UIKIT_EXTERN NSString *const UIKeyboardWillHideNotification; 
UIKIT_EXTERN NSString *const UIKeyboardDidHideNotification;
UIKIT_EXTERN NSString *const UIKeyboardCenterBeginUserInfoKey;  // NSValue of CGPoint
UIKIT_EXTERN NSString *const UIKeyboardCenterEndUserInfoKey;    // NSValue of CGPoint
UIKIT_EXTERN NSString *const UIKeyboardBoundsUserInfoKey;       // NSValue of CGRect
