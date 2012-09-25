//
//  UISegmentedControl.h
//  UIKit
//
//  Copyright 2005-2008 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <UIKit/UIControl.h>
#import <UIKit/UIKitDefines.h>

typedef enum {
    UISegmentedControlStylePlain,     // large plain
    UISegmentedControlStyleBordered,  // large bordered
    UISegmentedControlStyleBar,       // small button/nav bar style. tintable
} UISegmentedControlStyle;

enum {
    UISegmentedControlNoSegment = -1   // segment index for no selected segment
};

@class UIImage, UIColor;

UIKIT_EXTERN_CLASS @interface UISegmentedControl : UIControl <NSCoding>
{
    NSMutableArray *_segments;
    NSInteger       _selectedSegment;
    NSInteger       _highlightedSegment;
    UIView         *_selectionIndicator;
    UIView         *_highlightIndicator;
    id              _delegate;
    UIColor        *_tintColor;
    struct {
        unsigned int style:3;
        unsigned int size:2;
        unsigned int showsDisclosure:1;
        unsigned int delegateSelectedSegmentChanged:1;
        unsigned int delegateDisclosureButtonClicked:1;
        unsigned int delegateAlwaysNotifiesDelegateOfSegmentClicks:1;
        unsigned int momentaryClick:1;
        unsigned int dontAlwaysToggleForTwoSegments:1;
        unsigned int tracking:1;
        unsigned int mouseInside:1;
        unsigned int autosizeToFitSegments:1;
        unsigned int isSizingToFit:1;
    } _segmentedControlFlags;
}

- (id)initWithItems:(NSArray *)items; // items can be NSStrings or UIImages. control is automatically sized to fit content

@property(nonatomic) UISegmentedControlStyle segmentedControlStyle; // default is UISegmentedControlStylePlain
@property(nonatomic,getter=isMomentary) BOOL momentary;             // if set, then we don't keep showing selected state after tracking ends. default is NO
@property(nonatomic,retain) UIColor *tintColor;                     // default is nil. only used if style is UISegmentedControlStyleBar

@property(nonatomic,readonly) NSUInteger numberOfSegments;

- (void)insertSegmentWithTitle:(NSString *)title atIndex:(NSUInteger)segment animated:(BOOL)animated; // insert before segment number. 0..#segments. value pinned
- (void)insertSegmentWithImage:(UIImage *)image  atIndex:(NSUInteger)segment animated:(BOOL)animated;
- (void)removeSegmentAtIndex:(NSUInteger)segment animated:(BOOL)animated;
- (void)removeAllSegments;

- (void)setTitle:(NSString *)title forSegmentAtIndex:(NSUInteger)segment;      // can only have image or title, not both. must be 0..#segments - 1 (or ignored). default is nil
- (NSString *)titleForSegmentAtIndex:(NSUInteger)segment;

- (void)setImage:(UIImage *)image forSegmentAtIndex:(NSUInteger)segment;       // can only have image or title, not both. must be 0..#segments - 1 (or ignored). default is nil
- (UIImage *)imageForSegmentAtIndex:(NSUInteger)segment;

- (void)setWidth:(CGFloat)width forSegmentAtIndex:(NSUInteger)segment;         // set to 0.0 width to autosize. default is 0.0
- (CGFloat)widthForSegmentAtIndex:(NSUInteger)segment;

- (void)setContentOffset:(CGSize)offset forSegmentAtIndex:(NSUInteger)segment; // adjust offset of image or text inside the segment. default is (0,0)
- (CGSize)contentOffsetForSegmentAtIndex:(NSUInteger)segment;

- (void)setEnabled:(BOOL)enabled forSegmentAtIndex:(NSUInteger)segment;        // default is YES
- (BOOL)isEnabledForSegmentAtIndex:(NSUInteger)segment;

// ignored in momentary mode. returns last segment pressed. default is UISegmentedControlNoSegment until a segment is pressed
// the UIControlEventValueChanged action is invoked when the segment changes via a user event. set to UISegmentedControlNoSegment to turn off selection
@property(nonatomic) NSInteger selectedSegmentIndex;

@end

