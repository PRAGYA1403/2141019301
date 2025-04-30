#!/bin/bash

LOG_FILE="/var/log/syslog"
KEYWORDS=("error" "fail" "panic")

echo "Monitoring logs for keywords..."
for keyword in "${KEYWORDS[@]}"; do
    grep -i "$keyword" "$LOG_FILE" && echo "Keyword '$keyword' found!" 
done
