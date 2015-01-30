//
//  BaseGameEntity.cpp
//  aitest
//
//  Created by yzl on 15-1-27.
//
//

#include "BaseGameEntity.h"

MoveingEntity::MoveingEntity()
{
    m_pSteering = SteeringBehaviors::create(this);
}

MoveingEntity::~MoveingEntity()
{
    m_pSteering->release();
}

MoveingEntity *MoveingEntity::create(const char *fileName)
{
    MoveingEntity *pRet = new MoveingEntity();
    if (pRet && pRet->initWithFile(fileName)) {
        pRet->customInit();
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return NULL;
}

void MoveingEntity::customInit()
{
    m_vHeading = Vec2(1,0);
    m_vSide = Vec2(0,-1);
    this->scheduleUpdate();
}

void MoveingEntity::update(float dt)
{
    Vec2 force = m_pSteering->caculate();
    Vec2 accelerate = force/m_dMass;
    m_vVelocity += dt * accelerate;
    
    if (m_vVelocity.length() > m_dMaxSpeed) {
        m_vVelocity = m_vVelocity.getNormalized()*m_dMaxSpeed;
    }
    
    this->setPosition(this->getPosition()+dt*m_vVelocity);
    
    if (m_vVelocity.lengthSquared() > .00001f) {
        m_vHeading = m_vVelocity.getNormalized();
        m_vSide = m_vHeading.getPerp();
    }
}