 #pragma once
#include "SubSystem_Manager.h"
#include <box2d/box2d.h>
#include "SFML/Graphics.hpp"
class Physics_Sub
{
public:
    // In the project, 
    // do not use any other physics function except the collider,
    // so the physics system is just static but their is child system to make collider.
    

    static b2World world;
    //To convert pixel to meter. 
    // Box2d uses meter but sfml uses pixel.
    // For that, need to change the pixel coordinate to meter.
    static float Scaling_Factor;

};