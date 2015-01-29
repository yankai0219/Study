#!/usr/awk -f
BEGIN {
    printf "Begin parse netstat\n"
    printf "-------------------------------------------------\n"
    OFS = "\t"
    white="FIN"
}
## case1 
#$6 ~ /FIN_WAIT1|FIN_WAIT2|LISTEN/ || NR == 1 \
## case2 模式取反
$6 !~ /FIN_WAIT1|FIN_WAIT2|LISTEN/ || NR == 1 \
{ print \
      NR,
      $4,
      $5,
      $6
}
END {
    printf "End parse netstat\n"
}

