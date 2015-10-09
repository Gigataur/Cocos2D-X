#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

#include "ButtonHandlers.h"

using namespace cocostudio::timeline;

HelloWorld::HelloWorld()
: cocos2d::Layer()
, m_Handlers(NULL)
{
  
}

HelloWorld::~HelloWorld()
{
  deinit();
}

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer, 0, "HelloWorld");

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    cocos2d::Node* rootNode = CSLoader::createNode("MainScene.csb");

    auto size = Director :: getInstance () -> getVisibleSize ();
    rootNode-> setContentSize (size);
    ui :: Helper :: doLayout (rootNode);
  
    addChild(rootNode);

    m_Handlers  = new ButtonHandlers(rootNode);
  
    scheduleUpdate();
  
    return true;
}

void HelloWorld::deinit()
{
  if(m_Handlers != NULL)
  {
    delete m_Handlers;
    m_Handlers = NULL;
  }
}

void HelloWorld::onPause()
{
  if (m_Handlers != NULL)
    m_Handlers->onPause();
}

void HelloWorld::onResume()
{
  if (m_Handlers != NULL)
    m_Handlers->onResume();
}

void HelloWorld::update(float delta)
{
  if (m_Handlers != NULL)
    m_Handlers->update(delta);
}
