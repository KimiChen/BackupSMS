//
//  UISearchBar.h
//  UIKit
//
//  Copyright 2008 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIView.h>
#import <UIKit/UIInterface.h>
#import <UIKit/UITextField.h>
#import <UIKit/UIKitDefines.h>

@protocol UISearchBarDelegate;
@class UITextField, UILabel, UIButton, UIColor;

UIKIT_EXTERN_CLASS @interface UISearchBar : UIView { 
  @private
    UITextField            *_searchField;
    UILabel                *_promptLabel;
    UIButton               *_cancelButton;
    id<UISearchBarDelegate> _delegate;
    UIColor                *_tintColor;
    struct {
        unsigned int barStyle:3;
        unsigned int showsBookmarkButton:1;
        unsigned int showsCancelButton:1;
    } _searchBarFlags;
}

@property(nonatomic)        UIBarStyle              barStyle;              // default is UIBarStyleDefault (blue)
@property(nonatomic,assign) id<UISearchBarDelegate> delegate;              // weak reference. default is nil
@property(nonatomic,copy)   NSString               *text;                  // current/starting search text
@property(nonatomic,copy)   NSString               *prompt;                // default is nil
@property(nonatomic,copy)   NSString               *placeholder;           // default is nil
@property(nonatomic)        BOOL                    showsBookmarkButton;   // default is NO
@property(nonatomic)        BOOL                    showsCancelButton;     // default is NO
@property(nonatomic,retain) UIColor                *tintColor;             // default is nil

// available text input traits
@property(nonatomic) UITextAutocapitalizationType autocapitalizationType;  // default is UITextAutocapitalizationTypeNone
@property(nonatomic) UITextAutocorrectionType     autocorrectionType;      // default is UITextAutocorrectionTypeDefault
@property(nonatomic) UIKeyboardType               keyboardType;            // default is UIKeyboardTypeDefault

@end

@protocol UISearchBarDelegate <NSObject>

@optional

- (BOOL)searchBarShouldBeginEditing:(UISearchBar *)searchBar;                      // return NO to not become first responder
- (void)searchBarTextDidBeginEditing:(UISearchBar *)searchBar;                     // called when text starts editing
- (BOOL)searchBarShouldEndEditing:(UISearchBar *)searchBar;                        // return NO to not resign first responder
- (void)searchBarTextDidEndEditing:(UISearchBar *)searchBar;                       // called when text ends editing
- (void)searchBar:(UISearchBar *)searchBar textDidChange:(NSString *)searchText;   // called when text changes (including clear)

- (void)searchBarSearchButtonClicked:(UISearchBar *)searchBar;                     // called when keyboard search button pressed
- (void)searchBarBookmarkButtonClicked:(UISearchBar *)searchBar;                   // called when bookmark button pressed
- (void)searchBarCancelButtonClicked:(UISearchBar *) searchBar;                    // called when cancel button pressed

@end
