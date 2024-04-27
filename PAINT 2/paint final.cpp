#include <stdio.h>
#include <conio.h>
#include <windows.h> // Para manipular la consola

// Declaración de funciones
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

// Función para mover el cursor a una posición específica en la consola
void moveTo(int x, int y) {
    COORD position;
    position.X = x;
    position.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
}

// Función para obtener el tamaño de la consola
void getConsoleSize(int *width, int *height) {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    *width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    *height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
}

// Función para limpiar la consola
void clearConsole() {
    system("cls");
}
// Función para mostrar la barra de menú horizontal con cuadrados de altura 3, anchura 4 y color verde
// Función para mostrar la barra de menú horizontal con cuadrados de altura 1 y anchura 4
void mostrarBarraDeMenu() {
    // Define la posición inicial de la barra de menú (en la parte superior de la consola)
    int y = 0;
    int x = 0;

    // Establece el color de fondo blanco y el color de primer plano verde
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY | FOREGROUND_GREEN);

    // Dibuja los cuadrados de altura 1 y anchura 4 con etiquetas F1 a F12 y CTRL + A
    for (int i = 0; i < 12; i++) {
        // Mueve el cursor a la posición correspondiente
        moveTo(x + i * 4, y);
        // Imprime el texto en el cuadrado
        printf(" F%d ", i + 1);
    }

    // Añadir el cuadrado para CTRL + A
    moveTo(x + 13 * 4, y);
    printf("CTRL");

    // Restablece los colores predeterminados
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
}

// Función para mostrar el botón de menú
void mostrarBotonMenu(int consoleWidth, int consoleHeight) {
    // Calcula la posición para centrar el botón de menú
    int x = consoleWidth / 2 - 2;
    int y = consoleHeight / 2;

    // Mueve el cursor a la posición calculada
    moveTo(x, y);

    // Cambia el color a blanco sobre fondo negro
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);

    // Imprime el texto "MENÚ"
    printf("MENÚ");
}

// Función para dibujar un triángulo
void dibujarTriangulo(int altura, int x, int y) {
    // Dibuja el triángulo con *
    for (int i = 0; i < altura; i++) {
        moveTo(x - i, y + i);
        for (int j = 0; j <= 2 * i; j++) {
            printf("*");
        }
        printf("\n");
    }
}
// Función para manejar la opción de dibujar un triángulo
void manejarOpcionTriangulo(int consoleWidth, int consoleHeight) {
    // Ocultar la barra de menú
    for (int i = 0; i < 16; i++) {
        moveTo(i * 4, 0);
        printf("    ");
    }
    moveTo(12 * 4, 0);
    printf("     ");

    // Solicitar la altura del triángulo
    moveTo(0, consoleHeight - 3); // Mueve el cursor a la línea para mostrar los mensajes
    printf("Ingrese la altura del triángulo: ");
    int altura;
    scanf("%d", &altura);

    // Solicitar al usuario mover el cursor a una nueva posición
    printf("\nMueva el cursor a la nueva posición deseada con las teclas de flecha.");
    printf("\nPresione Enter para confirmar la posición del cursor...\n");

    int cursorX = consoleWidth / 2;
    int cursorY = consoleHeight / 2;
    moveTo(cursorX, cursorY);

    // Permitir al usuario mover el cursor y confirmar la posición
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
                // Mueve el cursor a la nueva posición
                moveTo(cursorX, cursorY);
            } else if (key == '\r') {
                // Confirmar la posición del cursor
                break;
            }
        }
    }

    // Limpiar los mensajes de solicitud de posición
    moveTo(0, consoleHeight - 3);
    printf("\033[K"); // Borra desde la posición actual hasta el final de la línea

    moveTo(0, consoleHeight - 2);
    printf("\033[K"); // Borra desde la posición actual hasta el final de la línea

    // Dibuja el triángulo en la nueva posición confirmada
    dibujarTriangulo(altura, cursorX, cursorY);

    // Volver a mostrar la barra de menú
    mostrarBarraDeMenu();
}

