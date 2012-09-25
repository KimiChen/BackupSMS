
/*
 *  CLError.h
 *  CoreLocation
 *
 *  Copyright 2008 Apple Computer, Inc. All rights reserved.
 *
 */

#import <Foundation/Foundation.h>


/*
 *  kCLErrorDomain
 *  
 *  Discussion:
 *    Error returned as the domain to NSError from CoreLocation.
 */
extern NSString *const kCLErrorDomain;

/*
 *  CLError
 *  
 *  Discussion:
 *    Error returned as code to NSError from CoreLocation.
 */
typedef enum {
	kCLErrorLocationUnknown  = 0, // location is currently unknown, but CL will keep trying
	kCLErrorDenied // CL access has been denied (eg, user declined location use)
} CLError;
