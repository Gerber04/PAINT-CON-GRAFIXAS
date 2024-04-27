#include <stdio.h>
#include <conio.h>
#include <windows.h> // Para manipular la consola

// Declaraci�n de funciones
void moveTo(int x, int y);
void getConsoleSize(int *width, int *height);
void clearConsole();
void mostrarComandosMenu();
void dibujarTriangulo(int altura, int x, int y);
void manejarOpcionTriangulo(int consoleWidth, int consoleHeight);
void manejarOpcionCuadrado(int consoleWidth, int consoleHeight);
void manejarOpcionRectangulo(int consoleWidth, int consoleHeight);
void manejarOpcionCirculo(int consoleWidth, int consoleHeight);
void manejarOpcionLinea(int consoleWidth, int consoleHeight);
void manejarOpcionRombo(int consoleWidth, int consoleHeight);
void manejarOpcionHexagono(int consoleWidth, int consoleHeight);
void mostrarBienvenida(int consoleWidth, int consoleHeight);
void dibujarCuadrado(int lado, int x, int y);
void dibujarRect(int altura, int anchura, int x, int y);
void dibujarCirculo(int radio, int x, int y);
void dibujarLinea(int longitud, int x, int y);
void dibujarRombo(int diagonalMayor, int x, int y);
void dibujarHexagono(int lado, int x, int y);

// Funci�n para mover el cursor a una posici�n espec�fica en la consola
void moveTo(int x, int y) {
    COORD position;
    position.X = x;
    position.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
}

// Funci�n para obtener el tama�o de la consola
void getConsoleSize(int *width, int *height) {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    *width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    *height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
}

// Funci�n para limpiar la consola
void clearConsole() {
    system("cls");
}
// Funci�n para mostrar la barra de men� horizontal con cuadrados de altura 3, anchura 4 y color verde
// Funci�n para mostrar la barra de men� horizontal con cuadrados de altura 1 y anchura 4
void mostrarBarraDeMenu() {
    // Define la posici�n inicial de la barra de men� (en la parte superior de la consola)
    int y = 0;
    int x = 0;

    // Establece el color de fondo blanco y el color de primer plano verde
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY | FOREGROUND_GREEN);

    // Dibuja los cuadrados de altura 1 y anchura 4 con etiquetas F1 a F12 y CTRL + A
    for (int i = 0; i < 12; i++) {
        // Mueve el cursor a la posici�n correspondiente
        moveTo(x + i * 4, y);
        // Imprime el texto en el cuadrado
        printf(" F%d ", i + 1);
    }

    // A�adir el cuadrado para CTRL + A
    moveTo(x + 13 * 4, y);
    printf("CTRL");

    // Restablece los colores predeterminados
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
}

// Funci�n para mostrar el bot�n de men�
void mostrarBotonMenu(int consoleWidth, int consoleHeight) {
    // Calcula la posici�n para centrar el bot�n de men�
    int x = consoleWidth / 2 - 2;
    int y = consoleHeight / 2;

    // Mueve el cursor a la posici�n calculada
    moveTo(x, y);

    // Cambia el color a blanco sobre fondo negro
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);

    // Imprime el texto "MEN�"
    printf("MEN�");
}

