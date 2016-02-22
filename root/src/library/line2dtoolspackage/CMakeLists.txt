
###############################
## Line2D LIBRARY MAIN CMAKE ##
###############################

add_library(Line2D_library Line2D.cpp Line2DMathTools.cpp Line2DImageDetector.cpp)

set(SOURCE_LIBS_LOCAL Line2D_library)
set(SOURCE_LIBS ${SOURCE_LIBS} ${SOURCE_LIBS_LOCAL})
set(SOURCE_LIBS ${SOURCE_LIBS} PARENT_SCOPE)