//
//  UIPickerView.h
//  UIKit
//
//  Copyright 2006-2008 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <UIKit/UIView.h>
#import <UIKit/UIKitDefines.h>

@protocol UIPickerViewDataSource, UIPickerViewDelegate;

UIKIT_EXTERN_CLASS @interface UIPickerView : UIView <NSCoding>
{ 
  @private
    NSMutableArray            *_tables;
    UIView                    *_topFrame;
    NSMutableArray            *_dividers;
    id<UIPickerViewDataSource> _dataSource;
    id<UIPickerViewDelegate>   _delegate;
    UIView                    *_backgroundView;
    NSInteger                  _numberOfComponents;
  @package
    struct {
        unsigned int needsLayout:1;
        unsigned int delegateRespondsToNumberOfComponentsInPickerView:1;
        unsigned int delegateRespondsToNumberOfRowsInComponent:1;
        unsigned int delegateRespondsToDidSelectRow:1;
        unsigned int delegateRespondsToViewForRow:1;
        unsigned int delegateRespondsToTitleForRow:1;
        unsigned int delegateRespondsToWidthForComponent:1;
        unsigned int delegateRespondsToRowHeightForComponent:1;
        unsigned int showsSelectionBar:1;
        unsigned int allowsMultipleSelection:1;
        unsigned int allowSelectingCells:1;
        unsigned int soundsEnabled:1;
    } _pickerViewFlags;
}

@property(nonatomic,assign) id<UIPickerViewDataSource> dataSource;                // default is nil. weak reference
@property(nonatomic,assign) id<UIPickerViewDelegate>   delegate;                  // default is nil. weak reference
@property(nonatomic)        BOOL                       showsSelectionIndicator;   // default is NO

// info that was fetched and cached from the delegate
@property(nonatomic,readonly) NSInteger numberOfComponents;
- (NSInteger)numberOfRowsInComponent:(NSInteger)component;
- (CGSize)rowSizeForComponent:(NSInteger)component;

// returns the view provided by the delegate via pickerView:viewForRow:forComponent:reusingView:
// or nil if the row/component is not visible or the delegate does not implement 
// pickerView:viewForRow:forComponent:reusingView:
- (UIView *)viewForRow:(NSInteger)row forComponent:(NSInteger)component;

// Reloading whole view or single component
- (void)reloadAllComponents;
- (void)reloadComponent:(NSInteger)component;

// selection. in this case, it means showing the appropriate row in the middle
- (void)selectRow:(NSInteger)row inComponent:(NSInteger)component animated:(BOOL)animated;  // scrolls the specified row to center.

- (NSInteger)selectedRowInComponent:(NSInteger)component;                                   // returns selected row. -1 if nothing selected

@end


@protocol UIPickerViewDataSource<NSObject>
@required

// returns the number of 'columns' to display.
- (NSInteger)numberOfComponentsInPickerView:(UIPickerView *)pickerView;

// returns the # of rows in each component..
- (NSInteger)pickerView:(UIPickerView *)pickerView numberOfRowsInComponent:(NSInteger)component;
@end


@protocol UIPickerViewDelegate<NSObject>
@optional

// returns width of column and height of row for each component. 
- (CGFloat)pickerView:(UIPickerView *)pickerView widthForComponent:(NSInteger)component;
- (CGFloat)pickerView:(UIPickerView *)pickerView rowHeightForComponent:(NSInteger)component;

// these methods return either a plain UIString, or a view (e.g UILabel) to display the row for the component.
// for the view versions, we cache any hidden and thus unused views and pass them back for reuse. 
// If you return back a different object, the old one will be released. the view will be centered in the row rect  
- (NSString *)pickerView:(UIPickerView *)pickerView titleForRow:(NSInteger)row forComponent:(NSInteger)component;
- (UIView *)pickerView:(UIPickerView *)pickerView viewForRow:(NSInteger)row forComponent:(NSInteger)component reusingView:(UIView *)view;

- (void)pickerView:(UIPickerView *)pickerView didSelectRow:(NSInteger)row inComponent:(NSInteger)component;

@end
