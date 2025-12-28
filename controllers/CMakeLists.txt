set(SRC
  foraging.cpp
  team1.cpp
  team2.cpp
  # Add other controller source files here
)

add_library(foraging_controllers MODULE ${SRC})

target_link_libraries(foraging_controllers
  PUBLIC
    argos3core_${ARGOS_BUILD_FOR}
    argos3plugin_${ARGOS_BUILD_FOR}_pipuck
)

target_include_directories(foraging_controllers
  PUBLIC
    ${ARGOS_INCLUDE_DIRS}
)

set_target_properties(foraging_controllers PROPERTIES
  OUTPUT_NAME foraging_controllers
)
