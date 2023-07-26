cmake_minimum_required(VERSION 3.5)

project(PoolsideGUI VERSION 2.0 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 COMPONENTS REQUIRED Core Gui Widgets SerialPort Network)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Gui Widgets SerialPort Network)

include_directories("${PROJECT_SOURCE_DIR}/Communication")
include_directories("${PROJECT_SOURCE_DIR}/Control")
include_directories("${PROJECT_SOURCE_DIR}/KX_Pult")
include_directories("${PROJECT_SOURCE_DIR}/PicFrame")
include_directories("${PROJECT_SOURCE_DIR}/StabilizationSettings")
include_directories("${PROJECT_SOURCE_DIR}/ThrusterSettings")
include_directories("${PROJECT_SOURCE_DIR}/UV")

include_directories("${PROJECT_SOURCE_DIR}")


set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp

        Communication/UdpClient.cpp

        Control/ControlBase.cpp
        Control/Joystick.cpp
        Control/Gamepad.cpp
        # Control/Keyboard.cpp

        KX_Pult/configdata.cpp
        KX_Pult/kx_protocol.cpp
        KX_Pult/qkx_coeffs.cpp
        KX_Pult/qpiconfig.cpp

        PicFrame/picframe.cpp

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
)

add_executable(${PROJECT_NAME}
        ${PROJECT_SOURCES}
        images.qrc
)

target_link_libraries(${PROJECT_NAME} PRIVATE
        sfml-graphics sfml-window sfml-system
        Qt${QT_VERSION_MAJOR}::Core
        Qt${QT_VERSION_MAJOR}::Gui
        Qt${QT_VERSION_MAJOR}::Widgets
        Qt${QT_VERSION_MAJOR}::SerialPort
        Qt${QT_VERSION_MAJOR}::Network
)

set(CMAKE_AUTOUIC_SEARCH_PATHS
        PicFrame
)
