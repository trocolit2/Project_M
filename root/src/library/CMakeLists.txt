########################
## LIBRARY MAIN CMAKE ##
########################

add_library(VideoTools VideoTools.cpp VideoTools.h RegexStringTools.cpp RegexStringTools.h)
##add_library(Stixel2D_library Stixel2D.cpp Stixel2D.h LineTools.cpp LineTools.h)
add_library(BackGroundSubtraction_library BackGroundSubtraction.cpp BackGroundSubtraction.h)
#Stixel2D_library

set(SOURCE_LIBS_LOCAL VideoTools  BackGroundSubtraction_library)
set(SOURCE_LIBS ${SOURCE_LIBS} ${SOURCE_LIBS_LOCAL})

include_directories(backgroundSubtractionPackage)
add_subdirectory(backgroundSubtractionPackage)

include_directories(stixelPackage)
add_subdirectory(stixelPackage)

set(SOURCE_LIBS ${SOURCE_LIBS} PARENT_SCOPE)
