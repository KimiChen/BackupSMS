//
//  UIButton.h
//  UIKit
//
//  Copyright 2005-2008 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIControl.h>
#import <UIKit/UIGeometry.h>
#import <UIKit/UIStringDrawing.h>
#import <UIKit/UIKitDefines.h>

@class UIImage, UIFont, UIColor, UIImageView, UILabel;

typedef enum {
    UIButtonTypeCustom = 0,           // no button type
    UIButtonTypeRoundedRect,          // rounded rect, flat white button, like in address card

    UIButtonTypeDetailDisclosure,
    UIButtonTypeInfoLight,
    UIButtonTypeInfoDark,
    UIButtonTypeContactAdd,
} UIButtonType;

UIKIT_EXTERN_CLASS @interface UIButton : UIControl <NSCoding> {
  @private
    CFMutableDictionaryRef _contentLookup;
    UIFont                *_font;
    UIEdgeInsets           _contentEdgeInsets;
    UIEdgeInsets           _titleEdgeInsets;
    UIEdgeInsets           _imageEdgeInsets;
    CGSize                 _titleShadowOffset;
    UILineBreakMode        _lineBreakMode;
    UIImageView           *_backgroundView;
    UIImageView           *_imageView;
    UILabel               *_titleView;
    struct {
        unsigned int reversesTitleShadowWhenHighlighted:1;
        unsigned int adjustsImageWhenHighlighted:1;
        unsigned int adjustsImageWhenDisabled:1;
        unsigned int autosizeToFit:1;
        unsigned int disabledDimsImage:1;
        unsigned int showsTouchWhenHighlighted:1;
        unsigned int buttonType:8;
    } _buttonFlags;
}

+ (id)buttonWithType:(UIButtonType)buttonType;

@property(nonatomic,retain) UIFont         *font;                           // default is nil. system font 18pt plain
@property(nonatomic)        UILineBreakMode lineBreakMode;                  // default is UILineBreakModeMiddleTruncation
@property(nonatomic)        UIEdgeInsets    contentEdgeInsets;              // default is UIEdgeInsetsZero
@property(nonatomic)        UIEdgeInsets    titleEdgeInsets;                // default is UIEdgeInsetsZero
@property(nonatomic)        CGSize          titleShadowOffset;              // default is CGSizeZero
@property(nonatomic)        BOOL            reversesTitleShadowWhenHighlighted; // default is NO. if YES, shadow reverses to shift between engrave and emboss appearance
@property(nonatomic)        UIEdgeInsets    imageEdgeInsets;                // default is UIEdgeInsetsZero
@property(nonatomic)        BOOL            adjustsImageWhenHighlighted;    // default is YES. if YES, image is drawn ligher when highlighted(pressed)
@property(nonatomic)        BOOL            adjustsImageWhenDisabled;       // default is YES. if YES, image is drawn darker when disabled
@property(nonatomic)        BOOL            showsTouchWhenHighlighted;      // default is NO. if YES, show a simple feedback (currently a glow) while highlighted

@property(nonatomic,readonly) UIButtonType buttonType;

// you can set the image, title color, title shadow color, and background image to use for each state. you can specify data
// for a combined state by using the flags added together. in general, you should specify a value for the normal state to be used
// by other states which don't have a custom value set

- (void)setTitle:(NSString *)title forState:(UIControlState)state;            // default is nil. title is assumed to be single line
- (void)setTitleColor:(UIColor *)color forState:(UIControlState)state;        // default if nil. use opaque white
- (void)setTitleShadowColor:(UIColor *)color forState:(UIControlState)state;  // default is nil. use 50% black
- (void)setImage:(UIImage *)image forState:(UIControlState)state;             // default is nil. should be same size if different for different states
- (void)setBackgroundImage:(UIImage *)image forState:(UIControlState)state;   // default is nil

- (NSString *)titleForState:(UIControlState)state;          // these getters only take a single state value
- (UIColor *)titleColorForState:(UIControlState)state;
- (UIColor *)titleShadowColorForState:(UIControlState)state;
- (UIImage *)imageForState:(UIControlState)state;
- (UIImage *)backgroundImageForState:(UIControlState)state;

// these are the values that will be used for the current state. you can also use these for overrides. a heuristic will be used to
// determine what image to choose based on the explict states set. For example, the 'normal' state value will be used for all states
// that don't have their own image defined.

@property(nonatomic,readonly,retain) NSString *currentTitle;             // normal/highlighted/selected/disabled. can return nil
@property(nonatomic,readonly,retain) UIColor  *currentTitleColor;        // normal/highlighted/selected/disabled. always returns non-nil. default is white(1,1)
@property(nonatomic,readonly,retain) UIColor  *currentTitleShadowColor;  // normal/highlighted/selected/disabled. default is white(0,0.5).
@property(nonatomic,readonly,retain) UIImage  *currentImage;             // normal/highlighted/selected/disabled. can return nil
@property(nonatomic,readonly,retain) UIImage  *currentBackgroundImage;   // normal/highlighted/selected/disabled. can return nil

// these return the rectangle for the background (assumes bounds), the content (image + title) and for the image and title separately. the content rect is calculated based
// on the title and image size and padding and then adjusted based on the control content alignment. there are no draw methods since the contents
// are rendered in separate subviews (UIImageView, UILabel)

- (CGRect)backgroundRectForBounds:(CGRect)bounds;
- (CGRect)contentRectForBounds:(CGRect)bounds;
- (CGRect)titleRectForContentRect:(CGRect)contentRect;
- (CGRect)imageRectForContentRect:(CGRect)contentRect;
@end
