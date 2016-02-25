########################
## LIBRARY MAIN CMAKE ##
########################

add_library(VideoTools VideoTools.cpp RegexStringTools.cpp)
add_library(BackGroundSubtraction_library BackGroundSubtraction.cpp)
add_library(Ransac_tool GenericRansac.cpp)

set(SOURCE_LIBS_LOCAL VideoTools  BackGroundSubtraction_library Ransac_tool)
set(SOURCE_LIBS ${SOURCE_LIBS} ${SOURCE_LIBS_LOCAL})

include_directories(backgroundSubtractionPackage)
add_subdirectory(backgroundSubtractionPackage)

include_directories(line2dtoolspackage)
add_subdirectory(line2dtoolspackage)

include_directories(vanishPointPackage)
add_subdirectory(vanishPointPackage)

set(SOURCE_LIBS ${SOURCE_LIBS} PARENT_SCOPE)
