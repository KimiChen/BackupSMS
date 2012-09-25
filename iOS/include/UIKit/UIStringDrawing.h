//
//  UIStringDrawing.h
//  UIKit
//
//  Copyright 2005-2008 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>

typedef enum {		
    UILineBreakModeWordWrap = 0,            // Wrap at word boundaries
    UILineBreakModeCharacterWrap,           // Wrap at character boundaries
    UILineBreakModeClip,                    // Simply clip when it hits the end of the rect
    UILineBreakModeHeadTruncation,          // Truncate at head of line: "...wxyz". Will truncate multiline text on first line
    UILineBreakModeTailTruncation,          // Truncate at tail of line: "abcd...". Will truncate multiline text on last line
    UILineBreakModeMiddleTruncation,        // Truncate middle of line:  "ab...yz". Will truncate multiline text in the middle
} UILineBreakMode;

typedef enum {
    UITextAlignmentLeft = 0,
    UITextAlignmentCenter,
    UITextAlignmentRight,                   // could add justified in future
} UITextAlignment;

typedef enum {
    UIBaselineAdjustmentAlignBaselines = 0, // default. used when shrinking text to position based on the original baseline
    UIBaselineAdjustmentAlignCenters,
    UIBaselineAdjustmentNone,
} UIBaselineAdjustment;

@class UIFont;

// these methods draw using a UIFont. draw methods return size of actual string. all draw in the current context using the current color

@interface NSString(UIStringDrawing)

// Single line, no wrapping. Truncation based on the UILineBreakMode.
- (CGSize)sizeWithFont:(UIFont *)font; // Uses UILineBreakModeWordWrap
- (CGSize)sizeWithFont:(UIFont *)font forWidth:(CGFloat)width lineBreakMode:(UILineBreakMode)lineBreakMode;

// Single line, no wrapping. Truncation based on the UILineBreakMode.
- (CGSize)drawAtPoint:(CGPoint)point withFont:(UIFont *)font; // Uses UILineBreakModeWordWrap
- (CGSize)drawAtPoint:(CGPoint)point forWidth:(CGFloat)width withFont:(UIFont *)font lineBreakMode:(UILineBreakMode)lineBreakMode;

// Wrapping to fit horizontal and vertical size. Text will be wrapped and truncated using the UILineBreakMode. If the height is less than a line of text, it may return
// a vertical size that is bigger than the one passed in. You can use this to figure out how high one line of text is.
- (CGSize)sizeWithFont:(UIFont *)font constrainedToSize:(CGSize)size; // Uses UILineBreakModeWordWrap
- (CGSize)sizeWithFont:(UIFont *)font constrainedToSize:(CGSize)size lineBreakMode:(UILineBreakMode)lineBreakMode; // UITextAlignment is not needed to determine size

// Wrapping to fit horizontal and vertical size.
- (CGSize)drawInRect:(CGRect)rect withFont:(UIFont *)font; // Uses UILineBreakModeWordWrap and UITextAlignmentLeft
- (CGSize)drawInRect:(CGRect)rect withFont:(UIFont *)font lineBreakMode:(UILineBreakMode)lineBreakMode; // Uses UITextAlignmentLeft
- (CGSize)drawInRect:(CGRect)rect withFont:(UIFont *)font lineBreakMode:(UILineBreakMode)lineBreakMode alignment:(UITextAlignment)alignment;

// These methods will behave identically to the above single line methods if the string will fit in the specified width in the specified font.
// If not, the font size will be reduced until either the string fits or the minimum font size is reached.  If the minimum font
// size is reached and the string still won't fit, the string will be truncated and drawn at the minimum font size.
// The first two methods are used together, and the actualFontSize returned in the sizeWithFont method should be passed to the drawAtPoint method.
// The last method will do the sizing calculation and drawing in one operation.
- (CGSize)sizeWithFont:(UIFont *)font minFontSize:(CGFloat)minFontSize actualFontSize:(CGFloat *)actualFontSize forWidth:(CGFloat)width lineBreakMode:(UILineBreakMode)lineBreakMode;

- (CGSize)drawAtPoint:(CGPoint)point forWidth:(CGFloat)width withFont:(UIFont *)font fontSize:(CGFloat)fontSize lineBreakMode:(UILineBreakMode)lineBreakMode baselineAdjustment:(UIBaselineAdjustment)baselineAdjustment; // default is UIBaselineAdjustmentAlignBaselines

- (CGSize)drawAtPoint:(CGPoint)point forWidth:(CGFloat)width withFont:(UIFont *)font minFontSize:(CGFloat)minFontSize actualFontSize:(CGFloat *)actualFontSize lineBreakMode:(UILineBreakMode)lineBreakMode baselineAdjustment:(UIBaselineAdjustment)baselineAdjustment; // default is UIBaselineAdjustmentAlignBaselines

@end
