//
//  PlaymiumInterface.h
//  Playmium
//
//  Created by Eric Dalrymple on 2015/07/10.
//  Copyright (c) 2015年 Gigataur. All rights reserved.
//

#include "PlaymiumInterface.h"

#import <Playmium/PlaymiumAnalytics.h>

#include <Playmium/CPlaymiumAds.h>
#include <Playmium/CPlaymiumSDK.h>
#include <Playmium/PlaymiumDefines.h>
#include <Playmium/CPlaymiumUserRating.h>

#include <sstream>

#pragma mark - Parameter Utilities

char             PARAM_DELIMITER                     = '|';

const size_t     PARSING_BUFFER_SIZE                 = 64;
char             PARSING_BUFFER[PARSING_BUFFER_SIZE];

unsigned short parseParamString( const char* paramString, NSMutableDictionary* output )
{
  size_t paramStringLength = 0;
  if( NULL != paramString )
  {
    //-- Can't parse a NULL string
    paramStringLength = strlen( paramString );
  }
  
  
  if( 0 == paramStringLength )
  {
    //-- Parsing complete; 0 parameters parsed
    return 0;
  }
  
  unsigned short loopCount = 0;
  unsigned short paramCount = 0;
  
  size_t toNextDelimiter = strcspn( paramString, &PARAM_DELIMITER );
  
  NSString* key = nil;
  NSString* object = nil;
  while( 0 < paramStringLength )
  {
    //-- Reset the parsing buffer
    memset( PARSING_BUFFER, 0, PARSING_BUFFER_SIZE );
    
    //-- Copy the next token into the parsing buffer
    strncpy( PARSING_BUFFER, paramString, toNextDelimiter );
    
    if( (0x1 && loopCount) == 0 )
    {
      //-- Key
      key = [NSString stringWithUTF8String:PARSING_BUFFER];
    }
    else
    {
      //-- Value
      object = [NSString stringWithUTF8String:PARSING_BUFFER];
      
      //-- Add the parameter to the dictionary
      [output setObject:object forKey:key];
    }
    
    //-- Move to next token
    size_t toNextParam = toNextDelimiter + 1;   //-- Compute offset to start of next parameter token
    paramString += toNextParam;                 //-- Move string pointer to start of next param
    paramStringLength -= toNextParam;           //-- Reduce string length to consume param token
    
    //-- Get the position of the next delimiter
    toNextDelimiter = strcspn( paramString, &PARAM_DELIMITER );
    
    //-- Tick loop count
    ++loopCount;
  }
  
  return paramCount;
}

static PlaymiumCallbackHandler *s_handler = NULL;

#pragma mark - Ad Listener
class DefaultPlaymiumAdsListener
: public CPlaymiumAdsListener
{
public:
  virtual void onAdShown( const CPlaymiumAdDef& ad )
  {
    if(s_handler != NULL)
    {
      s_handler->onAdShown(ad.getAdID());
    }
  }
  
  virtual void onAdFailedToDisplay( const CPlaymiumAdDef& ad )
  {
    if(s_handler != NULL)
    {
      s_handler->onAdFailed(ad.getAdID());
    }
  }
  
  virtual void onAdHidden( const CPlaymiumAdDef& ad )
  {
    //-- currently no callback for this
  }
  
  virtual void onAdAvailabilityUpdated( const CPlaymiumAdDef& ad, bool available )
  {
    if(s_handler != NULL)
    {
      s_handler->onStatusUpdate(ad.getAdID(), available);
    }
  }
  
  virtual void onRewardAdCompleted( const char* zoneId, const CPlaymiumAdRewardDef& rewardObject )
  {
    if(s_handler != NULL)
    {
      s_handler->onReward(zoneId, rewardObject.rewardAmount);
    }
  }
  
  virtual void onPushNotificationClicked( const char* key, const char* data )
  {
    if(s_handler != NULL)
    {
      s_handler->onPushNotificationClicked(key, data);
    }
  }
  
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
  
  // helper functions for spliting the string apart for the error messages
  std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems)
  {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim))
    {
      elems.push_back(item);
    }
    return elems;
  }
  
  
  std::vector<std::string> split(const std::string &s, char delim)
  {
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
  }
};


#pragma mark - Session API
///////////////////////////////
// SESSION
///////////////////////////////
DefaultPlaymiumAdsListener* adListener = NULL;

const char* PlaymiumInterface::getStringForErrorCode( unsigned int errorCode )
{
  Playmium::Error error = (Playmium::Error)errorCode;
  return CPlaymiumSDK::getStringForError( error );
}


void PlaymiumInterface::pauseSession()
{
  CPlaymiumSDK::pauseSession();
}


void PlaymiumInterface::resumeSession()
{
  CPlaymiumSDK::resumeSession();
}


unsigned int PlaymiumInterface::startSession( bool debugKeystone, bool enableLogging, PlaymiumCallbackHandler *handler)
{
  s_handler = handler;
  if(adListener == NULL)
  {
    adListener = new DefaultPlaymiumAdsListener();
  }
  CPlaymiumAds::addListener( adListener );
  
  Playmium::Error error = Playmium::PLAYMIUM_ERR_NONE;
  
  CPlaymiumSDK::startSession( debugKeystone, enableLogging, &error );
  
  return (unsigned int)error;
}


