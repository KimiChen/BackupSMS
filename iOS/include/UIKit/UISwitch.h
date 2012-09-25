//
//  UISwitch.h
//  UIKit
//
//  Copyright 2008 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <UIKit/UIControl.h>
#import <UIKit/UIKitDefines.h>

UIKIT_EXTERN_CLASS @interface UISwitch : UIControl <NSCoding> {
  @private
    id _control;
}

- (id)initWithFrame:(CGRect)frame;              // This class enforces a size appropriate for the control. The frame size is ignored.

@property(nonatomic,getter=isOn) BOOL on;
- (void)setOn:(BOOL)on animated:(BOOL)animated; // does not send action

@end
