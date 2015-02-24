
########################
## LIBRARY MAIN CMAKE ##
########################

add_library(Stixel_library StixelTools.cpp Stixel3D.cpp Stixel2D.cpp LineTools.cpp lsd.cpp)

set(SOURCE_LIBS_LOCAL Stixel_library)
set(SOURCE_LIBS ${SOURCE_LIBS} ${SOURCE_LIBS_LOCAL})
set(SOURCE_LIBS ${SOURCE_LIBS} PARENT_SCOPE)