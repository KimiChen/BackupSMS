//
//  ABUnknownPersonViewController.h
//  AddressBookUI
//
//  Copyright 2008 Apple Inc. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <AddressBook/AddressBook.h>

@protocol ABUnknownPersonViewControllerDelegate;

@interface ABUnknownPersonViewController : UIViewController
{
    @private
        NSString    *_alternateName;
        NSString    *_message;
        
        BOOL         _allowsActions;
        BOOL         _allowsAddingToAddressBook;
        
        id           _helper;
        id<ABUnknownPersonViewControllerDelegate> _unknownPersonViewDelegate;
}

@property(nonatomic,assign)    id<ABUnknownPersonViewControllerDelegate> unknownPersonViewDelegate;

    // The Address Book to use. Any contact returned will be from this ABAddressBook instance.
    // If not set, a new ABAddressBook will be created the first time the property is accessed.
@property(nonatomic,readwrite) ABAddressBookRef                      addressBook;

    // All the fields specified in displayedPerson will be displayed in the view
    // and used if the unknown person is added to Address Book or merged into an
    // existing person in Address Book.
    // If displayedPerson has been added to an ABAddressBook, then the addressBook
    // property will be updated to use the displayedPerson's ABAddressBook.
@property(nonatomic,readwrite) ABRecordRef displayedPerson;

    // An alternateName can be provided to replace the First and Last name
    // in case they are not available.
@property(nonatomic,copy)      NSString   *alternateName;
    // The message will be displayed below the alternateName.
@property(nonatomic,copy)      NSString   *message;

    // Actions depend on the available properties but include making phone calls,
    // sending text messages, emails, opening URLs, etc...
@property(nonatomic)           BOOL        allowsActions;
    // Whether options to create a contact or add to an existing contact should be
    // made available to the user.
@property(nonatomic)           BOOL        allowsAddingToAddressBook;

@end


@protocol ABUnknownPersonViewControllerDelegate <NSObject>

    // Called when picking has completed.  If picking was canceled, 'person' will be NULL.
    // Otherwise, person will be either a non-NULL resolved contact, or newly created and
    // saved contact, in both cases, person will be a valid contact in the Address Book.
    // It is up to the delegate to dismiss the view controller.
- (void)unknownPersonViewController:(ABUnknownPersonViewController *)unknownCardViewController didResolveToPerson:(ABRecordRef)person;

@end
