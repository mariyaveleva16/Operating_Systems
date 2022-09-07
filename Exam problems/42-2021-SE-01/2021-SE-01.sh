#!/bin/bash

path=$(printenv HOME)

find $path/sbornik -name "sum.sh"|wc -l

diag_dest=/home/students/s62445

find $diag_dest -maxdepth 1
