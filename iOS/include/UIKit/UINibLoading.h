//
//  UINibLoading.h
//  UIKit
//
//  Copyright 2005-2008 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKitDefines.h>

UIKIT_EXTERN NSString * const UINibProxiedObjectsKey;

@interface NSBundle(UINibLoadingAdditions)
- (NSArray *)loadNibNamed:(NSString *)name owner:(id)owner options:(NSDictionary *)options;
@end

@interface NSObject(UINibLoadingAdditions)
- (void)awakeFromNib;
@end
