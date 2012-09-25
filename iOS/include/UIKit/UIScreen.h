//
//  UIScreen.h
//  UIKit
//
//  Copyright 2007-2008 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <UIKit/UIKitDefines.h>

UIKIT_EXTERN_CLASS @interface UIScreen : NSObject {
  @private
    CGRect _bounds;
}

+ (UIScreen *)mainScreen;

@property(nonatomic,readonly) CGRect bounds;              // Bounds of entire screen in points
@property(nonatomic,readonly) CGRect applicationFrame;    // Frame of application screen area in points (i.e. entire screen minus status bar if visible)

@end
