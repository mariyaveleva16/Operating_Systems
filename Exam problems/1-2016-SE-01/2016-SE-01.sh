#!/bin/bash
echo "Броят на търсените редове е $(grep [245680] 2016-SE-01.txt |grep -v [a-w]|wc -l)"
