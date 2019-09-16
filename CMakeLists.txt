cmake_minimum_required(VERSION 3.11)

set(
    CLIENT_SOURCES_FILES
    "Client/Sources/Main.cpp"
)

add_executable(
    babel_client
    ${CLIENT_SOURCES_FILES}
)

set(
    SERVER_SOURCES_FILES
    "Server/Sources/Main.cpp"
)

add_executable(
    babel_server
    ${SERVER_SOURCES_FILES}
)