add_library(${PROJECT_NAME} STATIC
    ./src/AABBCollision.cpp
    ./src/CircleCollision.cpp
    ./src/CompoundCollision.cpp
    ./src/ConvexCollision.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC ./include)
