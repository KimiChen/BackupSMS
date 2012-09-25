/*
 *  ABPerson.h
 *  AddressBook
 *
 *  Copyright 2008 Apple, Inc. All rights reserved.
 *
 *  An ABPerson corresponds to a contact such as a person or organization.
 *
 */

#ifndef __ABPerson__
#define __ABPerson__

#include <CoreFoundation/CoreFoundation.h>

#include <AddressBook/ABAddressBook.h>
#include <AddressBook/ABRecord.h>

#if defined(__cplusplus)
extern "C" {
#endif

extern ABRecordRef ABPersonCreate(void);
extern ABPropertyType ABPersonGetTypeOfProperty(ABPropertyID property);
extern CFStringRef ABPersonCopyLocalizedPropertyName(ABPropertyID property);

typedef uint32_t ABPersonSortOrdering;
enum {
    kABPersonSortByFirstName = 0,
    kABPersonSortByLastName  = 1
};

extern ABPersonSortOrdering ABPersonGetSortOrdering(void);

typedef uint32_t ABPersonCompositeNameFormat;
enum  {
    kABPersonCompositeNameFormatFirstNameFirst = 0,
    kABPersonCompositeNameFormatLastNameFirst  = 1
};

extern ABPersonCompositeNameFormat ABPersonGetCompositeNameFormat(void);

// Images
extern bool ABPersonSetImageData(ABRecordRef person, CFDataRef imageData, CFErrorRef* error);
extern CFDataRef ABPersonCopyImageData(ABRecordRef person);
extern bool ABPersonHasImageData(ABRecordRef person);
extern bool ABPersonRemoveImageData(ABRecordRef person, CFErrorRef* error);

// Sorting
extern CFComparisonResult ABPersonComparePeopleByName(ABRecordRef person1, ABRecordRef person2, ABPersonSortOrdering ordering);

// Finding people
extern CFIndex ABAddressBookGetPersonCount(ABAddressBookRef addressBook);
extern ABRecordRef ABAddressBookGetPersonWithRecordID(ABAddressBookRef addressBook, ABRecordID recordID);
extern CFArrayRef ABAddressBookCopyArrayOfAllPeople(ABAddressBookRef addressBook);	
extern CFArrayRef ABAddressBookCopyPeopleWithName(ABAddressBookRef addressBook, CFStringRef name);

// Generic labels
extern const CFStringRef kABWorkLabel;
extern const CFStringRef kABHomeLabel;
extern const CFStringRef kABOtherLabel;

// Property keys
extern const ABPropertyID kABPersonFirstNameProperty;          // First name - kABStringPropertyType
extern const ABPropertyID kABPersonLastNameProperty;           // Last name - kABStringPropertyType
extern const ABPropertyID kABPersonMiddleNameProperty;         // Middle name - kABStringPropertyType
extern const ABPropertyID kABPersonPrefixProperty;             // Prefix ("Sir" "Duke" "General") - kABStringPropertyType
extern const ABPropertyID kABPersonSuffixProperty;             // Suffix ("Jr." "Sr." "III") - kABStringPropertyType
extern const ABPropertyID kABPersonNicknameProperty;           // Nickname - kABStringPropertyType
extern const ABPropertyID kABPersonFirstNamePhoneticProperty;  // First name Phonetic - kABStringPropertyType
extern const ABPropertyID kABPersonLastNamePhoneticProperty;   // Last name Phonetic - kABStringPropertyType
extern const ABPropertyID kABPersonMiddleNamePhoneticProperty; // Middle name Phonetic - kABStringPropertyType
extern const ABPropertyID kABPersonOrganizationProperty;       // Company name - kABStringPropertyType
extern const ABPropertyID kABPersonJobTitleProperty;           // Job Title - kABStringPropertyType
extern const ABPropertyID kABPersonDepartmentProperty;         // Department name - kABStringPropertyType
extern const ABPropertyID kABPersonEmailProperty;              // Email(s) - kABMultiStringPropertyType
extern const ABPropertyID kABPersonBirthdayProperty;           // Birthday associated with this person - kABDateTimePropertyType
extern const ABPropertyID kABPersonNoteProperty;               // Note - kABStringPropertyType
extern const ABPropertyID kABPersonCreationDateProperty;       // Creation Date (when first saved)
extern const ABPropertyID kABPersonModificationDateProperty;   // Last saved date

// Addresses
extern const ABPropertyID kABPersonAddressProperty;            // Street address - kABMultiDictionaryPropertyType
extern const CFStringRef kABPersonAddressStreetKey;
extern const CFStringRef kABPersonAddressCityKey;
extern const CFStringRef kABPersonAddressStateKey;
extern const CFStringRef kABPersonAddressZIPKey;
extern const CFStringRef kABPersonAddressCountryKey;
extern const CFStringRef kABPersonAddressCountryCodeKey;

/*
 * kABPersonAddressCountryCodeKey code must be one of the following:
 * iso country codes
 *
 *    ar = Argentina
 *    at = Austria
 *    au = Australia
 *    ba = Bosnia and Herzegovina
 *    be = Belgium
 *    bg = Bulgaria
 *    bh = Bahrain
 *    br = Brazil
 *    ca = Canada
 *    ch = Switzerland
 *    cn = China
 *    cz = Czech
 *    de = Germany
 *    dk = Denmark
 *    eg = Egypt
 *    es = Spain
 *    fi = Finland
 *    fr = France
 *    gr = Greece
 *    gl = Greenland
 *    hk = Hong Kong
 *    hr = Croatia
 *    hu = Hungary
 *    ie = Ireland
 *    il = Israel
 *    id = Indonesia
 *    in = India
 *    is = Iceland
 *    it = Italy
 *    jp = Japan
 *    jo = Jordan
 *    kr = South Korea
 *    kw = Kuwait
 *    lb = Lebanon
 *    lu = Luxembourg
 *    mk = Macedonia
 *    mx = Mexico
 *    nl = Netherlands
 *    no = Norway
 *    nz = New Zealand
 *    om = Oman
 *    pl = Poland
 *    pt = Portugal
 *    qa = Qatar
 *    ro = Romania
 *    ru = Russian Federation
 *    sa = Saudi Arabia
 *    se = Sweden
 *    sg = Singapore
 *    si = Slovenia
 *    sk = Slovakia
 *    sy = Syrian Arab Republic
 *    tw = Taiwan
 *    tr = Turkey
 *    ua = Ukraine
 *    uk = United Kingdom
 *    us = United States
 *    ye = Yemen
 *    za = South Africa
 *
 */

// Dates
extern const ABPropertyID kABPersonDateProperty;               // Dates associated with this person - kABMultiDatePropertyType
extern const CFStringRef kABPersonAnniversaryLabel;

// Kind
extern const ABPropertyID kABPersonKindProperty;               // Person/Organization - kABIntegerPropertyType
extern const CFNumberRef kABPersonKindPerson;
extern const CFNumberRef kABPersonKindOrganization;

// Phone numbers
extern const ABPropertyID kABPersonPhoneProperty;              // Generic phone number - kABMultiStringPropertyType
extern const CFStringRef kABPersonPhoneMobileLabel;
extern const CFStringRef kABPersonPhoneMainLabel;
extern const CFStringRef kABPersonPhoneHomeFAXLabel;
extern const CFStringRef kABPersonPhoneWorkFAXLabel;
extern const CFStringRef kABPersonPhonePagerLabel;

// IM
extern const ABPropertyID kABPersonInstantMessageProperty;     // Instant Messaging - kABMultiDictionaryPropertyType
extern const CFStringRef kABPersonInstantMessageServiceKey;     // Service ("Yahoo", "Jabber", etc.)
extern const CFStringRef kABPersonInstantMessageServiceYahoo;
extern const CFStringRef kABPersonInstantMessageServiceJabber;
extern const CFStringRef kABPersonInstantMessageServiceMSN;
extern const CFStringRef kABPersonInstantMessageServiceICQ;
extern const CFStringRef kABPersonInstantMessageServiceAIM;
extern const CFStringRef kABPersonInstantMessageUsernameKey;    // Username

// URLs
extern const ABPropertyID kABPersonURLProperty;                // URL - kABMultiStringPropertyType
extern const CFStringRef kABPersonHomePageLabel; // Home Page

// Related names
extern const ABPropertyID kABPersonRelatedNamesProperty;       // Names - kABMultiStringPropertyType
extern const CFStringRef kABPersonFatherLabel;    // Father
extern const CFStringRef kABPersonMotherLabel;    // Mother
extern const CFStringRef kABPersonParentLabel;    // Parent
extern const CFStringRef kABPersonBrotherLabel;   // Brother
extern const CFStringRef kABPersonSisterLabel;    // Sister
extern const CFStringRef kABPersonChildLabel;      // Child
extern const CFStringRef kABPersonFriendLabel;    // Friend
extern const CFStringRef kABPersonSpouseLabel;    // Spouse
extern const CFStringRef kABPersonPartnerLabel;   // Partner
extern const CFStringRef kABPersonAssistantLabel; // Assistant
extern const CFStringRef kABPersonManagerLabel;   // Manager
    
#if defined(__cplusplus)
}
#endif

#endif
