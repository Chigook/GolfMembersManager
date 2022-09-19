cmake_minimum_required(VERSION 3.0.0)

project(GolfMembersManager)

add_executable(${PROJECT_NAME}
    ./src/main
    ./src/app/Listener/Listener.cpp
    ./src/hw/rfid/mfrc522.cpp
    ./src/hw/spi/SPI.cpp
)  

target_include_directories(${PROJECT_NAME} PUBLIC
    ./src/app/Listener
    ./src/hw/rfid
    ./src/hw/spi
)

target_link_libraries(${PROJECT_NAME} PUBLIC
    -lwiringPi
)

target_compile_options(${PROJECT_NAME} PUBLIC
    -Wall
)