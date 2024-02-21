function(board_test TEST TARGET)
	#message("*** Target: ${TARGET}")
	# check if target exists
	if(TARGET ${TARGET})
		string(REGEX REPLACE ".*\\:" "" BOARD ${TARGET})
		set(NAME "${TEST}-${BOARD}")
		message("*** Board: ${BOARD}")

		add_executable(${NAME}
			${TEST}.cpp
		)
		target_include_directories(${NAME}
			PRIVATE
				../
				${BOARD}
		)
		target_link_libraries(${NAME}
			${TARGET}
			${PROJECT_NAME}
		)

		# generate hex file for flashing the target
		if(${CMAKE_CROSSCOMPILING})
			#message("*** Generate Hex for ${NAME} using ${CMAKE_OBJCOPY}")
			add_custom_command(TARGET ${NAME}
				POST_BUILD
				COMMAND ${CMAKE_OBJCOPY} -O ihex ${NAME} ${NAME}.hex
			)
		endif()
	endif()
endfunction()

#message("*** coco-devboards: ${coco-devboards_COMPONENT_NAMES}")

board_test(ClockTest coco-devboards::native)
board_test(ClockTest coco-devboards::emu)
board_test(ClockTest coco-devboards::nrf52dongle)
board_test(ClockTest coco-devboards::stm32f0discovery)



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
