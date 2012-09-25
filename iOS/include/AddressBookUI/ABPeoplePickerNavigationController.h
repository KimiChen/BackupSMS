//
//  ABPeoplePickerNavigationController.h
//  AddressBookUI
//
//  Copyright 2008 Apple Inc. All rights reserved.
//

#import <UIKit/UINavigationController.h>
#import <AddressBook/ABAddressBook.h>
#import <AddressBook/ABMultiValue.h>
#import <AddressBook/ABRecord.h>

@protocol ABPeoplePickerNavigationControllerDelegate;

@class ABModel;

    // The ABPeoplePickerNavigationController allows the user to select a person or value by presenting
    // the entire address book.
@interface ABPeoplePickerNavigationController : UINavigationController
{
    @private
        ABAddressBookRef        _addressBook;
        id                      _peoplePickerDelegate;
        
        ABModel                *_model;
        int                     _behavior;
        
        CFArrayRef              _displayedProperties;
        NSString               *_prompt;
        
        id                      _insertionValue;
        ABPropertyID            _insertionProperty;

        struct {
            unsigned            allowsEditing:1;
            unsigned            allowsCancel:1;
            unsigned            allowsActions:1;
        } _flags;
}

@property(nonatomic,assign)    id<ABPeoplePickerNavigationControllerDelegate>    peoplePickerDelegate;

    // An array of ABPropertyID listing the properties that should be visible when viewing a person.
    // If you are interested in one particular type of data (for example a phone number), displayedProperties
    // should be an array with a single NSNumber instance (representing kABPersonPhoneProperty).
    // Note that name information will always be shown if available.
@property(nonatomic,copy)      NSArray                                          *displayedProperties;

    // The Address Book to browse. All contacts returned will be from that ABAddressBook instance.
    // If not set, a new ABAddressBook will be created the first time the property is accessed.
@property(nonatomic,readwrite) ABAddressBookRef                                  addressBook;

@end

@protocol ABPeoplePickerNavigationControllerDelegate <NSObject>

    // Called after the user has pressed cancel
    // The delegate is responsible for dismissing the peoplePicker
- (void)peoplePickerNavigationControllerDidCancel:(ABPeoplePickerNavigationController *)peoplePicker;

    // Called after a person has been selected by the user.
    // Return YES if you want the person to be displayed.
    // Return NO  to do nothing (the delegate is responsible for dismissing the peoplePicker).
- (BOOL)peoplePickerNavigationController:(ABPeoplePickerNavigationController *)peoplePicker shouldContinueAfterSelectingPerson:(ABRecordRef)person;
    // Called after a value has been selected by the user.
    // Return YES if you want default action to be performed.
    // Return NO to do nothing (the delegate is responsible for dismissing the peoplePicker).
- (BOOL)peoplePickerNavigationController:(ABPeoplePickerNavigationController *)peoplePicker shouldContinueAfterSelectingPerson:(ABRecordRef)person property:(ABPropertyID)property identifier:(ABMultiValueIdentifier)identifier;

@end
