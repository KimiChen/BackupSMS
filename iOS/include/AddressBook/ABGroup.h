/*
 *  ABGroup.h
 *  AddressBook
 *
 *  Copyright 2008 Apple, Inc. All rights reserved.
 *
 *  An ABGroup is a non-ordered collection of records.
 *
 */

#ifndef __ABGroup__
#define __ABGroup__

#include <AddressBook/ABAddressBook.h>
#include <AddressBook/ABRecord.h>
#include <AddressBook/ABPerson.h>

#if defined(__cplusplus)
extern "C" {
#endif

extern const int kABGroupNameProperty;

extern ABRecordRef ABGroupCreate(void);
extern CFArrayRef ABGroupCopyArrayOfAllMembers(ABRecordRef group);
extern CFArrayRef ABGroupCopyArrayOfAllMembersWithSortOrdering(ABRecordRef group, ABPersonSortOrdering sortOrdering);
extern bool ABGroupAddMember(ABRecordRef group, ABRecordRef person, CFErrorRef* error);
extern bool ABGroupRemoveMember(ABRecordRef group, ABRecordRef member, CFErrorRef* error);

// Finding groups
extern ABRecordRef ABAddressBookGetGroupWithRecordID(ABAddressBookRef addressBook, ABRecordID recordID);
extern CFIndex ABAddressBookGetGroupCount(ABAddressBookRef addressBook);
extern CFArrayRef ABAddressBookCopyArrayOfAllGroups(ABAddressBookRef addressBook);

#if defined(__cplusplus)
}
#endif

#endif

