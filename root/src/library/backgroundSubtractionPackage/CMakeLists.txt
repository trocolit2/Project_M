###############################################
## Background Subtraction Package MAIN CMAKE ##
###############################################



add_library(BackgroundSubtraction_package AdaptiveBackgroundLearning.cpp MixtureOfGaussianV1BGS.cpp MedianFilterBGS.cpp)
add_library(BackgroundSubtraction_package_lb lb/LBAdaptiveSOM.cpp lb/BGModelSom.cpp lb/BGModel.cpp)
add_library(BackgroundSubtraction_package_jmo jmo/MultiLayerBGS.cpp jmo/CMultiLayerBGS.cpp jmo/BlobResult.cpp jmo/LocalBinaryPattern.cpp jmo/blob.cpp jmo/BlobExtraction.cpp)


##add_library(BackgroundSubtraction_interface IBGS.h)
##set_target_properties(BackgroundSubtraction_interface PROPERTIES PUBLIC_HEADER "IBGS.h")
##set_target_properties(BackgroundSubtraction_interface PROPERTIES LINKER_LANGUAGE CXX)

set(SOURCE_LIBS_LOCAL BackgroundSubtraction_package BackgroundSubtraction_package_lb BackgroundSubtraction_package_jmo)
set(SOURCE_LIBS ${SOURCE_LIBS} ${SOURCE_LIBS_LOCAL} PARENT_SCOPE)