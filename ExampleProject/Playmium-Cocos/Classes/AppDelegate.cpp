#include "AppDelegate.h"
#include "HelloWorldScene.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching() {
    int desiredResolutionX = 750;
    int desiredResolutionY = 1300;
  
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLViewImpl::createWithRect("Playmium-Cocos", Rect(0, 0, desiredResolutionX, desiredResolutionY));
        director->setOpenGLView(glview);
    }

    director->getOpenGLView()->setDesignResolutionSize(desiredResolutionX, desiredResolutionY, ResolutionPolicy::FIXED_HEIGHT);

    // turn on display FPS
    //director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    FileUtils::getInstance()->addSearchPath("res");

    // create a scene. it's an autorelease object
    auto scene = HelloWorld::createScene();

    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    auto director = Director::getInstance();
    Scene* scene = director->getRunningScene();
    if (scene != NULL)
    {
      HelloWorld* pHelloWorld = (HelloWorld*)scene->getChildByName("HelloWorld");
      if (pHelloWorld != NULL)
        pHelloWorld->onPause();
    }

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

  auto director = Director::getInstance();
  Scene* scene = director->getRunningScene();
  if (scene != NULL)
  {
    HelloWorld* pHelloWorld = (HelloWorld*)scene->getChildByName("HelloWorld");
    if (pHelloWorld != NULL)
      pHelloWorld->onResume();
  }

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
