cmake_minimum_required(VERSION 3.5)

project(PoolsideGUI VERSION 2.0 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(-Wall -Wextra)

include(FindPkgConfig)
if(!${PKG_CONFIG_FOUND})
  MESSAGE(FATAL_ERROR "pkg-config required. Please install it")
  return ("Error - pkg-config not found")
endif()

pkg_check_modules(GSTREAMER gstreamer-1.0>=1.6 gstreamer-video-1.0>=1.6 REQUIRED)

find_package(QT NAMES Qt6 COMPONENTS REQUIRED Qml Quick SerialPort Core Gui Widgets Network)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Qml Quick SerialPort Core Gui Widgets Network)

include_directories("${PROJECT_SOURCE_DIR}/Communication")
include_directories("${PROJECT_SOURCE_DIR}/Control")
include_directories("${PROJECT_SOURCE_DIR}/KX_Pult")
include_directories("${PROJECT_SOURCE_DIR}/StabilizationSettings")
include_directories("${PROJECT_SOURCE_DIR}/ThrusterSettings")
include_directories("${PROJECT_SOURCE_DIR}/UV")

include_directories("${PROJECT_SOURCE_DIR}")

qt6_add_resources(RESOURCES qmlsink.qrc)

link_directories(${GSTREAMER_LIBRARY_DIRS})
include_directories (${GSTREAMER_INCLUDE_DIRS})

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp

        Communication/UdpClient.cpp

        Control/ControlBase.cpp
        Control/Gamepad.cpp

        KX_Pult/configdata.cpp
        KX_Pult/kx_protocol.cpp
        KX_Pult/qkx_coeffs.cpp
        KX_Pult/qpiconfig.cpp

        StabilizationSettings/StabilizationWindow.cpp

        ThrusterSettings/Thruster.cpp
        ThrusterSettings/ThrusterWindow.cpp

        UV/i_basicData.cpp
        UV/i_controlData.cpp
        UV/i_serverData.cpp
        UV/i_tuningData.cpp
        UV/i_userInterfaceData.cpp
        UV/uv_controlCircuit.cpp
        UV/uv_state.cpp
        UV/uv_thruster.cpp
        UV/uv_device.cpp
)

add_executable(${PROJECT_NAME}
        ${PROJECT_SOURCES}
        ${RESOURCES}
        images.qrc
)

target_link_libraries(${PROJECT_NAME} PRIVATE
        sfml-graphics sfml-window sfml-system
        ${GSTREAMER_LIBRARIES}
        Qt${QT_VERSION_MAJOR}::Core
        Qt${QT_VERSION_MAJOR}::Gui
        Qt${QT_VERSION_MAJOR}::Widgets
        Qt${QT_VERSION_MAJOR}::Network
        Qt${QT_VERSION_MAJOR}::Qml
        Qt${QT_VERSION_MAJOR}::Quick
        Qt${QT_VERSION_MAJOR}::SerialPort
)
