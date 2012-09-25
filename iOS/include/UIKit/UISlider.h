//
//  UISlider.h
//  UIKit
//
//  Copyright 2006-2008 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <UIKit/UIControl.h>
#import <UIKit/UIKitDefines.h>

@class UIImageView, UIImage;

UIKIT_EXTERN_CLASS @interface UISlider : UIControl <NSCoding> {
  @package
    float _value;
    float _minValue;
    float _maxValue;

    CFMutableDictionaryRef _contentLookup;

    UIImageView *_minValueImageView;
    UIImageView *_maxValueImageView;
    UIImageView *_thumbView;
    UIImageView *_minTrackView;
    UIImageView *_maxTrackView;

    struct {
	unsigned int continuous:1;
	unsigned int animating:1;
	unsigned int showValue:1;
	unsigned int creatingSnapshot:1;
    } _sliderFlags;

    CGFloat _hitOffset;
}

@property(nonatomic) float value;                                 // default 0.0. this value will be pinned to min/max
@property(nonatomic) float minimumValue;                          // default 0.0. the current value may change if outside new min value
@property(nonatomic) float maximumValue;                          // default 1.0. the current value may change if outside new max value

@property(nonatomic,retain) UIImage *minimumValueImage;          // default is nil. image that appears to left of control (e.g. speaker off)
@property(nonatomic,retain) UIImage *maximumValueImage;          // default is nil. image that appears to right of control (e.g. speaker max)

@property(nonatomic,getter=isContinuous) BOOL continuous;        // if set, value change events are generated any time the value changes due to dragging. default = YES

- (void)setValue:(float)value animated:(BOOL)animated; // move slider at fixed velocity (i.e. duration depends on distance). does not send action

// set the images for the slider. there are 3, the thumb which is centered by default and the track. You can specify different left and right track
// e.g blue on the left as you increase and white to the right of the thumb. The track images should be 3 part stretchable along the direction that is longer

- (void)setThumbImage:(UIImage *)image forState:(UIControlState)state;
- (void)setMinimumTrackImage:(UIImage *)image forState:(UIControlState)state;
- (void)setMaximumTrackImage:(UIImage *)image forState:(UIControlState)state;

- (UIImage *)thumbImageForState:(UIControlState)state;
- (UIImage *)minimumTrackImageForState:(UIControlState)state;
- (UIImage *)maximumTrackImageForState:(UIControlState)state;

@property(nonatomic,readonly) UIImage* currentThumbImage;
@property(nonatomic,readonly) UIImage* currentMinimumTrackImage;
@property(nonatomic,readonly) UIImage* currentMaximumTrackImage;

// lets a subclass lay out the track and thumb as needed
- (CGRect)minimumValueImageRectForBounds:(CGRect)bounds;
- (CGRect)maximumValueImageRectForBounds:(CGRect)bounds;
- (CGRect)trackRectForBounds:(CGRect)bounds;
- (CGRect)thumbRectForBounds:(CGRect)bounds trackRect:(CGRect)rect value:(float)value;

@end