void PlaymiumInterface::stopSession()
{
  CPlaymiumAds::removeListener(adListener);
  if(adListener == NULL)
  {
    delete adListener;
    adListener = NULL;
  }
  CPlaymiumSDK::stopSession();
}


bool PlaymiumInterface::showEULA()
{
  return CPlaymiumSDK::showEULA();
}

void PlaymiumInterface::sendFeedback()
{
  return CPlaymiumSDK::showUserFeedbackForm(Playmium::UserFeedbackType::FEEDBACK_TYPE_GENERAL);
}

bool PlaymiumInterface::showPrivacyPolicy()
{
  return CPlaymiumSDK::showPrivacyPolicy();
}

void PlaymiumInterface::showOptionalUserRating()
{
  CPlaymiumUserRating::showOptionalUserRatingDlg();
}

void PlaymiumInterface::showUserRating()
{
  CPlaymiumUserRating::showUserRatingDlg();
}
  
#pragma mark - Ads API
///////////////////////////////
// ADS
///////////////////////////////

bool PlaymiumInterface::areAdsDone()
{
  return CPlaymiumAds::areAdsDone();
}


unsigned int PlaymiumInterface::isAdAvailable( unsigned int type, const char *adID )
{
  Playmium::Error error = Playmium::PLAYMIUM_ERR_NONE;
  CPlaymiumAdDef ad( (Playmium::AdType)type, adID );
  CPlaymiumAds::isAdAvailable( ad, &error );
  return (unsigned int)error;
}


void PlaymiumInterface::loadAd( unsigned int type, const char *adID )
{
  CPlaymiumAdDef ad( (Playmium::AdType)type, adID );
  CPlaymiumAds::loadAd( ad );
}


unsigned int PlaymiumInterface::showAd( unsigned int type, const char *adID )
{
  Playmium::Error error = Playmium::PLAYMIUM_ERR_NONE;
  CPlaymiumAdDef ad( (Playmium::AdType)type, adID );
  CPlaymiumAds::showAd( ad, &error );
  return (unsigned int)error;
}


unsigned int PlaymiumInterface::loadAndShowAd( unsigned int type, const char *adID )
{
  Playmium::Error error = Playmium::PLAYMIUM_ERR_NONE;
  CPlaymiumAdDef ad( (Playmium::AdType)type, adID );
  CPlaymiumAds::loadAndShowAd( ad, &error );
  return (unsigned int)error;
}

const char *PlaymiumInterface::getAdId(unsigned int type)
{
  // this is actually a stored string in the keystone so its safe to pass as a const char.
  return CPlaymiumAdDef::getZoneIDFromType((Playmium::AdType)type);
}
  
#pragma mark - Analytics
///////////////////////////////
// ANALYTICS
///////////////////////////////

bool PlaymiumInterface::logEvent( const char* eventName )
{
  return (bool)[PlaymiumAnalytics logEvent:[NSString stringWithUTF8String:eventName]];
}


bool PlaymiumInterface::logEventWithParams( const char* eventName, const char* paramString )
{
  //-- Compute length of parameter string
  size_t paramStringLength = 0;
  if( NULL != paramString )
  {
    paramStringLength = strlen( paramString );
  }
  
  if( 0 == paramStringLength )
  {
    //-- No parameter string; use simple monetization log
    return logEvent( eventName );
  }
  
  //-- Parse the parameters
  NSMutableDictionary* params = [[NSMutableDictionary alloc] init];
  unsigned short paramCount  = parseParamString( paramString, params );
  if( 0 < paramCount )
  {
    //-- Call native function
    return (bool)[PlaymiumAnalytics logEvent:[NSString stringWithUTF8String:eventName]
                              withParameters:params];
  }
  return false;
}


bool PlaymiumInterface::logMonetization( unsigned int amountInCents )
{
  return (bool)[PlaymiumAnalytics logMonetization:(NSUInteger)amountInCents];
}


bool PlaymiumInterface::logMonetizationWithParams( unsigned int amountInCents, const char* paramString )
{
  //-- Compute length of parameter string
  size_t paramStringLength = 0;
  if( NULL != paramString )
  {
    paramStringLength = strlen( paramString );
  }
  
  if( 0 == paramStringLength )
  {
    //-- No parameter string; use simple monetization log
    return logMonetization( amountInCents );
  }
  
  //-- Parse the parameters
  NSMutableDictionary* params = [[NSMutableDictionary alloc] init];
  unsigned short paramCount = parseParamString( paramString, params );
  if( 0 < paramCount )
  {
    //-- Call native function
    return (bool)[PlaymiumAnalytics logMonetization:(NSUInteger)amountInCents
                                     withParameters:params];
  }
  
  return false;
}


#pragma mark - Keystones
///////////////////////////////
// KEYSTONES
///////////////////////////////
void PlaymiumInterface::sendKeystoneFilePath( const char* directory )
{
  // pass keystone directory to plugin
  CPlaymiumSDK::sendKeystoneFilePath(directory);
}
