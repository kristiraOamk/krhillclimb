#ifndef __HILLCLIMB_LAYER_H__
#define __HILLCLIMB_LAYER_H__

#include <memory>
#include <map>
#include <chrono>

#include "cocos2d.h"
#include <Box2D/Box2D.h>
#include "HillClimbCar.h"
// Add missing includes here

USING_NS_CC;

namespace hillclimb {

    class HillClimbLayer : public cocos2d::Layer, public b2ContactListener {
    private:
        HillClimbCar* _car;
    public:
        static cocos2d::Scene* createScene();
        virtual bool init();
        
        CREATE_FUNC(HillClimbLayer);
        void update(float dt);
        bool isKeyPressed(cocos2d::EventKeyboard::KeyCode);
        void generateSomethingToHit();
        static std::map<cocos2d::EventKeyboard::KeyCode,
        std::chrono::high_resolution_clock::time_point> keys;

        b2World *world;
        float deltaTime;
        DrawNode *ln;
        double spriteScale;
    
        float hillStartY;
        float hillWidth;
        float hillSlices;
        float randomHeight;
        b2Vec2 hillPoint;
        float hillX;
        float hillY;
        int numberOfTracks;

        Vec2 rata[250];
        
        float hillLastX;
        float hillLastY;
        Label label;
        float ballPlace;

        int trackNumber;
        float trackSize[131];
        float trackWidth;
        float trackHeight;
        float xOffset;
        float yOffset;
        int pixelStep;

        int hillPointX;
        int hillPointY;
        int hillPointX2;
        int hillPointY2;
        //Car field;
        //Road field;
        cocos2d::Sprite* carSprite; // autoreleased by cocos2d so no need to delete
        double carStartY;
    
        void generateRoadParts();
        void deleteRoadParts();
        void drawHills();

    };

    cocos2d::Scene* createScene();
}
#endif // __HILLCLIMB_LAYER_H__
