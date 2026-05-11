#include <windows.h>
#include <iostream>

int main() {
    bool clicking = false;

    std::cout << "LEERTASTE = Start/Stop\n";
    std::cout << "ESC = Beenden\n";

    while (true) {

        // Leertaste gedrückt
        if (GetAsyncKeyState(VK_SPACE) & 1) {
            clicking = !clicking;

            if (clicking)
                std::cout << "Autoklicker AN\n";
            else
                std::cout << "Autoklicker AUS\n";
        }

        // ESC beendet Programm
        if (GetAsyncKeyState(VK_ESCAPE) & 1) {
            break;
        }

        // Klicks ausführen
        if (clicking) {
            mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
            mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);

            Sleep(50); // Geschwindigkeit
        }

        Sleep(10);
    }

    return 0;
}