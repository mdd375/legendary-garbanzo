add_library(philosophers philosophers.cpp)
add_executable(philosophers-bin philosophers_bin.cpp)
target_link_libraries(
    philosophers-bin 
    philosophers
)