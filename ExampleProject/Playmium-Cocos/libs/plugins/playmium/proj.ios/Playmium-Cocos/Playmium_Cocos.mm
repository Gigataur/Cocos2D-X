//
//  Playmium_Cocos.m
//  Playmium-Cocos
//
//  Created by Chris Fowler on 2015-09-14.
//  Copyright (c) 2015 Chris Fowler. All rights reserved.
//

#import "Playmium_Cocos.h"

#import <Playmium/PlaymiumAnalytics.h>
#include <Playmium/CPlaymiumAds.h>
#include <Playmium/CPlaymiumSDK.h>
#include <Playmium/PlaymiumDefines.h>
#import "AdsWrapper.h"

@implementation Playmium_Cocos


class DefaultPlaymiumAdsListener
: public CPlaymiumAdsListener
{
public:
  virtual void onAdShown( const CPlaymiumAdDef& ad )
  {
    [AdsWrapper onAdsResult:m_Owner withRet:kAdsShown  withMsg:generateReturnText(ad)];
  }
  
  virtual void onAdFailedToDisplay( const CPlaymiumAdDef& ad )
  {
    [AdsWrapper onAdsResult:m_Owner withRet:kNetworkError  withMsg:generateReturnText(ad)];
  }
  
  virtual void onAdHidden( const CPlaymiumAdDef& ad )
  {
    [AdsWrapper onAdsResult:m_Owner withRet:kAdsDismissed  withMsg:generateReturnText(ad)];
  }
  
  virtual void onAdAvailabilityUpdated( const CPlaymiumAdDef& ad, bool available )
  {
    [AdsWrapper onAdsResult:m_Owner withRet:kUnknownError  withMsg:generateReturnText(ad,available)];
  }
  
  virtual void onRewardAdCompleted( const char* zoneId, const CPlaymiumAdRewardDef& rewardObject )
  {
    [AdsWrapper onAdsResult:m_Owner withRet:kPointsSpendSucceed  withMsg:generateReturnText(zoneId,rewardObject)];
  }
  
  void setOwner(id owner) { m_Owner = owner; }
  
private:
  
  NSString *generateReturnText(const CPlaymiumAdDef& ad)
  {
    return [NSString stringWithFormat:@"%s", ad.getAdID()];
  }
  
  NSString *generateReturnText(const char* zoneId, const CPlaymiumAdRewardDef& rewardObject)
  {
    return [NSString stringWithFormat:@"%s|%d", zoneId, rewardObject.rewardAmount];
  }
  
  NSString *generateReturnText(const CPlaymiumAdDef& ad, bool available)
  {
    return [NSString stringWithFormat:@"%s|%s", ad.getAdID(), available ? "true" : "false"];
  }
  
  id m_Owner;
};


DefaultPlaymiumAdsListener* adListener = NULL;


- (void) configDeveloperInfo: (NSMutableDictionary*) devInfo
{
  NSLog(@"Playmium: configDeveloperInfo called");
  
  NSString *boolString = devInfo[@"debugMode"];
  bool bUseDebugKeystones = [boolString isEqualToString:@"true"];
  
  boolString = devInfo[@"enableLogging"];
  bool bEnableLogging = [boolString isEqualToString:@"true"];
  
  Playmium::Error error = Playmium::PLAYMIUM_ERR_NONE;
  CPlaymiumSDK::startSession( bUseDebugKeystones, bEnableLogging, &error );
  
  adListener = new DefaultPlaymiumAdsListener();
  adListener->setOwner(self);
  CPlaymiumAds::addListener( adListener );
}

- (void) LoadAndShowAd:(NSNumber*) adType
{  
  int numberVal = [adType intValue];
  NSLog(@"Playmium: LoadAndShowAd (%d)", numberVal);
  Playmium::AdType type = (Playmium::AdType)numberVal;
  
  CPlaymiumAdDef ad( type );
	CPlaymiumAds::loadAndShowAd( ad, NULL );
}

- (void) LoadAd:(NSNumber*) adType
{
  int numberVal = [adType intValue];
  NSLog(@"Playmium: LoadAd (%d)", numberVal);
  Playmium::AdType type = (Playmium::AdType)numberVal;
  
  CPlaymiumAdDef ad( type );
  CPlaymiumAds::loadAd( ad );
}


/*
 We have chosen not to implement through the protocol interface
 To call our consitent calls to our Interface.
 So the below are just stubbed code unused with our plugin
 */
- (void) showAds: (NSMutableDictionary*) info position:(int) pos
{
  
}

- (void) hideAds: (NSMutableDictionary*) info
{
  
}

- (void) queryPoints
{
  
}

- (void) spendPoints: (int) points
{
  
}

- (void) setDebugMode: (BOOL) isDebugMode
{
  
}

- (NSString*) getSDKVersion
{
  return @"1.0.0";
}

- (NSString*) getPluginVersion
{
  return @"1.0.0";
}

@end
