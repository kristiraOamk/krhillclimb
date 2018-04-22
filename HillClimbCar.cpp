#include "config.h"
#include "HillClimbCar.h"
namespace hillclimb {

    USING_NS_CC;

    #define worldScale 32.0
     
     
    HillClimbCar::HillClimbCar() {
     
    }
     
    HillClimbCar::~HillClimbCar() {
         
    }
     
    void HillClimbCar::accelerate(bool accelerating) {
        _accelerating = accelerating;
    }
     
    void HillClimbCar::reverse(bool reversing) {
        _reversing = reversing;
    }
     
    void HillClimbCar::update(float dt) {
        if(_accelerating) {
            _rearTireRevoluteJoint->SetMotorSpeed(_speed);
            _rearTireRevoluteJoint->SetMaxMotorTorque(_torque);
            _frontTireRevoluteJoint->SetMotorSpeed(_speed);
            _frontTireRevoluteJoint->SetMaxMotorTorque(_torque);
        }
         
    //    if(!_reversing && !_accelerating) {
        if(!_accelerating) {
            _rearTireRevoluteJoint->SetMotorSpeed(0);
            _rearTireRevoluteJoint->SetMaxMotorTorque(0);
            _frontTireRevoluteJoint->SetMotorSpeed(0);
            _frontTireRevoluteJoint->SetMaxMotorTorque(0);
        }
    }


     
    void HillClimbCar::init(b2World* world, Node* parent, Point pos) {
        _torque = 20.0f;
        _speed = 1000.0f;

        //_frontTireSprite = cocos2d::Sprite::create("car.png");
        //_rearTireSprite = cocos2d::Sprite::create("car.png");
        _bodySprite = cocos2d::Sprite::create("car.png");
    //    _driverSprite = Sprite::create("images/head1.png");
        
        //parent->addChild(_frontTireSprite);
        //parent->addChild(_rearTireSprite);
        //parent->addChild(_driverSprite);
        parent->addChild(_bodySprite);
         
        b2BodyDef bodyDef;
        bodyDef.position = b2Vec2(pos.x/PTM_RATIO, pos.y/PTM_RATIO);
        bodyDef.type = b2_dynamicBody;
         
        _body = world->CreateBody(&bodyDef);
        _body->SetUserData(_bodySprite);
        b2PolygonShape carShape;
        carShape.SetAsBox(25.0f/PTM_RATIO, 5.0f/PTM_RATIO);
         
        b2FixtureDef carFixtureDef;
        carFixtureDef.shape = &carShape;
        carFixtureDef.density = 1.1;
        carFixtureDef.friction = 1.0f;
        carFixtureDef.filter.categoryBits = 0x02;
        carFixtureDef.restitution = 2.2;
        carFixtureDef.filter.maskBits = 0x01;
        _body->CreateFixture(&carFixtureDef);
         
         
        b2BodyDef rearTireBodyDef;
        rearTireBodyDef.position.Set((pos.x + -10.0f)/PTM_RATIO, (pos.y - 15.0f)/PTM_RATIO);
        rearTireBodyDef.type = b2_dynamicBody;
         
        _rearTireBody = world->CreateBody(&rearTireBodyDef);
        //_rearTireBody->SetUserData(_rearTireSprite);
        b2CircleShape rearTireShape;
        rearTireShape.m_radius = 8.0f/PTM_RATIO;
         
        b2FixtureDef rearTireFixtureDef;
        rearTireFixtureDef.shape = &rearTireShape;
        rearTireFixtureDef.density = 1.15; //Massa
        rearTireFixtureDef.friction = 0.5f; //kitka
        rearTireFixtureDef.filter.categoryBits = 0x02;
        rearTireFixtureDef.restitution = 0.2; //kimmoisuus
         
        _rearTireBody->CreateFixture(&rearTireFixtureDef);
        b2BodyDef rearAxelBodyDef;
        rearAxelBodyDef.position.Set(_rearTireBody->GetWorldCenter().x, _rearTireBody->GetWorldCenter().y);
        rearAxelBodyDef.type = b2_dynamicBody;
        _rearAxelTireBody = world->CreateBody(&rearAxelBodyDef);
        b2PolygonShape rearAxelShape;
        rearAxelShape.SetAsBox(6.0f/PTM_RATIO, 12.0f/PTM_RATIO, b2Vec2_zero, -0.5);
        b2FixtureDef rearAxelFixtureDef;
        rearAxelFixtureDef.shape = &rearAxelShape;
        rearAxelFixtureDef.density = 0.01f; //Massa
        rearAxelFixtureDef.filter.categoryBits = 0x02;
        rearAxelFixtureDef.filter.maskBits = 2;
     
        _rearAxelTireBody->CreateFixture(&rearAxelFixtureDef);
         
        b2RevoluteJointDef rearWheelRevoluteJointDef;
        rearWheelRevoluteJointDef.enableMotor = true;
        rearWheelRevoluteJointDef.Initialize(_rearTireBody, _rearAxelTireBody, _rearTireBody->GetWorldCenter());
        _rearTireRevoluteJoint = (b2RevoluteJoint*)world->CreateJoint(&rearWheelRevoluteJointDef);
         
        b2PrismaticJointDef rearWheelPrismaticJointDef;
        rearWheelPrismaticJointDef.enableLimit = true;
        rearWheelPrismaticJointDef.enableMotor = true;
        rearWheelPrismaticJointDef.lowerTranslation = -0.3f/PTM_RATIO;
        rearWheelPrismaticJointDef.upperTranslation = 0.5f/PTM_RATIO;
        rearWheelPrismaticJointDef.Initialize(_body, _rearAxelTireBody, b2Vec2(_rearAxelTireBody->GetWorldCenter().x, _rearAxelTireBody->GetWorldCenter().y), b2Vec2(0, 2));
        _rearTirePrismaticJoint = (b2PrismaticJoint*)world->CreateJoint(&rearWheelPrismaticJointDef);
         
        b2BodyDef frontTireBodyDef;
        frontTireBodyDef.position.Set((pos.x + 12.0f)/PTM_RATIO, (pos.y - 15.0f)/PTM_RATIO);
        frontTireBodyDef.type = b2_dynamicBody;
         
        _frontTireBody = world->CreateBody(&frontTireBodyDef);
        //_frontTireBody->SetUserData(_frontTireSprite);
        b2CircleShape frontTireShape;
        frontTireShape.m_radius = 8.0f / PTM_RATIO;
         
        b2FixtureDef frontTireFixtureDef;
        frontTireFixtureDef.shape = &frontTireShape;
        frontTireFixtureDef.density = 1.15;
        frontTireFixtureDef.friction = 0.5;
        frontTireFixtureDef.filter.categoryBits = 0x02;
        frontTireFixtureDef.restitution = 0.2;
        _frontTireBody->CreateFixture(&frontTireFixtureDef);
     
        b2BodyDef frontAxelBodyDef;
        frontAxelBodyDef.position.Set(_frontTireBody->GetWorldCenter().x, _frontTireBody->GetWorldCenter().y);
        frontAxelBodyDef.type = b2_dynamicBody;
        _frontAxelTireBody = world->CreateBody(&frontAxelBodyDef);
        b2PolygonShape frontAxelShape;
        frontAxelShape.SetAsBox(6.0f/PTM_RATIO, 12.0f/PTM_RATIO, b2Vec2_zero, 0.5);
        b2FixtureDef frontAxelFixtureDef;
        frontAxelFixtureDef.shape = &frontAxelShape;
        frontAxelFixtureDef.density = 0.01f;
        frontAxelFixtureDef.filter.categoryBits = 0x01;
        frontAxelFixtureDef.filter.maskBits = 2;
         
        _frontAxelTireBody->CreateFixture(&frontAxelFixtureDef);
         
        b2RevoluteJointDef frontWheelRevoluteJointDef;
        frontWheelRevoluteJointDef.enableMotor = true;
        frontWheelRevoluteJointDef.Initialize(_frontTireBody, _frontAxelTireBody, _frontTireBody->GetWorldCenter());
        _frontTireRevoluteJoint = (b2RevoluteJoint*)world->CreateJoint(&frontWheelRevoluteJointDef);
         
        b2PrismaticJointDef frontWheelPrismaticJointDef;
        frontWheelPrismaticJointDef.enableLimit = true;
        frontWheelPrismaticJointDef.enableMotor = true;
        frontWheelPrismaticJointDef.lowerTranslation = -1.3f/PTM_RATIO;
        frontWheelPrismaticJointDef.upperTranslation = 1.5f/PTM_RATIO;
    /*    
        frontWheelPrismaticJointDef->setMaxMotorForce(1.0f);
        frontWheelPrismaticJointDef->setMotorSpeed(1.0f);
        frontWheelPrismaticJointDef->setMaxMotorForce(1.0f);
    */
        frontWheelPrismaticJointDef.Initialize(_body, _frontAxelTireBody, b2Vec2(_frontAxelTireBody->GetWorldCenter().x, _frontAxelTireBody->GetWorldCenter().y), b2Vec2(0, 2));
        _frontTirePrismaticJoint = (b2PrismaticJoint*)world->CreateJoint(&frontWheelPrismaticJointDef);

    /*
        b2PrismaticJointDef frontWheelPrismaticJointDef;
        frontWheelPrismaticJointDef.enableLimit = true;
        frontWheelPrismaticJointDef.enableMotor = true;
        frontWheelPrismaticJointDef.lowerTranslation = -0.3f/PTM_RATIO;
        frontWheelPrismaticJointDef.upperTranslation = 0.5f/PTM_RATIO;
        frontWheelPrismaticJointDef.Initialize(_body, _frontAxelTireBody, b2Vec2(_frontAxelTireBody->GetWorldCenter().x, _frontAxelTireBody->GetWorldCenter().y), b2Vec2(0, 2));
        _frontTirePrismaticJoint = (b2PrismaticJoint*)world->CreateJoint(&frontWheelPrismaticJointDef);
        */
    }
}