#!/bin/sh
#
# Author : ang.li
# Created date : 2022-05-16
#
# yfautorun.sh - used to capture logs.
#
# usage: 1. Put this script and its corresponding "yfautorun.md5" in 
#           the root directory of the U-disk.
#        2. Insert the u-disk into HU.
#        3. When you get enough logs, remove the u-disk from HU.
#
#   The obtained "logs" are stored in the "wmlog" directory under the root
# directory of the u-disk.
#   When the u-disk is mounted, the script starts to run and gets the logs
# until the u-disk is removed.
###########################################################################
# WARNING: DO NOT MODIFY ANYTHING IN THIS FILE !!!
###########################################################################
timestamp_format="%Y-%m-%d %H:%M:%S"
logd() {
    timestamp=`date +"$timestamp_format"`
    echo "\033[32m$timestamp $$ : $1\033[0m"
    if [ -d $LOGDIR ];then
        echo "$timestamp $$ : $1" >> $LOGDIR/script_logs.txt
    fi
}

make_snapshot() {
    logd "starting snapshot "
    # record log while insert u-disk
    $DF > $SNAPSHOT/diskusage.txt
    $CAT /proc/meminfo > $SNAPSHOT/proc_meminfo.txt
    $PS > $SNAPSHOT/ps.txt
    $DMESG > $SNAPSHOT/dmesg.txt
    $GETPROP > $SNAPSHOT/getprop.txt
    echo "settings list global ... " > $SNAPSHOT/settings.txt
    $SETTINGS list global >> $SNAPSHOT/settings.txt
    echo "\nsettings list system ... " >> $SNAPSHOT/settings.txt
    $SETTINGS list system >> $SNAPSHOT/settings.txt
    echo "\nsettings list secure ... " >> $SNAPSHOT/settings.txt
    $SETTINGS list secure >> $SNAPSHOT/settings.txt
    $SYNC
    if [ "$run_where" = "target" ];then
        logd "running in target"
        screencap -p $SNAPSHOT/screencap.png
        cp -r /data/tombstones/ $SNAPSHOT
        cp -r /data/anr/ $SNAPSHOT
        cp -rf /data/system/dropbox $SNAPSHOT
        # copy pki logs
        cp -rf /crypto $SNAPSHOT
        if [ "$who"x = "qcom"x ];then
            logd "specific content on qcom target"
        else
            pki_log_path=/sdcard/Android/data/com.wm.pkiservice/ # path in ase1
            if [ -d $pki_log_path ];then
                cp -rf $pki_log_path $SNAPSHOT
            else
                logd "pki logs path not exist:$pki_log_path"
            fi
        fi
    else
        adb shell screencap -p /data/screencap.png
        adb pull /data/screencap.png $SNAPSHOT/screencap.png
        adb shell rm -rf /data/screencap.png
        adb pull /data/tombstones $SNAPSHOT
        adb pull /data/anr/ $SNAPSHOT
        adb pull /data/system/dropbox $SNAPSHOT
        # copy pki logs
        adb pull /crypto $SNAPSHOT
        adb pull /sdcard/Android/data/com.wm.pkiservice/ $SNAPSHOT
    fi
    $DUMPSYS meminfo > $SNAPSHOT/meminfos.txt
    $DUMPSYS cpuinfo > $SNAPSHOT/cpuinfos.txt
    $SYNC
#    rm -rf /data/tombstones/*
#    rm -rf /data/anr/*
#    rm -rf /data/system/dropbox/*
#    $SYNC
}

