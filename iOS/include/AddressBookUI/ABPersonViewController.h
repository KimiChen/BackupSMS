//
//  ABPersonViewController.h
//  AddressBookUI
//
//  Copyright 2008 Apple Inc. All rights reserved.
//

#import <UIKit/UIViewController.h>
#import <AddressBook/AddressBook.h>

@protocol ABPersonViewControllerDelegate;

@interface ABPersonViewController : UIViewController
{
    @private
        id<ABPersonViewControllerDelegate> _personViewDelegate;
        BOOL                               _allowsActions;
        BOOL                               _allowsDeletion;
        BOOL                               _animatedRight;
        
        CFArrayRef                         _displayedProperties;
        
        id                                 _personView;
        id                                 _helper;
}

@property(nonatomic,assign)    id<ABPersonViewControllerDelegate> personViewDelegate;

    // The Address Book to use. Any contact returned will be from this ABAddressBook instance.
    // If not set, a new ABAddressBook will be created the first time the property is accessed.
@property(nonatomic,readwrite) ABAddressBookRef                   addressBook;

    // If displayedPerson has been added to an ABAddressBook, then the addressBook
    // property will be updated to use the displayedPerson's ABAddressBook.
@property(nonatomic,readwrite) ABRecordRef                        displayedPerson;


    // An array of NSNumber instances representing the properties (ABPropertyID) that should
    // be visible when viewing the person. Note that all the properties are visible when
    // editing a person.
@property(nonatomic,copy)      NSArray                           *displayedProperties;

    // Indicates whether an edit/save button should be shown.
@property(nonatomic)           BOOL                               allowsEditing;

	// Indicate whether to highlight a certain value for the displayedPerson,
    // if a single value property is specified, identifier will be ignored.
- (void)setHighlightedItemForProperty:(ABPropertyID)property withIdentifier:(ABMultiValueIdentifier)identifier;
	
@end

@protocol ABPersonViewControllerDelegate <NSObject>

    // Called when the user selects an individual value in the Person view, identifier will be kABMultiValueInvalidIdentifier if a single value property was selected.
    // Return NO if you do not want anything to be done or if you are handling the actions yourself.
    // Return YES if you want the ABPersonViewController to perform its default action.
- (BOOL)personViewController:(ABPersonViewController *)personViewController shouldPerformDefaultActionForPerson:(ABRecordRef)person property:(ABPropertyID)property identifier:(ABMultiValueIdentifier)identifier;

@end
