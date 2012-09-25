//
//  UIImageView.h
//  UIKit
//
//  Copyright 2006-2008 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIView.h>
#import <UIKit/UIKitDefines.h>

@class UIImage;

UIKIT_EXTERN_CLASS @interface UIImageView : UIView {
  @private
    id _storage;
}

- (id)initWithImage:(UIImage *)image;

@property(nonatomic,retain) UIImage *image;                                        // default is nil
@property(nonatomic,getter=isUserInteractionEnabled) BOOL userInteractionEnabled;  // default is NO

// these allow a set of images to be animated. the array may contain multiple copies of the same

@property(nonatomic,copy) NSArray *animationImages;            // The array must contain UIImages. Setting hides the single image. default is nil

@property(nonatomic) NSTimeInterval animationDuration;         // for one cycle of images. default is number of images * 1/30th of a second (i.e. 30 fps)
@property(nonatomic) NSInteger      animationRepeatCount;      // 0 means infinite (default is 0)

- (void)startAnimating;
- (void)stopAnimating;
- (BOOL)isAnimating;

@end
