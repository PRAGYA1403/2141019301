#!/bin/bash

echo "Starting system update..."
sudo apt update && sudo apt upgrade -y

echo "Cleaning up unnecessary packages..."
sudo apt autoremove -y
sudo apt autoclean

echo "Update and cleanup completed."
