SET(THRIFT_SOURCE_PREFIX ${CMAKE_SOURCE_DIR}/src/proxy)

SET(WORKER_THRIFT_SOURCE
    ${THRIFT_SOURCE_PREFIX}/worker/gen-cpp/worker_constants.cpp
    ${THRIFT_SOURCE_PREFIX}/worker/gen-cpp/Worker.h
    ${THRIFT_SOURCE_PREFIX}/worker/gen-cpp/worker_types.h
    ${THRIFT_SOURCE_PREFIX}/worker/gen-cpp/worker_constants.h
    ${THRIFT_SOURCE_PREFIX}/worker/gen-cpp/Worker.cpp
    ${THRIFT_SOURCE_PREFIX}/worker/gen-cpp/worker_types.cpp)

ADD_CUSTOM_COMMAND (
    OUTPUT ${WORKER_THRIFT_SOURCE}
    COMMAND thrift --gen cpp -r -o ${CMAKE_SOURCE_DIR}/src/proxy/worker
    ${CMAKE_SOURCE_DIR}/src/proxy/worker/worker.thrift
)

SET(MASTER_THRIFT_SOURCE
    ${THRIFT_SOURCE_PREFIX}/master/gen-cpp/master_constants.cpp
    ${THRIFT_SOURCE_PREFIX}/master/gen-cpp/Master.h
    ${THRIFT_SOURCE_PREFIX}/master/gen-cpp/master_types.h
    ${THRIFT_SOURCE_PREFIX}/master/gen-cpp/master_constants.h
    ${THRIFT_SOURCE_PREFIX}/master/gen-cpp/Master.cpp
    ${THRIFT_SOURCE_PREFIX}/master/gen-cpp/master_types.cpp)

ADD_CUSTOM_COMMAND (
    OUTPUT ${MASTER_THRIFT_SOURCE}
    COMMAND thrift --gen cpp -r -o ${CMAKE_SOURCE_DIR}/src/proxy/master
    ${CMAKE_SOURCE_DIR}/src/proxy/master/master.thrift
)

SET(SRC
    ${MASTER_THRIFT_SOURCE}
    ${WORKER_THRIFT_SOURCE}
    worker_config.cpp 
    resource_manager.cpp
    zk_worker.cpp
    worker_service.cpp
    vm_manager.cpp
    executor.cpp 
    work_thread.cpp
    worker.cpp
    )


ADD_EXECUTABLE(worker ${SRC})
TARGET_LINK_LIBRARIES(worker zookeeper_mt log4cplus thrift virt boost_thread)

INSTALL(TARGETS worker RUNTIME DESTINATION bin)

