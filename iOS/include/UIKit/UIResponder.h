//
//  UIResponder.h
//  UIKit
//
//  Copyright 2005-2008 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKitDefines.h>

@class UIEvent;

UIKIT_EXTERN_CLASS @interface UIResponder : NSObject {    
}

- (UIResponder*)nextResponder;

- (BOOL)canBecomeFirstResponder;
- (BOOL)becomeFirstResponder;

- (BOOL)canResignFirstResponder;
- (BOOL)resignFirstResponder;

- (BOOL)isFirstResponder;

- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event;
- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event;
- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event;
- (void)touchesCancelled:(NSSet *)touches withEvent:(UIEvent *)event;

@end