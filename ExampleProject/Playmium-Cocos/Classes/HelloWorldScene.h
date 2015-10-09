#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class ButtonHandlers;

class HelloWorld : public cocos2d::Layer
{
public:
  
    HelloWorld();
    virtual ~HelloWorld();
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    virtual void update(float delta);

    void onPause();
    void onResume();

    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
  
private:
  void deinit();
  
  ButtonHandlers *m_Handlers;
};

#endif // __HELLOWORLD_SCENE_H__
