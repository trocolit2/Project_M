##########################
## CONFIGURE MAIN CMAKE ##
##########################

configure_file(config.h.in "${include_build_path}/config.h")
#add_library(Config config.h.in)
#set_target_properties(Config PROPERTIES PUBLIC_HEADER "${include_build_path}/config.h")
#set_target_properties(Config PROPERTIES LINKER_LANGUAGE CXX)
#set(SOURCE_LIBS ${SOURCE_LIBS} Config PARENT_SCOPE) 