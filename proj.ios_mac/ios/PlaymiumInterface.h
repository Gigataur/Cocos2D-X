//
//  PlaymiumInterface
//  Playmium
//
//  Created by Eric Dalrymple on 2015/07/10.
//  Copyright (c) 2015年 Gigataur. All rights reserved.
//

#ifndef Playmium_CPlaymiumWrapperExtern_h
#define Playmium_CPlaymiumWrapperExtern_h

#include <string>
#include <vector>

class PlaymiumCallbackHandler
{
public:
  PlaymiumCallbackHandler() {};
  
  virtual void onReward(const char *AdID, const int rewardID) = 0;
  virtual void onAdShown(const char *AdID) = 0;
  virtual void onAdFailed(const char *AdID) = 0;
  virtual void onStatusUpdate(const char *AdID, const bool bAvailable) = 0;
  virtual void onPushNotificationClicked(const char *key, const char *data) = 0;
};

class PlaymiumInterface
{
public:
#pragma mark - Session API
  ///////////////////////////////
  // SESSION
  ///////////////////////////////

  static const char* getStringForErrorCode( unsigned int errorCode );
  static void pauseSession();
  static void resumeSession();
  static unsigned int startSession(bool debugKeystone, bool enableLogging, PlaymiumCallbackHandler *handler);
  static void stopSession();
  static bool showEULA();
  static bool showPrivacyPolicy();
  static void sendFeedback();
  static void showOptionalUserRating();
  static void showUserRating();

#pragma mark - Ads API
  ///////////////////////////////
  // ADS
  ///////////////////////////////

  static bool areAdsDone();
  static unsigned int isAdAvailable( unsigned int type, const char *adID = NULL );
  static void loadAd( unsigned int type, const char *adID = NULL );
  static unsigned int showAd( unsigned int type, const char *adID = NULL );
  static unsigned int loadAndShowAd( unsigned int type, const char *adID = NULL );
  static const char *getAdId(unsigned int type);

#pragma mark - Analytics
  ///////////////////////////////
  // ANALYTICS
  ///////////////////////////////

  static bool logEvent( const char* eventName );
  static bool logEventWithParams( const char* eventName, const char* paramString );
  static bool logMonetization( unsigned int amountInCents );
  static bool logMonetizationWithParams( unsigned int amountInCents, const char* paramString );

#pragma mark - Keystones
  ///////////////////////////////
  // KEYSTONES
  ///////////////////////////////
  static void sendKeystoneFilePath( const char* directory );
  
};

#endif