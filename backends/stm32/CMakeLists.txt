include_directories(include/)
add_subdirectory(stm32f0/)
add_subdirectory(stm32f1/)
add_subdirectory(stm32f4/)

add_mcu_hal(hal_stm32f051 stm32f051 ${CMAKE_CURRENT_SOURCE_DIR}/hal ${CMAKE_CURRENT_SOURCE_DIR}/hal)
target_include_directories(hal_stm32f051 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/)

add_mcu_hal(hal_stm32f100 stm32f100 ${CMAKE_CURRENT_SOURCE_DIR}/hal ${CMAKE_CURRENT_SOURCE_DIR}/hal)
target_include_directories(hal_stm32f100 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/)

add_mcu_hal(hal_stm32f103 stm32f103 ${CMAKE_CURRENT_SOURCE_DIR}/hal ${CMAKE_CURRENT_SOURCE_DIR}/hal)
target_include_directories(hal_stm32f103 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/)

add_mcu_hal(hal_stm32f407 stm32f407 ${CMAKE_CURRENT_SOURCE_DIR}/hal ${CMAKE_CURRENT_SOURCE_DIR}/hal)
target_include_directories(hal_stm32f407 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/)
