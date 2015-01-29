#!/usr/awk -f
BEGIN {
    ## 执行的ps命令是
    ## ps axo etime, pid, user, comm
    max = 10
}

{ 
    if (length($0) > max) 
    {
        tmp = max
        max = length($0)
        printf "max is change from " tmp " to" max "\n"
    }
    else
    {
        print "hello"
    }
}

END {
}

