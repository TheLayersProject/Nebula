cmake_minimum_required(VERSION 3.10)
project(Nebula)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if (WIN32)
    set(CMAKE_PREFIX_PATH "C:/Qt/6.9.0/msvc2022_64")
else()
    set(CMAKE_PREFIX_PATH "/Users/huntermalm/Qt/6.9.0/macos")
endif()

set(LAYERS_DIR $ENV{Layers})
set(QLAYERS_DIR $ENV{QLayers})
set(FUSION_DIR $ENV{Fusion})
set(VORTEX_DIR $ENV{Vortex})

# Find Qt modules
find_package(Qt6 6.9.0 COMPONENTS Core Gui Widgets Svg Network Concurrent REQUIRED)

# Set the definitions for Nebula
file(GLOB DEFINITIONS "definitions/definitions.cpp")

# Set the source files for Nebula
file(GLOB SOURCES "src/*.cpp")

# Set private header files for Nebula
file(GLOB PRIVATE_HEADERS "src/*.h")

# Generate moc files for all headers with Q_OBJECT
qt6_wrap_cpp(MOC_FILES ${PRIVATE_HEADERS})

# Set the resource files
set(IMAGES "images/images.qrc")

# Generate resource files
qt6_add_resources(IMAGES_RC ${IMAGES})

# Add the executable target
add_executable(Nebula ${SOURCES} ${DEFINITIONS} ${MOC_FILES} ${IMAGES_RC})

# Include directories
target_include_directories(Nebula PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
    "${LAYERS_DIR}/include"
    "${QLAYERS_DIR}/include"
    "${FUSION_DIR}/include"
    "${VORTEX_DIR}/include"
)

if(WIN32)
    set(LAYERS_LIBRARY_DEBUG "${LAYERS_DIR}/lib/Debug/Layersd.lib")
    set(LAYERS_LIBRARY_RELEASE "${LAYERS_DIR}/lib/Release/Layers.lib")
    set(QLAYERS_LIBRARY_DEBUG "${QLAYERS_DIR}/lib/Debug/QLayersd.lib")
    set(QLAYERS_LIBRARY_RELEASE "${QLAYERS_DIR}/lib/Release/QLayers.lib")
    set(FUSION_LIBRARY_DEBUG "${FUSION_DIR}/lib/Debug/Fusiond.lib")
    set(FUSION_LIBRARY_RELEASE "${FUSION_DIR}/lib/Release/Fusion.lib")
    set(VORTEX_LIBRARY_DEBUG "${VORTEX_DIR}/lib/Debug/Vortexd.lib")
    set(VORTEX_LIBRARY_RELEASE "${VORTEX_DIR}/lib/Release/Vortex.lib")
else()
    set(LAYERS_LIBRARY_DEBUG "${LAYERS_DIR}/lib/libLayersd.dylib")
    set(LAYERS_LIBRARY_RELEASE "${LAYERS_DIR}/lib/libLayers.dylib")
    set(QLAYERS_LIBRARY_DEBUG "${QLAYERS_DIR}/lib/libQLayersd.dylib")
    set(QLAYERS_LIBRARY_RELEASE "${QLAYERS_DIR}/lib/libQLayers.dylib")
    set(FUSION_LIBRARY_DEBUG "${FUSION_DIR}/lib/libFusiond.dylib")
    set(FUSION_LIBRARY_RELEASE "${FUSION_DIR}/lib/libFusion.dylib")
    set(VORTEX_LIBRARY_DEBUG "${VORTEX_DIR}/lib/libVortexd.dylib")
    set(VORTEX_LIBRARY_RELEASE "${VORTEX_DIR}/lib/libVortex.dylib")
endif()

# Link with the appropriate libraries and Qt6 libraries
target_link_libraries(Nebula PRIVATE
    $<$<CONFIG:Debug>:${LAYERS_LIBRARY_DEBUG} ${QLAYERS_LIBRARY_DEBUG} ${FUSION_LIBRARY_DEBUG} ${VORTEX_LIBRARY_DEBUG}>
    $<$<CONFIG:Release>:${LAYERS_LIBRARY_RELEASE} ${QLAYERS_LIBRARY_RELEASE} ${FUSION_LIBRARY_RELEASE} ${VORTEX_LIBRARY_RELEASE}>
    Qt6::Core Qt6::Gui Qt6::Widgets Qt6::Svg Qt6::Network Qt6::Concurrent
)

# Set the output directory for the built application
set_target_properties(Nebula PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin"
)

if(WIN32)
    add_custom_command(TARGET Nebula POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E echo "Copying Layers DLL to Nebula output directory"
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<IF:$<CONFIG:Debug>,${LAYERS_DIR}/bin/Debug/Layersd.dll,${LAYERS_DIR}/bin/Release/Layers.dll>
            $<TARGET_FILE_DIR:Nebula>
    )
    
    add_custom_command(TARGET Nebula POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E echo "Copying QLayers DLL to Nebula output directory"
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<IF:$<CONFIG:Debug>,${QLAYERS_DIR}/bin/Debug/QLayersd.dll,${QLAYERS_DIR}/bin/Release/QLayers.dll>
            $<TARGET_FILE_DIR:Nebula>
    )
    
    add_custom_command(TARGET Nebula POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E echo "Copying Fusion DLL to Nebula output directory"
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<IF:$<CONFIG:Debug>,${FUSION_DIR}/bin/Debug/Fusiond.dll,${FUSION_DIR}/bin/Release/Fusion.dll>
            $<TARGET_FILE_DIR:Nebula>
    )

    add_custom_command(TARGET Nebula POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E echo "Copying Vortex DLL to Nebula output directory"
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<IF:$<CONFIG:Debug>,${VORTEX_DIR}/bin/Debug/Vortexd.dll,${VORTEX_DIR}/bin/Release/Vortex.dll>
            $<TARGET_FILE_DIR:Nebula>
    )
endif()