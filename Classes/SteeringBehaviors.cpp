//
//  SteeringBehaviors.cpp
//  aitest
//
//  Created by yzl on 15-1-27.
//
//

#include "SteeringBehaviors.h"

SteeringBehaviors::SteeringBehaviors():
            m_dWanderDistance(40),
            m_dWanderJitter(5),
            m_dWanderRadius(30)
{
   float theta = CC_DEGREES_TO_RADIANS(30);
    m_vWanderTarget = Vec2(m_dWanderRadius*sin(theta),m_dWanderRadius*cos(theta));
}

SteeringBehaviors::~SteeringBehaviors()
{}

SteeringBehaviors *SteeringBehaviors::create(MoveingEntity *entity)
{
    SteeringBehaviors *pRet = new SteeringBehaviors();
    pRet->setMoveingEntity(entity);
    if (pRet) {
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return NULL;
}

Vec2 SteeringBehaviors::caculate()
{
    m_vSteeringForce = Vec2::ZERO;
    
    return this->wander();
}

Vec2 SteeringBehaviors::seek(cocos2d::Vec2 targetPos)
{
    Vec2 desiredVelocity = (targetPos-m_pMovingEntity->getPosition()).getNormalized()*m_pMovingEntity->getMaxSpeed();
    return desiredVelocity-m_pMovingEntity->getVelocity();
}

Vec2 SteeringBehaviors::flee(cocos2d::Vec2 targetPos)
{
    const double panicDistance = 100*100;
    if (targetPos.distanceSquared(m_pMovingEntity->getVelocity())>panicDistance) {
        return Vec2(0,0);
    }
    Vec2 desiredVelocity = (m_pMovingEntity->getPosition()-targetPos).getNormalized()*m_pMovingEntity->getMaxSpeed();
    return desiredVelocity-m_pMovingEntity->getVelocity();
}

Vec2 SteeringBehaviors::wander()
{
    m_vWanderTarget += Vec2(CCRANDOM_MINUS1_1()*m_dWanderJitter,
                            CCRANDOM_MINUS1_1()*m_dWanderJitter);
    m_vWanderTarget.normalize();
    m_vWanderTarget *= m_dWanderRadius;
    Vec2 targetLocal = m_vWanderTarget + Vec2(m_dWanderDistance,0);
    AffineTransform transform= __CCAffineTransformMake(m_pMovingEntity->getHeading().x, m_pMovingEntity->getHeading().y, m_pMovingEntity->getSide().x, m_pMovingEntity->getSide().y, 0, 0);
    Vec2 targetWorld = __CCPointApplyAffineTransform(targetLocal,transform);
    
    return targetWorld - m_pMovingEntity->getPosition();
}