#!/usr/awk -f
function trav_arr(arr)
{
    for (ele in arr)
    {
        
        printf("key:%s ele:%s\n", ele, arr[ele])
    }
}
BEGIN {
    printf "学习awk中字符串函数split知识\n"
}
{
    #split("12faf:dfada:3sfa", a, ":")
    #trav_arr(a)
    split("/user/vleverl?/afsd", b, "/")
    trav_arr(b)
    one_line = "10.104.79.65 [25/Jan/2015:23:56:08 +0800] \"GET /user/vlevel?qids=%5B%221368665732%22%5D&bizid=xiankan-pinglun&logid=54c512115cd8d209 HTTP/1.1\" 200 72 \"-\" \"-\" 187 0.010 0.008"
    pos = match(one_line, /\ /);
    ip = substr(one_line, 0, pos);
    printf("pos:%d ip:%s\n", pos, ip);
    action_pos = match(one_line, /\.*GET\ \//);
    action_end = match(one_line, /\?/);
    action = substr(one_line, action_pos, action_end);
    printf("action_pos:%d end:%d action:%s\n", action_pos,action_end, action);
}

END {
}

