//
//  UIActivityIndicator.h
//  UIKit
//
//  Copyright 2005-2008 Apple Inc. All rights reserved.
//

#import <UIKit/UIView.h>
#import <UIKit/UIKitDefines.h>

typedef enum {
    UIActivityIndicatorViewStyleWhiteLarge,
    UIActivityIndicatorViewStyleWhite,
    UIActivityIndicatorViewStyleGray,
} UIActivityIndicatorViewStyle;

UIKIT_EXTERN_CLASS @interface UIActivityIndicatorView : UIView <NSCoding>
{ 
  @package
    CFTimeInterval               _duration;
    BOOL                         _animating;
    UIActivityIndicatorViewStyle _activityIndicatorViewStyle;
    BOOL                         _hidesWhenStopped;
}

- (id)initWithActivityIndicatorStyle:(UIActivityIndicatorViewStyle)style;     // sizes the view according to the style

@property(nonatomic) UIActivityIndicatorViewStyle activityIndicatorViewStyle; // default is UIActivityIndicatorViewStyleWhite
@property(nonatomic) BOOL                         hidesWhenStopped;           // default is YES. calls -setHidden when animating gets set to NO

- (void)startAnimating;
- (void)stopAnimating;
- (BOOL)isAnimating;

@end
