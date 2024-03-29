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
elseif(${PLATFORM} MATCHES "^nrf52")
	target_sources(${PROJECT_NAME}
		PUBLIC FILE_SET platform_headers TYPE HEADERS BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/nrf52 FILES
			nrf52/coco/platform/Clock_RTC0.hpp
		PRIVATE
			nrf52/coco/platform/Clock_RTC0.cpp
	)
elseif(${PLATFORM} MATCHES "^stm32f0")
	target_sources(${PROJECT_NAME}
		PUBLIC FILE_SET platform_headers TYPE HEADERS BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/stm32f0 FILES
			stm32f0/coco/platform/Clock_TIM2.hpp
		PRIVATE
			stm32f0/coco/platform/Clock_TIM2.cpp
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
