project(babel)
cmake_minimum_required(VERSION 3.11)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()
find_package(Qt5Core) 
find_package(Qt5Widgets)
find_package(Qt5DBus)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

set(
    CLIENT_SOURCES_FILES
    "Client/Sources/Main.cpp"
)

add_executable(
    babel_client
    ${CLIENT_SOURCES_FILES}
)

target_compile_options(babel_client PRIVATE "-fPIC")
target_include_directories(babel_client PRIVATE ${CONAN_INCLUDE_DIRS_QT})
target_link_libraries(babel_client PRIVATE ${CONAN_LIBS} Qt5::Core Qt5::Widgets Qt5::DBus)

set(
    SERVER_SOURCES_FILES
    "Server/Sources/Main.cpp"
    "Server/Sources/Database/DatabaseMessageHandling.cpp"
    "Server/Sources/DatabaseMessageHandling.cpp"
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