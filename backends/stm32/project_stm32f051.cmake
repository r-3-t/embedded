
add_mcu_hal(hal_stm32f051 stm32f051 ${CMAKE_CURRENT_LIST_DIR}/hal ${CMAKE_CURRENT_LIST_DIR}/hal)
target_include_directories(hal_stm32f051 PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include/)

include_directories(${CMAKE_CURRENT_LIST_DIR}/include/)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/stm32f0/ ${CMAKE_CURRENT_BINARY_DIR}/stm32f0/)
