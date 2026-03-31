project(BlockingQueue)

add_executable(bq_demo demo/main.cpp util/thread/blocking_queue.h)

include_directories(bq_demo PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/util/thread)
