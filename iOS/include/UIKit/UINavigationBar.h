//
//  UINavigationBar.h
//  UIKit
//
//  Copyright 2005-2008 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <UIKit/UIView.h>
#import <UIKit/UIInterface.h>
#import <UIKit/UIFont.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UIButton.h>

@class UINavigationItem, UIBarButtonItem, UIImage, UIColor;
@protocol UINavigationBarDelegate;

UIKIT_EXTERN_CLASS @interface UINavigationBar : UIView <NSCoding> {
  @private
    NSMutableArray *_itemStack;
    CGFloat         _rightMargin;
    unsigned        _state;
    id              _delegate;
    UIView         *_titleView;
    UIView         *_leftView;
    UIView         *_rightView;
    UIView         *_prompt;
    UIView         *_accessoryView;
    UIColor        *_tintColor;
    struct {
        unsigned int animate:1;
        unsigned int animationDisabledCount:10;
        unsigned int barStyle:3;
        unsigned int disableLayout:1;
        unsigned int backPressed:1;
        unsigned int animatePromptChange:1;
        unsigned int pendingHideBackButton:1;
        unsigned int removeAccessoryOnPop:1;
        unsigned int titleAutosizesToFit:1;
        unsigned int usingNewAPI:1;
        unsigned int minibar:1;
        unsigned int isLocked:1;
        unsigned int shouldUpdatePromptAfterTransition:1;
    } _navbarFlags;
}

@property(nonatomic,assign) UIBarStyle barStyle;
@property(nonatomic,assign) id delegate;
@property(nonatomic,retain) UIColor *tintColor;

@property(nonatomic,copy) NSArray *items;
@property(nonatomic,readonly,retain) UINavigationItem *topItem;
@property(nonatomic,readonly,retain) UINavigationItem *backItem;

// Pushing a navigation item displays the item's title in the center of the navigation bar.
// The previous top navigation item (if it exists) is displayed as a "back" button on the left.
- (void)pushNavigationItem:(UINavigationItem *)item animated:(BOOL)animated;
- (UINavigationItem *)popNavigationItemAnimated:(BOOL)animated; // Returns the item that was popped.

@end

@protocol UINavigationBarDelegate <NSObject>

@optional

- (BOOL)navigationBar:(UINavigationBar *)navigationBar shouldPushItem:(UINavigationItem *)item; // called to push. return NO not to.
- (void)navigationBar:(UINavigationBar *)navigationBar didPushItem:(UINavigationItem *)item;    // called at end of animation of push or immediately if not animated
- (BOOL)navigationBar:(UINavigationBar *)navigationBar shouldPopItem:(UINavigationItem *)item;  // same as push methods
- (void)navigationBar:(UINavigationBar *)navigationBar didPopItem:(UINavigationItem *)item;

@end

UIKIT_EXTERN_CLASS @interface UINavigationItem : NSObject <NSCoding> {
 @private
    NSString        *_title;
    NSString        *_backButtonTitle;
    UIBarButtonItem *_backBarButtonItem;
    NSString        *_prompt;
    NSInteger        _tag;
    id               _context;
    UINavigationBar *_navigationBar;
    UIView          *_defaultTitleView;
    UIView          *_titleView;
    UIView          *_backButtonView;
    UIBarButtonItem *_leftBarButtonItem;
    UIBarButtonItem *_rightBarButtonItem;
    UIView          *_customLeftView;
    UIView          *_customRightView;
    BOOL             _hidesBackButton;
}

- (id)initWithTitle:(NSString *)title;

@property(nonatomic,copy)   NSString        *title;             // Title when topmost on the stack. default is nil
@property(nonatomic,retain) UIBarButtonItem *backBarButtonItem; // Bar button item to use for the back button in the child navigation item.
@property(nonatomic,retain) UIView          *titleView;         // Custom view to use in lieu of a title. May be sized horizontally. Only used when item is topmost on the stack.

@property(nonatomic,copy)   NSString *prompt;     // Explanatory text to display above the navigation bar buttons.

@property(nonatomic,assign) BOOL hidesBackButton; // If YES, this navigation item will hide the back button when it's on top of the stack.
- (void)setHidesBackButton:(BOOL)hidesBackButton animated:(BOOL)animated;

// Some navigation items want to display a custom left or right item when they're on top of the stack.
// A custom left item replaces the regular back button
@property(nonatomic,retain) UIBarButtonItem *leftBarButtonItem;
@property(nonatomic,retain) UIBarButtonItem *rightBarButtonItem;
- (void)setLeftBarButtonItem:(UIBarButtonItem *)item animated:(BOOL)animated;
- (void)setRightBarButtonItem:(UIBarButtonItem *)item animated:(BOOL)animated;

@end
