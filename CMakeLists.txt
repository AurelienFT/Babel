project(babel)
cmake_minimum_required(VERSION 3.11)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()
find_package(Qt5Core) 
find_package(Qt5Widgets)
find_package(Qt5DBus)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

add_subdirectory(${CMAKE_SOURCE_DIR}/Client/Sources/babelInterface)

set(
        CLIENT_SOURCES_FILES
        Client/Sources/babelInterface/mainwindow.cpp
        Client/Sources/babelInterface/mainwindow.h
        Client/Sources/babelInterface/customwidget.cpp
        Client/Sources/babelInterface/customwidget.h
        Client/Sources/babelInterface/friendlist.cpp
        Client/Sources/babelInterface/friendlist.h
        Client/Sources/babelInterface/contact.cpp
        Client/Sources/babelInterface/contact.h
        Client/Sources/babelInterface/chat.cpp
        Client/Sources/babelInterface/chat.h
        Client/Sources/babelInterface/message.cpp
        Client/Sources/babelInterface/message.h
        Client/Sources/babelInterface/home.cpp
        Client/Sources/babelInterface/home.h
        Client/Sources/babelInterface/conversation.cpp
        Client/Sources/babelInterface/conversation.h
        Client/Sources/babelInterface/login.cpp
        Client/Sources/babelInterface/login.h
        Client/Sources/babelInterface/loginform.cpp
        Client/Sources/babelInterface/loginform.h
        Client/Sources/babelInterface/loginregister.cpp
        Client/Sources/babelInterface/loginregister.h
        Client/Sources/Main.cpp
)

add_executable(
        babel_client
        ${CLIENT_SOURCES_FILES}
)

target_compile_options(babel_client PRIVATE "-fPIC")
target_include_directories(babel_client PRIVATE ${CONAN_INCLUDE_DIRS_QT} Client/Sources/babelInterface)
target_link_libraries(babel_client PRIVATE ${CONAN_LIBS} Qt5::Core Qt5::Widgets Qt5::DBus)

set(
    SERVER_SOURCES_FILES
    "Server/Sources/VoIpServer.cpp"
    "Server/Sources/VoIpServer.hpp"
    "Server/Sources/NetworkClient.cpp"
    "Server/Sources/NetworkClient.hpp"
    "Server/Sources/MainServer.cpp"
    "Server/Sources/MainServer.hpp"
    "Server/Sources/Main.cpp"
    "Server/Sources/Database/DatabaseMessageHandling.cpp"
    "Server/Sources/Database/DatabaseMessageHandling.cpp"
    "Server/Sources/User.cpp"
    "Server/Sources/Database/DatabaseDiscussionHandling.cpp"
    "Server/Sources/Database/DatabaseUserHandling.cpp"
    "Server/Sources/Database/DatabaseUserDiscussionHandling.cpp"
    "Server/Sources/Database/DatabaseUserFriendHandling.cpp"
)

add_executable(
    babel_server
    ${SERVER_SOURCES_FILES}
)

target_include_directories(babel_server PRIVATE ${CONAN_INCLUDE_DIRS_SQLITE3} "Server/Sources" "Server/Sources/Database")
target_link_libraries(babel_server ${CONAN_LIB_DIRS_SQLITE3}/libsqlite3.a pthread dl)

add_executable(
    audio_test
    "Client/Sources/AudioTest.cpp"
)

target_include_directories(audio_test PRIVATE ${CONAN_INCLUDE_DIRS_PORTAUDIO})
target_link_libraries(audio_test pthread ${CONAN_LIB_DIRS_PORTAUDIO}/libportaudio.a asound jack)

add_executable(
    audio_test2
    "Client/Sources/AudioTest2.cpp"
)

target_include_directories(audio_test2 PRIVATE ${CONAN_INCLUDE_DIRS_PORTAUDIO})
target_link_libraries(audio_test2 pthread ${CONAN_LIB_DIRS_PORTAUDIO}/libportaudio.a asound jack)

add_executable(
    my_audiotest
    "Client/Sources/Audio/Audio.cpp"
    "Client/Sources/Audio/TestMain.cpp"
)

target_include_directories(my_audiotest PRIVATE ${CONAN_INCLUDE_DIRS_PORTAUDIO})
target_link_libraries(my_audiotest pthread ${CONAN_LIB_DIRS_PORTAUDIO}/libportaudio.a asound jack)
target_compile_options(my_audiotest PRIVATE "-g3")
