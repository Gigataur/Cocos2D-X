//
//  PlaymiumSDK.h
//  PlaymiumSDK
//
//  Created by Eric Dalrymple on 2015/05/03.
//  Copyright (c) 2015 Gigataur. All rights reserved.
//

#ifndef PlaymiumSDK_PlaymiumSDK_h
#define PlaymiumSDK_PlaymiumSDK_h

#import <Foundation/Foundation.h>


@interface PlaymiumSDK : NSObject

/**
 * Returns a human readable string describing the specified error.
 * @param error an Error
 */
+(NSString*) getStringForError:(const int) error;

/**
 * Pauses the current Playmium session. This method should be called whenever
 * the application enters the background. This method has the same effect as
 * the method inside PlaymiumSDK with the same name and only one of them needs
 * to be called. The method is ineffective unless the current session is started
 * when called.
 */
+(void) pauseSession;

/**
 * Resumes the current Playmium session. This method should be called whenever
 * the application enters the foreground. This method has the same effect as
 * the method inside PlaymiumSDK with the same name and only one of them needs
 * to be called. The method is ineffective unless the currentsession is paused
 * when called.
 */
+(void) resumeSession;

/**
 * Starts a new Playmium session. This method should be called when the application
 * launches. This method has the same effect as the method of the same name inside
 * PlaymiumSDK and only one of them needs to be called.
 * @param debug 'true' to enable debug mode, 'false' otherwise
 */
+(void) startSession:(BOOL) debug;

/**
 * Starts a new Playmium session. This method should be called when the application
 * launches. This method has the same effect as the method of the same name inside
 * PlaymiumSDK and only one of them needs to be called.
 * @param debug           'true' to enable debug mode, 'false' otherwise
 * @param firstAppLaunch  'true' if this is the first time the application was launched, 'false' otherwise
 */
+(void) startSession:(BOOL) debug
         firstLaunch:(BOOL) firstAppLaunch;

/**
 * Stops the current Playmium session. This method be called when the application
 * shuts down. This method has the same effect as the method of the same name inside
 * PlaymiumSDK and only one of them needs to be called.
 */
+(void) stopSession;

/**
 * Opens the End User License Agreement using the device's internet browser. Calling
 * this function will force the application to the background.
 */
+(BOOL) showEULA;

/**
 * Opens the Privacy Policy using the device's internet browser. Calling
 * this function will force the application to the background.
 */
+(BOOL) showPrivacyPolicy;

/**
 * Stores the directory passed in as the place to find and extract the Keystone files used with configuration and authentication
 */
+(void) sendKeystoneFilePath:(NSString*) directory;

/**
 * Opens the  using the device's internet browser. Calling
 * this function will force the application to the background.
 */
+(void) showUserFeedbackForm:(const int) feedbackType;

/**
 * Stores the launch options used for various features of the SDK
 */
+(void) didFinishLaunchingWithOptions:(NSDictionary*)options;
+(NSDictionary*) getLaunchOptions;

@end

#endif /* defined(__PlaymiumSDK__PlaymiumSDKObjC__) */
