//
//  UITableView.h
//  UIKit
//
//  Copyright 2005-2008 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <UIKit/UIScrollView.h>
#import <UIKit/UITableViewCell.h>
#import <UIKit/UIKitDefines.h>

typedef enum {
    UITableViewStylePlain,              // regular table view
    UITableViewStyleGrouped             // preferences style table view
} UITableViewStyle;

typedef enum {
    UITableViewScrollPositionNone,        
    UITableViewScrollPositionTop,    
    UITableViewScrollPositionMiddle,   
    UITableViewScrollPositionBottom
} UITableViewScrollPosition;            // scroll so row of interest is completely visible at top/center/bottom of view

typedef enum {
    UITableViewRowAnimationFade,
    UITableViewRowAnimationRight,       // slide in from right (or out to right)
    UITableViewRowAnimationLeft,
    UITableViewRowAnimationTop,
    UITableViewRowAnimationBottom
} UITableViewRowAnimation;

@protocol UITableViewDataSource, UITableViewDelegate;

UIKIT_EXTERN_CLASS @interface UITableView : UIScrollView <NSCoding> {
  @private
    UITableViewStyle            _style;

    id <UITableViewDataSource>  _dataSource;
    
    id                          _rowData;
    CGFloat                     _rowHeight;
    CGFloat                     _sectionHeaderHeight;
    CGFloat                     _sectionFooterHeight;

    NSRange                     _visibleRows;
    NSMutableArray             *_visibleCells;
    NSIndexPath                *_firstResponderIndexPath;
    UITableViewCell            *_firstResponderCell;
    NSMutableDictionary        *_reusableTableCells;
    UITableViewCell            *_topSeparatorCell;
    id                          _topSeparator;
    NSMutableArray             *_extraSeparators;
    NSMutableDictionary        *_visibleHeaderViews;
    NSMutableDictionary        *_visibleFooterViews;
    NSMutableArray             *_reusableHeaderViews;
    NSMutableArray             *_reusableFooterViews;
    NSMutableArray             *_reusableTransparentHeaderViews;
    NSMutableArray             *_reusableTransparentFooterViews;

    BOOL                        _allowsMultipleSelection;
    NSInteger                   _selectedSection;
    NSInteger                   _selectedRow;
    NSInteger                   _lastSelectedSection;
    NSInteger                   _lastSelectedRow;
    NSInteger                   _swipeToDeleteSection;
    NSInteger                   _swipeToDeleteRow;
    NSIndexPath                *_pendingSelectionIndexPath;

    id                          _deleteAnimationSupport;
    id                          _reorderingSupport;

    UIView                     *_index;
    UIView                     *_tableHeaderBackgroundView;
    UIView                     *_tableHeaderView;
    UIView                     *_tableFooterView;
    id                          _countLabel;

    NSInteger                   _tableReloadingSuspendedCount;
    NSInteger                   _tableDisplaySuspendedCount;
    NSInteger                   _sectionIndexMinimumDisplayRowCount;
    NSInteger                   _itemCountFooterMinimumDisplayRowCount;

    CFMutableDictionaryRef      _piecesForCell;
    NSMutableArray             *_insertItems;
    NSMutableArray             *_deleteItems;
    
    UIColor                    *_separatorColor;
    
    NSArray                    *_defaultSectionIndexTitles;

    struct {
        unsigned int dataSourceNumberOfRowsInSection:1;
        unsigned int dataSourceCellForRow:1;
        unsigned int dataSourceNumberOfSectionsInTableView:1;
        unsigned int dataSourceTitleForHeaderInSection:1;
        unsigned int dataSourceTitleForFooterInSection:1;
        unsigned int dataSourceCommitEditingStyle:1;
        unsigned int dataSourceSectionIndexTitlesForTableView:1;
        unsigned int dataSourceSectionForSectionIndexTitle:1;
        unsigned int dataSourceCanEditRow:1;
        unsigned int dataSourceCanMoveRow:1;
        unsigned int delegateEditingStyleForRowAtIndexPath:1;
        unsigned int delegateShouldIndentWhileEditing:1;
        unsigned int dataSourceMoveRow:1;
        unsigned int delegateCellForRow:1;
        unsigned int delegateWillDisplayCell:1;
        unsigned int delegateHeightForRow:1;
        unsigned int delegateHeightForSectionHeader:1;
        unsigned int delegateHeightForSectionFooter:1;
        unsigned int delegateViewForHeaderInSection:1;
        unsigned int delegateViewForFooterInSection:1;
        unsigned int delegateDisplayedItemCountForRowCount:1;
        unsigned int delegateDisplayStringForRowCount:1;
        unsigned int delegateAccessoryTypeForRow:1;
        unsigned int delegateAccessoryButtonTappedForRow:1;
        unsigned int delegateWillSelectRow:1;
        unsigned int delegateSelectionDidChange:1;
        unsigned int delegateWillBeginEditing:1;
        unsigned int delegateDidEndEditing:1;
        unsigned int delegateWillMoveToRow:1;
        unsigned int delegateIndentationLevelForRow:1;
        unsigned int style:1;
        unsigned int separatorStyle:3;
        unsigned int isEditing:1;
        unsigned int scrollsToSelection:1;
        unsigned int reloadSkippedDuringSuspension:1;
        unsigned int updating:1;
        unsigned int displaySkippedDuringSuspension:1;
        unsigned int needsReload:1;
        unsigned int updatingVisibleCellsManually:1;
        unsigned int scheduledUpdateVisibleCells:1;
        unsigned int scheduledUpdateVisibleCellsFrames:1;
        unsigned int warnForForcedCellUpdateDisabled:1;
        unsigned int delaySendingSelectionChanged:1;
        unsigned int displayTopSeparator:1;
        unsigned int countStringInsignificantRowCount:4;
        unsigned int needToAdjustExtraSeparators:1;
        unsigned int ignoreDragSwipe:1;        
        unsigned int ignoreTouchSelect:1;
        unsigned int lastHighlightedRowActive:1;
        unsigned int reloading:1;
        unsigned int allowsSelectionDuringEditing:1;
        unsigned int showsSelectionImmediatelyOnTouchBegin:1;
        unsigned int indexHidden:1;
        unsigned int defaultShowsHorizontalScrollIndicator:1;
        unsigned int defaultShowsVerticalScrollIndicator:1;
        unsigned int sectionIndexTitlesLoaded:1;
    } _tableFlags;
}

