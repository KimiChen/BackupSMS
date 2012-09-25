//
//  UIEvent.h
//  UIKit
//
//  Copyright 2005-2008 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <UIKit/UIKitDefines.h>

@class UIWindow, UIView;

UIKIT_EXTERN_CLASS @interface UIEvent : NSObject
{
  @private
    CFTypeRef               _event;
    NSTimeInterval          _timestamp;
    NSMutableSet           *_touches;
    CFMutableDictionaryRef  _keyedTouches;
}

@property(nonatomic,readonly) NSTimeInterval  timestamp;

- (NSSet *)allTouches;
- (NSSet *)touchesForWindow:(UIWindow *)window;
- (NSSet *)touchesForView:(UIView *)view;

@end
