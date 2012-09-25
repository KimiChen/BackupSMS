//
//  UITableViewController.h
//  UIKit
//
//  Copyright 2008 Apple Inc. All rights reserved.
//
#import <Foundation/Foundation.h>
#import <UIKit/UIViewController.h>
#import <UIKit/UITableView.h>
#import <UIKit/UIKitDefines.h>

// Creates a table view with the correct dimensions and autoresizing, setting the datasource and delegate to self.
// In -viewWillAppear:, it reloads the table's data if it's empty. Otherwise, it deselects all rows (with or without animation).
// In -viewDidAppear:, it flashes the table's scroll indicators.
// Implements -setEditing:animated: to toggle the editing state of the table.

UIKIT_EXTERN_CLASS @interface UITableViewController : UIViewController <UITableViewDelegate, UITableViewDataSource> {
  @private
    UITableViewStyle _tableViewStyle;
    void            *_reserved;
}

- (id)initWithStyle:(UITableViewStyle)style;

@property(nonatomic,retain) UITableView *tableView;

@end
