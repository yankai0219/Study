#!/usr/awk -f
BEGIN {
    printf "Begin parse netstat\n"
    printf "-------------------------------------------------\n"
}
## case1 按照第六列分割文件
# NR != 1 \
# {print > $6}
## case 2 将指定的列输出到文件
# NR != 1 \
# {print $4,$5 > $6}
## case3 if-else
NR != 1 \
{ 
    if ($6 ~ /TIME|ESTABLISHED/)
    {
        print > "1.tmp";
        print $1;
    }
    else if ($6 ~ /LISTEN/) 
        print > "2.tmp";
    else 
        print > "3.tmp";
}

END {
    printf "End parse netstat\n"
}

