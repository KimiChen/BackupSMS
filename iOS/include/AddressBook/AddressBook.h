/*
 *  AddressBook.h
 *  AddressBook
 *
 *  Copyright (c) 2008 Apple, Inc. All rights reserved.
 *
 *  This library is not threadsafe. Recommended practice is to use
 *  a separate ABAddressBook instance on each thread in your
 *  application. You can register a callback on each instance
 *  that will be invoked when another instance in another thread
 *  or process makes changes to the shared Address Book database.
 *  
 *  Changes to records have no external effect until the ABAddressBook
 *  is saved. It is possible for other ABAddressBook instances to make
 *  conflicting changes during that time. To reduce the likelihood
 *  of that event, save the ABAddressBook as soon as possible after
 *  each set of related changes.
 *
 */

#ifndef __AddressBook__
#define __AddressBook__

#if defined(__cplusplus)
extern "C" {
#endif

#include <AddressBook/ABAddressBook.h>
#include <AddressBook/ABRecord.h>
#include <AddressBook/ABPerson.h>
#include <AddressBook/ABGroup.h>
#include <AddressBook/ABMultiValue.h>

#if defined(__cplusplus)
}
#endif

#endif


