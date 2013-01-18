#!/bin/bash
if [ -z $ZLYNN_HOME ]
then
    echo "LYNN_HOME is not set."
    exit -2
fi

rm -rf $ZLYNN_HOME/src/proxy/worker/gen-cpp $ZLYNN_HOME/src/proxy/master/gen-cpp

exit 0

