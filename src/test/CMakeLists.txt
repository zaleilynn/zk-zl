SET(THRIFT_SOURCE_PREFIX ${CMAKE_SOURCE_DIR}/src/proxy)

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
    test.cpp)

ADD_EXECUTABLE(test ${SRC})
TARGET_LINK_LIBRARIES(test zookeeper_mt thrift log4cplus classad)

INSTALL(TARGETS test RUNTIME DESTINATION test)

