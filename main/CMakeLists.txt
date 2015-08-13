add_compile_options(-std=c++14)

set(Main_SRCS
    main.cpp
)

add_executable(vcfFilter
    ${Main_SRCS}
)

# Specify here the libraries this program depends on
target_link_libraries(vcfFilter
    libvcf
)

install(TARGETS vcfFilter DESTINATION bin)
