#!/bin/bash

# check if filename is provided
if [ -z "$1" ]; then
    echo "Usage: ./log_summary.sh <filename>"
    exit 1
fi

LOGFILE=$1

# 1. print the total number of lines in the file
echo "LINES: $(wc -l < "$LOGFILE")"

# 2. print the total number of unique entries in column 1
echo "STATUS_COUNTS:"

# 3. extract column 1, count unique occurrences, sort by count descending
awk '{print $2}' "$LOGFILE" | sort | uniq -c | sort -rn | awk '{print $2, $1}'