// Funci�n para dibujar un tri�ngulo
void dibujarTriangulo(int altura, int x, int y) {
    // Dibuja el tri�ngulo con *
    for (int i = 0; i < altura; i++) {
        moveTo(x - i, y + i);
        for (int j = 0; j <= 2 * i; j++) {
            printf("*");
        }
        printf("\n");
    }
}
// Funci�n para manejar la opci�n de dibujar un tri�ngulo
void manejarOpcionTriangulo(int consoleWidth, int consoleHeight) {
    // Ocultar la barra de men�
    for (int i = 0; i < 16; i++) {
        moveTo(i * 4, 0);
        printf("    ");
    }
    moveTo(12 * 4, 0);
    printf("     ");

    // Solicitar la altura del tri�ngulo
    moveTo(0, consoleHeight - 3); // Mueve el cursor a la l�nea para mostrar los mensajes
    printf("Ingrese la altura del tri�ngulo: ");
    int altura;
    scanf("%d", &altura);

    // Solicitar al usuario mover el cursor a una nueva posici�n
    printf("\nMueva el cursor a la nueva posici�n deseada con las teclas de flecha.");
    printf("\nPresione Enter para confirmar la posici�n del cursor...\n");

    int cursorX = consoleWidth / 2;
    int cursorY = consoleHeight / 2;
    moveTo(cursorX, cursorY);

    // Permitir al usuario mover el cursor y confirmar la posici�n
    while (1) {
        if (_kbhit()) {
            int key = _getch();

            // Manejar las teclas de flecha para mover el cursor
            if (key == 0 || key == 224) {
                key = _getch();

                switch (key) {
                    case 72: // Flecha arriba
                        cursorY--;
                        break;
                    case 80: // Flecha abajo
                        cursorY++;
                        break;
                    case 75: // Flecha izquierda
                        cursorX--;
                        break;
                    case 77: // Flecha derecha
                        cursorX++;
                        break;
                }
                // Mueve el cursor a la nueva posici�n
                moveTo(cursorX, cursorY);
            } else if (key == '\r') {
                // Confirmar la posici�n del cursor
                break;
            }
        }
    }

    // Limpiar los mensajes de solicitud de posici�n
    moveTo(0, consoleHeight - 3);
    printf("\033[K"); // Borra desde la posici�n actual hasta el final de la l�nea

    moveTo(0, consoleHeight - 2);
    printf("\033[K"); // Borra desde la posici�n actual hasta el final de la l�nea

    // Dibuja el tri�ngulo en la nueva posici�n confirmada
    dibujarTriangulo(altura, cursorX, cursorY);

    // Volver a mostrar la barra de men�
    mostrarBarraDeMenu();
}

// Funci�n para dibujar un cuadrado
void dibujarCuadrado(int lado, int x, int y) {
    for (int i = 0; i < lado; i++) {
        moveTo(x, y + i);
        for (int j = 0; j < lado; j++) {
            printf("*");
        }
        printf("\n");
    }
}
// Funci�n para manejar la opci�n de dibujar un cuadrado
void manejarOpcionCuadrado(int consoleWidth, int consoleHeight) {
    // Ocultar la barra de men�
    for (int i = 0; i < 16; i++) {
        moveTo(i * 4, 0);
        printf("    ");
    }
    moveTo(12 * 4, 0);
    printf("     ");

    // Solicitar el lado del cuadrado
    moveTo(0, consoleHeight - 3);
    printf("Ingrese el lado del cuadrado: ");
    int lado;
    scanf("%d", &lado);

    // Solicitar al usuario mover el cursor a una nueva posici�n
    moveTo(0, consoleHeight - 2);
    printf("\nMueva el cursor a la nueva posici�n deseada con las teclas de flecha.");
    printf("\nPresione Enter para confirmar la posici�n del cursor...\n");

    int cursorX = consoleWidth / 2;
    int cursorY = consoleHeight / 2;
    moveTo(cursorX, cursorY);

    // Permitir al usuario mover el cursor y confirmar la posici�n
    while (1) {
        if (_kbhit()) {
            int key = _getch();

            // Manejar las teclas de flecha para mover el cursor
            if (key == 0 || key == 224) {
                key = _getch();

                switch (key) {
                    case 72: // Flecha arriba
                        cursorY--;
                        break;
                    case 80: // Flecha abajo
                        cursorY++;
                        break;
                    case 75: // Flecha izquierda
                        cursorX--;
                        break;
                    case 77: // Flecha derecha
                        cursorX++;
                        break;
                }
                // Mueve el cursor a la nueva posici�n
                moveTo(cursorX, cursorY);
            } else if (key == '\r') {
                // Confirmar la posici�n del cursor
                break;
            }
        }
    }

    // Limpia los mensajes de solicitud de posici�n
    moveTo(0, consoleHeight - 3);
    printf("\033[K"); // Borra desde la posici�n actual hasta el final de la l�nea

    moveTo(0, consoleHeight - 2);
    printf("\033[K"); // Borra desde la posici�n actual hasta el final de la l�nea

    // Dibuja el cuadrado en la nueva posici�n confirmada
    dibujarCuadrado(lado, cursorX, cursorY);

    // Volver a mostrar la barra de men�
    mostrarBarraDeMenu();
}

