QT -= gui

CONFIG += c++17 console
CONFIG -= app_bundle

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Confirm that we are using Qt IDE with the engine
DEFINES += IS_ENGINE_QT

# Game source files
HEADERS += \
		../cpp/app_src/activity/GameActivity.h \
		../cpp/app_src/config/ExtraConfig.h \
		../cpp/app_src/config/GameConfig.h \
		../cpp/app_src/gamesystem_ext/GameSystemExtended.h \
		../cpp/app_src/language/GameLanguage.h \
		../cpp/app_src/objects/HelloWorld.h \
		../cpp/app_src/objects/widgets/GameDialog.h \
		../cpp/app_src/scenes/HelloScene/HelloScene.h

SOURCES += \
        ../cpp/app_src/gamesystem_ext/GameSystemExtended.cpp \
        ../cpp/app_src/objects/widgets/GameDialog.cpp \
        ../cpp/basicSFMLmain.cpp

# is::Engine source files
HEADERS += \
		../cpp/isEngine/core/ActivityController.h \
		../cpp/isEngine/core/GameEngine.h \
		../cpp/isEngine/system/android/AdmobManager.h \
		../cpp/isEngine/system/display/GameDisplay.h \
		../cpp/isEngine/system/display/SDM.h \
		../cpp/isEngine/system/entity/Background.h \
		../cpp/isEngine/system/entity/Button.h \
		../cpp/isEngine/system/entity/Form.h \
		../cpp/isEngine/system/entity/MainObject.h \
		../cpp/isEngine/system/entity/parents/DepthObject.h \
		../cpp/isEngine/system/entity/parents/Destructible.h \
		../cpp/isEngine/system/entity/parents/FilePath.h \
		../cpp/isEngine/system/entity/parents/Health.h \
		../cpp/isEngine/system/entity/parents/HurtEffect.h \
		../cpp/isEngine/system/entity/parents/Name.h \
		../cpp/isEngine/system/entity/parents/ScorePoint.h \
		../cpp/isEngine/system/entity/parents/Step.h \
		../cpp/isEngine/system/entity/parents/Type.h \
		../cpp/isEngine/system/entity/parents/Visibilty.h \
		../cpp/isEngine/system/function/GameFunction.h \
		../cpp/isEngine/system/function/GameKeyData.h \
		../cpp/isEngine/system/function/GameKeyName.h \
		../cpp/isEngine/system/function/GameSlider.h \
		../cpp/isEngine/system/function/GameSystem.h \
		../cpp/isEngine/system/function/GameTime.h \
		../cpp/isEngine/system/graphic/GRM.h \
		../cpp/isEngine/system/graphic/GameFont.h \
		../cpp/isEngine/system/graphic/GameTexture.h \
		../cpp/isEngine/system/graphic/TransitionEffect.h \
        ../cpp/isEngine/system/islibconnect/isEngineWrapper.h \
        ../cpp/isEngine/system/islibconnect/isLibConnect.h \
		../cpp/isEngine/system/sound/GSM.h \
		../cpp/isEngine/system/sound/GameMusic.h \
		../cpp/isEngine/system/sound/GameSound.h \
		../cpp/isEngine/ext_lib/Box2D/Box2D.h \
		../cpp/isEngine/ext_lib/Box2D/Collision/Shapes/b2ChainShape.h \
		../cpp/isEngine/ext_lib/Box2D/Collision/Shapes/b2CircleShape.h \
		../cpp/isEngine/ext_lib/Box2D/Collision/Shapes/b2EdgeShape.h \
		../cpp/isEngine/ext_lib/Box2D/Collision/Shapes/b2PolygonShape.h \
		../cpp/isEngine/ext_lib/Box2D/Collision/Shapes/b2Shape.h \
		../cpp/isEngine/ext_lib/Box2D/Collision/b2BroadPhase.h \
		../cpp/isEngine/ext_lib/Box2D/Collision/b2Collision.h \
		../cpp/isEngine/ext_lib/Box2D/Collision/b2Distance.h \
		../cpp/isEngine/ext_lib/Box2D/Collision/b2DynamicTree.h \
		../cpp/isEngine/ext_lib/Box2D/Collision/b2TimeOfImpact.h \
		../cpp/isEngine/ext_lib/Box2D/Common/b2BlockAllocator.h \
		../cpp/isEngine/ext_lib/Box2D/Common/b2Draw.h \
		../cpp/isEngine/ext_lib/Box2D/Common/b2GrowableStack.h \
		../cpp/isEngine/ext_lib/Box2D/Common/b2Math.h \
		../cpp/isEngine/ext_lib/Box2D/Common/b2Settings.h \
		../cpp/isEngine/ext_lib/Box2D/Common/b2StackAllocator.h \
		../cpp/isEngine/ext_lib/Box2D/Common/b2Timer.h \
		../cpp/isEngine/ext_lib/Box2D/Dynamics/Contacts/b2ChainAndCircleContact.h \
		../cpp/isEngine/ext_lib/Box2D/Dynamics/Contacts/b2ChainAndPolygonContact.h \
		../cpp/isEngine/ext_lib/Box2D/Dynamics/Contacts/b2CircleContact.h \
		../cpp/isEngine/ext_lib/Box2D/Dynamics/Contacts/b2Contact.h \
		../cpp/isEngine/ext_lib/Box2D/Dynamics/Contacts/b2ContactSolver.h \
		../cpp/isEngine/ext_lib/Box2D/Dynamics/Contacts/b2EdgeAndCircleContact.h \
		../cpp/isEngine/ext_lib/Box2D/Dynamics/Contacts/b2EdgeAndPolygonContact.h \
		../cpp/isEngine/ext_lib/Box2D/Dynamics/Contacts/b2PolygonAndCircleContact.h \
		../cpp/isEngine/ext_lib/Box2D/Dynamics/Contacts/b2PolygonContact.h \
		../cpp/isEngine/ext_lib/Box2D/Dynamics/Joints/b2DistanceJoint.h \
		../cpp/isEngine/ext_lib/Box2D/Dynamics/Joints/b2FrictionJoint.h \
		../cpp/isEngine/ext_lib/Box2D/Dynamics/Joints/b2GearJoint.h \
		../cpp/isEngine/ext_lib/Box2D/Dynamics/Joints/b2Joint.h \
		../cpp/isEngine/ext_lib/Box2D/Dynamics/Joints/b2MotorJoint.h \
		../cpp/isEngine/ext_lib/Box2D/Dynamics/Joints/b2MouseJoint.h \
		../cpp/isEngine/ext_lib/Box2D/Dynamics/Joints/b2PrismaticJoint.h \
		../cpp/isEngine/ext_lib/Box2D/Dynamics/Joints/b2PulleyJoint.h \
		../cpp/isEngine/ext_lib/Box2D/Dynamics/Joints/b2RevoluteJoint.h \
		../cpp/isEngine/ext_lib/Box2D/Dynamics/Joints/b2RopeJoint.h \
		../cpp/isEngine/ext_lib/Box2D/Dynamics/Joints/b2WeldJoint.h \
		../cpp/isEngine/ext_lib/Box2D/Dynamics/Joints/b2WheelJoint.h \
		../cpp/isEngine/ext_lib/Box2D/Dynamics/b2Body.h \
		../cpp/isEngine/ext_lib/Box2D/Dynamics/b2ContactManager.h \
		../cpp/isEngine/ext_lib/Box2D/Dynamics/b2Fixture.h \
		../cpp/isEngine/ext_lib/Box2D/Dynamics/b2Island.h \
		../cpp/isEngine/ext_lib/Box2D/Dynamics/b2TimeStep.h \
		../cpp/isEngine/ext_lib/Box2D/Dynamics/b2World.h \
		../cpp/isEngine/ext_lib/Box2D/Dynamics/b2WorldCallbacks.h \
		../cpp/isEngine/ext_lib/Box2D/Rope/b2Rope.h \
		../cpp/isEngine/ext_lib/TinyFileDialogs/TinyDialogBox.h \
		../cpp/isEngine/ext_lib/TinyFileDialogs/tinyfiledialogs.h

