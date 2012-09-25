//
//  UITableViewCell.h
//  UIKit
//
//  Copyright 2005-2008 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <UIKit/UIView.h>
#import <UIKit/UIStringDrawing.h>
#import <UIKit/UIKitDefines.h>

@class UIImage, UIColor, UILabel, UIImageView;

typedef enum {
    UITableViewCellSeparatorStyleNone,
    UITableViewCellSeparatorStyleSingleLine
} UITableViewCellSeparatorStyle;

typedef enum {
    UITableViewCellSelectionStyleNone,
    UITableViewCellSelectionStyleBlue,
    UITableViewCellSelectionStyleGray
} UITableViewCellSelectionStyle;

typedef enum {
    UITableViewCellEditingStyleNone,
    UITableViewCellEditingStyleDelete,
    UITableViewCellEditingStyleInsert
} UITableViewCellEditingStyle;

typedef enum {
    UITableViewCellAccessoryNone,                   // don't show any accessory view
    UITableViewCellAccessoryDisclosureIndicator,    // regular chevron. doesn't track
    UITableViewCellAccessoryDetailDisclosureButton, // blue button w/ chevron. tracks
    UITableViewCellAccessoryCheckmark               // checkmark. doesn't track
} UITableViewCellAccessoryType;

UIKIT_EXTERN_CLASS @interface UITableViewCell : UIView <NSCoding> {
  @private
    id           _target;
    SEL          _editAction;
    SEL          _accessoryAction;
    id           _editingData;
    CGFloat      _rightMargin;
    NSInteger    _indentationLevel;
    CGFloat      _indentationWidth;
    NSString    *_reuseIdentifier;
    UIView      *_contentView;
    UIImage     *_image;
    UIImage     *_selectedImage;
    UILabel     *_textLabel;
    UIImageView *_imageView;
    UIView      *_backgroundView;
    UIView      *_selectedBackgroundView;
    CFMutableDictionaryRef _unhighlightedStates;
    struct {
        unsigned int showingDeleteConfirmation:1;
        unsigned int separatorStyle:3;
        unsigned int selectionStyle:3;
        unsigned int selectionFadeFraction:11;	// used to indicate selection
        unsigned int editing:1;
        unsigned int editingStyle:3;
        unsigned int accessoryType:3;
        unsigned int showsAccessoryWhenEditing:1;
        unsigned int showsReorderControl:1;
        unsigned int showDisclosure:1;
        unsigned int showTopSeparator:1;
        unsigned int disclosureClickable:1;
        unsigned int disclosureStyle:1;
        unsigned int showingRemoveControl:1;

        unsigned int alignment:3;
        unsigned int sectionLocation:3;
        unsigned int tableViewStyle:1;
        unsigned int shouldIndentWhileEditing:1;
        unsigned int fontSet:1;
        unsigned int usingDefaultSelectedBackgroundView:1;
    } _tableCellFlags;
    
    UIView *_accessoryView;
    UIView *_customAccessoryView;
}

// Designated initializer.  If the cell can be reused, you must pass in a reuse identifier.  You should use the same reuse identifier for all cells of the same form.  
- (id)initWithFrame:(CGRect)frame reuseIdentifier:(NSString *)reuseIdentifier;

// Content properties
@property(nonatomic,copy)   NSString              *text;                      // default is nil
@property(nonatomic,retain) UIFont                *font;                      // default is nil (Use default font)
@property(nonatomic) UITextAlignment               textAlignment;             // default is UITextAlignmentLeft
@property(nonatomic) UILineBreakMode               lineBreakMode;             // default is UILineBreakModeTailTruncation
@property(nonatomic,retain) UIColor               *textColor;                 // default is nil (text draws black)
@property(nonatomic,retain) UIColor               *selectedTextColor;         // default is nil (text draws white)

@property(nonatomic,retain) UIImage               *image;                     // default is nil. appears on left next to title.
@property(nonatomic,retain) UIImage               *selectedImage;             // default is nil

// If you want to customize cells by simply adding additional views, you should add them to the content view so they will be positioned appropriately as the cell transitions into and out of editing mode.
@property(nonatomic,readonly,retain) UIView       *contentView;

// Default is nil for cells in UITableViewStylePlain, and non-nil for UITableViewStyleGrouped. The 'backgroundView' will be added as a subview behind all other views.
@property(nonatomic,retain) UIView                *backgroundView;

// Default is nil for cells in UITableViewStylePlain, and non-nil for UITableViewStyleGrouped. The 'selectedBackgroundView' will be added as a subview directly above the backgroundView if not nil, or behind all other views. It is added as a subview only when the cell is selected. Calling -setSelected:animated: will cause the 'selectedBackgroundView' to animate in and out with an alpha fade.
@property(nonatomic,retain) UIView                *selectedBackgroundView;

@property(nonatomic,readonly,copy) NSString       *reuseIdentifier;
- (void)prepareForReuse;                                                       // if the cell is reusable (has a reuse identifier), this is called just before the cell is returned from the table view method dequeueReusableCellWithIdentifier:.  If you override, you MUST call super.

@property(nonatomic) UITableViewCellSelectionStyle  selectionStyle;            // default is UITableViewCellSelectionStyleBlue.
@property(nonatomic,getter=isSelected) BOOL         selected;                  // set selected state (title, image, background). default is NO. animated is NO
- (void)setSelected:(BOOL)selected animated:(BOOL)animated;                    // animate between regular and selected state

@property(nonatomic, readonly) UITableViewCellEditingStyle editingStyle;       // default is UITableViewCellEditingStyleNone. This is set by UITableView using the delegate's value for cells who customize their appearance accordingly.
@property(nonatomic) BOOL                           showsReorderControl;       // default is NO
@property(nonatomic) BOOL                           shouldIndentWhileEditing;  // default is YES.  This is unrelated to the indentation level below.

@property(nonatomic) UITableViewCellAccessoryType   accessoryType;             // default is UITableViewCellAccessoryNone. use to set standard type
@property(nonatomic,retain) UIView                 *accessoryView;             // if set, use custom view. ignore accessoryType. tracks if enabled can calls acc. action
@property(nonatomic) BOOL                           hidesAccessoryWhenEditing; // default is YES

@property(nonatomic) NSInteger                      indentationLevel;          // adjust content indent. default is 0
@property(nonatomic) CGFloat                        indentationWidth;          // width for each level. default is 10.0

@property(nonatomic,getter=isEditing) BOOL          editing;                   // show appropriate edit controls (+/- & reorder). By default -setEditing: calls setEditing:animated: with NO for animated.
- (void)setEditing:(BOOL)editing animated:(BOOL)animated;

@property(nonatomic,readonly) BOOL                  showingDeleteConfirmation; // currently showing "Delete" button

@property(nonatomic,assign) id                      target;                    // target for insert/delete/accessory clicks. default is nil (i.e. go up responder chain). weak reference
@property(nonatomic) SEL                            editAction;                // action to call on insert/delete call. set by UITableView
@property(nonatomic) SEL                            accessoryAction;           // action to call on accessory view clicked. set by UITableView

@end

