#!/bin/bash
find . -printf %n %fn 2>/dev/null|sort -n|tail -n 5