- (id)initWithFrame:(CGRect)frame style:(UITableViewStyle)style;            // must specify style at creation. -initWithFrame: calls this with UITableViewStylePlain

@property(nonatomic,readonly) UITableViewStyle           style;
@property(nonatomic,assign)   id <UITableViewDataSource> dataSource;
@property(nonatomic,assign)   id <UITableViewDelegate>   delegate;
@property(nonatomic)          CGFloat                    rowHeight;                  // will return the default value if unset
@property(nonatomic)          CGFloat                    sectionHeaderHeight;        // will return the default value if unset
@property(nonatomic)          CGFloat                    sectionFooterHeight;        // will return the default value if unset

// Data

- (void)reloadData;    // reloads everything from scratch. redisplays visible rows. because we only keep info about visible rows, this is cheap. will adjust offset if table shrinks

// Info

- (NSInteger)numberOfSections;
- (NSInteger)numberOfRowsInSection:(NSInteger)section;

- (CGRect)rectForSection:(NSInteger)section;                                // includes header, footer and all rows
- (CGRect)rectForHeaderInSection:(NSInteger)section;
- (CGRect)rectForFooterInSection:(NSInteger)section;
- (CGRect)rectForRowAtIndexPath:(NSIndexPath *)indexPath;

- (NSIndexPath *)indexPathForRowAtPoint:(CGPoint)point;                     // returns nil if point is outside table
- (NSIndexPath *)indexPathForCell:(UITableViewCell *)cell;                  // returns nil if cell is not visible
- (NSArray *)indexPathsForRowsInRect:(CGRect)rect;                          // returns nil if rect not valid 

- (UITableViewCell *)cellForRowAtIndexPath:(NSIndexPath *)indexPath;        // returns nil if cell is not visible or index path is out of range
- (NSArray *)visibleCells;
- (NSArray *)indexPathsForVisibleRows;

- (void)scrollToRowAtIndexPath:(NSIndexPath *)indexPath atScrollPosition:(UITableViewScrollPosition)scrollPosition animated:(BOOL)animated;
- (void)scrollToNearestSelectedRowAtScrollPosition:(UITableViewScrollPosition)scrollPosition animated:(BOOL)animated;

// Row insertion/deletion/insertion. calls dataSource and then update table using delegate

