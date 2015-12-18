//
//  PlaymiumDefines.h
//  PlaymiumSDK
//
//  Created by Eric Dalrymple on 2015/05/03.
//  Copyright (c) 2015 Gigataur. All rights reserved.
//

#ifndef PlaymiumSDK_PlaymiumDefines_h
#define PlaymiumSDK_PlaymiumDefines_h

namespace Playmium
{

#pragma mark - Enum PlaymiumError
  
  /**
   * Enumeration of errors that can be encountered while utilizing the Playmium SDK.
   */
  enum Error
  {
      PLAYMIUM_ERR_NONE = 0                       ///< No error
    , PLAYMIUM_ERR_KEYSTONE_NOT_FOUND             ///< Specified keystone resource not found in application bundle
    , PLAYMIUM_ERR_KEYSTONE_PARSE_ERROR           ///< Could not parse keystone due to mismatching format or bad data
    , PLAYMIUM_ERR_LOCAL_NOTIFICATIONS_NOT_FOUND  ///< Local notification data file could not be found in application bundle
    , PLAYMIUM_ERR_AD_IS_NOT_AVAILIABLE           ///< Ad was not available when attempting to show one
    , PLAYMIUM_ERR_AD_IS_NOT_REWARD_TYPE          ///< Attempting to use a rewarded video on a zone that doesn't support them
    , PLAYMIUM_ERR_SESSION_ALREADY_STARTED        ///< Trying to start an already started session
    , PLAYMIUM_ERR_SESSION_NOT_PAUSED             ///< Trying to resume the SDK session when it isn't paused
    , PLAYMIUM_ERR_SESSION_NOT_STARTED            ///< Trying to affect an SDK operation without having started the session
    , PLAYMIUM_ERR_LOCALIZED_STRINGS_NOT_FOUND    ///< Localized string data file could not be found in application bundle
  };

  
  
#pragma mark - Enum PlaymiumAdType
  
  /**
   * Enumeration of all the various supported ad types.
   */
  enum AdType
  {
      AD_TYPE_NONE = 0
    , AD_TYPE_VIDEO               ///< Fullscreen video
    , AD_TYPE_REWARDED_VIDEO      ///< Fullscreen rewarded video
    , AD_TYPE_STATIC              ///< Fullscreen static image
    , AD_TYPE_CROSS_PROMOTION     ///< Fullscreen cross-promotion image
    , AD_TYPE_OFFERS              ///< Fullscreen sale offer image
    , AD_TYPE_IAP_OFFER           ///< Fullscreen sale offer but on IAP image
    , AD_TYPE_VIRTUAL_GOOD_OFFER  ///< Fullscreen image with ability to give items on watching
    , AD_TYPE_DIRECT_DEALS        ///< Fullscreen cross promotion image for deals with external partners
  };
  
  
  
#pragma mark - Enum PlaymiumUserFeedbackType
  
  /**
   * Enumerations of all the various user feedback forums.
   */
  enum UserFeedbackType
  {
      FEEDBACK_TYPE_GENERAL = 0
    , FEEDBACK_TYPE_CONTACT
    , FEEDBACK_TYPE_FEEDBACK
    , FEEDBACK_TYPE_IDEA
  };
  
}

#endif
