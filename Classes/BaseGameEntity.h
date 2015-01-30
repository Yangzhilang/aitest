//
//  BaseGameEntity.h
//  aitest
//
//  Created by yzl on 15-1-27.
//
//

#ifndef __aitest__BaseGameEntity__
#define __aitest__BaseGameEntity__

#include "cocos2d.h"
using namespace cocos2d;
#include "SteeringBehaviors.h"

class SteeringBehaviors;

class MoveingEntity:public Sprite
{
public:
    MoveingEntity();
    ~MoveingEntity();
    static MoveingEntity* create(const char* fileName);
    void customInit();
    CC_SYNTHESIZE(int, m_iID, EntityID);
    CC_SYNTHESIZE(Vec2, m_vVelocity, Velocity);
    CC_SYNTHESIZE(Vec2, m_vHeading, Heading);
    CC_SYNTHESIZE(Vec2, m_vSide, Side);  //垂直于朝向
    CC_SYNTHESIZE(double, m_dMass, Mass);
    CC_SYNTHESIZE(double, m_dMaxSpeed, MaxSpeed);
    CC_SYNTHESIZE(double, m_dMaxForce, MaxForce);
    CC_SYNTHESIZE(SteeringBehaviors*, m_pSteering, Steering);
    CC_SYNTHESIZE(double, m_dMaxTurnRate, MaxTurnRate);
    virtual void update(float dt);
};

#endif /* defined(__aitest__BaseGameEntity__) */