killAllReparenting() {
    logd "killall re-parenting processes \"$1\" "
    #$PS | $GREP $1 | awk -F " " '{print $2,$3}' > $LOGS/tmp.txt
    $PS | $GREP $1 >> $LOGS/tmp.txt
    if [ ! -f $LOGS/tmp.txt ];then
        logd "no process found"
        return
    fi
    while read line
    do
        array=(${line// / })
        if [ ${array[2]} -eq 1 ];then
            logd "\tKilling ${array[1]} ${array[2]} ${array[8]}"
            $KILL -9 ${array[1]}
        fi
    done < $LOGS/tmp.txt
    $RM $LOGS/tmp.txt
}
killAll() {
    logd "killall processes \"$1\" "
    #$PS | $GREP $1 | awk -F " " '{print $2,$3}' > $LOGS/tmp.txt
    $PS | $GREP $1 >> $LOGS/tmp.txt
    if [ ! -f $LOGS/tmp.txt ];then
        logd "no process found"
        return
    fi
    while read line
    do
        array=(${line// / })
        logd "\tKilling ${array[1]} ${array[8]}"
        $KILL -9 ${array[1]}
    done < $LOGS/tmp.txt
    $RM $LOGS/tmp.txt
}
# grep -e sleep -e yfautorun.sh -e kmsg -e procrank -e logcat
termLogs() {
    killAllReparenting yfautorun
    killAllReparenting logcat
    killAll kmsg
    killAllReparenting dmesg
    killAllReparenting procrank
}

# these capture logs functions must be run in background
capture_dmesg() {
    # capture dmesg logs in background per 60s
    while true
    do
        timestamp=`date +"$timestamp_format"`
        logd "$timestamp starting output dmesg logs ... "
        echo "$timestamp starting output dmesg logs ... " >> $LOGS/dmesg.log
        $DMESG -c >> $LOGS/dmesg.log
        $SYNC
        sleep 60
    done
}
capture_kmsg() {
    # capture kmsg logs in background
    timestamp=`date +"$timestamp_format"`
    logd "$timestamp starting kmesg logs ... "
    echo "$timestamp starting kmesg logs ... " > $LOGS/kmsg.log
    $CAT /dev/kmsg >> $LOGS/kmsg.log
}

capture_logcat() {
    # capture logcat logs in background per 3600s
    while true
    do
        timestamp=`date +"$timestamp_format"`
        logd "$timestamp starting logcat logs ... "
        echo "$timestamp starting logcat logs ... " > $LOGS/logcat_logs/logcat.log
        logd "$timestamp starting logcat events logs ... "
        echo "$timestamp starting logcat events logs ... " > $LOGS/logcat_logs/logcat_events.log
        logd "$timestamp starting logcat radio logs ... "
        echo "$timestamp starting logcat radio logs ... " > $LOGS/logcat_logs/logcat_mcu.log
        $LOGCAT -G 2M
        $LOGCAT -v threadtime >> $LOGS/logcat_logs/logcat.log &
        $LOGCAT -b events >> $LOGS/logcat_logs/logcat_events.log &
        $LOGCAT -b radio >> $LOGS/logcat_logs/logcat_mcu.log &
        sleep 3600
        killAll logcat
        gzip $LOGS/logcat_logs/logcat.log $LOGS/logcat_logs/logcat_events.log $LOGS/logcat_logs/logcat_mcu.log
        TmpStamp=$(date +%Y-%m-%d_%H-%M-%S)
        mv $LOGS/logcat_logs/logcat.log.gz $LOGS/logcat_logs/logcat_$TmpStamp.log.gz
        mv $LOGS/logcat_logs/logcat_events.log.gz $LOGS/logcat_logs/logcat_events_$TmpStamp.log.gz
        mv $LOGS/logcat_logs/logcat_mcu.log.gz $LOGS/logcat_logs/logcat_mcu_$TmpStamp.log.gz
    done
}

# capture cpu and memory infos per 30s
capture_cpu_mem_infos() {
    while true
    do
        $PS | $GREP procrank
        if [ $? -ne 0 ];then
            timestamp=`date +"$timestamp_format"`
            logd "$timestamp starting procrank ... "
            echo "$timestamp starting procrank ... " >> $LOGS/procrank.log
            $PROCRANK >> $LOGS/procrank.log
            echo "\n\n" >> $LOGS/procrank.log

        fi
        $PS | $GREP $DUMPSYS
        if [ $? -ne 0 ];then
            timestamp=`date +"$timestamp_format"`
            logd "$timestamp starting dumpsys meminfo ... "
            echo "$timestamp starting dumpsys meminfo ... " >> $LOGS/meminfos.log
            $DUMPSYS meminfo >> $LOGS/meminfos.log
            echo "\n\n" >> $LOGS/meminfos.log

            timestamp=`date +"$timestamp_format"`
            logd "$timestamp starting dumpsys cpuinfo ... "
            echo "$timestamp starting dumpsys cpuinfo ... " >> $LOGS/cpuinfos.log
            $DUMPSYS cpuinfo >> $LOGS/cpuinfos.log
            echo "\n\n" >> $LOGS/cpuinfos.log
        fi
        sleep 30
        $SYNC
    done
}
#######################################################
location_path=`dirname $0`
script=`basename $0`
date_str=$(date +%Y-%m-%d_%H-%M-%S)
LOGDIR=$location_path/wmlog/$date_str
SNAPSHOT=$LOGDIR/snapshot
LOGS=$LOGDIR/logs

mkdir -p $SNAPSHOT
mkdir -p $LOGS
# mkdir path to store logcat logs
mkdir -p $LOGS/logcat_logs

if [ -f /init ];then
    run_where="target"
else
    run_where="host"
    CMD_PRE="adb shell "
fi
# define the commands to use
RM=$CMD_PRE"rm"
DF=$CMD_PRE"df"
CAT=$CMD_PRE"cat"
DMESG=$CMD_PRE"dmesg"
SYNC=$CMD_PRE"sync"
DUMPSYS=$CMD_PRE"dumpsys"
GETPROP=$CMD_PRE"getprop"
LOGCAT=$CMD_PRE"logcat"
PROCRANK=$CMD_PRE"procrank"
KILL=$CMD_PRE"kill"
SETTINGS=$CMD_PRE"settings"

who=`$GETPROP ro.hardware`
if [ "$who"x = "qcom"x ];then
    logd "running in qcom target"
    GREP=$CMD_PRE"grep"
    PS="ps -A"
else
    GREP=$CMD_PRE"/yf/bin/busybox grep"
    PS="ps"
fi

termLogs
make_snapshot
capture_dmesg &
capture_kmsg &
capture_cpu_mem_infos &
capture_logcat