SOURCES += \
        ../cpp/isEngine/core/GameEngine.cpp \
        ../cpp/isEngine/system/display/GameDisplay.cpp \
        ../cpp/isEngine/system/entity/MainObject.cpp \
        ../cpp/isEngine/system/function/GameFunction.cpp \
        ../cpp/isEngine/system/function/GameKeyData.cpp \
        ../cpp/isEngine/system/function/GameSlider.cpp \
        ../cpp/isEngine/system/function/GameSystem.cpp \
        ../cpp/isEngine/system/function/GameTime.cpp \
        ../cpp/isEngine/system/graphic/TransitionEffect.cpp \
        ../cpp/isEngine/system/islibconnect/isEngineWrapper.cpp \
        ../cpp/isEngine/ext_lib/Box2D/Collision/Shapes/b2ChainShape.cpp \
        ../cpp/isEngine/ext_lib/Box2D/Collision/Shapes/b2CircleShape.cpp \
        ../cpp/isEngine/ext_lib/Box2D/Collision/Shapes/b2EdgeShape.cpp \
        ../cpp/isEngine/ext_lib/Box2D/Collision/Shapes/b2PolygonShape.cpp \
        ../cpp/isEngine/ext_lib/Box2D/Collision/b2BroadPhase.cpp \
        ../cpp/isEngine/ext_lib/Box2D/Collision/b2CollideCircle.cpp \
        ../cpp/isEngine/ext_lib/Box2D/Collision/b2CollideEdge.cpp \
        ../cpp/isEngine/ext_lib/Box2D/Collision/b2CollidePolygon.cpp \
        ../cpp/isEngine/ext_lib/Box2D/Collision/b2Collision.cpp \
        ../cpp/isEngine/ext_lib/Box2D/Collision/b2Distance.cpp \
        ../cpp/isEngine/ext_lib/Box2D/Collision/b2DynamicTree.cpp \
        ../cpp/isEngine/ext_lib/Box2D/Collision/b2TimeOfImpact.cpp \
        ../cpp/isEngine/ext_lib/Box2D/Common/b2BlockAllocator.cpp \
        ../cpp/isEngine/ext_lib/Box2D/Common/b2Draw.cpp \
        ../cpp/isEngine/ext_lib/Box2D/Common/b2Math.cpp \
        ../cpp/isEngine/ext_lib/Box2D/Common/b2Settings.cpp \
        ../cpp/isEngine/ext_lib/Box2D/Common/b2StackAllocator.cpp \
        ../cpp/isEngine/ext_lib/Box2D/Common/b2Timer.cpp \
        ../cpp/isEngine/ext_lib/Box2D/Dynamics/Contacts/b2ChainAndCircleContact.cpp \
        ../cpp/isEngine/ext_lib/Box2D/Dynamics/Contacts/b2ChainAndPolygonContact.cpp \
        ../cpp/isEngine/ext_lib/Box2D/Dynamics/Contacts/b2CircleContact.cpp \
        ../cpp/isEngine/ext_lib/Box2D/Dynamics/Contacts/b2Contact.cpp \
        ../cpp/isEngine/ext_lib/Box2D/Dynamics/Contacts/b2ContactSolver.cpp \
        ../cpp/isEngine/ext_lib/Box2D/Dynamics/Contacts/b2EdgeAndCircleContact.cpp \
        ../cpp/isEngine/ext_lib/Box2D/Dynamics/Contacts/b2EdgeAndPolygonContact.cpp \
        ../cpp/isEngine/ext_lib/Box2D/Dynamics/Contacts/b2PolygonAndCircleContact.cpp \
        ../cpp/isEngine/ext_lib/Box2D/Dynamics/Contacts/b2PolygonContact.cpp \
        ../cpp/isEngine/ext_lib/Box2D/Dynamics/Joints/b2DistanceJoint.cpp \
        ../cpp/isEngine/ext_lib/Box2D/Dynamics/Joints/b2FrictionJoint.cpp \
        ../cpp/isEngine/ext_lib/Box2D/Dynamics/Joints/b2GearJoint.cpp \
        ../cpp/isEngine/ext_lib/Box2D/Dynamics/Joints/b2Joint.cpp \
        ../cpp/isEngine/ext_lib/Box2D/Dynamics/Joints/b2MotorJoint.cpp \
        ../cpp/isEngine/ext_lib/Box2D/Dynamics/Joints/b2MouseJoint.cpp \
        ../cpp/isEngine/ext_lib/Box2D/Dynamics/Joints/b2PrismaticJoint.cpp \
        ../cpp/isEngine/ext_lib/Box2D/Dynamics/Joints/b2PulleyJoint.cpp \
        ../cpp/isEngine/ext_lib/Box2D/Dynamics/Joints/b2RevoluteJoint.cpp \
        ../cpp/isEngine/ext_lib/Box2D/Dynamics/Joints/b2RopeJoint.cpp \
        ../cpp/isEngine/ext_lib/Box2D/Dynamics/Joints/b2WeldJoint.cpp \
        ../cpp/isEngine/ext_lib/Box2D/Dynamics/Joints/b2WheelJoint.cpp \
        ../cpp/isEngine/ext_lib/Box2D/Dynamics/b2Body.cpp \
        ../cpp/isEngine/ext_lib/Box2D/Dynamics/b2ContactManager.cpp \
        ../cpp/isEngine/ext_lib/Box2D/Dynamics/b2Fixture.cpp \
        ../cpp/isEngine/ext_lib/Box2D/Dynamics/b2Island.cpp \
        ../cpp/isEngine/ext_lib/Box2D/Dynamics/b2World.cpp \
        ../cpp/isEngine/ext_lib/Box2D/Dynamics/b2WorldCallbacks.cpp \
        ../cpp/isEngine/ext_lib/Box2D/Rope/b2Rope.cpp \
        ../cpp/isEngine/ext_lib/TinyFileDialogs/tinyfiledialogs.cpp \
        ../cpp/main.cpp

LIBS += -LC:\SFML_Qt_MinGW\lib\

CONFIG(debug, debug|release): LIBS += -lsfml-audio-d \
                                    -lsfml-network-d \
                                    -lsfml-graphics-d \
                                    -lsfml-window-d \
                                    -lsfml-system-d \
                                    -lsfml-main-d \
                                    # Only for Tiny File Dialog Windows
                                    -lOle32 \
                                    -lcomdlg32

CONFIG(release, debug|release): LIBS += -lsfml-audio \
                                    -lsfml-network \
                                    -lsfml-graphics \
                                    -lsfml-window \
                                    -lsfml-system \
                                    -lsfml-main \
                                    # Only for Tiny File Dialog Windows
                                    -lOle32 \
                                    -lcomdlg32

INCLUDEPATH += C:\SFML_Qt_MinGW\include
DEPENDPATH += C:\SFML_Qt_MinGW\include

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
