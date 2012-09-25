//
//  UIAccelerometer.h
//  UIKit
//
//  Copyright 2007-2008 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKitDefines.h>

typedef double UIAccelerationValue;

@protocol UIAccelerometerDelegate;

UIKIT_EXTERN_CLASS @interface UIAcceleration : NSObject {
  @private
    NSTimeInterval timestamp;
    UIAccelerationValue x, y, z;
}

@property(nonatomic,readonly) NSTimeInterval timestamp;
@property(nonatomic,readonly) UIAccelerationValue x;
@property(nonatomic,readonly) UIAccelerationValue y;
@property(nonatomic,readonly) UIAccelerationValue z;

@end

UIKIT_EXTERN_CLASS @interface UIAccelerometer : NSObject {
  @private
    NSTimeInterval               _updateInterval;
    id <UIAccelerometerDelegate> _delegate;
    struct {
        unsigned int delegateDidAccelerate:1;
        unsigned int reserved:31;
    } _accelerometerFlags;
}

+ (UIAccelerometer *)sharedAccelerometer;

@property(nonatomic) NSTimeInterval updateInterval; //May be capped at a minimum interval
@property(nonatomic,assign) id<UIAccelerometerDelegate> delegate;

@end

@protocol UIAccelerometerDelegate<NSObject>
@optional

- (void)accelerometer:(UIAccelerometer *)accelerometer didAccelerate:(UIAcceleration *)acceleration;

@end
