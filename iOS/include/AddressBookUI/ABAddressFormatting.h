//
//  ABAddressFormatting.h
//  AddressBookUI
//
//  Copyright 2008 Apple Inc. All rights reserved.
//

#import <AddressBook/AddressBook.h>

#if defined(__cplusplus)
extern "C" {
#endif    

    // address: an address dictionary obtained representing the address (kABAddressProperty) of a person (ABRecordRef)
    // addCountryName: whether to always include the country name in the address string, regardless of whether it is specified
    //                 in the dictionary. If not specified by the user a localized country name will be added.
    // returns a formatted string that contains the full address. The string is likely to contain line endings.
NSString *ABCreateStringWithAddressDictionary(NSDictionary *address, BOOL addCountryName);

#if defined(__cplusplus)
}
#endif
