#include <iostream>
#include <windows.h>
#include <conio.h>

#define Izquierda 75
#define Derecha 77

using namespace std;

class ContraladorConsola
{
  public:
    ControladorConsola();
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
    char obtieneCaracterConsola(int x, int y)
    {

        HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

        char characterFromConsole;

        COORD positionInBuffer;
        positionInBuffer.X = x; // Column number
        positionInBuffer.Y = y; // Row number

        DWORD numberOfCharactersReaded = 0;

        DWORD numberOfCharactersToRead = 1;

        ReadConsoleOutputCharacter(
            consoleHandle,
            &characterFromConsole,
            numberOfCharactersToRead,
            positionInBuffer,
            &numberOfCharactersReaded);

        return characterFromConsole;
    }
};

class Escenario : public ContraladorConsola
{
  private:
    int largoEscenario;
    int anchoEscenario;

  public:
    Escenario(int nuevoLargo, int nuevoAncho);
    void dibujaEscenario();
    void animaEscenario();
    void detectarColision(Coche coche, CocheEnemigo cocheEnemigo); //Obtener las coordenadas de cada elemento y comparar si son iguales
};

Escenario::Escenario(int xLargo, int yAncho) : ContraladorConsola()
{
    this->anchoEscenario = xLargo;
    this->largoEscenario = yAncho;
}

void Escenario ::dibujaEscenario()
{
    //Orillas de la carretera
    for (int x = 0; x < anchoEscenario; x++)
    {
        for (int y = 0; y < largoEscenario; y++)
        {
            Escenario::situaCoordenada(x, y);
            if ((x == 0 || x == anchoEscenario - 1) && (y % 2 == 0))
            {
                cout << "|";
            }
            else
            {
                cout << " ";
            }
        }

        //Lineas centrales de la carretera
        for (int y = 0; y < largoEscenario; y += 4)
        {
            this->situaCoordenada((anchoEscenario - 1) / 2, y);
            cout << "::";
            this->situaCoordenada((anchoEscenario - 1) / 2, y + 1);
            cout << "::";
        }
    }
}

void Escenario::animaEscenario()
{
    int x1 = 0, x2 = anchoEscenario - 1, x3 = x2 / 2;
    char caracter1, caracter2, caracter3;

    //anima orillas de la carretera
    for (int y = 0; y < largoEscenario; y++)
    {

        this->situaCoordenada(x1, y);
        caracter1 = this->obtieneCaracterConsola(x1, y);
        this->situaCoordenada(x2, y);
        caracter2 = this->obtieneCaracterConsola(x2, y);
        if (caracter1 == '|' && caracter2 == '|')
        {
            this->situaCoordenada(x1, y);
            cout << " ";
            this->situaCoordenada(x2, y);
            cout << " ";
            Sleep(20); // velocidad de desplazamiento
        }
        else
        {
            this->situaCoordenada(x1, y);
            cout << "|";
            this->situaCoordenada(x2, y);
            cout << "|";
        }
    }
    for (int y = 0; y < largoEscenario; y += 4)
    {
        this->situaCoordenada(x3, y);
        caracter3 = this->obtieneCaracterConsola(x3, y);
        if (caracter3 == ':')
        {
            this->situaCoordenada(x3, y);
            cout << " ";
            this->situaCoordenada(x3 + 1, y);
            cout << " ";

            this->situaCoordenada(x3, y + 1);
            cout << " ";
            this->situaCoordenada(x3 + 1, y + 1);
            cout << " ";
            Sleep(300); // control de velocidad de las lineas
        }
        else
        {
            this->situaCoordenada(x3, y);
            cout << ":";
            this->situaCoordenada(x3 + 1, y);
            cout << ":";

            this->situaCoordenada(x3, y + 1);
            cout << ":";
            this->situaCoordenada(x3 + 1, y + 1);
            cout << ":";
            Sleep(300); // control de velocidad de las lineas
        }
    }
}

class Coche : public ContraladorConsola
{
  private:
    int posicionX;
    int posicionY;
    int velocidad;

  public:
    Coche(int x, int y);

    //largo coche  x : 1-6, ancho y: 1-3
    void dibujaCoche(int x, int y);
    void moverCoche();
    void borraCoche();
    void explotaCoche();
};

Coche::Coche(int x, int y) : ContraladorConsola()
{
    this->posicionX = x;
    this->posicionY = y;
    dibujaCoche(x, y);
}

