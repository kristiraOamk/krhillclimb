#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

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
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
    closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
    
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}


//*/
/*
#include <cmath>
#include <map>
#include <chrono>
#include <iostream>

#include "cocos2d.h"
#include "HelloWorldScene.h"
#include "HillClimbUtility.h"
// Add missing includes here.

namespace hillclimb {

    std::map<cocos2d::EventKeyboard::KeyCode,
             std::chrono::high_resolution_clock::time_point> HelloWorld::keys;

    bool HelloWorld::init() {
        if (!Layer::init()) {
            return false;
        }

        const auto director = cocos2d::Director::getInstance();
        const auto winSize = director->getWinSize();
        double winWidth = static_cast<double>(winSize.width);
        double winHeight = static_cast<double>(winSize.height);
    
        double spriteScale = DESIGN_RESOLUTION_SIZE.width / winWidth;
        this->carSprite = cocos2d::Sprite::create("car.png");
        this->carSprite->setScale(spriteScale, spriteScale);

        const auto carSize = this->carSprite->getContentSize();
        double carStartX = carSize.width / 2;
        this->carStartY = winSize.height / 2.0 + carSize.height;
        this->carSprite->setPosition(carStartX, carStartY);
        this->carSprite->setAnchorPoint(cocos2d::Vec2(0.5, 0.5));
        this->addChild(this->carSprite, 0);
    
        //Initialize car field here. Arguments: carStartX, carStartY, spriteScale
        //Initialize road field here. Arguments: winWidth, winHeight
        this->generateRoadParts();

        auto eventListener = cocos2d::EventListenerKeyboard::create();
        director->getOpenGLView()->setIMEKeyboardState(true);
        eventListener->onKeyPressed = [=](cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event){
            if (keys.find(keyCode) == keys.end()){
                keys[keyCode] = std::chrono::high_resolution_clock::now();
            }
        };
        eventListener->onKeyReleased = [=](cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event){
            keys.erase(keyCode);
        };
        this->_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener, this);
        this->scheduleUpdate();
    
        return true;
    }

    bool HelloWorld::isKeyPressed(cocos2d::EventKeyboard::KeyCode code) {
        if (keys.find(code) != keys.end())
            return true;
        return false;
    }

    void HelloWorld::generateRoadParts() {
        //MIN_ROAD_SIZE = 2
        //get part count of road
        //get part coordinate pairs of road
    
        //if partCount < MIN_ROAD_SIZE
            //return

        auto drawNode = cocos2d::DrawNode::create();
        drawNode->setName("drawNode");
        /*Loop through partCoordPairs:
            beginCoords = partCoordPair at current index
            endCoords = partCoordPair at current index + 1
            drawNode->drawLine(cocos2d::Point(x of beginCoords, y of beginCoords),
            cocos2d::Point(x of endCoords, y of endCoords),
            cocos2d::Color4F::WHITE);
        */
/*
        this->addChild(drawNode);
    }

    void HelloWorld::deleteRoadParts() {
        this->removeChildByName("drawNode");
    }

    void HelloWorld::update(float dt) {
        cocos2d::Node::update(dt);
        if (isKeyPressed(cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW)) {
            //Speed the car up with the updateThrottle method
        } else if (isKeyPressed(cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW)) {
            //Put the brake on with the updateThrottle method
        } else {
            //Slow the car down with the updateThrottle method
        }

        /*Get car transition
          Get car angle. Use std::fmod for it with STRAIGHT_ANGLE as divisor.
    
          Check if the car is touching the road AND if its angle is over or below some limit, to determine if it has crashed
          Check if the car's transition is below some value to determine if it is reversing
          if the car is either crashed or reversing:
               Reset the car with carStartY as argument
               Reset the road
          else
               Update the car with road and dt as arguments
               Move the road with carTransition as argument
          }*/
/*               
        this->deleteRoadParts();
        this->generateRoadParts();
        //Set carSprite position with setPositionY(y). The argument y should be the y position of the car
        //Set sprite rotation with setRotation(angle / STRAIGHT_ANGLE * 180);
    }

    cocos2d::Scene* HelloWorld::createScene() {
        auto scene = cocos2d::Scene::create();
        auto layer = HelloWorld::create();

        scene->addChild(layer);
        return scene;
    }
}
*/