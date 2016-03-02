
###############################
## Line2D LIBRARY MAIN CMAKE ##
###############################

add_library(Line2D_library Line2DImageTools.cpp Line2D.cpp Line2DMathTools.cpp)
add_library(lsd_c_library lsd.c lsd.h)
set(SOURCE_LIBS_LOCAL Line2D_library lsd_c_library)
set(SOURCE_LIBS ${SOURCE_LIBS} ${SOURCE_LIBS_LOCAL})
set(SOURCE_LIBS ${SOURCE_LIBS} PARENT_SCOPE)