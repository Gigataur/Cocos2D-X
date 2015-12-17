//
//  ButtonHandlers.h
//  Playmium-Cocos
//
//  Created by Chris Fowler on 2015-09-14.
//
//

#ifndef __Playmium_Cocos__ButtonHandlers__
#define __Playmium_Cocos__ButtonHandlers__

#include "cocos2d.h"
#include <ui/UIButton.h>
#include <ui/UITextField.h>
#include <ui/UIWidget.h>
#include "PlaymiumInterface.h"


class GameCallbackHandler : public PlaymiumCallbackHandler
{
  
  virtual void onReward(const char *AdID, const int rewardID);
  virtual void onAdShown(const char *AdID);
  virtual void onAdFailed(const char *AdID);
  virtual void onStatusUpdate(const char *AdID, const bool bAvailable);
  virtual void onPushNotificationClicked(const char *key, const char *data);
};


class ButtonHandlers
{
public:
  ButtonHandlers(cocos2d::Node* sceneNode);
  ~ButtonHandlers();
  
  void menuCallback(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type);
  
  void setErrorText(std::string &message);
  void addReward(int number);
  
  void onPause();
  void onResume();
  void update(float deltaSeconds);
  
  const char *getLoadAdId() { return m_loadVideoId.c_str(); }
  void enablePlayButton();
  
private:
  
  void enableButtons(bool bEnabled);
  void handleButtonPress(cocos2d::Ref* pSender);

  enum InternalState { State_SplashScreen, State_Interactive };
  
  //buttons
  cocos2d::ui::Button *m_StartSession;
  cocos2d::ui::Button *m_Interstitial;
  cocos2d::ui::Button *m_VideoPlay;
  cocos2d::ui::Button *m_VideoLoad;
  cocos2d::ui::Button *m_RewardVideo;
  cocos2d::ui::Button *m_CrossPromotion;
  cocos2d::ui::Button *m_VirtualGoods;
  cocos2d::ui::Button *m_DirectDeal;
  cocos2d::ui::Button *m_OptionsButton;
  cocos2d::ui::Button *m_CloseOptionsButton;
  cocos2d::ui::Button *m_EULAButton;
  cocos2d::ui::Button *m_FeedbackButton;
  cocos2d::ui::Button *m_PolicyButton;
  cocos2d::ui::Button *m_RateButton;
  cocos2d::ui::TextField *m_ErrorCode;
  cocos2d::ui::TextField *m_RewardText;
  cocos2d::ui::Widget* m_OptionsMenu;
  cocos2d::Node* m_SplashScreen;
  cocos2d::Node* m_RootNode;
  
  GameCallbackHandler m_handler;
  InternalState m_state;
  float m_stateAge;  
  int m_reward;
  
  std::string m_loadVideoId;
};

#endif /* defined(__Playmium_Cocos__ButtonHandlers__) */
