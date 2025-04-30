include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.0
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

add_executable(example)

target_include_directories(example PRIVATE .)

target_sources(example PRIVATE
    main.cpp
    CollidableShape.cpp
    CircleCollidableShape.cpp
    ConcaveCollidableShape.cpp
    ConvexCollidableShape.cpp
    RectangleCollidableShape.cpp
)

target_compile_definitions(
    example PRIVATE

    SFML_STATIC
)

target_link_libraries(
    example PRIVATE

    Collider2D

    SFML::Graphics
    SFML::Window
    SFML::System
)

add_custom_target(copy_assets
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/assets ${CMAKE_CURRENT_BINARY_DIR}/assets
)
add_dependencies(example copy_assets)
