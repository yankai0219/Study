#!/usr/awk -f
BEGIN {
    printf "统计每个用户的进程占了多少内存"
    printf "-------------------------------------------------\n"
}
NR != 1 \
{
    a[$1] += $6
}

END {
    for ( i in a)
        print i "," a[i] "KB"
}

