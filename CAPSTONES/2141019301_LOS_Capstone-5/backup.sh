#!/bin/bash

BACKUP_DIR="/tmp/backup_$(date +%F_%T)"
SOURCE_DIR="/home/$USER"

mkdir -p "$BACKUP_DIR"

if cp -r "$SOURCE_DIR" "$BACKUP_DIR"; then
    echo "Backup completed successfully to $BACKUP_DIR"
else
    echo "Backup failed!" >&2
fi
