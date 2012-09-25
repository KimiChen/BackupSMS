//
//  UIToolbar.h
//  UIKit
//
//  Copyright 2006-2008 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UIView.h>
#import <UIKit/UIInterface.h>

@class UIBarButtonItem, UIColor;

UIKIT_EXTERN_CLASS @interface UIToolbar : UIView {
  @private
    UIView*                _customizeView;
    id                     _delegate;
    NSArray               *_items;
    UIBarButtonItem       *_selectedItem;
    NSArray               *_customizationItems;
    UIColor               *_tintColor;
    struct {
        unsigned int barStyle:2;
        unsigned int mode:2;
        unsigned int roundsCorners:1;
        unsigned int alertShown:1;
        unsigned int wasEnabled:1;
        unsigned int customized:1;
        unsigned int downButtonSentAction:1;
    } _toolbarFlags;
    CFMutableDictionaryRef _groups;
    NSArray               *_buttonItems;
    NSInteger              _currentButtonGroup;
    CFMutableArrayRef      _hiddenItems;
    NSInteger              _selectedTag;
    NSInteger              _trackingTag;    
}

@property(nonatomic)        UIBarStyle barStyle;    // default is UIBarStyleDefault (blue)
@property(nonatomic,copy)   NSArray   *items;       // get/set visible UIBarButtonItem. default is nil. changes not animated. shown in order
@property(nonatomic,retain) UIColor   *tintColor;   // default is nil

- (void)setItems:(NSArray *)items animated:(BOOL)animated;   // will fade in or out or reorder and adjust spacing

@end
