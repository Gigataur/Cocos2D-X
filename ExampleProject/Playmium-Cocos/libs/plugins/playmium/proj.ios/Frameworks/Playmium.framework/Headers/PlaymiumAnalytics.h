//
//  PlaymiumAnalytics.h
//  PlaymiumSDK
//
//  Created by Eric Dalrymple on 2015/05/03.
//  Copyright (c) 2015 Gigataur. All rights reserved.
//

#ifndef __PlaymiumSDK__PlaymiumAnalytics__
#define __PlaymiumSDK__PlaymiumAnalytics__

#import <Foundation/Foundation.h>

/**
 * An interface to Playmium's analytics module.
 */
@interface PlaymiumAnalytics : NSObject

/**
 * Log an analytics event with a specified name.
 * @param eventName an NSString name for the event
 * @return          a boolean representing if the event was succesfully logged
 */
+(BOOL)logEvent:(NSString*)eventName;

/**
 * Logs an analytics event with a specified name and parameter list.
 * @param eventName an NSString name for the event
 * @param params    an NSDictionary containing event parameters
 * @return          a boolean representing if the event was succesfully logged
 */
+(BOOL)logEvent:(NSString*)eventName
 withParameters:(NSDictionary*)params;

/**
 * Log a monetization event for an amount of money specified in cents. If the device is not connected to the
 * internet, the event will be sent using best effort next time the device is connected
 * to the internet while in the application.
 * @param amountInCents   an NSUInteger number of cents
 * @return                a boolean representing whether the monetization event was succesfully logged
 */
+(BOOL)logMonetization:(NSUInteger)amountInCents;

/**
 * Logs a monetization event for an amount of money specified in cents and with a list of parameters. If the
 * device is not connected to the internet, the event will be sent using best effort next time the device
 * is connected to the internet while in the application.
 * @param amountInCents   an NSUInteger number of cents
 * @param params          an NSDictionary containing event parameters
 * @return                a boolean representing whether the monetization event was succesfully logged
 */
+(BOOL)logMonetization:(NSUInteger)amountInCents
        withParameters:(NSDictionary*)params;

@end

#endif /* defined(__PlaymiumSDK__PlaymiumAnalytics__) */