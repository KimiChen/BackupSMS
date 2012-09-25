/*	NSNotification.h
	Copyright (c) 1994-2007, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>

@class NSString, NSDictionary;

/****************	Notifications	****************/

@interface NSNotification : NSObject <NSCopying, NSCoding>

- (NSString *)name;
- (id)object;
- (NSDictionary *)userInfo;

@end

@interface NSNotification (NSNotificationCreation)

+ (id)notificationWithName:(NSString *)aName object:(id)anObject;
+ (id)notificationWithName:(NSString *)aName object:(id)anObject userInfo:(NSDictionary *)aUserInfo;

@end

/****************	Notification Center	****************/

@interface NSNotificationCenter : NSObject {
    @protected
    void * __strong _impl;
    void *_callback_block[4];
    void *_pad[8];
}

+ (id)defaultCenter;
    
- (void)addObserver:(id)observer selector:(SEL)aSelector name:(NSString *)aName object:(id)anObject;

- (void)postNotification:(NSNotification *)notification;
- (void)postNotificationName:(NSString *)aName object:(id)anObject;
- (void)postNotificationName:(NSString *)aName object:(id)anObject userInfo:(NSDictionary *)aUserInfo;

- (void)removeObserver:(id)observer;
- (void)removeObserver:(id)observer name:(NSString *)aName object:(id)anObject;

@end

