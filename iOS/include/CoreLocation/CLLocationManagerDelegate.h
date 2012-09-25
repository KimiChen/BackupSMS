
/*
 *  CLLocationManagerDelegate.h
 *  CoreLocation
 *
 *  Copyright 2008 Apple Computer, Inc. All rights reserved.
 *
 */

#import <Foundation/Foundation.h>

@class CLLocation;
@class CLLocationManager;


/*
 *  CLLocationManagerDelegate
 *  
 *  Discussion:
 *    Delegate for CLLocationManager.
 */
@protocol CLLocationManagerDelegate<NSObject>

@optional

/*
 *  locationManager:updatedLocation:
 *  
 *  Discussion:
 *    Invoked when a new location is available. oldLocation may be nil if there is no previous location
 *    available.
 */
- (void)locationManager:(CLLocationManager *)manager
	didUpdateToLocation:(CLLocation *)newLocation
	fromLocation:(CLLocation *)oldLocation;

/*
 *  locationManager:failedWithError:
 *  
 *  Discussion:
 *    Invoked when an error has occurred.
 */
- (void)locationManager:(CLLocationManager *)manager
	didFailWithError:(NSError *)error;

@end
