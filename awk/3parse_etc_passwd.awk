#!/usr/awk -f
BEGIN {
    printf "Begin parse /etc/passwd\n"
    printf "-------------------------------------------------\n"
    FS = ":"
    OFS = "\t"
}
{
    print $1, $3, $6
}
END {
    printf "Begin parse /etc/passwd\n"
}

