//
//  MPVolumeView.h
//  MediaPlayer
//
//  Copyright 2008 Apple, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <MediaPlayer/MediaPlayerDefines.h>

MP_EXTERN_CLASS @interface MPVolumeView : UIView {
@package
    id _volumeSlider;
}

- (CGSize)sizeThatFits:(CGSize)size;

@end
