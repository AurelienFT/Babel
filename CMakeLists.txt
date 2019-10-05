project(babel)
cmake_minimum_required(VERSION 3.11)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
#set(CMAKE_PREFIX_PATH "/Qt/5.13.1/mingw73_64/lib/cmake/Qt5")

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
if (WIN32)
	set (CMAKE_PREFIX_PATH "/Qt/5.13.1/msvc2017_64/lib/cmake/Qt5")
endif()
conan_basic_setup()
if(UNIX)
	find_package(Qt5Core)
	find_package(Qt5Widgets)
	find_package(Qt5DBus)
endif()
if (WIN32)
	find_package(Qt5 COMPONENTS Core REQUIRED)
	find_package(Qt5 COMPONENTS Widgets REQUIRED)
	find_package(Qt5 COMPONENTS DBus REQUIRED)
	find_package(Threads REQUIRED)
endif()

message(Qt5::Widgets)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

#add_subdirectory(${CMAKE_SOURCE_DIR}/Client/Sources/Graphic)

set(
        CLIENT_SOURCES_FILES
        Client/Sources/Graphic/mainwindow.cpp
        Client/Sources/Graphic/customwidget.cpp
        Client/Sources/Graphic/friendlist.cpp
        Client/Sources/Graphic/contact.cpp
        Client/Sources/Graphic/chat.cpp
        Client/Sources/Graphic/message.cpp
        Client/Sources/Graphic/home.cpp
        Client/Sources/Graphic/conversation.cpp
	Client/Sources/Graphic/friendrequest.cpp
        Client/Sources/Graphic/login.cpp
        Client/Sources/Graphic/loginform.cpp
        Client/Sources/Graphic/loginregister.cpp
        Client/Sources/Graphic/managefriend.cpp
        Client/Sources/Network/NetworkClient.cpp
        Client/Sources/Main.cpp
        Client/Sources/Network/VoIpClient.cpp
)

add_executable(
        babel_client
        ${CLIENT_SOURCES_FILES}
)
if(UNIX)
	target_compile_options(babel_client PRIVATE "-fPIC" "-g3")
endif()

target_include_directories(babel_client PRIVATE ${CONAN_INCLUDE_DIRS_QT} Client/Sources/Graphic Client/Sources/Network Interface)

if (WIN32)

	file(
		GLOB_RECURSE
		DLLS
		"/Qt/5.13.1/msvc2017_64/bin/*.dll"
	)

	foreach(DLL ${DLLS})
	        file (COPY ${DLL} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/bin)
	endforeach()
	target_link_libraries(babel_client PRIVATE ${CONAN_LIBS} Qt5::Core Qt5::Widgets Qt5::DBus wsock32 ws2_32 Threads::Threads)
endif()

if (UNIX)
	target_link_libraries(babel_client PRIVATE ${CONAN_LIBS} Qt5::Core Qt5::Widgets Qt5::DBus pthread)
endif()

set(
        SERVER_SOURCES_FILES
        "Server/Sources/Network/VoIpServer.cpp"
        "Server/Sources/Network/VoIpServer.hpp"
        "Server/Sources/Network/NetworkClient.cpp"
        "Server/Sources/Network/NetworkClient.hpp"
        "Server/Sources/Network/MainServer.hpp"
        "Server/Sources/Main.cpp"
        "Server/Sources/Database/DatabaseMessageHandling.cpp"
        "Server/Sources/User.cpp"
        "Server/Sources/Database/DatabaseDiscussionHandling.cpp"
        "Server/Sources/Database/DatabaseUserHandling.cpp"
        "Server/Sources/Database/DatabaseUserDiscussionHandling.cpp"
        "Server/Sources/Database/DatabaseUserFriendHandling.cpp"
        "Server/Sources/Network/VoIp.cpp" 
        "Server/Sources/Network/VoIp.hpp"
)

add_executable(
        babel_server
        ${SERVER_SOURCES_FILES}
)

target_include_directories(babel_server PRIVATE ${CONAN_INCLUDE_DIRS_SQLITE3} "Server/Sources" "Server/Sources/Database" "Server/Sources/Network" "Interface")
target_link_libraries(babel_server ${CONAN_LIB_DIRS_SQLITE3}/libsqlite3.a pthread dl)
if (UNIX)
	target_compile_options(babel_server PRIVATE "-g3")
endif()
add_executable(
        my_audiotest
        "Client/Sources/Audio/Audio.cpp"
        "Client/Sources/Audio/TestMain.cpp"
)

target_include_directories(my_audiotest PRIVATE ${CONAN_INCLUDE_DIRS_PORTAUDIO})
target_link_libraries(my_audiotest pthread ${CONAN_LIB_DIRS_PORTAUDIO}/libportaudio.a asound jack pthread)
target_compile_options(my_audiotest PRIVATE "-g3")

add_executable(
        audiotest_client
        "Client/Sources/Audio/Audio.cpp"
        "Client/Sources/Audio/TestMainClient.cpp"
)

target_include_directories(audiotest_client PRIVATE ${CONAN_INCLUDE_DIRS_PORTAUDIO})
target_link_libraries(audiotest_client pthread ${CONAN_LIB_DIRS_PORTAUDIO}/libportaudio.a asound jack pthread)
target_compile_options(audiotest_client PRIVATE "-g3")

add_executable(
        audiotest_server
        "Client/Sources/Audio/Audio.cpp"
        "Client/Sources/Audio/TestMainServer.cpp"
)

target_include_directories(audiotest_server PRIVATE ${CONAN_INCLUDE_DIRS_PORTAUDIO} ${CONAN_LIB_DIRS_OPUS})
if (UNIX)
	target_link_libraries(audiotest_server pthread ${CONAN_LIB_DIRS_PORTAUDIO}/libportaudio.a asound jack pthread ${CONAN_LIB_DIRS_OPUS}/libopus.a)
endif()
if (WIN32)
	target_include_directories(audiotest_server PRIVATE ${CONAN_INCLUDE_DIRS_PORTAUDIO})
	target_link_libraries(audiotest_server ${CONAN_LIB_DIRS_PORTAUDIO}/portaudio_x64.lib ${CONAN_LIB_DIRS_OPUS}/opus.lib Threads::Threads)
endif()
target_compile_options(audiotest_server PRIVATE "-g3")

add_executable(
        VoIp_Server_Test
        "Server/Sources/Network/VoIp.cpp"
        "Server/Sources/Network/VoIp.hpp"
        "Server/Sources/Network/VoIpMain.cpp"
)
target_link_libraries(VoIp_Server_Test pthread ${CONAN_LIB_DIRS_PORTAUDIO}/libportaudio.a asound jack pthread)
target_compile_options(VoIp_Server_Test PRIVATE "-g3")

add_executable(
        VoIp_Client_Test
      "Client/Sources/Network/VoIpClient.cpp"
      "Client/Sources/Network/VoIpClient.hpp"
        Client/Sources/Network/VoIpMainTest.cpp)
target_link_libraries(VoIp_Client_Test pthread ${CONAN_LIB_DIRS_PORTAUDIO}/libportaudio.a asound jack pthread)
target_compile_options(VoIp_Client_Test PRIVATE "-g3")
