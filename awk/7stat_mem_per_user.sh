#!/bin/sh
ps aux | awk -f 7stat_mem_per_proc.awk
