add_compile_options(-std=c++14)

set(libvcf_SRCS
	utilities.h
	utilities.cpp
	variant.h
	variant.cpp
	variantcollection.h
	variantcollection.cpp
)

# Declare the library
add_library(libvcf STATIC
    ${libvcf_SRCS}
)

# Specify here the include directories exported
# by this library
target_include_directories(libvcf PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)
