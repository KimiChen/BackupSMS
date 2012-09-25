//
//  UITextField.h
//  UIKit
//
//  Copyright 2005-2008 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UIControl.h>
#import <UIKit/UIFont.h>
#import <UIKit/UIStringDrawing.h>
#import <UIKit/UITextInputTraits.h>

@class UIImage, UIImageView, UILabel, UIColor;
@class UITextFieldAtomBackgroundView;
@class UITextFieldBackgroundView;
@class UITextFieldBorderView;
@class UITextFieldLabel;
@class UITextInputTraits;
@protocol UITextFieldDelegate;

typedef enum {
    UITextBorderStyleNone,
    UITextBorderStyleLine,
    UITextBorderStyleBezel,
    UITextBorderStyleRoundedRect
} UITextBorderStyle;

typedef enum {
    UITextFieldViewModeNever,
    UITextFieldViewModeWhileEditing,
    UITextFieldViewModeUnlessEditing,
    UITextFieldViewModeAlways
} UITextFieldViewMode;

UIKIT_EXTERN_CLASS @interface UITextField : UIControl <UITextInputTraits, NSCoding> {
  @private
    NSString           *_text;
    UIColor            *_textColor;
    UITextBorderStyle   _borderStyle;
    CGFloat             _minimumFontSize;
    id                  _delegate;
    UIImage            *_background;
    UIImage            *_disabledBackground;
    UITextFieldViewMode _clearButtonMode;
    UIView             *_leftView;
    UITextFieldViewMode _leftViewMode;
    UIView             *_rightView;
    UITextFieldViewMode _rightViewMode;

    UITextInputTraits  *_traits;
    CGFloat             _fullFontSize; // font size to use when no shrinkage is needed.
    CGFloat             _paddingLeft;
    CGFloat             _paddingTop;
    CGFloat             _paddingRight;
    CGFloat             _paddingBottom;
    NSString           *_textFont; // This ivar will go away. This is deprecated and people should use _font
    UIColor            *_caretColor;
    NSRange             _selectionRange;
    int                 _scrollXOffset;
    int                 _scrollYOffset;
    float               _progress;
    NSString           *_style;
    CFTimeInterval      _mouseDownTime;
    
    UIView             *_clearButton;
    CGSize              _clearButtonOffset;
    
    CGSize              _leftViewOffset;
    CGSize              _rightViewOffset;

    UITextFieldBorderView     *_backgroundView;
    UITextFieldBorderView     *_disabledBackgroundView;
    UITextFieldBackgroundView *_systemBackgroundView;
    
    UITextFieldLabel *_textLabel;
    UITextFieldLabel *_placeholderLabel;
    UIImageView      *_iconView;
    UILabel          *_label;
    CGFloat          _labelOffset;
    
    UITextFieldAtomBackgroundView *_atomBackgroundView;

    struct {
        unsigned int secureTextChanged:1;
        unsigned int guard:1;
        unsigned int delegateRespondsToHandleKeyDown:1;
        unsigned int verticallyCenterText:1;
        unsigned int isAnimating:4;
        unsigned int inactiveHasDimAppearance:1;
        unsigned int becomesFirstResponderOnClearButtonTap:1;
	unsigned int clearsOnBeginEditing:1;
	unsigned int adjustsFontSizeToFitWidth:1;
	unsigned int fieldEditorAttached:1;
	unsigned int inBecomeFirstResponder:1;
    } _textFieldFlags;
}

// End ivars
// =============================================================================
// Begin SDK properties

