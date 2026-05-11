#pragma once
#include <iostream>
#include <cmath>
#include <chrono>
#include <thread>

using namespace std;

void kreis() {
    int radius = 10;

    while (true) {
        // Bildschirm "löschen"
        system("clear"); // Windows: system("cls");

        for (int y = -15; y <= 15; y++) {
            for (int x = -30; x <= 30; x++) {

                // Kreisbewegung berechnen
                double angle = chrono::duration<double>(
                    chrono::system_clock::now().time_since_epoch()
                ).count();

                int px = (int)(radius * cos(angle));
                int py = (int)(radius * sin(angle));

                if (x == px && y == py)
                    cout << "#";  // dein "Viereck"
                else
                    cout << " ";
            }
            cout << endl;
        }

        this_thread::sleep_for(chrono::milliseconds(50));
    }
}
void rechteck() {
     int radius = 10;

    while (true) {
        // Bildschirm "löschen"
        system("clear"); // Windows: system("cls");

        for (int y = -15; y <= 15; y++) {
            for (int x = -30; x <= 30; x++) {

                // Kreisbewegung berechnen
                double angle = chrono::duration<double>(
                    chrono::system_clock::now().time_since_epoch()
                ).count();

                int px = (int)(radius * cos(angle));
                int py = (int)(radius * sin(angle));

                if (x <= px && y <= py)
                    cout << "#";  // dein "Viereck"
                else
                    cout << " ";
            }
            cout << endl;
        }

        this_thread::sleep_for(chrono::milliseconds(50));
    }
}  