- (void)beginUpdates;   // allow multiple insert/delete of rows and sections to be animated simultaneously. Not nestable
- (void)endUpdates;     // only call insert/delete calls inside otherwise things like row count, etc. may be invalid.

- (void)insertSections:(NSIndexSet *)sections withRowAnimation:(UITableViewRowAnimation)animation;
- (void)deleteSections:(NSIndexSet *)sections withRowAnimation:(UITableViewRowAnimation)animation;

- (void)insertRowsAtIndexPaths:(NSArray *)indexPaths withRowAnimation:(UITableViewRowAnimation)animation;
- (void)deleteRowsAtIndexPaths:(NSArray *)indexPaths withRowAnimation:(UITableViewRowAnimation)animation;

// Editing. When set, rows show insert/delete/reorder controls based on data source queries

@property(nonatomic) BOOL allowsSelectionDuringEditing;                                // default is NO. if YES, can select rows during editing and the disclosure will still be present.

@property(nonatomic,getter=isEditing) BOOL editing;                                    // default is NO. setting is not animated
- (void)setEditing:(BOOL)editing animated:(BOOL)animated;                              // turn on/off row insert/delete/reorder controls.

// Selection

- (NSIndexPath *)indexPathForSelectedRow;                                              // return nil or index path representing section and row of selection.

// Selects and deselects rows. These methods will not call the delegate methods (-tableView:willSelectRowAtIndexPath: or tableView:didSelectRowAtIndexPath:), nor will it send out a notification.
- (void)selectRowAtIndexPath:(NSIndexPath *)indexPath animated:(BOOL)animated scrollPosition:(UITableViewScrollPosition)scrollPosition;
- (void)deselectRowAtIndexPath:(NSIndexPath *)indexPath animated:(BOOL)animated;

// Appearance

@property(nonatomic) NSInteger sectionIndexMinimumDisplayRowCount;                     // show special section index list on right when row count reaches this value. default is NSInteger Max

@property(nonatomic) UITableViewCellSeparatorStyle separatorStyle;                     // default is UITableViewCellSeparatorStyleSingleLine
@property(nonatomic,retain) UIColor               *separatorColor;                     // default is the standard separator gray

@property(nonatomic,retain) UIView *tableHeaderView;                                   // accessory view for above row content. default is nil. not to be confused with section header
@property(nonatomic,retain) UIView *tableFooterView;                                   // accessory view below content. default is nil. not to be confused with section footer

- (UITableViewCell *)dequeueReusableCellWithIdentifier:(NSString *)identifier;         // Used by the delegate to acquire an already allocated cell, in lieu of allocating a new one.

@end

//_______________________________________________________________________________________________________________
// this protocol represents the data model object. as such, it supplies no information about appearance (including the cells)

@protocol UITableViewDataSource<NSObject>

@required

- (NSInteger)tableView:(UITableView *)table numberOfRowsInSection:(NSInteger)section;

// Row display. Implementers should *always* try to reuse cells by setting each cell's reuseIdentifier and querying for available reusable cells with dequeueReusableCellWithIdentifier:
// Cell gets various attributes set automatically based on table (separators) and data source (accessory views, editing controls)

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath;

@optional

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView; // Default is 1 if not implemented

- (NSString *)tableView:(UITableView *)tableView titleForHeaderInSection:(NSInteger)section;    // fixed font style. use custom view (UILabel) if you want something different
- (NSString *)tableView:(UITableView *)tableView titleForFooterInSection:(NSInteger)section;

// Information. called on editing, this tells us that we need to reserve space for the various edit controls even if no visible views show them

// Editing

// Individual rows can opt out of having the -editing property set for them. If not implemented, all rows are assumed to be editable.
- (BOOL)tableView:(UITableView *)tableView canEditRowAtIndexPath:(NSIndexPath *)indexPath;

// Moving/reordering

// Allows the reorder accessory view to optionally be shown for a particular row. By default, the reorder control will be shown only if the datasource implements -tableView:moveRowAtIndexPath:toIndexPath:
- (BOOL)tableView:(UITableView *)tableView canMoveRowAtIndexPath:(NSIndexPath *)indexPath;

// Index

- (NSArray *)sectionIndexTitlesForTableView:(UITableView *)tableView;                                                    // return list of section titles to display in section index view (e.g. "ABCD...Z#")
- (NSInteger)tableView:(UITableView *)tableView sectionForSectionIndexTitle:(NSString *)title atIndex:(NSInteger)index;  // tell table which section corresponds to section title/index (e.g. "B",1))