@property(nonatomic,copy)   NSString               *text;                 // default is nil
@property(nonatomic,retain) UIColor                *textColor;            // default is nil. use opaque black
@property(nonatomic,retain) UIFont                 *font;                 // default is nil. use system font 12 pt
@property(nonatomic)        UITextAlignment         textAlignment;        // default is UITextAlignmentLeft
@property(nonatomic)        UITextBorderStyle       borderStyle;          // default is UITextBorderStyleNone. ignored if custom background image set.
@property(nonatomic,copy)   NSString               *placeholder;          // default is nil. string is drawn 70% gray
@property(nonatomic)        BOOL                    clearsOnBeginEditing; // default is NO which moves cursor to location clicked. if YES, all text cleared
@property(nonatomic)        BOOL                    adjustsFontSizeToFitWidth; // default is NO. if YES, text will shrink to minFontSize along baseline
@property(nonatomic)        CGFloat                 minimumFontSize;      // default is 0.0. actual min may be pinned to something readable. used if adjustsFontSizeToFitWidth is YES
@property(nonatomic,assign) id<UITextFieldDelegate> delegate;             // default is nil. weak reference
@property(nonatomic,retain) UIImage                *background;           // default is nil. draw in border rect. image should be stretchable
@property(nonatomic,retain) UIImage                *disabledBackground;   // default is nil. ignored if background not set. image should be stretchable

@property(nonatomic,readonly,getter=isEditing) BOOL editing;

// You can supply custom views which are displayed at the left or right
// sides of the text field. Uses for such views could be to show an icon or
// a button to operate on the text in the field in an application-defined
// manner.
// 
// A very common use is to display a clear button on the right side of the
// text field, and a standard clear button is provided. Note: if the clear
// button overlaps one of the other views, the clear button will be given
// precedence.

@property(nonatomic)        UITextFieldViewMode  clearButtonMode; // sets when the clear button shows up. default is UITextFieldViewNever

@property(nonatomic,retain) UIView              *leftView;        // e.g. magnifying glass
@property(nonatomic)        UITextFieldViewMode  leftViewMode;    // sets when the left view shows up. default is UITextFieldViewNever

@property(nonatomic,retain) UIView              *rightView;       // e.g. bookmarks button
@property(nonatomic)        UITextFieldViewMode  rightViewMode;   // sets when the right view shows up. default is UITextFieldViewNever

// drawing and positioning overrides

- (CGRect)borderRectForBounds:(CGRect)bounds;
- (CGRect)textRectForBounds:(CGRect)bounds;
- (CGRect)placeholderRectForBounds:(CGRect)bounds;
- (CGRect)editingRectForBounds:(CGRect)bounds;
- (CGRect)clearButtonRectForBounds:(CGRect)bounds;
- (CGRect)leftViewRectForBounds:(CGRect)bounds;
- (CGRect)rightViewRectForBounds:(CGRect)bounds;

- (void)drawTextInRect:(CGRect)rect;
- (void)drawPlaceholderInRect:(CGRect)rect;

@end

@interface UIView (UITextField)
- (BOOL)endEditing:(BOOL)force;    // use to make the view or any subview that is the first responder resign (optionally force)
@end

@protocol UITextFieldDelegate <NSObject>

@optional

- (BOOL)textFieldShouldBeginEditing:(UITextField *)textField;        // return NO to disallow editing.
- (void)textFieldDidBeginEditing:(UITextField *)textField;           // became first responder
- (BOOL)textFieldShouldEndEditing:(UITextField *)textField;          // return YES to allow editing to stop and to resign first responder status. NO to disallow the editing session to end
- (void)textFieldDidEndEditing:(UITextField *)textField;             // may be called if forced even if shouldEndEditing returns NO (e.g. view removed from window) or endEditing:YES called

- (BOOL)textField:(UITextField *)textField shouldChangeCharactersInRange:(NSRange)range replacementString:(NSString *)string;   // return NO to not change text

- (BOOL)textFieldShouldClear:(UITextField *)textField;               // called when clear button pressed. return NO to ignore (no notifications)
- (BOOL)textFieldShouldReturn:(UITextField *)textField;              // called when 'return' key pressed. return NO to ignore.

@end

UIKIT_EXTERN NSString *const UITextFieldTextDidBeginEditingNotification;
UIKIT_EXTERN NSString *const UITextFieldTextDidEndEditingNotification;
UIKIT_EXTERN NSString *const UITextFieldTextDidChangeNotification;