// Funci�n para dibujar un rect�ngulo
void dibujarRect(int altura, int anchura, int x, int y) {
    for (int i = 0; i < altura; i++) {
        moveTo(x, y + i);
        for (int j = 0; j < anchura; j++) {
            printf("*");
        }
        printf("\n");
    }
}
// Funci�n para manejar la opci�n de dibujar un rect�ngulo
void manejarOpcionRectangulo(int consoleWidth, int consoleHeight) {
    // Ocultar la barra de men�
    for (int i = 0; i < 16; i++) {
        moveTo(i * 4, 0);
        printf("    ");
    }
    moveTo(12 * 4, 0);
    printf("     ");

    // Solicitar la altura y anchura del rect�ngulo
    moveTo(0, consoleHeight - 3);
    printf("Ingrese la altura del rect�ngulo: ");
    int altura;
    scanf("%d", &altura);

    printf("Ingrese la anchura del rect�ngulo: ");
    int anchura;
    scanf("%d", &anchura);

    // Solicitar al usuario mover el cursor a una nueva posici�n
    moveTo(0, consoleHeight - 2);
    printf("\nMueva el cursor a la nueva posici�n deseada con las teclas de flecha.");
    printf("\nPresione Enter para confirmar la posici�n del cursor...\n");

    int cursorX = consoleWidth / 2;
    int cursorY = consoleHeight / 2;
    moveTo(cursorX, cursorY);

    // Permitir al usuario mover el cursor y confirmar la posici�n
    while (1) {
        if (_kbhit()) {
            int key = _getch();

            // Manejar las teclas de flecha para mover el cursor
            if (key == 0 || key == 224) {
                key = _getch();

                switch (key) {
                    case 72: // Flecha arriba
                        cursorY--;
                        break;
                    case 80: // Flecha abajo
                        cursorY++;
                        break;
                    case 75: // Flecha izquierda
                        cursorX--;
                        break;
                    case 77: // Flecha derecha
                        cursorX++;
                        break;
                }
                // Mueve el cursor a la nueva posici�n
                moveTo(cursorX, cursorY);
            } else if (key == '\r') {
                // Confirma la posici�n del cursor
                break;
            }
        }
    }

    // Limpia los mensajes de solicitud de posici�n
    moveTo(0, consoleHeight - 3);
    printf("\033[K"); // Borra desde la posici�n actual hasta el final de la l�nea

    moveTo(0, consoleHeight - 2);
    printf("\033[K"); // Borra desde la posici�n actual hasta el final de la l�nea

    // Dibuja el rect�ngulo en la nueva posici�n confirmada
    dibujarRect(altura, anchura, cursorX, cursorY);

    // Volver a mostrar la barra de men�
    mostrarBarraDeMenu();
}

// Funci�n para dibujar un c�rculo
void dibujarCirculo(int radio, int x, int y) {
    // Algoritmo para dibujar un c�rculo usando el m�todo de Bresenham

    int x0 = x;
    int y0 = y;
    int a = radio;
    int b = 0;
    int d = 3 - 2 * a;

    while (b <= a) {
        // Dibuja los puntos del c�rculo en octante
        moveTo(x0 + a, y0 + b);
        printf("*");
        moveTo(x0 - a, y0 + b);
        printf("*");
        moveTo(x0 + a, y0 - b);
        printf("*");
        moveTo(x0 - a, y0 - b);
        printf("*");
        moveTo(x0 + b, y0 + a);
        printf("*");
        moveTo(x0 - b, y0 + a);
        printf("*");
        moveTo(x0 + b, y0 - a);
        printf("*");
        moveTo(x0 - b, y0 - a);
        printf("*");

        // Calcula el siguiente punto
        if (d < 0) {
            d = d + 4 * b + 6;
        } else {
            d = d + 4 * (b - a) + 10;
            a--;
        }
        b++;
    }
}
// Funci�n para manejar la opci�n de dibujar un c�rculo
void manejarOpcionCirculo(int consoleWidth, int consoleHeight) {
    // Ocultar la barra de men�
    for (int i = 0; i < 16; i++) {
        moveTo(i * 4, 0);
        printf("    ");
    }
    moveTo(12 * 4, 0);
    printf("     ");

    // Solicitar el radio del c�rculo
    moveTo(0, consoleHeight - 3);
    printf("Ingrese el radio del c�rculo: ");
    int radio;
    scanf("%d", &radio);

    // Solicitar al usuario mover el cursor a una nueva posici�n
    moveTo(0, consoleHeight - 2);
    printf("\nMueva el cursor a la nueva posici�n deseada con las teclas de flecha.");
    printf("\nPresione Enter para confirmar la posici�n del cursor...\n");

    int cursorX = consoleWidth / 2;
    int cursorY = consoleHeight / 2;
    moveTo(cursorX, cursorY);

    // Permitir al usuario mover el cursor y confirmar la posici�n
    while (1) {
        if (_kbhit()) {
            int key = _getch();

            // Manejar las teclas de flecha para mover el cursor
            if (key == 0 || key == 224) {
                key = _getch();

                switch (key) {
                    case 72: // Flecha arriba
                        cursorY--;
                        break;
                    case 80: // Flecha abajo
                        cursorY++;
                        break;
                    case 75: // Flecha izquierda
                        cursorX--;
                        break;
                    case 77: // Flecha derecha
                        cursorX++;
                        break;
                }
                // Mueve el cursor a la nueva posici�n
                moveTo(cursorX, cursorY);
            } else if (key == '\r') {
                // Confirma la posici�n del cursor
                break;
            }
        }
    }

    // Limpia los mensajes de solicitud de posici�n
    moveTo(0, consoleHeight - 3);
    printf("\033[K"); // Borra desde la posici�n actual hasta el final de la l�nea

    moveTo(0, consoleHeight - 2);
    printf("\033[K"); // Borra desde la posici�n actual hasta el final de la l�nea

    // Dibuja el c�rculo en la nueva posici�n confirmada
    dibujarCirculo(radio, cursorX, cursorY);

    // Volver a mostrar la barra de men�
    mostrarBarraDeMenu();
}