// Data manipulation - insert and delete support

// After a row has the minus or plus button invoked (based on the UITableViewCellEditingStyle for the cell), the dataSource must commit the change
- (void)tableView:(UITableView *)tableView commitEditingStyle:(UITableViewCellEditingStyle)editingStyle forRowAtIndexPath:(NSIndexPath *)indexPath;

// Data manipulation - reorder / moving support

- (void)tableView:(UITableView *)tableView moveRowAtIndexPath:(NSIndexPath *)sourceIndexPath toIndexPath:(NSIndexPath *)destinationIndexPath;

@end

//_______________________________________________________________________________________________________________
// this represents the display and behaviour of the cells.

@protocol UITableViewDelegate<NSObject, UIScrollViewDelegate>

@optional

// Display customization

- (void)tableView:(UITableView *)tableView willDisplayCell:(UITableViewCell *)cell forRowAtIndexPath:(NSIndexPath *)indexPath;

// Variable height support

- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath;
- (CGFloat)tableView:(UITableView *)tableView heightForHeaderInSection:(NSInteger)section;
- (CGFloat)tableView:(UITableView *)tableView heightForFooterInSection:(NSInteger)section;

// Section header & footer information. Views are preferred over title should you decide to provide both

- (UIView *)tableView:(UITableView *)tableView viewForHeaderInSection:(NSInteger)section;   // custom view for header. will be adjusted to default or specified header height
- (UIView *)tableView:(UITableView *)tableView viewForFooterInSection:(NSInteger)section;   // custom view for footer. will be adjusted to default or specified footer height

// Accessories (disclosures). 

// When the editing state changes, these methods will be called again to allow the accessory to be hidden when editing, if required.
- (UITableViewCellAccessoryType)tableView:(UITableView *)tableView accessoryTypeForRowWithIndexPath:(NSIndexPath *)indexPath;
- (void)tableView:(UITableView *)tableView accessoryButtonTappedForRowWithIndexPath:(NSIndexPath *)indexPath;

// Selection

// Called before the user changes the selection. Returning a new indexPath, or nil, to change the proposed selection.
- (NSIndexPath *)tableView:(UITableView *)tableView willSelectRowAtIndexPath:(NSIndexPath *)indexPath;
// Called after the user changes the selection.
- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath;

// Editing

// Allows customization of the editingStyle for a particular cell located at 'indexPath'. If not implemented, all editable cells will have UITableViewCellEditingStyleDelete set for them when the table has editing property set to YES.
- (UITableViewCellEditingStyle)tableView:(UITableView *)tableView editingStyleForRowAtIndexPath:(NSIndexPath *)indexPath;

// Controls whether the background is indented while editing.  If not implemented, the default is YES.  This is unrelated to the indentation level below.
- (BOOL)tableView:(UITableView *)tableView shouldIndentWhileEditingRowAtIndexPath:(NSIndexPath *)indexPath;

// The willBegin/didEnd methods are called whenever the 'editing' property is automatically changed by the table (allowing insert/delete/move). This is done by a swipe activating a single row
- (void)tableView:(UITableView*)tableView willBeginEditingRowAtIndexPath:(NSIndexPath *)indexPath;
- (void)tableView:(UITableView*)tableView didEndEditingRowAtIndexPath:(NSIndexPath *)indexPath;

// Moving/reordering

// Allows customization of the target row for a particular row as it is being moved/reordered
- (NSIndexPath *)tableView:(UITableView *)tableView targetIndexPathForMoveFromRowAtIndexPath:(NSIndexPath *)sourceIndexPath toProposedIndexPath:(NSIndexPath *)proposedDestinationIndexPath;               

// Indentation

- (NSInteger)tableView:(UITableView *)tableView indentationLevelForRowAtIndexPath:(NSIndexPath *)indexPath; // return 'depth' of row for hierarchies

@end

UIKIT_EXTERN NSString *const UITableViewSelectionDidChangeNotification;

//_______________________________________________________________________________________________________________

// This category provides convenience methods to make it easier to use an NSIndexPath to represent a section and row
@interface NSIndexPath (UITableView)

+ (NSIndexPath *)indexPathForRow:(NSUInteger)row inSection:(NSUInteger)section;

@property(nonatomic,readonly) NSUInteger section;
@property(nonatomic,readonly) NSUInteger row;

@end
