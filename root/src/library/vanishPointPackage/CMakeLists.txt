#######################################
## VANISH POINT DETECTION MAIN CMAKE ##
#######################################

##VPTools.cpp
add_library(VP_library VanishingPointDetection.cpp)

set(SOURCE_LIBS_LOCAL VP_library)
set(SOURCE_LIBS ${SOURCE_LIBS} ${SOURCE_LIBS_LOCAL})
set(SOURCE_LIBS ${SOURCE_LIBS} PARENT_SCOPE)