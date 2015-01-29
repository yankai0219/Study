#!/usr/awk -f
    function delete_arr(arr)
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
    }
    function traverse_arr(arr)
    {
        for (ele in arr)
        {
            printf("ele:%s\n", arr[ele])
        }
    }
BEGIN {
    printf "学习awk中函数知识\n"
    arr["a1"] = "a1111" 
    arr["a2"] = "a2222" 
    arr["a3"] = "a3333" 
    arr["a4"] = "a4444" 
}

{
    traverse_arr(arr)
    delete_arr(arr)
    traverse_arr(arr)
}

END {
}

