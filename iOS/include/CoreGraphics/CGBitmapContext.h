/* CoreGraphics - CGBitmapContext.h
 * Copyright (c) 2000-2008 Apple Inc.
 * All rights reserved. */

#ifndef CGBITMAPCONTEXT_H_
#define CGBITMAPCONTEXT_H_

#include <CoreGraphics/CGBase.h>
#include <CoreGraphics/CGContext.h>

/* Create a bitmap context. The context draws into a bitmap which is `width'
   pixels wide and `height' pixels high. The number of components for each
   pixel is specified by `colorspace', which may also specify a destination
   color profile. The number of bits for each component of a pixel is
   specified by `bitsPerComponent'. The number of bytes per pixel is equal
   to `(bitsPerComponent * number of components + 7)/8'. Each row of the
   bitmap consists of `bytesPerRow' bytes, which must be at least `width *
   bytes per pixel' bytes; in addition, `bytesPerRow' must be an integer
   multiple of the number of bytes per pixel. `data' points a block of
   memory at least `bytesPerRow * height' bytes. `bitmapInfo' specifies
   whether the bitmap should contain an alpha channel and how it's to be
   generated, along with whether the components are floating-point or
   integer. */

CG_EXTERN CGContextRef CGBitmapContextCreate(void *data, size_t width,
    size_t height, size_t bitsPerComponent, size_t bytesPerRow,
    CGColorSpaceRef colorspace, CGBitmapInfo bitmapInfo)
    CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Return the data associated with the bitmap context `c', or NULL if `c' is
   not a bitmap context. */

CG_EXTERN void *CGBitmapContextGetData(CGContextRef c)
    CG_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_2_0);

/* Return the width of the bitmap context `c', or 0 if `c' is not a bitmap
   context. */

CG_EXTERN size_t CGBitmapContextGetWidth(CGContextRef c)
    CG_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_2_0);

/* Return the height of the bitmap context `c', or 0 if `c' is not a bitmap
   context. */

CG_EXTERN size_t CGBitmapContextGetHeight(CGContextRef c)
    CG_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_2_0);

/* Return the bits per component of the bitmap context `c', or 0 if `c' is
   not a bitmap context. */

CG_EXTERN size_t CGBitmapContextGetBitsPerComponent(CGContextRef c)
    CG_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_2_0);

/* Return the bits per pixel of the bitmap context `c', or 0 if `c' is not a
   bitmap context. */

CG_EXTERN size_t CGBitmapContextGetBitsPerPixel(CGContextRef c)
    CG_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_2_0);

/* Return the bytes per row of the bitmap context `c', or 0 if `c' is not a
   bitmap context. */

CG_EXTERN size_t CGBitmapContextGetBytesPerRow(CGContextRef c)
    CG_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_2_0);

/* Return the colorspace of the bitmap context `c', or NULL if `c' is not a
   bitmap context. */

CG_EXTERN CGColorSpaceRef CGBitmapContextGetColorSpace(CGContextRef c)
    CG_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_2_0);

/* Return the alpha info of the bitmap context `c', or kCGImageAlphaNone if
   `c' is not a bitmap context. */

CG_EXTERN CGImageAlphaInfo CGBitmapContextGetAlphaInfo(CGContextRef c)
    CG_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_2_0);

/* Return the bitmap info of the bitmap context `c', or 0 if `c' is not a
   bitmap context. */

CG_EXTERN CGBitmapInfo CGBitmapContextGetBitmapInfo(CGContextRef c)
    CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_2_0);

/* Return an image containing a snapshot of the bitmap context `c'. If
   context is not a bitmap context, or if the image cannot be created for
   any reason, this function returns NULL. This is a "copy" operation ---
   subsequent changes to context will not affect the contents of the
   returned image.

   Note that in some cases the copy will actually follow "copy-on-write"
   semantics, so that the actual physical copy of the bits will only occur
   if the underlying data in the bitmap context is modified. As a
   consequence, you may wish to use the resulting image and release it
   before performing more drawing into the bitmap context; in this way, the
   actual physical copy of the data may be avoided. */

CG_EXTERN CGImageRef CGBitmapContextCreateImage(CGContextRef c)
    CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_2_0);

#endif	/* CGBITMAPCONTEXT_H_ */
