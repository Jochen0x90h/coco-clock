# hex generator
separate_arguments(GENERATE_HEX)
macro(generate_hex TARGET)
	if(NOT "${GENERATE_HEX}" STREQUAL "" AND NOT "${GENERATE_HEX}" STREQUAL "None")
		#message("*** Generate Hex for ${TARGET}: ${GENERATE_HEX}")
		add_custom_command(TARGET ${TARGET}
			POST_BUILD
			COMMAND ${GENERATE_HEX} ${TARGET} ${TARGET}.hex
		)
	endif()
endmacro()

# generate ClockTest for every board
foreach(COMPONENT ${coco-devboards_COMPONENT_NAMES})
	string(REGEX REPLACE ".*\\:" "" BOARD ${COMPONENT})
	message("*** Board: ${BOARD}")
	if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${BOARD}/ClockTest.hpp)
		set(NAME "ClockTest-${BOARD}")
		add_executable(${NAME}
			ClockTest.cpp
			${BOARD}/ClockTest.hpp
		)
		target_include_directories(${NAME}
			PRIVATE
				../
				${BOARD}
		)

		# find link.ld of board
		get_target_property(INCLUDES ${COMPONENT} INTERFACE_INCLUDE_DIRECTORIES)
		target_link_directories(${NAME}
			PRIVATE	
				${INCLUDES}
		)

		target_link_libraries(${NAME}
			coco::coco
			${COMPONENT}
			coco-loop::coco-loop
			${PROJECT_NAME}
		)

		# windows specific libraries
		if(WIN32)
			target_link_libraries(${NAME} wsock32 ws2_32 winmm)
		endif()

		# generate hex file for flashing the target
		generate_hex(${NAME})
	endif()
endforeach()


# unit tests for "normal" operating systems
if(NOT ${CMAKE_CROSSCOMPILING})
	add_executable(gTest
		gTest.cpp
	)
	target_include_directories(gTest
		PRIVATE
		..
	)
	target_link_libraries(gTest
		${PROJECT_NAME}
		GTest::gtest
	)

	add_test(NAME gTest
		COMMAND gTest --gtest_output=xml:report.xml
		#WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../testdata
	)
endif()
