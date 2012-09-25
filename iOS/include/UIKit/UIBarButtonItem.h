//
//  UIBarButtonItem.h
//  UIKit
//
//  Copyright 2008 Apple Inc. All rights reserved.
//

#import <CoreGraphics/CoreGraphics.h>
#import <Foundation/Foundation.h>
#import <UIKit/UIBarItem.h>
#import <UIKit/UIKitDefines.h>

typedef enum {
    UIBarButtonItemStylePlain,    // shows glow when pressed
    UIBarButtonItemStyleBordered,
    UIBarButtonItemStyleDone,
} UIBarButtonItemStyle;

typedef enum {
    UIBarButtonSystemItemDone,
    UIBarButtonSystemItemCancel,
    UIBarButtonSystemItemEdit,  
    UIBarButtonSystemItemSave,  
    UIBarButtonSystemItemAdd,
    UIBarButtonSystemItemFlexibleSpace,
    UIBarButtonSystemItemFixedSpace,
    UIBarButtonSystemItemCompose,
    UIBarButtonSystemItemReply,
    UIBarButtonSystemItemAction,
    UIBarButtonSystemItemOrganize,
    UIBarButtonSystemItemBookmarks,
    UIBarButtonSystemItemSearch,
    UIBarButtonSystemItemRefresh,
    UIBarButtonSystemItemStop,
    UIBarButtonSystemItemCamera,
    UIBarButtonSystemItemTrash,
    UIBarButtonSystemItemPlay,
    UIBarButtonSystemItemPause,
    UIBarButtonSystemItemRewind,
    UIBarButtonSystemItemFastForward,
} UIBarButtonSystemItem;

@class UIImage, UIView;

UIKIT_EXTERN_CLASS @interface UIBarButtonItem : UIBarItem {
  @private
    NSString     *_title;
    NSSet        *_possibleTitles;
    SEL           _action;
    id            _target;
    UIImage      *_image;
    UIEdgeInsets  _imageInsets;
    CGFloat       _width;   
    UIView       *_view;
    NSInteger     _tag;
    struct {
        unsigned int enabled:1;
        unsigned int style:3;
        unsigned int isSystemItem:1;
        unsigned int systemItem:7;
        unsigned int viewIsCustom:1;
    } _barButtonItemFlags;
}

- (id)initWithImage:(UIImage *)image style:(UIBarButtonItemStyle)style target:(id)target action:(SEL)action;
- (id)initWithTitle:(NSString *)title style:(UIBarButtonItemStyle)style target:(id)target action:(SEL)action;
- (id)initWithBarButtonSystemItem:(UIBarButtonSystemItem)systemItem target:(id)target action:(SEL)action;
- (id)initWithCustomView:(UIView *)customView;

@property(nonatomic)         UIBarButtonItemStyle style;            // default is UIBarButtonItemStylePlain
@property(nonatomic)         CGFloat              width;            // default is 0.0
@property(nonatomic,copy)    NSSet               *possibleTitles;   // default is nil
@property(nonatomic,retain)  UIView              *customView;       // default is nil
@property(nonatomic)         SEL                  action;           // default is NULL
@property(nonatomic,assign)  id                   target;           // default is nil

@end
