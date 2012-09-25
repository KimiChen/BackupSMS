//
//  UIImagePickerController.h
//  UIKit
//
//  Copyright 2008 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UINavigationController.h>
#import <UIKit/UIKitDefines.h>

@class UIImage;
@protocol UIImagePickerControllerDelegate;

enum {
    UIImagePickerControllerSourceTypePhotoLibrary,
    UIImagePickerControllerSourceTypeCamera,
    UIImagePickerControllerSourceTypeSavedPhotosAlbum
};
typedef NSUInteger UIImagePickerControllerSourceType;

// editingInfo dictionary keys
UIKIT_EXTERN NSString *const UIImagePickerControllerOriginalImage;  // a UIImage
UIKIT_EXTERN NSString *const UIImagePickerControllerCropRect;       // an NSValue (CGRect)

UIKIT_EXTERN_CLASS @interface UIImagePickerController : UINavigationController <NSCoding> {
  @private
    UIImagePickerControllerSourceType _sourceType;
    struct {
        unsigned int allowsImageEditing:1;
        unsigned int visible:1;
        unsigned int isCleaningUp:1;
    } _imagePickerFlags;
}

+ (BOOL)isSourceTypeAvailable:(UIImagePickerControllerSourceType)sourceType;    // returns YES if source is available (i.e. camera present)

@property(nonatomic,assign)   id <UINavigationControllerDelegate, UIImagePickerControllerDelegate> delegate;

@property(nonatomic)           UIImagePickerControllerSourceType     sourceType;           // default value is UIImagePickerControllerSourceTypePhotoLibrary.
@property(nonatomic)           BOOL                                  allowsImageEditing;   // default value is NO

@end


@protocol UIImagePickerControllerDelegate<NSObject>
@optional
// If image editing is disabled, the editInfoDictionary will be nil.
// The picker does not dismiss itself; the client dismisses it in these callbacks.
// The delegate will receive one or the other, but not both, depending whether the user
// confirms or cancels.
- (void)imagePickerController:(UIImagePickerController *)picker didFinishPickingImage:(UIImage *)image editingInfo:(NSDictionary *)editingInfo;
- (void)imagePickerControllerDidCancel:(UIImagePickerController *)picker;

@end


// Adds a photo to the saved photos album.  The optional completionSelector should have the form:
//  - (void)image:(UIImage *)image didFinishSavingWithError:(NSError *)error contextInfo:(void *)contextInfo;
UIKIT_EXTERN void UIImageWriteToSavedPhotosAlbum(UIImage *image, id completionTarget, SEL completionSelector, void *contextInfo);
