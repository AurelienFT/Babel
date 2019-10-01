cmake_minimum_required(VERSION 3.5)

project(babelInterface LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(babelInterface
  main.cpp
  mainwindow.cpp
  mainwindow.hpp
  customwidget.cpp
  customwidget.hpp
  friendlist.cpp
  friendlist.hpp
  contact.cpp
  contact.hpp
  chat.cpp
  chat.hpp
  message.cpp
  message.hpp
  home.cpp
  home.hpp
  conversation.cpp
  conversation.hpp
  login.cpp
  login.hpp
  loginform.cpp
  loginform.hpp
  loginregister.cpp
  loginregister.hpp
  friendrequest.cpp
  friendrequest.hpp
  managefriend.cpp
  managefriend.hpp
  )

target_link_libraries(babelInterface PRIVATE Qt5::Widgets)
