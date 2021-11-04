CMAKE_MINIMUM_REQUIRED(VERSION 3.21)
PROJECT( game2 )

SET( CC "g++")
SET( CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -std=c++14 -pedantic -g3 -ggdb3 -fdiagnostics-color=always" )
SET( CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -std=c++14 -g0 O2" )

SET( CMAKE_BUILD_TYPE "Debug" )
SET( SOURCE_FILES
	src/main.cpp
    src/app.cpp
    src/systems.cpp
    src/components.cpp
    src/player/components.cpp
)
FIND_PACKAGE(SFML 2.5 COMPONENTS network system window graphics)

INCLUDE_DIRECTORIES( include )
INCLUDE_DIRECTORIES( src )

INCLUDE_DIRECTORIES( 
    /usr/local/Cellar/sdl2/2.0.16/include/SDL2
    /usr/local/Cellar/sdl2_image/2.0.5/include/SDL2 
    /usr/local/Cellar/glm/0.9.9.8/include
    /usr/local/Cellar/entityx/1.3.0/include
    )

ADD_EXECUTABLE( game2
	${SOURCE_FILES}
)

TARGET_LINK_LIBRARIES( game2 
"-L/usr/local/Cellar/sdl2/2.0.16/lib  -lSDL2" 
"-L/usr/local/Cellar/sdl2_image/2.0.5/lib -lSDL2_image"
"-L/usr/local/Cellar/entityx/1.3.0/lib -lentityx"
sfml-graphics 
sfml-audio
)

INSTALL(TARGETS game2
        RUNTIME DESTINATION .)