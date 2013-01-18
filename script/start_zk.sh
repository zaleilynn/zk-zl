#!/bin/bash
if [ $UID -ne 0 ]
then
    echo "Must be root to run this script."
    exit -1
fi

if [ -z $ZLYNN_HOME ]
then
    echo "ZLYNN_HOME is not set."
    exit -1
fi

export ZOO_LOG_DIR=$ZLYNN_HOME/log

/root/server1/zookeeper-3.4.5/bin/zkServer.sh start
/root/server2/zookeeper-3.4.5/bin/zkServer.sh start
/root/server3/zookeeper-3.4.5/bin/zkServer.sh start

