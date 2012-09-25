//
//  UIBarItem.h
//  UIKit
//
//  Copyright 2008 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIGeometry.h>
#import <UIKit/UIKitDefines.h>

@class UIImage;

UIKIT_EXTERN_CLASS @interface UIBarItem : NSObject {
}

@property(nonatomic,getter=isEnabled) BOOL         enabled;      // default is YES
@property(nonatomic,copy)             NSString    *title;        // default is nil
@property(nonatomic,retain)           UIImage     *image;        // default is nil
@property(nonatomic)                  UIEdgeInsets imageInsets;  // default is UIEdgeInsetsZero
@property(nonatomic)                  NSInteger    tag;          // default is 0
@end
