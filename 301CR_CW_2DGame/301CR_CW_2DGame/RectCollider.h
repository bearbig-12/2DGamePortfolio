#pragma once
#include "Physics_Sub.h"
#include <iostream>

// This is the Object's collider class.
// This class get world value from physics subsystem and make
// objects collider.
class RectCollider :
    public Physics_Sub
{
public:
    RectCollider() {};
    RectCollider(sf::RectangleShape& object, int type);
    virtual ~RectCollider();

    void GraphicsToPhysicsPos(sf::RectangleShape& GraphicsObject);
    void PhysicsToGraphicsPos(sf::RectangleShape& GraphicsObject);
    b2PolygonShape PolygonShape;
    b2BodyDef BodyDef;


    b2FixtureDef fixtureDef;
    b2Body* Object;

    b2BodyDef BulletBodyDef;
    
    //Main player = 0
    //bullet = 1
    //Enemy = 2
    // Wall =3
    int Coll_type;
};

