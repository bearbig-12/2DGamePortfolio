#include "RectCollider.h"

// This is the function to make a Object Collider.
RectCollider::RectCollider(sf::RectangleShape& object, int type)
{
	Coll_type = type;
	//Player 
	if (Coll_type == 0 )
	{
		// Need to get Physics width and height.
		float obj_half_width, obj_half_height;
		//obj_half_width = ((object.getSize().x / 2) / Physics_Sub::Scaling_Factor);
		//obj_half_height = ((object.getSize().y / 2) / Physics_Sub::Scaling_Factor);
		obj_half_width = ((object.getSize().x / 2 ) / Physics_Sub::Scaling_Factor) - 0.3f;
		obj_half_height = ((object.getSize().y / 2) / Physics_Sub::Scaling_Factor) - 0.3f;


		//obj_half_width = 0.5f;
		//obj_half_height = 0.3f;

		//std::cout << "Player Half width : " << obj_half_width << " , " << obj_half_height << std::endl;

		b2Vec2 ObjPhysicsPosition;
		//In Box2d Negative y ( -y) is down.
		//But, in sfml, Negative y (-y) is up.
		ObjPhysicsPosition.x = (object.getPosition().x / Scaling_Factor) + obj_half_width;
		ObjPhysicsPosition.y = (object.getPosition().y / Scaling_Factor * -1.0f) - obj_half_height;

		PolygonShape.SetAsBox(obj_half_width, obj_half_height);

		//Create Physics body
		BodyDef.type = b2_dynamicBody;
		BodyDef.position.Set(ObjPhysicsPosition.x, ObjPhysicsPosition.y);
		Object = Physics_Sub::world.CreateBody(&BodyDef);

		//Create Physics body's collider and connect the both.
		fixtureDef.shape = &PolygonShape;
		fixtureDef.density = 1.0f;
		fixtureDef.friction = 1.0f;


		Object->CreateFixture(&fixtureDef);
	}
	//bullet
	if (Coll_type == 1)
	{
		float obj_half_width, obj_half_height;
		obj_half_width = ((object.getSize().x / 2) / Physics_Sub::Scaling_Factor);
		obj_half_height = ((object.getSize().y / 2) / Physics_Sub::Scaling_Factor);


		b2Vec2 ObjPhysicsPosition;
		ObjPhysicsPosition.x = (object.getPosition().x / Scaling_Factor) + obj_half_width;
		ObjPhysicsPosition.y = (object.getPosition().y / Scaling_Factor * -1.0f) - obj_half_height;

		PolygonShape.SetAsBox(obj_half_width, obj_half_height);

		BodyDef.type = b2_dynamicBody;
		BodyDef.bullet = true;
		BodyDef.position.Set(ObjPhysicsPosition.x, ObjPhysicsPosition.y);

		Object = Physics_Sub::world.CreateBody(&BodyDef);

		fixtureDef.shape = &PolygonShape;
		fixtureDef.density = 0.001;
		fixtureDef.friction = 0.001f;



		Object->CreateFixture(&fixtureDef);

	}
	//Enemy
	if (Coll_type == 2)
	{

		float obj_half_width, obj_half_height;
		//obj_half_width = ((object.getSize().x / 2) / Physics_Sub::Scaling_Factor);
		//obj_half_height = ((object.getSize().y / 2) / Physics_Sub::Scaling_Factor);
		obj_half_width = ((object.getSize().x / 2) / Physics_Sub::Scaling_Factor) - 0.3f;
		obj_half_height = ((object.getSize().y / 2) / Physics_Sub::Scaling_Factor) - 0.3f ;

	
		b2Vec2 ObjPhysicsPosition;
		ObjPhysicsPosition.x = (object.getPosition().x / Scaling_Factor) + obj_half_width;
		ObjPhysicsPosition.y = (object.getPosition().y / Scaling_Factor * -1.0f) - obj_half_height;

		PolygonShape.SetAsBox(obj_half_width, obj_half_height);

		BodyDef.type = b2_dynamicBody;
		BodyDef.bullet = true;
		BodyDef.position.Set(ObjPhysicsPosition.x, ObjPhysicsPosition.y);

		Object = Physics_Sub::world.CreateBody(&BodyDef);

		fixtureDef.shape = &PolygonShape;
		fixtureDef.density = 0.0f;
		fixtureDef.friction = 0.0f;



		Object->CreateFixture(&fixtureDef);
		
	}
	//Wall
	if (Coll_type == 3)
	{
		float obj_half_width, obj_half_height;
		obj_half_width = ((object.getSize().x / 2) / Physics_Sub::Scaling_Factor);
		obj_half_height = ((object.getSize().y / 2) / Physics_Sub::Scaling_Factor);

		//obj_half_width = 8.0f;
		//obj_half_height = 0.3f;

		b2Vec2 ObjPhysicsPosition;
		ObjPhysicsPosition.x = (object.getPosition().x / Scaling_Factor) + obj_half_width;
		ObjPhysicsPosition.y = (object.getPosition().y / Scaling_Factor * -1.0f) - obj_half_height;

		PolygonShape.SetAsBox(obj_half_width, obj_half_height);

		BodyDef.type = b2_staticBody;
		BodyDef.position.Set(ObjPhysicsPosition.x, ObjPhysicsPosition.y);



		Object = Physics_Sub::world.CreateBody(&BodyDef);

		fixtureDef.shape = &PolygonShape;

		Object->CreateFixture(&fixtureDef);
	}
		
}

RectCollider::~RectCollider()
{
	// When the RectCollider get deleted, also need to destory it. 
	this->Object->GetWorld()->DestroyBody(this->Object);
}
// When need to covenrt graphics infromation(shape) to physics information(collider)
void RectCollider::GraphicsToPhysicsPos(sf::RectangleShape& GraphicsObject)
{
	float obj_half_width, obj_half_height;
	obj_half_width = ((GraphicsObject.getSize().x / 2) / Physics_Sub::Scaling_Factor);
	obj_half_height = ((GraphicsObject.getSize().y / 2) / Physics_Sub::Scaling_Factor);
	b2Vec2 ObjPhysicsPosition;

	ObjPhysicsPosition.x = (GraphicsObject.getPosition().x + obj_half_width) / Physics_Sub::Scaling_Factor;
	ObjPhysicsPosition.y = ((GraphicsObject.getPosition().y - obj_half_width) / Physics_Sub::Scaling_Factor) * -1.0f;
	Object->SetTransform(ObjPhysicsPosition, 0.0f);
}
// When need to covenrt physics infromation(shape) to graphics information(collider)
void RectCollider::PhysicsToGraphicsPos( sf::RectangleShape& GraphicsObject)
{
	float obj_half_width, obj_half_height;
	obj_half_width = ((GraphicsObject.getSize().x / 2) / Physics_Sub::Scaling_Factor);
	obj_half_height = ((GraphicsObject.getSize().y / 2) / Physics_Sub::Scaling_Factor);

	b2Vec2 PhysicsPosition = this->Object->GetPosition();
	sf::Vector2f GraphicsPosTemp;
	GraphicsPosTemp.x = (PhysicsPosition.x - obj_half_width) * Physics_Sub::Scaling_Factor;
	GraphicsPosTemp.y = ((PhysicsPosition.y + obj_half_width) * Physics_Sub::Scaling_Factor) * -1.0f;

	GraphicsObject.setPosition(GraphicsPosTemp);
}
