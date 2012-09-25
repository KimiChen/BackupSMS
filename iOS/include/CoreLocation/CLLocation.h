
/*
 *  CLLocation.h
 *  CoreLocation
 *
 *  Copyright 2008 Apple Computer, Inc. All rights reserved.
 *
 */

#import <Foundation/Foundation.h>


/*
 *  CLLocationDegrees
 *  
 *  Discussion:
 *    Type used to represent a latitude or longitude coordinate in degrees under the WGS 84 reference
 *    frame. The degree can be positive (North and East) or negative (South and West).  
 */
typedef double CLLocationDegrees;

/*
 *  CLLocationAccuracy
 *  
 *  Discussion:
 *    Type used to represent a location accuracy level in meters. The lower the value in meters, the
 *    more physically precise the location is. A negative accuracy value indicates an invalid location.
 */
typedef double CLLocationAccuracy;

/*
 *  CLLocationCoordinate2D
 *  
 *  Discussion:
 *    A structure that contains a geographical coordinate.
 *
 *  Fields:
 *    latitude:
 *      The latitude in degrees.
 *    longitude:
 *      The longitude in degrees.
 */
typedef struct {
	CLLocationDegrees latitude;
	CLLocationDegrees longitude;
} CLLocationCoordinate2D;

/*
 *  CLLocationDistance
 *  
 *  Discussion:
 *    Type used to represent a distance in meters.
 */
typedef double CLLocationDistance;

/*
 *  kCLDistanceFilterNone
 *  
 *  Discussion:
 *    Use as the distanceFilter property for CLLocationManager. This indicates 
 *    to the location service that no minimum movement filter is desired - ie, client will be informed
 *    of any movement.
 */
extern const CLLocationDistance kCLDistanceFilterNone;

/*
 *  kCLLocationAccuracy<x>
 *  
 *  Discussion:
 *    Used to specify the accuracy level desired. The location service will try its best to achieve
 *    your desired accuracy. However, it is not guaranteed. To optimize
 *    power performance, be sure to specify an appropriate accuracy for your usage scenario (eg,
 *    use a large accuracy value when only a coarse location is needed).
 */
extern const CLLocationAccuracy kCLLocationAccuracyBest;
extern const CLLocationAccuracy kCLLocationAccuracyNearestTenMeters;
extern const CLLocationAccuracy kCLLocationAccuracyHundredMeters;
extern const CLLocationAccuracy kCLLocationAccuracyKilometer;
extern const CLLocationAccuracy kCLLocationAccuracyThreeKilometers;


/*
 *  CLLocation
 *  
 *  Discussion:
 *    Represents a geographical coordinate along with accuracy and timestamp information.
 */
@interface CLLocation : NSObject <NSCopying, NSCoding>
{
@private
	id _internal;
}

/*
 *  coordinate
 *  
 *  Discussion:
 *    Returns the coordinate of the current location.
 */
@property(readonly, nonatomic) CLLocationCoordinate2D coordinate;

/*
 *  altitude
 *  
 *  Discussion:
 *    Returns the altitude of the location. Can be positive (above sea level) or negative (below sea level).
 */
@property(readonly, nonatomic) CLLocationDistance altitude;

/*
 *  horizontalAccuracy
 *  
 *  Discussion:
 *    Returns the horizontal accuracy of the location. Negative if the lateral location is invalid.
 */
@property(readonly, nonatomic) CLLocationAccuracy horizontalAccuracy;

/*
 *  verticalAccuracy
 *  
 *  Discussion:
 *    Returns the vertical accuracy of the location. Negative if the altitude is invalid.
 */
@property(readonly, nonatomic) CLLocationAccuracy verticalAccuracy;

/*
 *  timestamp
 *  
 *  Discussion:
 *    Returns the timestamp when this location was determined.
 */
@property(readonly, nonatomic) NSDate *timestamp;

/*
 *  initWithLatitude:longitude:
 *  
 *  Discussion:
 *    Initialize with the specified latitude and longitude.
 */
- (id)initWithLatitude:(CLLocationDegrees)latitude
	longitude:(CLLocationDegrees)longitude;

/*
 *  initWithCoordinate:altitude:horizontalAccuracy:verticalAccuracy:timestamp:
 *  
 *  Discussion:
 *    Initialize with the specified parameters.
 */
- (id)initWithCoordinate:(CLLocationCoordinate2D)coordinate
	altitude:(CLLocationDistance)altitude
	horizontalAccuracy:(CLLocationAccuracy)hAccuracy
	verticalAccuracy:(CLLocationAccuracy)vAccuracy
	timestamp:(NSDate *)timestamp;

/*
 *  description
 *  
 *  Discussion:
 *    Returns a string representation of the location.
 */
- (NSString *)description;

/*
 *  getDistanceFrom:
 *
 *  Discussion:
 *    Returns the lateral distance between two locations.
 */
- (CLLocationDistance)getDistanceFrom:(const CLLocation *)location;

@end
