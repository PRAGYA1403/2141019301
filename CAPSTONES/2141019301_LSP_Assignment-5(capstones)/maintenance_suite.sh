#!/bin/bash

echo "System Maintenance Suite"
PS3="Choose an option: "
options=("Backup" "Update & Cleanup" "Log Monitor" "Exit")

select opt in "${options[@]}"; do
    case $opt in
        "Backup")
            ./backup.sh
            ;;
        "Update & Cleanup")
            ./update_cleanup.sh
            ;;
        "Log Monitor")
            ./log_monitor.sh
            ;;
        "Exit")
            break
            ;;
        *) echo "Invalid option." ;;
    esac
done
