//
//  UIScrollView.h
//  UIKit
//
//  Copyright 2007-2008 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <UIKit/UIView.h>
#import <UIKit/UIGeometry.h>
#import <UIKit/UIKitDefines.h>

typedef enum {
    UIScrollViewIndicatorStyleDefault,     // black with white border. good against any background
    UIScrollViewIndicatorStyleBlack,       // black only. smaller. good against a white background
    UIScrollViewIndicatorStyleWhite        // white only. smaller. good against a black background
} UIScrollViewIndicatorStyle;

@class UIEvent, UIImageView;
@protocol UIScrollViewDelegate;

UIKIT_EXTERN_CLASS @interface UIScrollView : UIView <NSCoding> {
  @package
    CGSize       _contentSize;
    UIEdgeInsets _contentInset;
    id           _delegate;
    UIImageView* _verticalScrollIndicator;
    UIImageView* _horizontalScrollIndicator;
    UIEdgeInsets _scrollIndicatorInset;
    struct {
        unsigned int tracking:1;
        unsigned int dragging:1;
        unsigned int bounceEnabled:1;
	unsigned int bouncesZoom:1;
	unsigned int zoomBouncing:1;
	unsigned int alwaysBounceHorizontal:1;
	unsigned int alwaysBounceVertical:1;
	unsigned int canCancelContentTouches:1;
	unsigned int delaysContentTouches:1;
        unsigned int scrollDisabled:1;
        unsigned int scrollTriggered:1;
        unsigned int scrollDisabledOnTouchBegan:1;
        unsigned int ignoreNextTouchesMoved:1;
        unsigned int cancelNextContentTouchEnded:1;
        unsigned int inContentViewCall:1;
        unsigned int dontSelect:1;
        unsigned int contentTouched:1;
	unsigned int cantCancel:1;
        unsigned int directionalLockEnabled:1;	
        unsigned int lockVertical:1;
        unsigned int lockHorizontal:1;
        unsigned int keepLocked:1;	
        unsigned int showsHorizontalScrollIndicator:1;
        unsigned int showsVerticalScrollIndicator:1;
        unsigned int indicatorStyle:2;
        unsigned int inZoom:1;
        unsigned int hideIndicatorsInZoom:1;
        unsigned int pushedTrackingMode:1;
        unsigned int multipleDrag:1;
        unsigned int displayingScrollIndicators:1;
        unsigned int verticalIndicatorShrunk:1;
        unsigned int horizontalIndicatorShrunk:1;
        unsigned int contentFitDisableScrolling:1;
	unsigned int pagingEnabled:1;
	unsigned int dontScrollToTop:1;
	unsigned int scrollingToTop:1;
    } _scrollViewFlags;
    CGFloat           _farthestDistance;
    CGPoint           _initialTouchPosition;
    CGPoint           _startTouchPosition;
    CFTimeInterval    _startTouchTime;
    CGPoint           _startOffset;
    CGPoint           _lastTouchPosition;
    CFTimeInterval    _lastTouchTime;
    CFTimeInterval    _lastUpdateTime;
    CGPoint           _lastUpdateOffset;
    UIView           *_contentView;
    float             _minimumZoomScale;
    float             _maximumZoomScale;
    UIView           *_zoomView;
    double            _horizontalVelocity;
    double            _verticalVelocity;
    double            _previousHorizontalVelocity;
    double            _previousVerticalVelocity;
    CGPoint           _stopOffset;
    CFTypeRef         _scrollHeartbeat;
    CGSize            _decelerationFactor;
    double            _decelerationLnFactorH;
    double            _decelerationLnFactorV;
    NSArray*          _deferredBeginTouchesInfo;
    UIImageView     **_shadows;
    id                _scrollNotificationViews;
    CGSize            _gridBounceLnFactor;
    CFTimeInterval    _contentOffsetAnimationDuration;
}

@property(nonatomic)         CGPoint                      contentOffset;                  // default CGPointZero
@property(nonatomic)         CGSize                       contentSize;                    // default CGSizeZero
@property(nonatomic)         UIEdgeInsets                 contentInset;                   // default UIEdgeInsetsZero. add additional scroll area around content
@property(nonatomic,assign) id<UIScrollViewDelegate>      delegate;                       // default nil. weak reference
@property(nonatomic,getter=isDirectionalLockEnabled) BOOL directionalLockEnabled;         // default NO. if YES, try to lock vertical or horizontal scrolling while dragging
@property(nonatomic)         BOOL                         bounces;                        // default YES. if YES, bounces past edge of content and back again
@property(nonatomic)         BOOL                         alwaysBounceVertical;           // default NO. if YES and bounces is YES, even if content is smaller than bounds, allow drag vertically
@property(nonatomic)         BOOL                         alwaysBounceHorizontal;         // default NO. if YES and bounces is YES, even if content is smaller than bounds, allow drag horizontally
@property(nonatomic,getter=isPagingEnabled) BOOL          pagingEnabled;                  // default NO. if YES, stop on multiples of view bounds
@property(nonatomic,getter=isScrollEnabled) BOOL          scrollEnabled;                  // default YES. turn off any dragging temporarily
@property(nonatomic)         BOOL                         showsHorizontalScrollIndicator; // default YES. show indicator while we are tracking. fades out after tracking
@property(nonatomic)         BOOL                         showsVerticalScrollIndicator;   // default YES. show indicator while we are tracking. fades out after tracking
@property(nonatomic)         UIEdgeInsets                 scrollIndicatorInsets;          // default is UIEdgeInsetsZero. adjust indicators inside of insets
@property(nonatomic)         UIScrollViewIndicatorStyle   indicatorStyle;                 // default is UIScrollViewIndicatorStyleDefault

