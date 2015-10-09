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

#include "PluginManager.h"  // needed to load plugins
#include "ProtocolAds.h"    // needed for kAdsReceived enums

using namespace cocos2d::ui;
using namespace cocos2d::plugin;


cocos2d::plugin::ProtocolAds* PlaymiumInterface::m_Playmium=NULL;
static PlaymiumCallbackHandler *s_handler = NULL;

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


#pragma mark - Session API
///////////////////////////////
// SESSION
///////////////////////////////

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


unsigned int PlaymiumInterface::startSession( bool debug, PlaymiumCallbackHandler *handler)
{
  if (m_Playmium == NULL)
  {
    m_Playmium = dynamic_cast<ProtocolAds*>(PluginManager::getInstance()->loadPlugin("Playmium_Cocos"));
    if (m_Playmium == NULL)
      return Playmium::PLAYMIUM_ERR_SESSION_NOT_STARTED;
  }

  Playmium::Error error = Playmium::PLAYMIUM_ERR_NONE;

  TAdsDeveloperInfo devInfo;
  // developer info is just the debugMode.
  std::string debugMode("true");
  devInfo["debugMode"] = debugMode;
    
  m_Playmium->setDebugMode(debug);
  m_Playmium->configDeveloperInfo(devInfo);
  
  cocos2d::plugin::ProtocolAds::ProtocolAdsCallback callback = handler->callbackFunction;
  m_Playmium->setCallback(callback);
  
  s_handler = handler;
  
  return (unsigned int)error;
}


void PlaymiumInterface::stopSession()
{
  CPlaymiumSDK::stopSession();
}


bool PlaymiumInterface::showEULA()
{
  return CPlaymiumSDK::showEULA();
}


bool PlaymiumInterface::showPrivacyPolicy()
{
  return CPlaymiumSDK::showPrivacyPolicy();
}
  
  
#pragma mark - Ads API
///////////////////////////////
// ADS
///////////////////////////////

bool PlaymiumInterface::areAdsDone()
{
  return CPlaymiumAds::areAdsDone();
}


unsigned int PlaymiumInterface::isAdAvailable( unsigned int type )
{
  Playmium::Error error = Playmium::PLAYMIUM_ERR_NONE;
  CPlaymiumAdDef ad( (Playmium::AdType)type );
  CPlaymiumAds::isAdAvailable( ad, &error );
  return (unsigned int)error;
}


void PlaymiumInterface::loadAd( unsigned int type )
{
  CPlaymiumAdDef ad( (Playmium::AdType)type );
  CPlaymiumAds::loadAd( ad );
}


unsigned int PlaymiumInterface::showAd( unsigned int type )
{
  Playmium::Error error = Playmium::PLAYMIUM_ERR_NONE;
  CPlaymiumAdDef ad( (Playmium::AdType)type );
  CPlaymiumAds::showAd( ad, &error );
  return (unsigned int)error;
}


unsigned int PlaymiumInterface::loadAndShowAd( unsigned int type )
{
  Playmium::Error error = Playmium::PLAYMIUM_ERR_NONE;
  CPlaymiumAdDef ad( (Playmium::AdType)type );
  CPlaymiumAds::loadAndShowAd( ad, &error );
  return (unsigned int)error;
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



///////////////////////////////
// PlaymiumCallbackHandler
///////////////////////////////

void PlaymiumCallbackHandler::callbackFunction(int type, std::string &message)
{
#ifdef CC_TARGET_OS_IPHONE
  std::vector<std::string> splitArray = split(message, '|');
  
  // no strings so exit here nothing to parse.
  if(splitArray.size() <= 0)
  {
    return;
  }
  
  switch(type)
  {
    case cocos2d::plugin::kAdsShown: // ad is shown
    {
      if(s_handler)
        s_handler->onAdShown(splitArray[0].c_str());
      break;
    }
      
    case cocos2d::plugin::kAdsDismissed: // ad is hidden
    {
      break;
    }
      
    case cocos2d::plugin::kPointsSpendSucceed: // reward points recieved
    {
      //split to get ad id and the reward amount
      int rewardID = -1;
      if(splitArray[1].length() > 0)
      {
        rewardID = atoi(splitArray[1].c_str());
      }
      
      if(s_handler != NULL)
        s_handler->onReward(splitArray[0].c_str(), rewardID);
      
      break;
    }
      
    case cocos2d::plugin::kNetworkError: // failed to show ad
    {
      // error only has id same as shown /dismissed
      if(s_handler != NULL)
        s_handler->onAdFailed(splitArray[0].c_str());
      
      break;
    }
      
    case cocos2d::plugin::kUnknownError: // update status return value.
    {
      // has if the zone if was available or not.
      bool bAvailable = strcmp(splitArray[1].c_str(), "true") == 0;
      
      if(s_handler != NULL)
      {
        s_handler->onStatusUpdate(splitArray[0].c_str(), bAvailable);
      }
      
      break;
    }
      
      
    default:
    {
      std::string messageText = "UNKOWN ERROR CODE Please check with support! playme@glitchsoft.com";
      
      //if(s_Handlers)
      //  s_Handlers->setErrorText(messageText);
      break;
    }
  }
#endif // CC_TARGET_OS_IPHONE
}

// helper functions for spliting the string apart for the error messages
std::vector<std::string> &PlaymiumCallbackHandler::split(const std::string &s, char delim, std::vector<std::string> &elems)
{
  std::stringstream ss(s);
  std::string item;
  while (std::getline(ss, item, delim))
  {
    elems.push_back(item);
  }
  return elems;
}


std::vector<std::string> PlaymiumCallbackHandler::split(const std::string &s, char delim)
{
  std::vector<std::string> elems;
  split(s, delim, elems);
  return elems;
}

