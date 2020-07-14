# engine source file
set(
    isengine

	main.cpp

	# Basic SFML rendering loop
	basicSFMLmain.cpp

	# core
	isEngine/core/GameEngine.cpp

	# system
	# display
	isEngine/system/display/GameDisplay.cpp
	
	# entity
	isEngine/system/entity/MainObject.cpp
	
	# function
	isEngine/system/function/GameFunction.cpp		
	isEngine/system/function/GameKeyData.cpp
	isEngine/system/function/GameSystem.cpp
	isEngine/system/function/GameTime.cpp
	
	# ext
	isEngine/ext_lib/TinyFileDialogs/tinyfiledialogs.cpp
	
	# box 2d source
	isEngine/ext_lib/Box2D/Collision/b2BroadPhase.cpp
	isEngine/ext_lib/Box2D/Collision/b2CollideCircle.cpp
	isEngine/ext_lib/Box2D/Collision/b2CollideEdge.cpp
	isEngine/ext_lib/Box2D/Collision/b2CollidePolygon.cpp
	isEngine/ext_lib/Box2D/Collision/b2Collision.cpp
	isEngine/ext_lib/Box2D/Collision/b2Distance.cpp
	isEngine/ext_lib/Box2D/Collision/b2DynamicTree.cpp
	isEngine/ext_lib/Box2D/Collision/b2TimeOfImpact.cpp
	isEngine/ext_lib/Box2D/Collision/Shapes/b2CircleShape.cpp
	isEngine/ext_lib/Box2D/Collision/Shapes/b2EdgeShape.cpp
	isEngine/ext_lib/Box2D/Collision/Shapes/b2ChainShape.cpp
	isEngine/ext_lib/Box2D/Collision/Shapes/b2PolygonShape.cpp
	isEngine/ext_lib/Box2D/Common/b2BlockAllocator.cpp
	isEngine/ext_lib/Box2D/Common/b2Draw.cpp
	isEngine/ext_lib/Box2D/Common/b2Math.cpp
	isEngine/ext_lib/Box2D/Common/b2Settings.cpp
	isEngine/ext_lib/Box2D/Common/b2StackAllocator.cpp
	isEngine/ext_lib/Box2D/Common/b2Timer.cpp
	isEngine/ext_lib/Box2D/Dynamics/b2Body.cpp
	isEngine/ext_lib/Box2D/Dynamics/b2ContactManager.cpp
	isEngine/ext_lib/Box2D/Dynamics/b2Fixture.cpp
	isEngine/ext_lib/Box2D/Dynamics/b2Island.cpp
	isEngine/ext_lib/Box2D/Dynamics/b2World.cpp
	isEngine/ext_lib/Box2D/Dynamics/b2WorldCallbacks.cpp
	isEngine/ext_lib/Box2D/Dynamics/Contacts/b2CircleContact.cpp
	isEngine/ext_lib/Box2D/Dynamics/Contacts/b2Contact.cpp
	isEngine/ext_lib/Box2D/Dynamics/Contacts/b2ContactSolver.cpp
	isEngine/ext_lib/Box2D/Dynamics/Contacts/b2PolygonAndCircleContact.cpp
	isEngine/ext_lib/Box2D/Dynamics/Contacts/b2EdgeAndCircleContact.cpp
	isEngine/ext_lib/Box2D/Dynamics/Contacts/b2EdgeAndPolygonContact.cpp
	isEngine/ext_lib/Box2D/Dynamics/Contacts/b2ChainAndCircleContact.cpp
	isEngine/ext_lib/Box2D/Dynamics/Contacts/b2ChainAndPolygonContact.cpp
	isEngine/ext_lib/Box2D/Dynamics/Contacts/b2PolygonContact.cpp
	isEngine/ext_lib/Box2D/Dynamics/Joints/b2DistanceJoint.cpp
	isEngine/ext_lib/Box2D/Dynamics/Joints/b2FrictionJoint.cpp
	isEngine/ext_lib/Box2D/Dynamics/Joints/b2GearJoint.cpp
	isEngine/ext_lib/Box2D/Dynamics/Joints/b2Joint.cpp
	isEngine/ext_lib/Box2D/Dynamics/Joints/b2MotorJoint.cpp
	isEngine/ext_lib/Box2D/Dynamics/Joints/b2MouseJoint.cpp
	isEngine/ext_lib/Box2D/Dynamics/Joints/b2PrismaticJoint.cpp
	isEngine/ext_lib/Box2D/Dynamics/Joints/b2PulleyJoint.cpp
	isEngine/ext_lib/Box2D/Dynamics/Joints/b2RevoluteJoint.cpp
	isEngine/ext_lib/Box2D/Dynamics/Joints/b2RopeJoint.cpp
	isEngine/ext_lib/Box2D/Dynamics/Joints/b2WeldJoint.cpp
	isEngine/ext_lib/Box2D/Dynamics/Joints/b2WheelJoint.cpp
)