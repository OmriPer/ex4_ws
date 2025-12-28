set(SRC
    foraging_loop_functions.cpp
    qt_functions.cpp
    # Add other loop function source files here
)

add_library(foraging_loop_functions MODULE ${SRC})

target_link_libraries(foraging_loop_functions
  PUBLIC
    argos3core_${ARGOS_BUILD_FOR}
    argos3plugin_${ARGOS_BUILD_FOR}_pipuck
)

target_include_directories(foraging_loop_functions
  PUBLIC
    ${ARGOS_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}/controllers
)

set_target_properties(foraging_loop_functions PROPERTIES
  OUTPUT_NAME foraging_loop_functions
)
