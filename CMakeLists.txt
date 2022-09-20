cmake_minimum_required(VERSION 3.0.0)

project(GolfMembersManager)

add_executable(${PROJECT_NAME}
    ./src/main.cpp
    ./src/GolfMembershipManager.cpp
    ./src/app/Listener/Listener.cpp
    ./src/app/Controller/Controller.cpp
    ./src/app/Entity/MembersEntity.cpp
    ./src/hw/Rfid/mfrc522.cpp
    ./src/hw/Rfid/CardReader.cpp
    ./src/hw/Spi/SPI.cpp
    ./src/hw/Monitor/Monitor.cpp
)  

target_include_directories(${PROJECT_NAME} PUBLIC
    ./src
    ./src/app/Model
    ./src/app/Listener
    ./src/app/Controller
    ./src/app/Entity
    ./src/hw/Rfid
    ./src/hw/Spi
    ./src/hw/Monitor
)

target_link_libraries(${PROJECT_NAME} PUBLIC
    -lwiringPi
)

target_compile_options(${PROJECT_NAME} PUBLIC
    -Wall
)