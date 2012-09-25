//
//  UITabBar.h
//  UIKit
//
//  Copyright 2008 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UIView.h>

@class UITabBarItem;
@protocol UITabBarDelegate;

UIKIT_EXTERN_CLASS @interface UITabBar : UIView {
  @private
    UIView*                _customizeView;
    id<UITabBarDelegate>   _delegate;
    NSArray               *_items;
    UITabBarItem          *_selectedItem;
    NSArray               *_customizationItems;
    struct {
        unsigned int roundsCorners:1;
        unsigned int alertShown:1;
        unsigned int wasEnabled:1;
        unsigned int customized:1;
        unsigned int downButtonSentAction:1;
    } _tabBarFlags;
    NSArray               *_buttonItems;
    CFMutableArrayRef      _hiddenItems;
}

@property(nonatomic,assign) id<UITabBarDelegate> delegate;     // weak reference. default is nil
@property(nonatomic,copy)   NSArray             *items;        // get/set visible UITabBarItems. default is nil. changes not animated. shown in order
@property(nonatomic,assign) UITabBarItem        *selectedItem; // will show feedback based on mode. default is nil

- (void)setItems:(NSArray *)items animated:(BOOL)animated;   // will fade in or out or reorder and adjust spacing

// Reorder items. This will display a sheet with all the items listed, allow the user to change/reorder items and shows a 'Done' button at the top

- (void)beginCustomizingItems:(NSArray *)items;   // list all items that can be reordered. always animates a sheet up. visible items not listed are fixed in place
- (BOOL)endCustomizingAnimated:(BOOL)animated;    // hide customization sheet. normally you should let the user do it. check list of items to see new layout. returns YES if layout changed
- (BOOL)isCustomizing;

@end

//___________________________________________________________________________________________________

@protocol UITabBarDelegate<NSObject>
@optional

- (void)tabBar:(UITabBar *)tabBar didSelectItem:(UITabBarItem *)item; // called when a new view is selected by the user (but not programatically)

/* called when user shows or dismisses customize sheet. you can use the 'willEnd' to set up what appears underneath. 
 changed is YES if there was some change to which items are visible or which order they appear. If selectedItem is no longer visible, 
 it will be set to nil.
 */

- (void)tabBar:(UITabBar *)tabBar willBeginCustomizingItems:(NSArray *)items;                     // called before customize sheet is shown. items is current item list
- (void)tabBar:(UITabBar *)tabBar didBeginCustomizingItems:(NSArray *)items;                      // called after customize sheet is shown. items is current item list
- (void)tabBar:(UITabBar *)tabBar willEndCustomizingItems:(NSArray *)items changed:(BOOL)changed; // called before customize sheet is hidden. items is new item list
- (void)tabBar:(UITabBar *)tabBar didEndCustomizingItems:(NSArray *)items changed:(BOOL)changed;  // called after customize sheet is hidden. items is new item list

@end
