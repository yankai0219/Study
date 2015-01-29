#!/usr/awk -f
function bar(i)
{
    for (i = 0; i < 3; i++)
    print "bar's i=" i

    return i
}
function foo(i)
{
    i = i + 1
    print "foo's i=" i
    j = 10
    i = bar(i)
    print "foo's i=" i
}
BEGIN { 
    i = 10
    j = 20
    print "top's i=" i
    print "top's j=" j
    foo(0)
    print "top's i=" i
    print "top's j=" j
}
