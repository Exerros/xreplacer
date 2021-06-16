################################################################################
#
#
 
set(MODULE_NAME "xrep_logger")
set(MODULE_INCLUDE "include/")
set(MODULE_SRC "src/")
set(MODULE_PROPERTIES LINKER_LANGUAGE CXX CXX_STANDARD 17)
set(MODULE_COMPILE_FEATURES cxx_std_17)
set(MODULE_COMPILE_OPTIONS -Wall -Wextra -Wpedantic)
set(MODULE_LINK_WITH xrep pugixml)
