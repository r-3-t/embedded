
add_mcu_lib(lm4f120xl 	${TI_STELLARIS_LIBRARY_FILES})

target_compile_definitions(lm4f120xl PUBLIC -Dgcc)

add_mcu_hal(hal_lm4f120xl lm4f120xl ${CMAKE_CURRENT_LIST_DIR}/stellaris/hal ${CMAKE_CURRENT_LIST_DIR}/stellaris/hal)

target_include_directories(hal_lm4f120xl PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include)
