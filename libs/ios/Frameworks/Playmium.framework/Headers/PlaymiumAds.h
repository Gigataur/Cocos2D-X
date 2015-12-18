//
//  PlaymiumAds.h
//  PlaymiumSDK
//
//  Created by Brendan Sheedy on 2015-05-21.
//  Copyright (c) 2015 Gigataur. All rights reserved.
//

#ifndef __PlaymiumSDK__PlaymiumAds__
#define __PlaymiumSDK__PlaymiumAds__

#import <Foundation/Foundation.h>

#include "./PlaymiumDefines.h"

/**
 * The PlaymiumAdDef struct serves as a convenience for defining a specific
 * instance of an ad. Various types of ads (e.g. static, video) can be associated
 * to the same zone ID, you need both the zone ID and the ad type in order to
 * define a specific instance of an ad.
 */
@interface PlaymiumAdDef : NSObject
{
  @public NSString* zoneId;           ///< Zone ID
  @public Playmium::AdType type;      ///< Ad type (e.g. static, interstitial video, rewarded video, etc.)
}

+(id) defWithAdId:(Playmium::AdType) pAdType;
-(id) initWithAdId:(Playmium::AdType) pAdType;
-(id) initWithZoneId:(NSString*) pZoneId andAdType:(Playmium::AdType) pAdType;

@end


/**
 * The PlaymiumAdRewardDef struct defines a reward that should be awarded for
 * watching a particular ad.
 */
struct PlaymiumAdRewardDef
{
  NSUInteger rewardAmount;    ///< Typically refers to an amount of in-game currency
  
  PlaymiumAdRewardDef( NSUInteger pRewardAmount );
};


/**
 * A delegate interface that allows implementers to receive events related to ads. In order
 * for the delegate's callbacks to be called, it must be added using [PlaymiumAds addDelegate: ...].
 */
@protocol PlaymiumAdsDelegate

/**
 * Called when an ad is succesfully shown.
 * @param ad  the definition for the shown ad
 */
-(void) adShown:(PlaymiumAdDef*) ad;

/**
 * Called when an ad has failed to display when asked to show.
 * @param ad  the definition for the ad that has failed to display
 */
-(void) adFailedToDisplay:(PlaymiumAdDef*) ad;

/**
 * Called when an ad was succesfully hidden. This callback gets called regardless
 * of whether the ad was successfully watched by the user and provides no means of
 * varifying that.
 * @param ad  the definition for the ad that was hidden
 */
-(void) adHidden:(PlaymiumAdDef*) ad;

/**
 * Called when an ad's availablity gets updated. Typically called after checking if
 * an ad is available or when attempting to preload an ad.
 * @param ad          the definition for the ad that has changed
 * @param available   if the ad is now available
 */
-(void) adAvailabilityUpdated:(PlaymiumAdDef*) ad
              andAvailability:(BOOL) available;

/**
 * When a rewarded ad has been completed. Provides the zone ID and the reward definition
 * for the completed ad. This callback is only called if a rewarded ad was successfully watched.
 * @param zoneID        the zone ID of the ad that has been completed
 * @param rewardDef     the reward definition for this zone ID
 */
-(void) rewardedAdCompleted:(NSString*) adId
                 withReward:(const PlaymiumAdRewardDef&) rewardDef;

/**
 * When a push notification is tapped any custom data is passed back to the app
 * @param key      key for this data
 * @param data     data string
 */
-(void) onPushNotificationClicked:(NSString*) key data:(NSString*) data;

@end


/**
 * An interface to Playmium's ad mediation module.
 */
@interface PlaymiumAds : NSObject

/**
 * Return whether any ads are currently being displayed or are in a transtional state.
 * @return  'true' if all ads are done showing, 'false' otherwise
 */
+(BOOL) areAdsDone;

/**
 * Checks to see if an ad matching a specified definition is loaded and ready to show. If it
 * isn't available, it will atempt to load it.
 * @param ad      a definition for the ad being checked
 * @return        if the adId is abiliable to show with this adType
 */
+(BOOL) isAdAvailable:(PlaymiumAdDef*) ad;

/**
 * Will attempt to load an ad corresponding to the specified ad definition.
 * @param ad : a definition for an ad to be preloaded
 */
+(void) loadAd:(PlaymiumAdDef*) ad;

/**
 * Will attempt to show an ad corresponding to the specified ad definition. Calls 'isAdAvailable'
 * to verify the ad is configured to show before atempting to display.
 * @param ad  a definition for the ad to be shown
 * @return    'true' if the ad was able to request a show successfully, 'false' otherwise
 */
+(BOOL) showAd:(PlaymiumAdDef*) ad;

/**
 *
 * Will attempt to load and play the ad listed. It will queue it for load when load is complete it will then play it
 * @param ad      a definition for the ad to be shown
 */
+(void) loadAndShowAd:(PlaymiumAdDef*) ad;

/**
 * Adds a delegate to PlaymiumAds. Once added it will receive callbacks. If the
 * specified delegate has already been added, it will not be added twice.
 * @param delegate  a CPlaymiumAdsListener
 */
+(void) addDelegate:(NSObject<PlaymiumAdsDelegate>*) delegate;

/**
 * Removes a delegate to PlaymiumAds. Once removed it will not longer receive callbacks. If the
 * specified delegate has not been added, this method has no effect.
 * @param delegate  a CPlaymiumAdsListener
 */
+(void) removeDelegate:(NSObject<PlaymiumAdsDelegate>*) delegate;

@end

#endif /* defined(__PlaymiumSDK__PlaymiumAds__) */
