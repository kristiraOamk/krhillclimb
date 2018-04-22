#ifndef __HILLCLIMB_CAR_H__
#define __HILLCLIMB_CAR_H__
 
#include <Box2d/Box2D.h>
#include "cocos2d.h"

#define PTM_RATIO 10
 


USING_NS_CC;
namespace hillclimb {
class HillClimbCar {
private:
    bool _accelerating;
    bool _reversing;
 
    float _speed;
    float _torque;
     
    Sprite* _bodySprite;
    Sprite* _frontTireSprite;
   // Sprite* _driverSprite;
    Sprite* _rearTireSprite;
     
    b2Body* _frontTireBody;
    b2Body* _frontAxelTireBody;
    b2Body* _rearTireBody;
    b2Body* _rearAxelTireBody;
    b2Body* _body;
   // b2Body* _headBody;
     
    b2RevoluteJoint* _rearTireRevoluteJoint;
    b2PrismaticJoint* _rearTirePrismaticJoint;
    b2RevoluteJoint* _frontTireRevoluteJoint;
    b2PrismaticJoint* _frontTirePrismaticJoint;
    //b2RevoluteJoint* _neckRevoluteJoint;
public:
    HillClimbCar();
    ~HillClimbCar();
   
    void init(b2World* world, Node* parent, Point pos);
     
    void accelerate(bool accelerating);
    void reverse(bool reversing);
 
    //our camera class needs to get a target body which to follow
    b2Body* getBody() {
        return _body;
    }
 
    //for collision detection
    Sprite* getSprite() {
        return _bodySprite;
    }
     
    void update(float dt);
};
}
#endif