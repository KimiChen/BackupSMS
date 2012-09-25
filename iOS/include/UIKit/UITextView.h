//
//  UITextView.h
//  UIKit
//
//  Copyright 2007-2008 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <UIKit/UIScrollView.h>
#import <UIKit/UIStringDrawing.h>
#import <UIKit/UITextInputTraits.h>
#import <UIKit/UIKitDefines.h>

@class DOMHTMLElement;
@class UIDelayedAction;
@class UIEvent, UITouch, UIFont, UIColor;
@class UITextInputTraits;
@class UIWebDocumentView;
@class WebCoreFrameBridge;
@class WebFrame;
@protocol UITextViewDelegate;

UIKIT_EXTERN_CLASS @interface UITextView : UIScrollView <UITextInputTraits> {
  @package
    WebFrame           *m_frame;
    WebCoreFrameBridge *m_bridge;
    DOMHTMLElement     *m_body;
    int                 m_marginTop;
    UIDelayedAction    *m_selectionTimer;
    UIDelayedAction    *m_longPressAction;
    CGPoint             m_touchPoint;
    CGPoint             m_touchOffset;
    UITouch            *m_syntheticTouch;
    BOOL                m_selecting;
    BOOL                m_handlingMouse;
    BOOL                m_sentMouseDown;
    BOOL                m_passMouseDownToOther;
    BOOL                m_scrollOnMouseUp;

    // property ivars
    UIWebDocumentView  *m_webView;
    UIFont             *m_font;
    UIColor            *m_textColor;
    UITextAlignment    m_textAlignment;
    NSRange            m_selectedRange;
    BOOL               m_editable;    
}

@property(nonatomic,assign) id<UITextViewDelegate> delegate;
@property(nonatomic,copy) NSString *text;
@property(nonatomic,retain) UIFont *font;
@property(nonatomic,retain) UIColor *textColor;
@property(nonatomic) UITextAlignment textAlignment;    // default is UITextAlignmentLeft
@property(nonatomic) NSRange selectedRange;            // only ranges of length 0 are supported
@property(nonatomic,getter=isEditable) BOOL editable;

- (BOOL)hasText;
- (void)scrollRangeToVisible:(NSRange)range;

@end

@protocol UITextViewDelegate <NSObject>

@optional

- (BOOL)textViewShouldBeginEditing:(UITextView *)textView;
- (BOOL)textViewShouldEndEditing:(UITextView *)textView;

- (void)textViewDidBeginEditing:(UITextView *)textView;
- (void)textViewDidEndEditing:(UITextView *)textView;

- (BOOL)textView:(UITextView *)textView shouldChangeTextInRange:(NSRange)range replacementText:(NSString *)text;
- (void)textViewDidChange:(UITextView *)textView;

- (void)textViewDidChangeSelection:(UITextView *)textView;

@end

UIKIT_EXTERN NSString * const UITextViewTextDidBeginEditingNotification;
UIKIT_EXTERN NSString * const UITextViewTextDidChangeNotification;
UIKIT_EXTERN NSString * const UITextViewTextDidEndEditingNotification;