// Función para dibujar un cuadrado
void dibujarCuadrado(int lado, int x, int y) {
    for (int i = 0; i < lado; i++) {
        moveTo(x, y + i);
        for (int j = 0; j < lado; j++) {
            printf("*");
        }
        printf("\n");
    }
}
// Función para manejar la opción de dibujar un cuadrado
void manejarOpcionCuadrado(int consoleWidth, int consoleHeight) {
    // Ocultar la barra de menú
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

    // Solicitar al usuario mover el cursor a una nueva posición
    moveTo(0, consoleHeight - 2);
    printf("\nMueva el cursor a la nueva posición deseada con las teclas de flecha.");
    printf("\nPresione Enter para confirmar la posición del cursor...\n");

    int cursorX = consoleWidth / 2;
    int cursorY = consoleHeight / 2;
    moveTo(cursorX, cursorY);

    // Permitir al usuario mover el cursor y confirmar la posición
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
                // Mueve el cursor a la nueva posición
                moveTo(cursorX, cursorY);
            } else if (key == '\r') {
                // Confirmar la posición del cursor
                break;
            }
        }
    }

    // Limpia los mensajes de solicitud de posición
    moveTo(0, consoleHeight - 3);
    printf("\033[K"); // Borra desde la posición actual hasta el final de la línea

    moveTo(0, consoleHeight - 2);
    printf("\033[K"); // Borra desde la posición actual hasta el final de la línea

    // Dibuja el cuadrado en la nueva posición confirmada
    dibujarCuadrado(lado, cursorX, cursorY);

    // Volver a mostrar la barra de menú
    mostrarBarraDeMenu();
}

// Función para dibujar un rectángulo
void dibujarRect(int altura, int anchura, int x, int y) {
    for (int i = 0; i < altura; i++) {
        moveTo(x, y + i);
        for (int j = 0; j < anchura; j++) {
            printf("*");
        }
        printf("\n");
    }
}
// Función para manejar la opción de dibujar un rectángulo
void manejarOpcionRectangulo(int consoleWidth, int consoleHeight) {
    // Ocultar la barra de menú
    for (int i = 0; i < 16; i++) {
        moveTo(i * 4, 0);
        printf("    ");
    }
    moveTo(12 * 4, 0);
    printf("     ");

    // Solicitar la altura y anchura del rectángulo
    moveTo(0, consoleHeight - 3);
    printf("Ingrese la altura del rectángulo: ");
    int altura;
    scanf("%d", &altura);

    printf("Ingrese la anchura del rectángulo: ");
    int anchura;
    scanf("%d", &anchura);

    // Solicitar al usuario mover el cursor a una nueva posición
    moveTo(0, consoleHeight - 2);
    printf("\nMueva el cursor a la nueva posición deseada con las teclas de flecha.");
    printf("\nPresione Enter para confirmar la posición del cursor...\n");

    int cursorX = consoleWidth / 2;
    int cursorY = consoleHeight / 2;
    moveTo(cursorX, cursorY);

    // Permitir al usuario mover el cursor y confirmar la posición
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
                // Mueve el cursor a la nueva posición
                moveTo(cursorX, cursorY);
            } else if (key == '\r') {
                // Confirma la posición del cursor
                break;
            }
        }
    }

    // Limpia los mensajes de solicitud de posición
    moveTo(0, consoleHeight - 3);
    printf("\033[K"); // Borra desde la posición actual hasta el final de la línea

    moveTo(0, consoleHeight - 2);
    printf("\033[K"); // Borra desde la posición actual hasta el final de la línea

    // Dibuja el rectángulo en la nueva posición confirmada
    dibujarRect(altura, anchura, cursorX, cursorY);

    // Volver a mostrar la barra de menú
    mostrarBarraDeMenu();
}

// Función para dibujar un círculo
void dibujarCirculo(int radio, int x, int y) {
    // Algoritmo para dibujar un círculo usando el método de Bresenham

    int x0 = x;
    int y0 = y;
    int a = radio;
    int b = 0;
    int d = 3 - 2 * a;

    while (b <= a) {
        // Dibuja los puntos del círculo en octante
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
// Función para manejar la opción de dibujar un círculo
void manejarOpcionCirculo(int consoleWidth, int consoleHeight) {
    // Ocultar la barra de menú
    for (int i = 0; i < 16; i++) {
        moveTo(i * 4, 0);
        printf("    ");
    }
    moveTo(12 * 4, 0);
    printf("     ");

    // Solicitar el radio del círculo
    moveTo(0, consoleHeight - 3);
    printf("Ingrese el radio del círculo: ");
    int radio;
    scanf("%d", &radio);

    // Solicitar al usuario mover el cursor a una nueva posición
    moveTo(0, consoleHeight - 2);
    printf("\nMueva el cursor a la nueva posición deseada con las teclas de flecha.");
    printf("\nPresione Enter para confirmar la posición del cursor...\n");

    int cursorX = consoleWidth / 2;
    int cursorY = consoleHeight / 2;
    moveTo(cursorX, cursorY);

    // Permitir al usuario mover el cursor y confirmar la posición
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
                // Mueve el cursor a la nueva posición
                moveTo(cursorX, cursorY);
            } else if (key == '\r') {
                // Confirma la posición del cursor
                break;
            }
        }
    }

    // Limpia los mensajes de solicitud de posición
    moveTo(0, consoleHeight - 3);
    printf("\033[K"); // Borra desde la posición actual hasta el final de la línea

    moveTo(0, consoleHeight - 2);
    printf("\033[K"); // Borra desde la posición actual hasta el final de la línea

    // Dibuja el círculo en la nueva posición confirmada
    dibujarCirculo(radio, cursorX, cursorY);

    // Volver a mostrar la barra de menú
    mostrarBarraDeMenu();
}

