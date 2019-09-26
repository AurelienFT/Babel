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
  mainwindow.h
  customwidget.cpp
  customwidget.h
  friendlist.cpp
  friendlist.h
  contact.cpp
  contact.h
  chat.cpp
  chat.h
  message.cpp
  message.h
  home.cpp
  home.h
  conversation.cpp
  conversation.h
  login.cpp
  login.h
  loginform.cpp
  loginform.h
  loginregister.cpp
  loginregister.h
  )

target_link_libraries(babelInterface PRIVATE Qt5::Widgets)
