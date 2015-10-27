//
//  Playmium_Cocos.h
//  Playmium-Cocos
//
//  Created by Chris Fowler on 2015-09-14.
//  Copyright (c) 2015 Chris Fowler. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "InterfaceAds.h"
#import "PlaymiumAds.h"


@interface Playmium_Cocos : NSObject <InterfaceAds>

- (void) LoadAndShowAd:(NSNumber*) adType;
- (void) LoadAd:(NSNumber*) adType;

- (void) LoadAndShowAd:(NSNumber*) adType : (NSString*) adID;
- (void) LoadAd:(NSNumber*) adType : (NSString*) adID;

/**
 interfaces of protocol : InterfaceAds
 */
- (void) configDeveloperInfo: (NSMutableDictionary*) devInfo;
- (void) showAds: (NSMutableDictionary*) info position:(int) pos;
- (void) hideAds: (NSMutableDictionary*) info;
- (void) queryPoints;
- (void) spendPoints: (int) points;
- (void) setDebugMode: (BOOL) isDebugMode;
- (NSString*) getSDKVersion;
- (NSString*) getPluginVersion;


@end
