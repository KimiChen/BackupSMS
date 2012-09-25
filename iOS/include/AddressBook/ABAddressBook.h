/*
 *  ABAddressBook.h
 *  AddressBook
 *
 *  Copyright (c) 2008 Apple, Inc. All rights reserved.
 *
 */

#ifndef __ABAddressBook__
#define __ABAddressBook__

#include <CoreFoundation/CoreFoundation.h>
#include <AddressBook/ABRecord.h>

#if defined(__cplusplus)
extern "C" {
#endif

extern const CFStringRef ABAddressBookErrorDomain;

enum {
    kABOperationNotPermittedByStoreError = 0
};

typedef CFTypeRef ABAddressBookRef;

ABAddressBookRef ABAddressBookCreate(void);

extern bool ABAddressBookSave(ABAddressBookRef addressBook, CFErrorRef* error);
extern bool ABAddressBookHasUnsavedChanges(ABAddressBookRef addressBook);

extern bool ABAddressBookAddRecord(ABAddressBookRef addressBook, ABRecordRef record, CFErrorRef* error);
extern bool ABAddressBookRemoveRecord(ABAddressBookRef addressBook, ABRecordRef record, CFErrorRef* error);

// Some labels are special keys representing generic labels. Use this
// function to obtain a localized string for a label to display to a user.
extern CFStringRef ABAddressBookCopyLocalizedLabel(CFStringRef label);

// Register an external change callback if you want to be informed of
// changes to the shared Address Book database by other instances or
// processes.
// Only one callback and context pointer may be registered at a time.
// The callback will be invoked by CFRunLoop on the thread where it
// was registered.
// The ABAddressBook does not take any action by default to flush or
// synchronize cached state with the database. If you want to ensure
// that you don't see any stale values, use ABAddressBookRevert().

// The info argument may eventually contain information describing the
// change. Currently it will always be NULL.
typedef void (*ABExternalChangeCallback)(ABAddressBookRef addressBook, CFDictionaryRef info, void *context);

// Only one callback can be registered per ABAddressBook instance. 
// Registering a second callback without unregistering the current
// callback first is not supported.
extern void ABAddressBookRegisterExternalChangeCallback(ABAddressBookRef addressBook, ABExternalChangeCallback callback, void *context);
// when unregistering a callback both the callback and the context
// need to match the ones that were registered.
extern void ABAddressBookUnregisterExternalChangeCallback(ABAddressBookRef addressBook, ABExternalChangeCallback callback, void *context);

// ABAddressBookRevert() discards all cached properties and any
// unsaved changes so that records and properties retrieved subsequently
// will reflect any changes made by external ABAddressBook instances.
// If records were deleted externally, the corresponding ABRecord
// instances will return NULL for all properties. If necessary you can
// identify these deleted records by checking whether the class accessor
// (eg. ABPersonGetPersonWithRecordID()) returns the record.
void ABAddressBookRevert(ABAddressBookRef addressBook);

#if defined(__cplusplus)
}
#endif

#endif
