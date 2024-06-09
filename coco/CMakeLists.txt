add_library(${PROJECT_NAME})
target_sources(${PROJECT_NAME}
    PUBLIC FILE_SET headers TYPE HEADERS FILES
        Clock.hpp
        ClockTime.hpp
    PRIVATE
        Clock.cpp
)

if(${PLATFORM} STREQUAL "native" OR ${PLATFORM} STREQUAL "emu")
    # native platform (Windows, MacOS, Linux)
    target_sources(${PROJECT_NAME}
        PUBLIC FILE_SET platform_headers TYPE HEADERS BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/native FILES
            native/coco/platform/Clock_chrono.hpp
        PRIVATE
            native/coco/platform/Clock_chrono.cpp
    )
elseif(${PLATFORM} MATCHES "^nrf52" OR ${PLATFORM} MATCHES "^stm32")
    target_sources(${PROJECT_NAME}
        PUBLIC FILE_SET platform_headers TYPE HEADERS BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/generic FILES
            generic/coco/platform/Clock_Loop.hpp
        PRIVATE
            generic/coco/platform/Clock_Loop.cpp
    )
endif()

target_link_libraries(${PROJECT_NAME}
    coco::coco
    coco-loop::coco-loop
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        ..
)

# install the library
install(TARGETS ${PROJECT_NAME}
    FILE_SET headers DESTINATION include/coco
    FILE_SET platform_headers DESTINATION include
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)
