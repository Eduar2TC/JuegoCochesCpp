
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <thread>

using namespace std;

class Ejemplo
{
  public:
    void situaCoordenada(int a, int b)
    {
        HANDLE mueve;
        mueve = GetStdHandle(STD_OUTPUT_HANDLE);
        COORD Posicion;
        Posicion.X = a;
        Posicion.Y = b;
        SetConsoleCursorPosition(mueve, Posicion);
    }

    void OcultaCursor()
    {
        HANDLE Posicion;
        Posicion = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_CURSOR_INFO rosruC;
        rosruC.dwSize = 2;
        rosruC.bVisible = FALSE;
        SetConsoleCursorInfo(Posicion, &rosruC);
    }

    void escribeHola()
    {
        /*cout << "Hola";
        Sleep(100);*/
        for (int i = 10; i < 20; i++)
        {
            situaCoordenada(i, 5);
            fflush(stdout);
            cout << i - 10 << "  ";
            Sleep(400);
        }
    }
    void escribeMundo()
    {

        /*cout << "caca ";
        Sleep(500);
        cout << "Mundo";*/
        for (int i = 30; i < 40; i++)
        {
            fflush(stdout);
            situaCoordenada(i, 5);
            cout << i - 30;
            Sleep(2000);
        }
    }
};

int main()
{
    /*  std::thread t1(&escribeHola);
    std::thread t2(&escribeMundo);*/
    Ejemplo *eje1 = new Ejemplo();
    std::thread t1(&Ejemplo::escribeHola, eje1);
    std::thread t2(&Ejemplo::escribeMundo, eje1);

    t1.join();
    t2.join();

    cin.get();
    return 0;
}