// Funci�n para dibujar una l�nea horizontal
void dibujarLinea(int longitud, int x, int y) {
    moveTo(x, y);
    for (int i = 0; i < longitud; i++) {
        printf("*");
    }
}

// Funci�n para manejar la opci�n de dibujar una l�nea
void manejarOpcionLinea(int consoleWidth, int consoleHeight) {
    // Ocultar la barra de men�
    for (int i = 0; i < 16; i++) {
        moveTo(i * 4, 0);
        printf("    ");
    }
    moveTo(12 * 4, 0);
    printf("     ");

    // Solicitar la longitud de la l�nea
    moveTo(0, consoleHeight - 3);
    printf("Ingrese la longitud de la l�nea: ");
    int longitud;
    scanf("%d", &longitud);

    // Solicitar al usuario mover el cursor a una nueva posici�n
    moveTo(0, consoleHeight - 2);
    printf("\nMueva el cursor a la nueva posici�n deseada con las teclas de flecha.");
    printf("\nPresione Enter para confirmar la posici�n del cursor...\n");

    int cursorX = consoleWidth / 2;
    int cursorY = consoleHeight / 2;
    moveTo(cursorX, cursorY);

    // Permitir al usuario mover el cursor y confirmar la posici�n
    while (1) {
        if (_kbhit()) {
            int key = _getch();

            // Manejar las teclas de flecha para mover el cursor
            if (key == 0 || key == 224) {
                key = _getch();

                switch (key) {
                    case 72: // Flecha arriba
                        cursorY--;
                        break;
                    case 80: // Flecha abajo
                        cursorY++;
                        break;
                    case 75: // Flecha izquierda
                        cursorX--;
                        break;
                    case 77: // Flecha derecha
                        cursorX++;
                        break;
                }
                // Mueve el cursor a la nueva posici�n
                moveTo(cursorX, cursorY);
            } else if (key == '\r') {
                // Confirma la posici�n del cursor
                break;
            }
        }
    }

    // Limpia los mensajes de solicitud de posici�n
    moveTo(0, consoleHeight - 3);
    printf("\033[K"); // Borra desde la posici�n actual hasta el final de la l�nea

    moveTo(0, consoleHeight - 2);
    printf("\033[K"); // Borra desde la posici�n actual hasta el final de la l�nea

    // Dibuja la l�nea en la nueva posici�n confirmada
    dibujarLinea(longitud, cursorX, cursorY);

    // Volver a mostrar la barra de men�
    mostrarBarraDeMenu();
}


