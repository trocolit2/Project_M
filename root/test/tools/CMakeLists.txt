########################
## TEST TOOLS CMAKE ##
########################

add_library(TestTools_library TestTools.cpp TestTools.h)
add_library(EvaluationsTools_library EvaluationsTools.cpp EvaluationsTools.h)

set(SOURCE_LIBS_LOCAL TestTools_library EvaluationsTools_library)
set(SOURCE_LIBS ${SOURCE_LIBS_LOCAL} ${SOURCE_LIBS} PARENT_SCOPE)