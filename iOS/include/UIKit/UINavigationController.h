//
//  UINavigationController.h
//  UIKit
//
//  Copyright 2007-2008 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <UIKit/UIViewController.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UIInterface.h>

/*!
 UINavigationController manages a stack of view controllers and a navigation bar.
 It performs horizontal view transitions for pushed and popped views while keeping the navigation bar in sync.
 
 To use in your application, add its view to the view hierarchy, then push and pop controllers.
 Most clients will not need to subclass UINavigationController.
 
 If a navigation controller is nested in a toolbar controller, it uses the title and toolbar attributes of the bottom view controller on the stack.
 
 UINavigationController is rotatable if its top view controller is rotatable.
 Navigation between controllers with non-uniform rotatability is currently not supported.
*/

extern const CGFloat UINavigationControllerHideShowBarDuration;

@class UIView, UINavigationBar, UINavigationItem;
@protocol UINavigationControllerDelegate;

UIKIT_EXTERN_CLASS @interface UINavigationController : UIViewController {
  @package
    UIView           *_containerView;
    UINavigationBar  *_navigationBar;
    Class             _navigationBarClass;
    CGFloat           _currentScrollContentInsetDelta;
    CGFloat           _previousScrollContentInsetDelta;
    CGFloat           _previousScrollContentOffsetDelta;
    UIView           *_navigationTransitionView;
    NSMutableArray   *_viewControllers;
    UIViewController *_disappearingViewController;
    UIViewController *_topViewControllerDuringWillAppear;
    UIViewController *_bottomBarRedisplayViewController;
    id <UINavigationControllerDelegate> _delegate;
    struct {
	unsigned int isAnimating:1;
	unsigned int isShown:1;
	unsigned int isAlreadyPoppingNavigationItem:1;
	unsigned int isPushing:1;
	unsigned int needsDeferredTransition:1;
	unsigned int isNavigationBarHidden:1;
    } _navigationControllerFlags;
}

- (id)initWithRootViewController:(UIViewController *)rootViewController; // Convenience method pushes the root view controller without animation.

- (void)pushViewController:(UIViewController *)viewController animated:(BOOL)animated; // Uses a horizontal slide transition. Has no effect if the view controller is already in the stack.

- (UIViewController *)popViewControllerAnimated:(BOOL)animated; // Returns the popped controller.
- (NSArray *)popToViewController:(UIViewController *)viewController animated:(BOOL)animated; // Pops view controllers until the one specified is on top. Returns the popped controllers.
- (NSArray *)popToRootViewControllerAnimated:(BOOL)animated; // Pops until there's only a single view controller left on the stack. Returns the popped controllers.

@property(nonatomic,readonly,retain) UIViewController *topViewController; // The top view controller on the stack.
@property(nonatomic,readonly,retain) UIViewController *visibleViewController; // Return modal view controller if it exists. Otherwise the top view controller.
@property(nonatomic,copy) NSArray *viewControllers; // The current view controller stack.

@property(nonatomic,getter=isNavigationBarHidden) BOOL navigationBarHidden;
- (void)setNavigationBarHidden:(BOOL)hidden animated:(BOOL)animated; // Hide or show the navigation bar. If animated, it will transition vertically using UINavigationControllerHideShowBarDuration.

@property(nonatomic,readonly) UINavigationBar *navigationBar; // The navigation bar managed by the controller. Pushing, popping or setting navigation items on a managed navigation bar is not supported.

@property(nonatomic, assign) id<UINavigationControllerDelegate> delegate;

@end

@protocol UINavigationControllerDelegate <NSObject>

@optional
- (void)navigationController:(UINavigationController *)navigationController willShowViewController:(UIViewController *)viewController animated:(BOOL)animated;
- (void)navigationController:(UINavigationController *)navigationController didShowViewController:(UIViewController *)viewController animated:(BOOL)animated;

@end

@interface UIViewController (UINavigationControllerItem)

@property(nonatomic,readonly,retain) UINavigationItem *navigationItem; // Created on-demand so that a view controller may customize its navigation appearance.
@property(nonatomic) BOOL hidesBottomBarWhenPushed; // If YES, then when this view controller is pushed into a controller hierarchy with a bottom bar (like a tab bar), the bottom bar will slide out. Default is NO.
@property(nonatomic,readonly,retain) UINavigationController *navigationController; // If this view controller has been pushed onto a navigation controller, return it.

@end
