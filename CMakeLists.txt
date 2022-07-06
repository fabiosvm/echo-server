
cmake_minimum_required(VERSION 3.0)

project(echo-server)

add_executable(${PROJECT_NAME}
  src/server.c
  src/socket.c)

add_executable(client
  src/client.c
  src/socket.c)

if(WIN32)
  target_link_libraries(${PROJECT_NAME} ws2_32)
  target_link_libraries(client ws2_32)
endif()
