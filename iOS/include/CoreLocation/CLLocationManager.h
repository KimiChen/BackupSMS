
/*
 *  CLLocationManager.h
 *  CoreLocation
 *
 *  Copyright 2008 Apple Computer, Inc. All rights reserved.
 *
 */

#import <Foundation/Foundation.h>

@class CLLocation;
@protocol CLLocationManagerDelegate;


/*
 *  CLLocationManager
 *  
 *  Discussion:
 *    The CLLocationManager object is your entry point to the location service.
 */
@interface CLLocationManager : NSObject
{
@private
	id _internal;
}

@property(assign, nonatomic) id<CLLocationManagerDelegate> delegate;

/*
 *  locationServicesEnabled
 *  
 *  Discussion:
 *      Determines whether the user has location services enabled on the device (Settings -> General -> LocationServices).
 *      If NO, and you proceed to call other CoreLocation API, user will be prompted with the confirmation
 *      dialog. You may want to check this property and use location services only when explicitly requested by the user.
 */
@property(readonly, nonatomic) BOOL locationServicesEnabled;

/*
 *  distanceFilter
 *  
 *  Discussion:
 *      Specifies the minimum update distance in meters. Client will not be notified of movements of less 
 *      than the stated value, unless the accuracy has improved. Pass in kCLDistanceFilterNone to be 
 *      notified of all movements. By default, kCLDistanceFilterNone is used.
 */
@property(assign, nonatomic) CLLocationDistance distanceFilter;

/*
 *  desiredAccuracy
 *  
 *  Discussion:
 *      The desired location accuracy. The location service will try its best to achieve
 *      your desired accuracy. However, it is not guaranteed. To optimize
 *      power performence, be sure to specify an appropriate accuracy for your usage scenario (eg,
 *      use a large accuracy value when only a coarse location is needed). Use kCLLocationAccuracyBest to
 *      achieve the best possible accuracy. By default, kCLLocationAccuracyBest is used.
 */
@property(assign, nonatomic) CLLocationAccuracy desiredAccuracy;

/*
 *  lastLocation
 *  
 *  Discussion:
 *      The last location received. Will be nil until a location has been received.
 */
@property(readonly, nonatomic) CLLocation *location;

/*
 *  startUpdatingLocation
 *  
 *  Discussion:
 *      Start updating locations.
 */
- (void)startUpdatingLocation;

/*
 *  stopUpdatingLocation
 *  
 *  Discussion:
 *      Stop updating locations.
 */
- (void)stopUpdatingLocation;

@end
