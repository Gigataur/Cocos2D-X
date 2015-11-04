//
//  ButtonHandlers.cpp
//  Playmium-Cocos
//
//  Created by Chris Fowler on 2015-09-14.
//
//

#include "ButtonHandlers.h"
#include <ui/UIImageView.h>

#ifdef CC_TARGET_OS_IPHONE
#include "PlaymiumInterface.h"
#include <Playmium/PlaymiumDefines.h>
#endif

using namespace cocos2d::ui;

// this is a local static var to update the error code visually in our test application
static ButtonHandlers *s_Handlers = NULL;

void GameCallbackHandler::onReward(const char *AdID, const int rewardID)
{
  std::string messageText = "REWARD: ";
  messageText.append(AdID);
  
  if(s_Handlers)
  {
    s_Handlers->setErrorText(messageText);
    s_Handlers->addReward(rewardID);
  }
}

void GameCallbackHandler::onAdShown(const char *AdID)
{
  std::string messageText = "AD Shown: ";
  messageText.append(AdID);
  
  if(s_Handlers)
    s_Handlers->setErrorText(messageText);
}

void GameCallbackHandler::onAdFailed(const char *AdID)
{
  std::string messageText = "AD FAILED: ";
  messageText.append(AdID);
  
  if(s_Handlers)
    s_Handlers->setErrorText(messageText);
}

void GameCallbackHandler::onStatusUpdate(const char *AdID, const bool bAvailable)
{
  if(bAvailable == false)
  {
    std::string messageText = "AD FAILED LOAD: ";
    messageText.append(AdID);
    
    if(s_Handlers)
      s_Handlers->setErrorText(messageText);
  }
}


ButtonHandlers::ButtonHandlers(cocos2d::Node* sceneNode)
  : m_reward(0)
  , m_stateAge(0.0f)
  , m_state(State_SplashScreen)
{
  if(s_Handlers == NULL)
  {
    s_Handlers = this;
  }
  
  m_RootNode = sceneNode->getChildByName("RootNode");
  
  m_StartSession = static_cast<Button*>(m_RootNode->getChildByName("Button_StartSession"));
  m_StartSession->addTouchEventListener(CC_CALLBACK_2(ButtonHandlers::menuCallback, this));

  m_Interstitial = static_cast<Button*>(m_RootNode->getChildByName("Button_Interstitial"));
  m_Interstitial->addTouchEventListener(CC_CALLBACK_2(ButtonHandlers::menuCallback, this));
  
  m_Video = static_cast<Button*>(m_RootNode->getChildByName("Button_Video"));
  m_Video->addTouchEventListener(CC_CALLBACK_2(ButtonHandlers::menuCallback, this));
  
  m_RewardVideo = static_cast<Button*>(m_RootNode->getChildByName("Button_VideoReward"));
  m_RewardVideo->addTouchEventListener(CC_CALLBACK_2(ButtonHandlers::menuCallback, this));
  
  m_CrossPromotion = static_cast<Button*>(m_RootNode->getChildByName("Button_CrossPromotion"));
  m_CrossPromotion->addTouchEventListener(CC_CALLBACK_2(ButtonHandlers::menuCallback, this));
  
  m_VirtualGoods = static_cast<Button*>(m_RootNode->getChildByName("Button_VirtualGoods"));
  m_VirtualGoods->addTouchEventListener(CC_CALLBACK_2(ButtonHandlers::menuCallback, this));
  
  m_DirectDeal = static_cast<Button*>(m_RootNode->getChildByName("Button_DirectDeal"));
  m_DirectDeal->addTouchEventListener(CC_CALLBACK_2(ButtonHandlers::menuCallback, this));
  
  m_OptionsButton = static_cast<Button*>(sceneNode->getChildByName("Button_Options"));
  m_OptionsButton->addTouchEventListener(CC_CALLBACK_2(ButtonHandlers::menuCallback, this));
  
  m_ErrorCode = static_cast<TextField*>(m_RootNode->getChildByName("error_code"));
  m_RewardText = static_cast<TextField*>(m_RootNode->getChildByName("reward_text"));
  m_OptionsMenu = static_cast<Widget*>(m_RootNode->getChildByName("OptionsMenu"));
  
  if (m_OptionsMenu != NULL)
  {
    m_OptionsMenu->setVisible(false);
    
    m_CloseOptionsButton = static_cast<Button*>(m_OptionsMenu->getChildByName("Button_Close"));
    m_CloseOptionsButton->addTouchEventListener(CC_CALLBACK_2(ButtonHandlers::menuCallback, this));
    
    m_EULAButton = static_cast<Button*>(m_OptionsMenu->getChildByName("Button_EULA"));
    m_EULAButton->addTouchEventListener(CC_CALLBACK_2(ButtonHandlers::menuCallback, this));

    m_PolicyButton = static_cast<Button*>(m_OptionsMenu->getChildByName("Button_Policy"));
    m_PolicyButton->addTouchEventListener(CC_CALLBACK_2(ButtonHandlers::menuCallback, this));
  }
  else
  {
    m_CloseOptionsButton = NULL;
  }
  
  m_SplashScreen = sceneNode->getChildByName("SplashScreen");
  
  // Enable the splash screen
  m_RootNode->setVisible(false);
  m_StartSession->setEnabled(false);
  m_SplashScreen->setVisible(true);
  
  enableButtons(false);
}

