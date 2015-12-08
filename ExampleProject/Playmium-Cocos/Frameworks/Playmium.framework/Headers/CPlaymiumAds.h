//
//  CPlaymiumAds.h
//  PlaymiumSDK
//
//  Created by Brendan Sheedy on 2015-05-21.
//  Copyright (c) 2015 Gigataur. All rights reserved.
//

#ifndef __PlaymiumSDK__CPlaymiumAds__
#define __PlaymiumSDK__CPlaymiumAds__

#include <cstddef>
#include <string>

#include "./PlaymiumDefines.h"


/**
 * The CPlaymiumAdDef struct serves as a convenience for defining a specific
 * instance of an ad. Various types of ads (e.g. static, video) can be associated
 * to the same zone ID, you need both the zone ID and the ad type in order to
 * define a specific instance of an ad.
 */
#define PLAYMIUM_ADDEF_CHAR_COUNT 12

struct CPlaymiumAdDef
{
  CPlaymiumAdDef( const Playmium::AdType pAdType );
  CPlaymiumAdDef( const char *adID );
  CPlaymiumAdDef( const Playmium::AdType pAdType, const char *adID);
  ~CPlaymiumAdDef();
  
  const char *getZoneIDFromType(Playmium::AdType pAdType);
  const Playmium::AdType getAdTypeFromID(const char *adID);
  
  const char *getAdID() const { return m_AdID; }
  const Playmium::AdType getAdType() const { return m_Type; }
  
  void setAdID(const char *adID);
  void setAdType(Playmium::AdType type) { m_Type = type; }
  
  
private:
  CPlaymiumAdDef() {};
  bool isValidZone(const char *adID) const;
  
  char m_AdID[PLAYMIUM_ADDEF_CHAR_COUNT]; ///< Ad ID
  Playmium::AdType m_Type;                ///< Ad type (e.g. static, interstitial video, rewarded video, etc.)
};

/**
 * The CPlaymiumAdRewardDef struct defines a reward that should be awarded for
 * watching a particular ad.
 */
struct CPlaymiumAdRewardDef
{
  unsigned int rewardAmount;   ///< Typically refers to an amount of in-game currency
  
  CPlaymiumAdRewardDef( unsigned int pRewardAmount );
};



/**
 * A listener interface that allows implementers to receive events related to ads. In order
 * for the listener's callbacks to be called, it must be added using 'CPlaymiumAds::addListener( ... )'.
 */
class CPlaymiumAdsListener
{
public:
  /**
   * Called when an ad is succesfully shown.
   * @param ad  the definition for the shown ad
   */
  virtual void onAdShown( const CPlaymiumAdDef &ad  ) = 0;
  
  /**
   * Called when an ad has failed to display when asked to show.
   * @param ad  the definition for the ad that has failed to display
   */
  virtual void onAdFailedToDisplay( const CPlaymiumAdDef &ad ) = 0;
  
  /**
   * Called when an ad was succesfully hidden. This callback gets called regardless
   * of whether the ad was successfully watched by the user and provides no means of
   * varifying that.
   * @param ad  the definition for the ad that was hidden
   */
  virtual void onAdHidden( const CPlaymiumAdDef &ad ) = 0;
  
  /**
   * Called when an ad's availablity gets updated. Typically called after checking if
   * an ad is available or when attempting to preload an ad.
   * @param ad          the definition for the ad that has changed
   * @param available   if the ad is now available
   */
  virtual void onAdAvailabilityUpdated( const CPlaymiumAdDef& ad, bool available ) = 0;
  
  /**
   * When a rewarded ad has been completed. Provides the zone ID and the reward definition
   * for the completed ad. This callback is only called if a rewarded ad was successfully watched.
   * @param zoneID        the zone ID of the ad that has been completed
   * @param rewardDef     the reward definition for this zone ID
   */
  virtual void onRewardAdCompleted( const char* zoneId, const CPlaymiumAdRewardDef& rewardObject ) = 0;
  
  /**
   * When a push notification is tapped any custom data is passed back to the app
   * @param key      key for this data
   * @param data     data string
   */
  virtual void onPushNotificationClicked( const char* key, const char* data ) = 0;
};


/**
 * An interface to Playmium's ad mediation module.
 */
class CPlaymiumAds
{
public:
  /**
   * Returns whether any ads are currently being displayed or are in a transtional state.
   * @return  if all ads are done showing
   */
  static bool areAdsDone();
  
  /**
   * Checks to see if an ad matching a specified definition is loaded and ready to show. If it
   * isn't available, it will atempt to load it.
   * @param ad      a definition for the ad being checked
   * @param error   an Error output reference or NULL
   * @return        if the adId is abiliable to show with this adType
   */
  static bool isAdAvailable( const CPlaymiumAdDef& ad, Playmium::Error* error = NULL, bool bAllowPreload = true);
  
  /**
   * Will attempt to load an ad corresponding to the specified ad definition.
   * @param ad : a definition for an ad to be preloaded
   */
  static void loadAd( const CPlaymiumAdDef& ad );
  
  /**
   * Will attempt to show an ad corresponding to the specified ad definition. Calls 'isAdAvailable'
   * to verify the ad is configured to show before atempting to display.
   * @param ad      a definition for the ad to be shown
   * @param error   an Error output reference or NULL
   * @return        'true' if the ad was able to request a show successfully, 'false' otherwise
   */
  static bool showAd( const CPlaymiumAdDef& ad, Playmium::Error* error = NULL );
  
  /**
   * 
   * Will attempt to load and play the ad listed. It will queue it for load when load is complete it will then play it
   * @param ad      a definition for the ad to be shown
   * @param error   an Error output reference or NULL
   */
  static void loadAndShowAd( const CPlaymiumAdDef& ad, Playmium::Error* error = NULL );
  
  /**
   * Adds a listener to CPlaymiumAds. Once added it will receive call back calls. If the
   * specified listener has already been added, it will not be added twice.
   * @param listener  a CPlaymiumAdsListener
   */
  static void addListener( CPlaymiumAdsListener* listener );
  
  /**
   * Removes a listener to CPlaymiumAds. Once removed it will not longer receive call
   * back calls. If the specified listener has not been added, this method has no effect.
   * @param listener  a CPlaymiumAdsListener
   */
  static void removeListener( CPlaymiumAdsListener* listener );
};

#endif /* defined(__PlaymiumSDK__CPlaymiumAds__) */