// Función para dibujar una línea horizontal
void dibujarLinea(int longitud, int x, int y) {
    moveTo(x, y);
    for (int i = 0; i < longitud; i++) {
        printf("*");
    }
}

// Función para manejar la opción de dibujar una línea
void manejarOpcionLinea(int consoleWidth, int consoleHeight) {
    // Ocultar la barra de menú
    for (int i = 0; i < 16; i++) {
        moveTo(i * 4, 0);
        printf("    ");
    }
    moveTo(12 * 4, 0);
    printf("     ");

    // Solicitar la longitud de la línea
    moveTo(0, consoleHeight - 3);
    printf("Ingrese la longitud de la línea: ");
    int longitud;
    scanf("%d", &longitud);

    // Solicitar al usuario mover el cursor a una nueva posición
    moveTo(0, consoleHeight - 2);
    printf("\nMueva el cursor a la nueva posición deseada con las teclas de flecha.");
    printf("\nPresione Enter para confirmar la posición del cursor...\n");

    int cursorX = consoleWidth / 2;
    int cursorY = consoleHeight / 2;
    moveTo(cursorX, cursorY);

    // Permitir al usuario mover el cursor y confirmar la posición
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
                // Mueve el cursor a la nueva posición
                moveTo(cursorX, cursorY);
            } else if (key == '\r') {
                // Confirma la posición del cursor
                break;
            }
        }
    }

    // Limpia los mensajes de solicitud de posición
    moveTo(0, consoleHeight - 3);
    printf("\033[K"); // Borra desde la posición actual hasta el final de la línea

    moveTo(0, consoleHeight - 2);
    printf("\033[K"); // Borra desde la posición actual hasta el final de la línea

    // Dibuja la línea en la nueva posición confirmada
    dibujarLinea(longitud, cursorX, cursorY);

    // Volver a mostrar la barra de menú
    mostrarBarraDeMenu();
}


// Función para dibujar un rombo
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
// Función para manejar la opción de dibujar un rombo
void manejarOpcionRombo(int consoleWidth, int consoleHeight) {
    // Ocultar la barra de menú
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

    // Solicitar al usuario mover el cursor a una nueva posición
    moveTo(0, consoleHeight - 2);
    printf("\nMueva el cursor a la nueva posición deseada con las teclas de flecha.");
    printf("\nPresione Enter para confirmar la posición del cursor...\n");

    int cursorX = consoleWidth / 2;
    int cursorY = consoleHeight / 2;
    moveTo(cursorX, cursorY);

    // Permitir al usuario mover el cursor y confirmar la posición
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
                // Mueve el cursor a la nueva posición
                moveTo(cursorX, cursorY);
            } else if (key == '\r') {
                // Confirma la posición del cursor
                break;
            }
        }
    }

    // Limpia los mensajes de solicitud de posición
    moveTo(0, consoleHeight - 3);
    printf("\033[K"); // Borra desde la posición actual hasta el final de la línea

    moveTo(0, consoleHeight - 2);
    printf("\033[K"); // Borra desde la posición actual hasta el final de la línea

    // Dibuja el rombo en la nueva posición confirmada
    dibujarRombo(diagonalMayor, cursorX, cursorY);

    // Volver a mostrar la barra de menú
    mostrarBarraDeMenu();
}