ButtonHandlers::~ButtonHandlers()
{
#ifdef CC_TARGET_OS_IPHONE
  PlaymiumInterface::stopSession();
#endif
}

void ButtonHandlers::update(float deltaSeconds)
{
  m_stateAge += deltaSeconds;
  
  if (m_state == State_SplashScreen)
  {
    const float SplashScreenDuration = 4.0f;
    const float SplashFadeStart = SplashScreenDuration - 1.5f;
    const float SplashFadeEnd = SplashScreenDuration - 1.0f;
    
    cocos2d::ui::ImageView* pImageBG = static_cast<cocos2d::ui::ImageView*>(m_SplashScreen->getChildByName("bg_white"));
    cocos2d::ui::ImageView* pImageLogo = static_cast<cocos2d::ui::ImageView*>(m_SplashScreen->getChildByName("Logo"));
    
    GLubyte splashBrightness = 255;
    
    // Fade out the splash screen
    if (m_stateAge >= SplashFadeStart)
    {
      float ratio = (m_stateAge-SplashFadeStart) / (SplashFadeEnd - SplashFadeStart);
      if (ratio > 1.0f) ratio = 1.0f;
      splashBrightness = (GLubyte)((1.0f-ratio) * 255.0f);
    }
    
    cocos2d::Color3B splashColor(splashBrightness, splashBrightness, splashBrightness);
    pImageBG->setColor(splashColor);
    pImageLogo->setColor(splashColor);
    
    if (m_stateAge >= SplashScreenDuration)
    {
      // Disable the splash screen
      m_RootNode->setVisible(true);
      m_StartSession->setEnabled(true);
      m_SplashScreen->setVisible(false);
      m_state = State_Interactive;
      m_stateAge = 0.0f;
    }
  }
}

void ButtonHandlers::menuCallback(cocos2d::Ref* pSender, Widget::TouchEventType type)
{
  switch (type)
  {
    case Widget::TouchEventType::BEGAN:
      break;
      
    case Widget::TouchEventType::ENDED:
      handleButtonPress(pSender);
      break;
      
    default:
      break;
  }
}

