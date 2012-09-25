//
//  UITabBarController.h
//  UIKit
//
//  Copyright 2007-2008 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIViewController.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UITabBar.h>

/*!
 UITabBarController manages a button bar and transition view, for an application with multiple top-level modes.
 
 To use in your application, add its view to the view hierarchy, then add top-level view controllers in order.
 Most clients will not need to subclass UITabBarController.

 If more than five view controllers are added to a toolbar controller, only the first four will display.
 The rest will be accessible under an automatically generated More item.
 
 UITabBarController is rotatable if all of its view controllers are rotatable.
 */

@class UIView, UIImage, UINavigationController, UITabBarItem;
@protocol UITabBarControllerDelegate;

UIKIT_EXTERN_CLASS @interface UITabBarController : UIViewController <UITabBarDelegate, NSCoding> {
  @package
    UITabBar               *_tabBar;
    
    UIView                 *_containerView;
    UIView                 *_viewControllerTransitionView;
    
    NSMutableArray         *_viewControllers;
    id                      _tabBarItemsToViewControllers;
    UIViewController       *_selectedViewController; // Weak

    UINavigationController *_moreNavigationController;
    NSArray                *_customizableViewControllers;
    
    id<UITabBarControllerDelegate> _delegate;
    
    UIViewController       *_selectedViewControllerDuringWillAppear;
    
    struct {
	unsigned int isShown:1;
	unsigned int isShowingMoreItem:1;
	unsigned int needsToRebuildItems:1;
	unsigned int isBarHidden:1;
    } _tabBarControllerFlags;
}

@property(nonatomic,copy) NSArray *viewControllers;
// If the number of view controllers is greater than the number displayable by a tab bar, a "More" navigation controller will automatically be shown.
// The "More" navigation controller will not be returned by -viewControllers, but it may be returned by -selectedViewController.
- (void)setViewControllers:(NSArray *)viewControllers animated:(BOOL)animated;

@property(nonatomic,assign) UIViewController *selectedViewController; // This may return the "More" navigation controller if it exists.
@property(nonatomic) NSUInteger selectedIndex;

@property(nonatomic,readonly) UINavigationController *moreNavigationController; // Returns the "More" navigation controller if it exists.
@property(nonatomic,copy) NSArray *customizableViewControllers; // If non-nil, then the "More" view will include an "Edit" button that displays customization UI for the specified controllers. By default, all view controllers are customizable.

@property(nonatomic,assign) id<UITabBarControllerDelegate> delegate;

@end

@protocol UITabBarControllerDelegate <NSObject>
@optional
- (void)tabBarController:(UITabBarController *)tabBarController didSelectViewController:(UIViewController *)viewController;
- (void)tabBarController:(UITabBarController *)tabBarController didEndCustomizingViewControllers:(NSArray *)viewControllers changed:(BOOL)changed;
@end

@interface UIViewController (UITabBarControllerItem)

@property(nonatomic,retain) UITabBarItem *tabBarItem; // Automatically created lazily with the view controller's title if it's not set explicitly.

@property(nonatomic,readonly,retain) UITabBarController *tabBarController; // If the view controller has a toolbar controller as its ancestor, return it. Returns nil otheriwse.

@end