- (void)setContentOffset:(CGPoint)contentOffset animated:(BOOL)animated;  // animate at constant velocity to new offset
- (void)scrollRectToVisible:(CGRect)rect animated:(BOOL)animated;         // scroll so rect is just visible (nearest edges). nothing if rect completely visible

- (void)flashScrollIndicators;             // displays the scroll indicators for a short time. This should be done whenever you bring the scroll view to front.

/*
 Scrolling with no scroll bars is a bit complex. on touch down, we don't know if the user will want to scroll or track a subview like a control so we need to intercept the touch
 events temporarily. on touch down, we start a timer and also look at any movement. if the time elapses without sufficient change in position, we start sending events to
 the hit view in the content subview. if the user then drags far enough, we switch back to dragging and cancel any tracking in the subview.
 the methods below are called by the scroll view and give subclasses override points to add in custom behaviour.
 you can remove the delay by setting delaysContentTouches to NO.
 */

@property(nonatomic,readonly,getter=isTracking)     BOOL tracking;        // returns YES if user has touched. may not yet have started dragging
@property(nonatomic,readonly,getter=isDragging)     BOOL dragging;        // returns YES if user has started scrolling. this may require some time and or distance to move to initiate dragging
@property(nonatomic,readonly,getter=isDecelerating) BOOL decelerating;    // returns YES if user isn't dragging (touch up) but scroll view is still moving

@property(nonatomic) BOOL delaysContentTouches;       // default is YES. if NO, we immediately call -touchesShouldBegin:withEvent:inContentView:
@property(nonatomic) BOOL canCancelContentTouches;    // default is YES. if NO, then once we start tracking, we don't try to drag if the touch moves

// override points. default is to call touch methods on the content subview. if -touchesShouldCancelInContentView: returns NO in order to start dragging after we have started tracking the content view, we don't drag and continue to feed events to the content subview. if -touchesShouldBegin:withEvent:inContentView: returns NO, we don't send events even if we don't drag

- (BOOL)touchesShouldBegin:(NSSet *)touches withEvent:(UIEvent *)event inContentView:(UIView *)view;   // default returns YES
- (BOOL)touchesShouldCancelInContentView:(UIView *)view;                                               // not called if canCancelContentTouches is NO. default returns YES if view isn't UIControl

/*
 this is for a zooming/panning gesture. as the user tracks with two fingers, we adjust the offset and the scale of the content. When the gesture ends, you should update the content
 as necessary. Note that the gesture can end and a finger could still be down. While the gesture is in progress, we do not send any tracking calls to the subview
 the delegate must implement both viewForZoomingInScrollView: and scrollViewDidEndZooming:withView:atScale: in order for zooming to work and the max/min zoom scale must be different
 note that we are not scaling the actual scroll view but the 'content view' returned by the delegate.
 */

@property(nonatomic) float minimumZoomScale;     // default is 1.0
@property(nonatomic) float maximumZoomScale;     // default is 1.0. must be > minimum zoom scale to enable zooming
@property(nonatomic) BOOL  bouncesZoom;          // default is YES. if set, user can go past min/max zoom while gesturing and the zoom will animate to the min/max value at gesture end

@property(nonatomic,readonly,getter=isZooming)       BOOL zooming;       // returns YES if user in zoom gesture
@property(nonatomic,readonly,getter=isZoomBouncing)  BOOL zoomBouncing;  // returns YES if we are in the middle of zooming back to the min/max value

/*
 this is for the scroll to top gesture. by default, a single scroll visible scroll view with this flag set will get the call. if there is more than one visible with this
 flag set or the delegeat method returns NO, the view isn't scrolled 
 */
@property(nonatomic) BOOL  scrollsToTop;          // default is YES. if set, special gesture will scroll to top of view after consulting delegate

@end

@protocol UIScrollViewDelegate<NSObject>

@optional

- (void)scrollViewDidScroll:(UIScrollView *)scrollView;               // any offset changes

- (void)scrollViewWillBeginDragging:(UIScrollView *)scrollView;                              // called on start of dragging (may require some time and or distance to move)
- (void)scrollViewDidEndDragging:(UIScrollView *)scrollView willDecelerate:(BOOL)decelerate; // called on finger up if user dragged. decelerate is true if it will continue moving afterwards

- (void)scrollViewWillBeginDecelerating:(UIScrollView *)scrollView;   // called on finger up as we are moving
- (void)scrollViewDidEndDecelerating:(UIScrollView *)scrollView;      // called when scroll view grinds to a halt

- (void)scrollViewDidEndScrollingAnimation:(UIScrollView *)scrollView; // called when setContentOffset/scrollRectVisible:animated: finishes. not called if not animating

- (UIView *)viewForZoomingInScrollView:(UIScrollView *)scrollView;     // return a view that will be scaled. if delegate returns nil, nothing happens
- (void)scrollViewDidEndZooming:(UIScrollView *)scrollView withView:(UIView *)view atScale:(float)scale; // scale between minimum and maximum. called after any 'bounce' animations

- (BOOL)scrollViewShouldScrollToTop:(UIScrollView *)scrollView;   // return a yes if you want to scroll to the top. if not defined, assumes YES
- (void)scrollViewDidScrollToTop:(UIScrollView *)scrollView;      // called when scrolling animation finished. may be called immediately if already at top

@end
