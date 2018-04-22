#include <cmath>
#include <map>
#include <chrono>
#include <iostream>
#include <vector>
#include <stdlib.h>     // srand, rand 
#include <math.h>       // cos 

#include "cocos2d.h"
#include "HillClimbLayer.h"
#include "HillClimbUtility.h"
#include "HillClimbRoad.h"
// Add missing includes here.

namespace hillclimb {

    std::map<cocos2d::EventKeyboard::KeyCode,
             std::chrono::high_resolution_clock::time_point> HillClimbLayer::keys;

    HillClimbRoad *road;
    
    bool HillClimbLayer::init() {
        if (!Layer::init()) {
            return false;
        }
        ln = DrawNode::create();
        this->addChild(ln);


        b2Vec2 gravity = b2Vec2(0.0f, -10.0f);
        world = new b2World(gravity); 

        const auto director = cocos2d::Director::getInstance();
        const auto winSize = director->getWinSize();
        double winWidth = static_cast<double>(winSize.width);
        double winHeight = static_cast<double>(winSize.height);
    
        spriteScale = DESIGN_RESOLUTION_SIZE.width / winWidth;

        //This is debug track from older project
        //This is waiting for impletation of new tracksystem
        trackNumber=1;
        float trackSize[]= {
            25, 25, 25, 25, 25, 25, 25, 25, 25, 25,
            25, 25, 74, 76, 23, 64, 34, 63, 23, 25,
            94, 84, 54, 76, 45, 23, 65, 86, 75, 78,
            24, 43, 56, 29, 56, 21, 54, 23, 65, 86,
            72,  80, 19,  43,   4, 11,  5,  79,  40,  87, 
            5, 73,  57, 43, 62, 43, 44, 10, 58,  42,
             47, 54, 39, 32, 75, 62, 66,  73,  49,  24,
             2, 37,  52, 53, 92,   0,   1,  75, 61,  86,
            75,  94, 60,  15,  4,  13,  68,  54, 74,  9,
            14, 97, 23,  9,  38, -87,  40, 100, 85, 76,
            55, 27,  33, 55,  29, 57, 66, 70,  56,   4,
             79, 82,  40, 70, 34,  17,  42,  61, 30, 18,
             47,  74,  19, 78,  14,  97,  33,  47,  44,  53,
             26,   9, 66,  44, 37,  56, 97, 82,  30,  35,
             45
            };
        trackWidth=5;
        trackHeight=5;

        //this is just for testing on my own computer
        spriteScale = 1024 / winWidth;

        //Initialize car field here. Arguments: carStartX, carStartY, spriteScale
        //Initialize car
        const Point startPoint = Point(100, 50);
        _car = new HillClimbCar();
        _car->init(world, ln, startPoint);

        this->runAction(Follow::create(_car->getSprite()));


        //Initialize road field here. Arguments: winWidth, winHeight
        road = new HillClimbRoad(winWidth, winHeight);
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


        // Define the ground body.
        b2BodyDef groundBodyDef;
        groundBodyDef.position.Set(0, 0); // bottom-left corner

        // Call the body factory which allocates memory for the ground body
        // from a pool and creates the ground box shape (also from a pool).
        // The body is also added to the world.
        b2Body* groundBody = world->CreateBody(&groundBodyDef);
 
        // Define the ground box shape.
        b2EdgeShape groundBox;

        groundBox.Set(b2Vec2(0,0), b2Vec2(18,0));
        groundBody->CreateFixture(&groundBox, 0);

        //This is just for debuging and showing something
        //draw real track
        HillClimbLayer::drawHills();
        HillClimbLayer::drawHills();
        HillClimbLayer::drawHills();
        HillClimbLayer::drawHills();

        //Make ground and line that shows it
        //Ground has collider, track doesn't
        HillClimbLayer::generateSomethingToHit();

        return true;
    }


    bool HillClimbLayer::isKeyPressed(cocos2d::EventKeyboard::KeyCode code) {
        if (keys.find(code) != keys.end())
            return true;
        return false;
    }

    void HillClimbLayer::generateSomethingToHit(){
        world->SetContinuousPhysics(true);

        // Define the ground body.
        b2BodyDef groundBodyDef;
        groundBodyDef.position.Set(0, 0); // bottom-left corner

        // Call the body factory which allocates memory for the ground body
        // from a pool and creates the ground box shape (also from a pool).
        // The body is also added to the world.
        b2Body* groundBody = world->CreateBody(&groundBodyDef);
     
        // Define the ground box shape.
        b2PolygonShape groundBox;
        groundBox.SetAsBox(10000, 1.0f);

        groundBody->CreateFixture(&groundBox, 1.0f);

        //Draw ground
        auto drawNode = cocos2d::DrawNode::create();
            drawNode->setName("drawNode");

        drawNode->drawLine(cocos2d::Point(0, 0),
            cocos2d::Point(10000,0),
            cocos2d::Color4F::WHITE);
    
        this->addChild(drawNode);
    }