void Coche::dibujaCoche(int x, int y)
{
    this->situaCoordenada(x, y);
    cout
        << "()<"
        << "[|]"
        << ">()";
    this->situaCoordenada(x + 3, y + 1);
    cout << "|||";
    this->situaCoordenada(x, y + 2);
    cout
        << "()<"
        << "[|]"
        << ">()";
}

void Coche::borraCoche()
{
    Coche::situaCoordenada(this->posicionX, this->posicionY);
    cout << "         ";
    Coche::situaCoordenada(this->posicionX, this->posicionY + 1);
    cout << "         ";
    Coche::situaCoordenada(this->posicionX, this->posicionY + 2);
    cout << "         ";
    Coche::situaCoordenada(this->posicionX, this->posicionY + 3);
    cout << "         ";
}

void Coche::explotaCoche()
{
    Coche::situaCoordenada(this->posicionX, this->posicionY);
    //Cuadro 1
    cout << "       ";
    Coche::situaCoordenada(this->posicionX, this->posicionY + 1);
    cout << "   ***   ";
    Coche::situaCoordenada(this->posicionX, this->posicionY + 2);
    cout << "   ***   ";
    Coche::situaCoordenada(this->posicionX, this->posicionY + 3);
    cout << "       ";
    Sleep(100);

    //Cuadro 2
    Coche::borraCoche();
    Coche::situaCoordenada(this->posicionX, this->posicionY);
    cout << "*       *";
    Coche::situaCoordenada(this->posicionX, this->posicionY + 1);
    cout << "   ***   ";
    Coche::situaCoordenada(this->posicionX, this->posicionY + 2);
    cout << "   ***   ";
    Coche::situaCoordenada(this->posicionX, this->posicionY + 3);
    cout << "*       *";
    Sleep(150);

    //Cuadro3
    Coche::borraCoche();
    Coche::situaCoordenada(this->posicionX, this->posicionY);
    cout << "    *    ";
    Coche::situaCoordenada(this->posicionX, this->posicionY + 1);
    cout << "*      *";
    Coche::situaCoordenada(this->posicionX, this->posicionY + 2);
    cout << "*      *";
    Coche::situaCoordenada(this->posicionX, this->posicionY + 3);
    cout << "    *    ";
    Sleep(300);

    //Cuadro 4
    Coche::borraCoche();
    Coche::dibujaCoche(this->posicionX, this->posicionY);
}

void Coche::moverCoche()
{
    if (kbhit() == true)
    {
        char teclaPresionada = getch();
        switch (teclaPresionada)
        {
        case 'a':
        {
            if (this->posicionX > 1)
            {
                situaCoordenada(this->posicionX, this->posicionY);
                Coche::borraCoche();
                this->posicionX = this->posicionX - 11;
                Coche::dibujaCoche(this->posicionX, this->posicionY);
            }
            break;
        }
        case 'd':
        {
            if (this->posicionX < 11)
            {
                situaCoordenada(this->posicionX, this->posicionY);
                Coche::borraCoche();
                this->posicionX = this->posicionX + 11;
                Coche::dibujaCoche(this->posicionX, this->posicionY);
            }
            break;
        }
        case Izquierda:
        {
            if (this->posicionX > 1)
            {
                situaCoordenada(this->posicionX, this->posicionY);
                Coche::borraCoche();
                this->posicionX--;
                Coche::dibujaCoche(this->posicionX, this->posicionY);
            }
            break;
        }
        case Derecha:
        {
            if (this->posicionX < 13)
            {
                situaCoordenada(this->posicionX, this->posicionY);
                Coche::borraCoche();
                this->posicionX++;
                Coche::dibujaCoche(this->posicionX, this->posicionY);
            }
            break;
        }
        case 'f':
        {
            Coche::explotaCoche();
            break;
        }
        default:
        {
            Coche::situaCoordenada(this->posicionX, this->posicionY);
            Coche::dibujaCoche(this->posicionX, this->posicionY);
            break;
        }
        }
    }
}

class CocheEnemigo : public ControladorConsola
{
  private:
    int posicionX;
    int posicionY;

  public:
    void animaEnemigo();
};

void CocheEnemigo::animaEnemigo()
{
}

int main()
{
    // (x-largo, y-ancho)
    bool gameOver = false;
    Escenario escena(22, 12);
    escena.dibujaEscenario();
    escena.OcultaCursor();
    Coche coche(12, 9); // alternar coordenada x

    while (gameOver == false)
    {
        coche.moverCoche();
        Sleep(10);
        escena.animaEscenario();
    }

    cin.get();
    return 0;
}