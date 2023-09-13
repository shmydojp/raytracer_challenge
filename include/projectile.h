#ifndef _PROJECTILE_H
#define _PROJECTILE_H
#include "tuple.h"

namespace Mido::Entity{
    struct Environemt
    {
        Tuple gravity;
        Tuple wind;
        
        Environemt() : gravity({0,0,0,0}), wind({0,0,0,0}) {}
        Environemt(Tuple grav, Tuple wind) 
        : gravity(grav), wind(wind)
          {
          }
          
    };

    struct Projectile
    {
        Tuple position;
        Tuple velocity;

        Projectile() : position({0,0,0,1}), velocity({0,0,0,0}){}
        Projectile(Tuple pos, Tuple vel)
        : position(pos), velocity(vel)
          {
          }
    };

    inline void proj_update(Environemt& env, Projectile& proj){
        proj.position = proj.position + proj.velocity,
        proj.velocity = proj.velocity + env.gravity + env.wind;
    }

};

#endif 