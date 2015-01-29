#!/usr/awk -f
BEGIN {
    printf "Begin parse awk\n"
    printf "-------------------------------------------------\n"
    total = 100000;
}
{
    total += $5
}

END {
    printf "End parse awk\n"
    printf "sum:%d\n", total
}

