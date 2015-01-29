#!/usr/awk -f
BEGIN {
    printf "Begin statastic netstat\n"
    printf "-------------------------------------------------\n"
}
### 运行中
### 只是打印
##{
##    # case 1
##    print $1, $4
##    # case 2
##    printf "%-8s %-8s %-8s\n", $1, $3, $4
##}
### 过滤记录
## case 3
# $3 == 0 && $6 == "LISTEN" \
# {
#     print $1, $3, $6
# }

# case4
$3 > 0 || NR == 1\
{
    print $0
}
END {
    printf "Ent statastic netsat\n"
}