// Funci�n para dibujar un rombo
void dibujarRombo(int diagonalMayor, int x, int y) {
    // Calcula la diagonal menor
    int diagonalMenor = diagonalMayor / 2;

    // Dibuja la parte superior del rombo
    for (int i = 0; i < diagonalMenor; i++) {
        moveTo(x - i, y + i);
        for (int j = 0; j <= 2 * i; j++) {
            printf("*");
        }
        printf("\n");
    }

    // Dibuja la parte inferior del rombo
    for (int i = diagonalMenor; i >= 0; i--) {
        moveTo(x - i, y + (diagonalMayor - i));
        for (int j = 0; j <= 2 * i; j++) {
            printf("*");
        }
        printf("\n");
    }
}
// Funci�n para manejar la opci�n de dibujar un rombo
void manejarOpcionRombo(int consoleWidth, int consoleHeight) {
    // Ocultar la barra de men�
    for (int i = 0; i < 16; i++) {
        moveTo(i * 4, 0);
        printf("    ");
    }
    moveTo(12 * 4, 0);
    printf("     ");

    // Solicitar la diagonal mayor del rombo
    moveTo(0, consoleHeight - 3);
    printf("Ingrese la diagonal mayor del rombo: ");
    int diagonalMayor;
    scanf("%d", &diagonalMayor);

    // Solicitar al usuario mover el cursor a una nueva posici�n
    moveTo(0, consoleHeight - 2);
    printf("\nMueva el cursor a la nueva posici�n deseada con las teclas de flecha.");
    printf("\nPresione Enter para confirmar la posici�n del cursor...\n");

    int cursorX = consoleWidth / 2;
    int cursorY = consoleHeight / 2;
    moveTo(cursorX, cursorY);

    // Permitir al usuario mover el cursor y confirmar la posici�n
    while (1) {
        if (_kbhit()) {
            int key = _getch();

            // Manejar las teclas de flecha para mover el cursor
            if (key == 0 || key == 224) {
                key = _getch();

                switch (key) {
                    case 72: // Flecha arriba
                        cursorY--;
                        break;
                    case 80: // Flecha abajo
                        cursorY++;
                        break;
                    case 75: // Flecha izquierda
                        cursorX--;
                        break;
                    case 77: // Flecha derecha
                        cursorX++;
                        break;
                }
                // Mueve el cursor a la nueva posici�n
                moveTo(cursorX, cursorY);
            } else if (key == '\r') {
                // Confirma la posici�n del cursor
                break;
            }
        }
    }

    // Limpia los mensajes de solicitud de posici�n
    moveTo(0, consoleHeight - 3);
    printf("\033[K"); // Borra desde la posici�n actual hasta el final de la l�nea

    moveTo(0, consoleHeight - 2);
    printf("\033[K"); // Borra desde la posici�n actual hasta el final de la l�nea

    // Dibuja el rombo en la nueva posici�n confirmada
    dibujarRombo(diagonalMayor, cursorX, cursorY);

    // Volver a mostrar la barra de men�
    mostrarBarraDeMenu();
}

// Funci�n para dibujar un hex�gono
void dibujarHexagono(int lado, int x, int y) {
    // Calcula la altura del hex�gono
    double alturaHexagono = lado * 1.732;

    // Calcula la distancia entre l�neas
    int distanciaEntreLineas = lado;

    // Dibuja el hex�gono
    for (int i = 0; i < lado; i++) {
        moveTo(x - i, y + i);
        for (int j = 0; j <= lado * 2 + i; j++) {
            printf("*");
        }
        printf("\n");
    }

    for (int i = lado - 1; i >= 0; i--) {
        moveTo(x - i, y + lado * 2 - i);
        for (int j = 0; j <= lado * 2 + i; j++) {
            printf("*");
        }
        printf("\n");
    }
}
// Funci�n para manejar la opci�n de dibujar un hex�gono
void manejarOpcionHexagono(int consoleWidth, int consoleHeight) {
    // Ocultar la barra de men�
    for (int i = 0; i < 16; i++) {
        moveTo(i * 4, 0);
        printf("    ");
    }
    moveTo(12 * 4, 0);
    printf("     ");

    // Solicitar la longitud del lado del hex�gono
    moveTo(0, consoleHeight - 3);
    printf("Ingrese la longitud del lado del hex�gono: ");
    int lado;
    scanf("%d", &lado);

    // Solicitar al usuario mover el cursor a una nueva posici�n
    moveTo(0, consoleHeight - 2);
    printf("\nMueva el cursor a la nueva posici�n deseada con las teclas de flecha.");
    printf("\nPresione Enter para confirmar la posici�n del cursor...\n");

    int cursorX = consoleWidth / 2;
    int cursorY = consoleHeight / 2;
    moveTo(cursorX, cursorY);

    // Permitir al usuario mover el cursor y confirmar la posici�n
    while (1) {
        if (_kbhit()) {
            int key = _getch();

            // Manejar las teclas de flecha para mover el cursor
            if (key == 0 || key == 224) {
                key = _getch();

                switch (key) {
                    case 72: // Flecha arriba
                        cursorY--;
                        break;
                    case 80: // Flecha abajo
                        cursorY++;
                        break;
                    case 75: // Flecha izquierda
                        cursorX--;
                        break;
                    case 77: // Flecha derecha
                        cursorX++;
                        break;
                }
                // Mueve el cursor a la nueva posici�n
                moveTo(cursorX, cursorY);
            } else if (key == '\r') {
                // Confirma la posici�n del cursor
                break;
            }
        }
    }

    // Limpia los mensajes de solicitud de posici�n
    moveTo(0, consoleHeight - 3);
    printf("\033[K"); // Borra desde la posici�n actual hasta el final de la l�nea

    moveTo(0, consoleHeight - 2);
    printf("\033[K"); // Borra desde la posici�n actual hasta el final de la l�nea

    // Dibuja el hex�gono en la nueva posici�n confirmada
    dibujarHexagono(lado, cursorX, cursorY);

    // Volver a mostrar la barra de men�
    mostrarBarraDeMenu();
}

