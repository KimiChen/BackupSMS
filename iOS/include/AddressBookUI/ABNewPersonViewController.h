//
//  ABNewPersonViewController.h
//  AddressBookUI
//
//  Copyright 2008 Apple Inc. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <AddressBook/AddressBook.h>

@protocol ABNewPersonViewControllerDelegate;

@interface ABNewPersonViewController : UIViewController
{
    @private
        id<ABNewPersonViewControllerDelegate> _newPersonViewDelegate;
        
        id                                    _parentGroup;
        
        id                                    _personView;
        id                                    _helper;
}

@property(nonatomic,assign)    id<ABNewPersonViewControllerDelegate> newPersonViewDelegate;

    // The Address Book to use. Any contact returned will be from this ABAddressBook instance.
    // If not set, a new ABAddressBook will be created the first time the property is accessed.
@property(nonatomic,readwrite) ABAddressBookRef                      addressBook;

    // Specify a displayedPerson to prefill some fields in the card. This is optional.
    // If displayedPerson has been added to an ABAddressBook, then the addressBook
    // property will be updated to use the displayedPerson's ABAddressBook.
@property(nonatomic,readwrite) ABRecordRef                           displayedPerson;
    // Specify a parentGroup the person should be added to when saved. This is optional.
@property(nonatomic,readwrite) ABRecordRef                           parentGroup;

@end

@protocol ABNewPersonViewControllerDelegate <NSObject>

    // Called when the user selects Save or Cancel. If the new person was saved, person will be
    // a valid person that was saved into the Address Book. Otherwise, person will be NULL.
    // It is up to the delegate to dismiss the view controller.
- (void)newPersonViewController:(ABNewPersonViewController *)newPersonView didCompleteWithNewPerson:(ABRecordRef)person;

@end