// Función para dibujar un hexágono
void dibujarHexagono(int lado, int x, int y) {
    // Calcula la altura del hexágono
    double alturaHexagono = lado * 1.732;

    // Calcula la distancia entre líneas
    int distanciaEntreLineas = lado;

    // Dibuja el hexágono
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
// Función para manejar la opción de dibujar un hexágono
void manejarOpcionHexagono(int consoleWidth, int consoleHeight) {
    // Ocultar la barra de menú
    for (int i = 0; i < 16; i++) {
        moveTo(i * 4, 0);
        printf("    ");
    }
    moveTo(12 * 4, 0);
    printf("     ");

    // Solicitar la longitud del lado del hexágono
    moveTo(0, consoleHeight - 3);
    printf("Ingrese la longitud del lado del hexágono: ");
    int lado;
    scanf("%d", &lado);

    // Solicitar al usuario mover el cursor a una nueva posición
    moveTo(0, consoleHeight - 2);
    printf("\nMueva el cursor a la nueva posición deseada con las teclas de flecha.");
    printf("\nPresione Enter para confirmar la posición del cursor...\n");

    int cursorX = consoleWidth / 2;
    int cursorY = consoleHeight / 2;
    moveTo(cursorX, cursorY);

    // Permitir al usuario mover el cursor y confirmar la posición
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
                // Mueve el cursor a la nueva posición
                moveTo(cursorX, cursorY);
            } else if (key == '\r') {
                // Confirma la posición del cursor
                break;
            }
        }
    }

    // Limpia los mensajes de solicitud de posición
    moveTo(0, consoleHeight - 3);
    printf("\033[K"); // Borra desde la posición actual hasta el final de la línea

    moveTo(0, consoleHeight - 2);
    printf("\033[K"); // Borra desde la posición actual hasta el final de la línea

    // Dibuja el hexágono en la nueva posición confirmada
    dibujarHexagono(lado, cursorX, cursorY);

    // Volver a mostrar la barra de menú
    mostrarBarraDeMenu();
}

// Función para mostrar el mensaje de bienvenida
void mostrarBienvenida(int consoleWidth, int consoleHeight) {
    // Calcula la posición para centrar el mensaje
    int x = consoleWidth / 2 - 10;
    int y = consoleHeight / 2 - 1;

    // Mueve el cursor a la posición calculada
    moveTo(x, y);

    // Cambia el color a blanco sobre fondo negro
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);

    // Imprime el mensaje de bienvenida
    printf("¡BIENVENIDO A MI PROGRAMA!\n");
    printf("PRESIONE ENTER PARA CONTINUAR...\n");

    // Espera a que el usuario presione Enter
    while (1) {
        int key = _getch();
        if (key == '\r') {
            // Limpia la consola después de presionar Enter
            clearConsole();
            break;
        }
    }

    // Calcula la posición para centrar el mensaje de F10
    int messageX = consoleWidth / 2 - 16; // Ajusta la longitud del mensaje para centrarlo
    int messageY = consoleHeight / 2;

    // Mueve el cursor a la posición calculada para el mensaje de F10
    moveTo(messageX, messageY);

    // Imprime el mensaje "Presione F10 para mostrar los comandos"
    printf("Presione F10 para mostrar los comandos\n");

}

// Función principal
int main() {
    int consoleWidth, consoleHeight;

    // Obtiene el tamaño de la consola
    getConsoleSize(&consoleWidth, &consoleHeight);

    // Muestra el mensaje de bienvenida
    mostrarBienvenida(consoleWidth, consoleHeight);

    // Bucle para manejar la entrada de teclado
    while (1) {
        // Verifica si hay una tecla presionada
        if (_kbhit()) {
            // Obtiene la tecla presionada
            int key = _getch();

            // Maneja F10 para mostrar la barra de menú
            if (key == 68) { // Código de F10
                // Borra cualquier mensaje anterior y muestra la barra de menú
                clearConsole();
                mostrarBarraDeMenu();
            }

            // Maneja otras teclas...
            if (key == 59) { // Código de F1
                manejarOpcionTriangulo(consoleWidth, consoleHeight);
            }
            // Maneja F2 para dibujar un cuadrado
            if (key == 60) { // Código de F2
                manejarOpcionCuadrado(consoleWidth, consoleHeight);
            }
            // Maneja F3 para dibujar un rectángulo
            if (key == 61) { // Código de F3
                manejarOpcionRectangulo(consoleWidth, consoleHeight);
            }
            // Maneja F4 para dibujar un círculo
            if (key == 62) { // Código de F4
                manejarOpcionCirculo(consoleWidth, consoleHeight);
            }
            // Maneja F5 para dibujar una línea
            if (key == 63) { // Código de F5
                manejarOpcionLinea(consoleWidth, consoleHeight);
            }
            // Maneja F6 para dibujar un rombo
            if (key == 64) { // Código de F6
                manejarOpcionRombo(consoleWidth, consoleHeight);
            }
            // Maneja F7 para dibujar un hexágono
            if (key == 65) { // Código de F7
                manejarOpcionHexagono(consoleWidth, consoleHeight);
            }
        }
    }

    return 0;
}
