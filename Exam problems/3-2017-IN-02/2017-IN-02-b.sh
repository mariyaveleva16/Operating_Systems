#!/bin/bash
find /home/students/s62445 -printf '%s:%f \n' | sort -n|tail -n 5|cut -d : -f2