void ButtonHandlers::enableButtons(bool bEnabled)
{
  if(m_StartSession)
  {
    m_StartSession->setVisible(!bEnabled);
    m_StartSession->setEnabled(!bEnabled);
  }
  
  if(m_Interstitial)
  {
    m_Interstitial->setVisible(bEnabled);
    m_Interstitial->setEnabled(bEnabled);
  }
  
  if(m_Video)
  {
    m_Video->setVisible(bEnabled);
    m_Video->setEnabled(bEnabled);
  }
  
  if(m_RewardVideo)
  {
    m_RewardVideo->setVisible(bEnabled);
    m_RewardVideo->setEnabled(bEnabled);
  }
  
  if(m_CrossPromotion)
  {
    m_CrossPromotion->setVisible(bEnabled);
    m_CrossPromotion->setEnabled(bEnabled);
  }
  
  if(m_VirtualGoods)
  {
    m_VirtualGoods->setVisible(bEnabled);
    m_VirtualGoods->setEnabled(bEnabled);
  }
  
  if(m_DirectDeal)
  {
    m_DirectDeal->setVisible(bEnabled);
    m_DirectDeal->setEnabled(bEnabled);
  }
  
  if (m_OptionsButton)
  {
    m_OptionsButton->setVisible(bEnabled);
    m_OptionsButton->setEnabled(bEnabled);
  }
}

void ButtonHandlers::setErrorText(std::string &message)
{
  if(m_ErrorCode == NULL)
    return;
  
  m_ErrorCode->setString(message);
}


void ButtonHandlers::addReward(int number)
{
  if(m_RewardText == NULL)
    return;
  
  m_reward += number;
  std::string rewardText = std::to_string(m_reward);
  
  m_RewardText->setString(rewardText);
}


void ButtonHandlers::handleButtonPress(cocos2d::Ref* pSender)
{
#ifdef CC_TARGET_OS_IPHONE
  if(pSender == m_StartSession)
  {
    PlaymiumInterface::startSession(true, false, &m_handler);
    enableButtons(true);
  }
  
  if(pSender == m_Interstitial)
  {
    PlaymiumInterface::loadAndShowAd( Playmium::AD_TYPE_STATIC );
  }
  
  if(pSender == m_Video)
  {
    PlaymiumInterface::loadAndShowAd( Playmium::AD_TYPE_VIDEO );
  }
  
  if(pSender == m_RewardVideo)
  {
    PlaymiumInterface::loadAndShowAd( Playmium::AD_TYPE_REWARDED_VIDEO );
  }
  
  if(pSender == m_CrossPromotion)
  {
    PlaymiumInterface::loadAndShowAd( Playmium::AD_TYPE_CROSS_PROMOTION );
  }
  
  if(pSender == m_VirtualGoods)
  {
    PlaymiumInterface::loadAndShowAd( Playmium::AD_TYPE_VIRTUAL_GOOD_OFFER );
  }
  
  if(pSender == m_DirectDeal)
  {
    PlaymiumInterface::loadAndShowAd( Playmium::AD_TYPE_DIRECT_DEALS );
  }
  
  if (pSender == m_OptionsButton)
  {
    if (m_OptionsMenu != NULL)
    {
      enableButtons(false);
      m_OptionsMenu->setVisible(true);
    }
  }
  
  if (pSender == m_CloseOptionsButton)
  {
    if (m_OptionsMenu != NULL)
    {
      enableButtons(true);
      m_OptionsMenu->setVisible(false);
    }
  }
  
  if (pSender == m_EULAButton)
  {
    PlaymiumInterface::showEULA();
  }
  
  if (pSender == m_PolicyButton)
  {
    PlaymiumInterface::showPrivacyPolicy();
  }
  
  
#endif // #ifdef CC_TARGET_OS_IPHONE
}

void ButtonHandlers::onPause()
{
#ifdef CC_TARGET_OS_IPHONE
  PlaymiumInterface::pauseSession();
#endif
}

void ButtonHandlers::onResume()
{
#ifdef CC_TARGET_OS_IPHONE
  PlaymiumInterface::resumeSession();
#endif
}