// Funci�n para mostrar el mensaje de bienvenida
void mostrarBienvenida(int consoleWidth, int consoleHeight) {
    // Calcula la posici�n para centrar el mensaje
    int x = consoleWidth / 2 - 10;
    int y = consoleHeight / 2 - 1;

    // Mueve el cursor a la posici�n calculada
    moveTo(x, y);

    // Cambia el color a blanco sobre fondo negro
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);

    // Imprime el mensaje de bienvenida
    printf("�BIENVENIDO A MI PROGRAMA!\n");
    printf("PRESIONE ENTER PARA CONTINUAR...\n");

    // Espera a que el usuario presione Enter
    while (1) {
        int key = _getch();
        if (key == '\r') {
            // Limpia la consola despu�s de presionar Enter
            clearConsole();
            break;
        }
    }

    // Calcula la posici�n para centrar el mensaje de F10
    int messageX = consoleWidth / 2 - 16; // Ajusta la longitud del mensaje para centrarlo
    int messageY = consoleHeight / 2;

    // Mueve el cursor a la posici�n calculada para el mensaje de F10
    moveTo(messageX, messageY);

    // Imprime el mensaje "Presione F10 para mostrar los comandos"
    printf("Presione F10 para mostrar los comandos\n");

}

// Funci�n principal
int main() {
    int consoleWidth, consoleHeight;

    // Obtiene el tama�o de la consola
    getConsoleSize(&consoleWidth, &consoleHeight);

    // Muestra el mensaje de bienvenida
    mostrarBienvenida(consoleWidth, consoleHeight);

    // Bucle para manejar la entrada de teclado
    while (1) {
        // Verifica si hay una tecla presionada
        if (_kbhit()) {
            // Obtiene la tecla presionada
            int key = _getch();

            // Maneja F10 para mostrar la barra de men�
            if (key == 68) { // C�digo de F10
                // Borra cualquier mensaje anterior y muestra la barra de men�
                clearConsole();
                mostrarBarraDeMenu();
            }

            // Maneja otras teclas...
            if (key == 59) { // C�digo de F1
                manejarOpcionTriangulo(consoleWidth, consoleHeight);
            }
            // Maneja F2 para dibujar un cuadrado
            if (key == 60) { // C�digo de F2
                manejarOpcionCuadrado(consoleWidth, consoleHeight);
            }
            // Maneja F3 para dibujar un rect�ngulo
            if (key == 61) { // C�digo de F3
                manejarOpcionRectangulo(consoleWidth, consoleHeight);
            }
            // Maneja F4 para dibujar un c�rculo
            if (key == 62) { // C�digo de F4
                manejarOpcionCirculo(consoleWidth, consoleHeight);
            }
            // Maneja F5 para dibujar una l�nea
            if (key == 63) { // C�digo de F5
                manejarOpcionLinea(consoleWidth, consoleHeight);
            }
            // Maneja F6 para dibujar un rombo
            if (key == 64) { // C�digo de F6
                manejarOpcionRombo(consoleWidth, consoleHeight);
            }
            // Maneja F7 para dibujar un hex�gono
            if (key == 65) { // C�digo de F7
                manejarOpcionHexagono(consoleWidth, consoleHeight);
            }
        }
    }

    return 0;
}
