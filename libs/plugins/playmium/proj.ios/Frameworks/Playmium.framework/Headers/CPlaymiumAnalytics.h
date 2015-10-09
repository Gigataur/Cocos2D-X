//
//  CPlaymiumAnalytics.h
//  PlaymiumSDK
//
//  Created by Eric Dalrymple on 2015/05/03.
//  Copyright (c) 2015 Gigataur. All rights reserved.
//

#ifndef __PlaymiumSDK__CPlaymiumAnalytics__
#define __PlaymiumSDK__CPlaymiumAnalytics__

/**
 * An interface to Playmium's analytics module.
 */
class CPlaymiumAnalytics
{
public:
  /**
   * Logs an analytics event with a specified name. If the device is not connected to the
   * internet, the event will be sent using best effort next time the device is connected
   * to the internet while in the application.
   * @param eventName a c-string event name
   */
  static void logEvent( const char* eventName );
  
  /**
   * Logs an analytics event with a specified name and a set of specified parameters. The
   * number of parameters following 'parameterCount' must correspond to twice the value of
   * parameter count and must all be c-strings. Each odd parameter is the name of an event
   * parameter and each even parameter is the value. If the device is not connected to the
   * internet, the event will be sent using best effort next time the device is connected
   * to the internet while in the application.
   * @param eventName       a c-string event name
   * @param parameterCount  an int number of event parameters
   * @param ...             a list of c-string event parameter key/value pairs
   */
  static void logEventWithList( const char* eventName, int parameterCount, ... );
  
  /**
   * Logs a monetization event with a specified name. If the device is not connected to the
   * internet, the event will be sent using best effort next time the device is connected
   * to the internet while in the application.
   * @param amountInCents   an int number of cents
   */
  static void logMonetization( unsigned int amountInCents );
  
  /**
   * Logs a monetization event with a specified name and a set of specified parameters. The
   * number of parameters following 'parameterCount' must correspond to twice the value of
   * parameter count and must all be c-strings. Each odd parameter is the name of an event
   * parameter and each even parameter is the value. If the device is not connected to the
   * internet, the event will be sent using best effort next time the device is connected
   * to the internet while in the application.
   * @param amountInCents   an int number of cents
   * @param parameterCount  an int number of event parameters
   * @param ...             a list of c-string event parameter key/value pairs
   */
  static void logMonetizationWithList( unsigned int amountInCents, int parameterCount, ... );
  
};

#endif /* defined(__PlaymiumSDK__CPlaymiumAnalytics__) */
