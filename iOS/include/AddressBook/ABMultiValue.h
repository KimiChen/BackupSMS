/*
 *  ABMultiValue.h
 *  AddressBook
 *
 *  Copyright 2008 Apple, Inc. All rights reserved.
 *
 *  MultiValues are ordered, homogeneous collections of values. Each
 *  value has a unique persistent identifier which can be use to
 *  identify the value across changes to the MultiValue (ie. when
 *  the value's index may have changed). Each value may also have a
 *  non-unique string label.
 *
 */

#ifndef __ABMultiValue__
#define __ABMultiValue__

#include <CoreFoundation/CoreFoundation.h>
#include <AddressBook/ABRecord.h>

#if defined(__cplusplus)
extern "C" {
#endif

typedef CFTypeRef ABMultiValueRef;

typedef int32_t ABMultiValueIdentifier;
#define kABMultiValueInvalidIdentifier -1

// Type of the contained values
extern ABPropertyType ABMultiValueGetPropertyType(ABMultiValueRef multiValue);

extern CFIndex ABMultiValueGetCount(ABMultiValueRef multiValue);

extern CFTypeRef ABMultiValueCopyValueAtIndex(ABMultiValueRef multiValue, CFIndex index);
extern CFArrayRef ABMultiValueCopyArrayOfAllValues(ABMultiValueRef multiValue);

extern CFStringRef ABMultiValueCopyLabelAtIndex(ABMultiValueRef multiValue, CFIndex index);
    
extern CFIndex ABMultiValueGetIndexForIdentifier(ABMultiValueRef multiValue, ABMultiValueIdentifier identifier);
extern ABMultiValueIdentifier ABMultiValueGetIdentifierAtIndex(ABMultiValueRef multiValue, CFIndex index);
    
extern CFIndex ABMultiValueGetFirstIndexOfValue(ABMultiValueRef multiValue, CFTypeRef value);

// Mutable multivalues

typedef CFTypeRef ABMutableMultiValueRef;

extern ABMutableMultiValueRef ABMultiValueCreateMutable(ABPropertyType type);
extern ABMutableMultiValueRef ABMultiValueCreateMutableCopy(ABMultiValueRef multiValue);
 
extern bool ABMultiValueAddValueAndLabel(ABMutableMultiValueRef multiValue, CFTypeRef value, CFStringRef label, ABMultiValueIdentifier *outIdentifier);
extern bool ABMultiValueInsertValueAndLabelAtIndex(ABMutableMultiValueRef multiValue, CFTypeRef value, CFStringRef label, CFIndex index, ABMultiValueIdentifier *outIdentifier);
extern bool ABMultiValueRemoveValueAndLabelAtIndex(ABMutableMultiValueRef multiValue, CFIndex index);
extern bool ABMultiValueReplaceValueAtIndex(ABMutableMultiValueRef multiValue, CFTypeRef value, CFIndex index);
extern bool ABMultiValueReplaceLabelAtIndex(ABMutableMultiValueRef multiValue, CFStringRef label, CFIndex index);
    
#if defined(__cplusplus)
}
#endif

#endif

