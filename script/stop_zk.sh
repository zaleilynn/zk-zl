#!/bin/bash
if [ $UID -ne 0 ]
then
    echo "Must be root to run this script."
    exit -1
fi

/root/server1/zookeeper-3.4.5/bin/zkServer.sh stop
/root/server2/zookeeper-3.4.5/bin/zkServer.sh stop
/root/server3/zookeeper-3.4.5/bin/zkServer.sh stop

