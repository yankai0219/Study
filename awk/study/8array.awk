#!/usr/awk -f
BEGIN {
    printf "学习awk中数组知识\n"
    arr["a1"] = "a1111" 
    arr["a2"] = "a2222" 
    arr["a3"] = "a3333" 
    arr["a4"] = "a4444" 
}
{
    for (ele in arr)
    {
        printf arr[ele] "\n"
        if ( ele == "a1")
        {
            printf "delele" ele " in arr\n"
            delete arr[ele]
        }
    }
    if ( "a1" in arr)
    {
        printf "a1 is in arr\n"
    }
    else
    {
        printf "a1 is NOT in arr\n"
    }
}

END {
}

