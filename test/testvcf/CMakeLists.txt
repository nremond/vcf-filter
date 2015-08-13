add_compile_options(-std=c++14)

file(GLOB SRCS *.cpp)

ADD_EXECUTABLE(testvcf ${SRCS})

TARGET_LINK_LIBRARIES(testvcf
    libvcf
    libgtest
    libgmock
)

add_test(NAME testvcf
         COMMAND testvcf)
