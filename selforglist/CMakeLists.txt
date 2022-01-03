add_library(selforglist src/list.c include/selforglist/models.h)
target_include_directories(selforglist PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)