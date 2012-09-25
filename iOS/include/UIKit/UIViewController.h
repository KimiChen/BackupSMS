//
//  UIViewController.h
//  UIKit
//
//  Copyright 2007-2008 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UIApplication.h>

/*!
 UIViewController is a generic controller base class that manages a view.
 It has methods that are called when a view appears or disappears.
 
 Subclasses should override -loadView to create their custom view hierarchy.
 This class is also a good place for delegate & datasource methods, and other controller stuff.
*/

@class UIView, UIImage;
@class UINavigationItem, UIBarButtonItem, UITabBarItem;
@class UITabBarController, UINavigationController;
@class NSHashTable;

UIKIT_EXTERN_CLASS @interface UIViewController : UIResponder <NSCoding> {
  @package
    UIView           *_view;
    UITabBarItem     *_tabBarItem;
    UINavigationItem *_navigationItem;
    NSString         *_title;
    
    NSString         *_nibName;
    NSBundle         *_nibBundle;
    
    UIViewController *_parentViewController; // weak
    NSHashTable      *_childViewControllers; // weak
    
    UIViewController *_childModalViewController;
    UIView           *_modalTransitionView;
    id                _currentAction;
    
    UIView           *_savedHeaderSuperview;
    UIView           *_savedFooterSuperview;
        
    UIBarButtonItem  *_editButtonItem;
    
    struct {
	unsigned int isRootViewController:1;
	unsigned int isEditing:1;
	unsigned int isPerformingModalTransition:1;
	unsigned int hidesBottomBarWhenPushed:1;
	unsigned int autoresizesArchivedViewToFullSize:1;
    } _viewControllerFlags;
}

// The designated initializer. The specified nib should typically have the class of the file's owner set to UIViewController or a subclass, with the "view" outlet connected to a view.
// If you pass in a nil nib name, then you must either call -setView: before -view is invoked, or override -loadView to set up your views.
- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil;

@property(nonatomic,retain) UIView *view; // The getter first invokes [self loadView] if the view hasn't been set yet. Subclasses must call super if they override the setter or getter.
- (void)loadView; // This is where subclasses should create their custom view hierarchy if they aren't using a nib. Should never be called directly.
- (void)viewDidLoad; // Called after the view has been loaded. For view controllers created in code, this is after -loadView. For view controllers unarchived from a nib, this is after the view is set.

@property(readonly, copy) NSString *nibName;     // The name of the nib to be loaded to instantiate the view.
@property(readonly, retain) NSBundle *nibBundle; // The bundle from which to load the nib.

- (void)viewWillAppear:(BOOL)animated;    // Called when the view is about to made visible. Default does nothing
- (void)viewDidAppear:(BOOL)animated;     // Called when the view has been fully transitioned onto the screen. Default does nothing
- (void)viewWillDisappear:(BOOL)animated; // Called when the view is dismissed, covered or otherwise hidden. Default does nothing
- (void)viewDidDisappear:(BOOL)animated;  // Called after the view was dismissed, covered or otherwise hidden. Default does nothing

@property(nonatomic,copy) NSString *title;  // Localized title for use by a parent controller.

- (void)didReceiveMemoryWarning; // Called when the parent application receives a memory warning. Default implementation releases the view if it doesn't have a superview.

- (void)presentModalViewController:(UIViewController *)modalViewController animated:(BOOL)animated; // Display another view controller as a modal child. Uses a vertical sheet transition if animated.
- (void)dismissModalViewControllerAnimated:(BOOL)animated; // Dismiss the current modal child. Uses a vertical sheet transition if animated.
@property(nonatomic,readonly) UIViewController *modalViewController;

@property(nonatomic,readonly) UIViewController *parentViewController; // If this view controller is inside a navigation controller or tab bar controller, or has been presented modally by another view controller, return it.

@end

// To make it more convenient for applications to adopt rotation, a view controller may implement the below methods.
// Your UIWindow's frame should use [UIScreen mainScreen].bounds as its frame.
@interface UIViewController (UIViewControllerRotation)

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation; // Override to allow rotation. Default returns YES only for UIDeviceOrientationPortrait

// The rotating header and footer views will slide out during the rotation and back in once it has completed.
- (UIView *)rotatingHeaderView;     // Default returns nil.
- (UIView *)rotatingFooterView;     // Default returns the active keyboard.

@property(nonatomic,readonly) UIInterfaceOrientation interfaceOrientation;

- (void)willRotateToInterfaceOrientation:(UIInterfaceOrientation)toInterfaceOrientation duration:(NSTimeInterval)duration; // Notification of rotation beginning.
- (void)willAnimateFirstHalfOfRotationToInterfaceOrientation:(UIInterfaceOrientation)toInterfaceOrientation duration:(NSTimeInterval)duration;
- (void)willAnimateSecondHalfOfRotationFromInterfaceOrientation:(UIInterfaceOrientation)fromInterfaceOrientation duration:(NSTimeInterval)duration; // A this point, our view orientation is set to the new orientation.
- (void)didRotateFromInterfaceOrientation:(UIInterfaceOrientation)fromInterfaceOrientation;    // Notification of rotation ending.

@end

// Many view controllers have a view that may be in an editing state or not- for example, a UITableView.
// These view controllers can track the editing state, and generate an Edit|Done button to be used in a navigation bar.
@interface UIViewController (UIViewControllerEditing)

@property(nonatomic,getter=isEditing) BOOL editing;
- (void)setEditing:(BOOL)editing animated:(BOOL)animated; // Updates the appearance of the Edit|Done button item as necessary. Clients who override it must call super first.

- (UIBarButtonItem *)editButtonItem; // Return an Edit|Done button that can be used as a navigation item's custom view. Default action toggles the editing state with animation.

@end
