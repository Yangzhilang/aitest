//
//  SteeringBehaviors.h
//  aitest
//
//  Created by yzl on 15-1-27.
//
//

#ifndef __aitest__SteeringBehaviors__
#define __aitest__SteeringBehaviors__

#include "BaseGameEntity.h"

class MoveingEntity;

class SteeringBehaviors:public Ref
{
public:
    SteeringBehaviors();
    ~SteeringBehaviors();
    enum BehaviorType{
        kBehaviorNone = 0,
        kBehaviorSeek = 2,
        kBehaviorFlee = 4,
    };
    static SteeringBehaviors *create(MoveingEntity* entity);
    CC_SYNTHESIZE(MoveingEntity*, m_pMovingEntity, MoveingEntity);
    CC_SYNTHESIZE(Vec2, m_vSteeringForce, SteeringForce);
    CC_SYNTHESIZE(MoveingEntity*, m_pTargetAgent1, TargetAgent1);
    CC_SYNTHESIZE(MoveingEntity*, m_pTargetAgent2, TargetAgent2);
    CC_SYNTHESIZE(int, m_iFlag, Flag);
    
    Vec2 caculate();

    Vec2 seek(Vec2 targetPos);
    Vec2 flee(Vec2 targetPos);
    Vec2 arrive(Vec2 targetPos);
    Vec2 wander();
    
    void fleeOn() {m_iFlag |= kBehaviorFlee;}
    
private:
    Vec2 m_vWanderTarget;
    double m_dWanderJitter;
    double m_dWanderRadius;
    double m_dWanderDistance;
};

#endif /* defined(__aitest__SteeringBehaviors__) */
