//
//  UITextInputTraits.h
//  UIKit
//
//  Copyright 2006-2008 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

//
// UITextAutocapitalizationType
//
// Controls autocapitalization behavior for a text widget.
// Note: Capitalization does not apply in all script systems. In such
// cases, these values are ignored by the keyboard/input method implementation.
//
typedef enum {
    UITextAutocapitalizationTypeNone,
    UITextAutocapitalizationTypeWords,
    UITextAutocapitalizationTypeSentences,
    UITextAutocapitalizationTypeAllCharacters,
} UITextAutocapitalizationType;

//
// UITextAutocorrectionType
//
// Controls keyboard autocorrection behavior for a text widget.
// Note: Some input methods do not support inline autocorrection, and 
// instead use a conversion and/or candidate selection methodology. In such
// cases, these values are ignored by the keyboard/input method implementation.
//
typedef enum {
    UITextAutocorrectionTypeDefault,
    UITextAutocorrectionTypeNo,
    UITextAutocorrectionTypeYes,
} UITextAutocorrectionType;

//
// UIKeyboardType
//
// Requests that a particular keyboard type be displayed when a text widget
// becomes first responder. 
// Note: Some keyboard/input methods types may not support every variant. 
// In such cases, the input method will make a best effort to find a close 
// match to the requested type (e.g. displaying UIKeyboardTypeNumbersAndPunctuation 
// type if UIKeyboardTypeNumberPad is not supported).
//
typedef enum {
    UIKeyboardTypeDefault,                // Default type for the current input method.
    UIKeyboardTypeASCIICapable,           // Displays a keyboard which can enter ASCII characters.
    UIKeyboardTypeNumbersAndPunctuation,  // Numbers and assorted punctuation.
    UIKeyboardTypeURL,                    // A type optimized for URL entry (shows . / .com prominently).
    UIKeyboardTypeNumberPad,              // A number pad (0-9). Suitable for PIN entry.
    UIKeyboardTypePhonePad,               // A phone pad (1-9, *, 0, #, with letters under the numbers).
    UIKeyboardTypeNamePhonePad,           // A type optimized for entering a person's name or phone number.
    UIKeyboardTypeEmailAddress,           // A type optimized for multiple email address entry (shows space @ . prominently).

    UIKeyboardTypeAlphabet = UIKeyboardTypeASCIICapable, // Deprecated

} UIKeyboardType;

//
// UIKeyboardAppearance
//
// Requests a keyboard appearance be used when a text widget
// becomes first responder.. 
// Note: Some keyboard/input methods types may not support every variant. 
// In such cases, the input method will make a best effort to find a close 
// match to the requested type.
//
typedef enum {
    UIKeyboardAppearanceDefault,          // Default apperance for the current input method.
    UIKeyboardAppearanceAlert,            // Appearance suitable for use in "alert" scenarios.
} UIKeyboardAppearance;

//
// UIReturnKeyType
//
// Controls the display of the return key. 
//
// Note: This enum is under discussion and may be replaced with a 
// different implementation.
//
typedef enum {
    UIReturnKeyDefault,
    UIReturnKeyGo,
    UIReturnKeyGoogle,
    UIReturnKeyJoin,
    UIReturnKeyNext,
    UIReturnKeyRoute,
    UIReturnKeySearch,
    UIReturnKeySend,
    UIReturnKeyYahoo,
    UIReturnKeyDone,
    UIReturnKeyEmergencyCall,
} UIReturnKeyType;

//
// UITextInputTraits
//
// Controls features of text widgets (or other custom objects that might wish 
// to respond to keyboard input).
//
@protocol UITextInputTraits <NSObject>

@optional

@property(nonatomic) UITextAutocapitalizationType autocapitalizationType; // default is UITextAutocapitalizationTypeNone
@property(nonatomic) UITextAutocorrectionType autocorrectionType;         // default is UITextAutocorrectionTypeDefault
@property(nonatomic) UIKeyboardType keyboardType;                         // default is UIKeyboardTypeDefault
@property(nonatomic) UIKeyboardAppearance keyboardAppearance;             // default is UIKeyboardAppearanceDefault
@property(nonatomic) UIReturnKeyType returnKeyType;                       // default is UIReturnKeyDefault (See note under UIReturnKeyType enum)
@property(nonatomic) BOOL enablesReturnKeyAutomatically;                  // default is NO (when YES, will automatically disable return key when text widget has zero-length contents, and will automatically enable when text widget has non-zero-length contents)
@property(nonatomic,getter=isSecureTextEntry) BOOL secureTextEntry;      // default is NO

@end

