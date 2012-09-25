//
//  UIImage.h
//  UIKit
//
//  Copyright 2005-2008 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UIColor.h>

typedef enum {
    UIImageOrientationUp,            // default orientation
    UIImageOrientationDown,          // 180 deg rotation
    UIImageOrientationLeft,          // 90 deg CCW
    UIImageOrientationRight,         // 90 deg CW
    UIImageOrientationUpMirrored,    // as above but image mirrored along other axis. horizontal flip
    UIImageOrientationDownMirrored,  // horizontal flip
    UIImageOrientationLeftMirrored,  // vertical flip
    UIImageOrientationRightMirrored, // vertical flip
} UIImageOrientation;

UIKIT_EXTERN_CLASS @interface UIImage : NSObject {
  @package
    CFTypeRef _imageRef;
    struct {
	unsigned int named:1;
	unsigned int imageOrientation:3;
	unsigned int cached:1;
	unsigned int stretchable:1;
    } _imageFlags;
}

+ (UIImage *)imageNamed:(NSString *)name;      // load from main bundle

+ (UIImage *)imageWithContentsOfFile:(NSString *)path;
+ (UIImage *)imageWithData:(NSData *)data;
+ (UIImage *)imageWithCGImage:(CGImageRef)imageRef;

- (id)initWithContentsOfFile:(NSString *)path;
- (id)initWithData:(NSData *)data;
- (id)initWithCGImage:(CGImageRef)imageRef;

@property(nonatomic,readonly) CGSize             size;             // reflects orientation setting. size is in pixels
@property(nonatomic,readonly) CGImageRef         CGImage;          // returns underlying CGImageRef
@property(nonatomic,readonly) UIImageOrientation imageOrientation; // this will affect how the image is composited

// the these draw the image 'right side up' in the usual coordinate system with 'point' being the top-left.

- (void)drawAtPoint:(CGPoint)point;                                                        // mode = kCGBlendModeNormal, alpha = 1.0
- (void)drawAtPoint:(CGPoint)point blendMode:(CGBlendMode)blendMode alpha:(CGFloat)alpha;
- (void)drawInRect:(CGRect)rect;                                                           // mode = kCGBlendModeNormal, alpha = 1.0
- (void)drawInRect:(CGRect)rect blendMode:(CGBlendMode)blendMode alpha:(CGFloat)alpha;

- (void)drawAsPatternInRect:(CGRect)rect; // draws the image as a CGPattern

// create a custom image that is stretchable. Note that this might return a new instance of a different class

- (UIImage *)stretchableImageWithLeftCapWidth:(NSInteger)leftCapWidth topCapHeight:(NSInteger)topCapHeight;
@property(nonatomic,readonly) NSInteger leftCapWidth;   // default is 0. if non-zero, horiz. stretchable. right cap is calculated as width - leftCapWidth - 1
@property(nonatomic,readonly) NSInteger topCapHeight;   // default is 0. if non-zero, vert. stretchable. bottom cap is calculated as height - topCapWidth - 1

@end

UIKIT_EXTERN NSData *UIImagePNGRepresentation(UIImage *image);                               // return image as PNG. May return nil if image has no CGImageRef or invalid bitmap format
UIKIT_EXTERN NSData *UIImageJPEGRepresentation(UIImage *image, CGFloat compressionQuality);  // return image as JPEG. May return nil if image has no CGImageRef or invalid bitmap format. compression is 0(most)..1(least)
