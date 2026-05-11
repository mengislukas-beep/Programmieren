#!/bin/bash

echo "Autoklicker startet in 3 Sekunden..."
echo "Stoppen mit CTRL + C"
sleep 2

while true
do
    ydotool click 0xC0
    sleep 0.05
done