    void HillClimbLayer::generateRoadParts() {
        int MIN_ROAD_SIZE = 7;
        
        //road.
        //get part count of road
        //get part coordinate pairs of road


        //This make that zic zec road
        //this is new road system, and I should use this with the old one
        //So there would be a road that is properly done
        for(int i=0;i<MIN_ROAD_SIZE;++i)
        {
            auto drawNode = cocos2d::DrawNode::create();
            drawNode->setName("drawNode");

            //Loop through partCoordPairs:
            std::vector<Coordinates> beginCoords = road->getPartCoords();//partCoordPair at current index
            std::vector<Coordinates> endCoords = road->getPartCoords();//partCoordPair at current index + 1
            auto beginnin = beginCoords[i];
            auto end = beginCoords[i+1];
            drawNode->drawLine(cocos2d::Point(beginnin.x, beginnin.y),
            cocos2d::Point(end.x,end.y),
            cocos2d::Color4F::WHITE);
         
            this->addChild(drawNode);
        }
    }

    void HillClimbLayer::deleteRoadParts() {
        this->removeChildByName("drawNode");
    }

    void HillClimbLayer::update(float dt) {

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
        
        this->deleteRoadParts();
        this->generateRoadParts();

        //Set carSprite position with setPositionY(y). The argument y should be the y position of the car
        //Set sprite rotation with setRotation(angle / STRAIGHT_ANGLE * 180);
        Sprite *carbody = _car->getSprite();
        int positionIterations = 10;  
        int velocityIterations = 10;


        deltaTime = dt;
        world->Step(dt, velocityIterations, positionIterations);  
       
        for (b2Body *body = world->GetBodyList(); body != NULL; body = body->GetNext())
        {   
            if (body->GetUserData()!=NULL) 
            {  
                Sprite *sprite = (Sprite *) body->GetUserData();  
                spriteScale=32.0f;
                sprite->setPosition(Vec2(body->GetPosition().x * spriteScale,body->GetPosition().y * spriteScale));  
                sprite->setRotation(-1 * CC_RADIANS_TO_DEGREES(body->GetAngle()));
            }

            //This is used for destroying road parts that are too far away from car    
            if(body->GetPosition().x<carbody->getPosition().x/spriteScale-200)//&&body->GetPosition().x>1000) 
            {
                world->DestroyBody(body);
            }

        }

        _car->update(dt);

        world->ClearForces();
    }

    void HillClimbLayer::drawHills()
    {

        //This part of code is from my old project and this draw that nice curvy road

        xOffset=trackWidth;
        yOffset=trackHeight;
        pixelStep=10;

        hillStartY=yOffset;

        hillWidth=520;//+rand() % 200 + 1;
        trackWidth+=hillWidth/2;
        hillSlices=hillWidth/pixelStep;
        if(xOffset==0){randomHeight=0;}
        else
        {
            randomHeight=rand() % 30 - 15;
        }
        randomHeight=50;
        trackHeight+=randomHeight;
        hillStartY+=randomHeight;

        for(int i=0;i<=223;i++)
        {
            rata[0+i]=rata[i+26];
        }

        for(int j=0;j<hillSlices/2;j++)
        {
            int i=1;
            hillPointX=j*pixelStep+hillWidth*i/2+xOffset;

            hillPointY=hillStartY-randomHeight*cos(2*3.14159/hillSlices*j)+yOffset;

            if(hillPointY2!=NULL)
            {
                rata[223+j]=Vec2(hillPointX,hillPointY);
            }
            hillPointY2=hillPointY;
            hillPointX2=hillPointX;
        }

        //draw
        for(int i=1;i<249;i++)
        {
            auto drawNode = cocos2d::DrawNode::create();
            drawNode->setName("drawNode");

            drawNode->drawLine(rata[i-1], rata[i],
            cocos2d::Color4F::RED);
            this->addChild(drawNode);
        }
        trackNumber++;
    }

    cocos2d::Scene* HillClimbLayer::createScene() {
        auto scene = cocos2d::Scene::create();
        auto layer = HillClimbLayer::create();
        layer->init();

        scene->addChild(layer);
        return scene;
    }
}
