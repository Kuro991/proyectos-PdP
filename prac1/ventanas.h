
#include <stdio.h>
#include <windows.h>

void gotoxy(int col, int ren)
{
    COORD C;
    C.X = col;
    C.Y = ren;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), C);
}
void cls()
{
   system("CLS");
}

void PonCaracter(int c1, int r1, int c)
{
   gotoxy(c1,r1);
   printf("%c", c);
}

void PonMensaje(int c, int r, char *Mensaje)
{
    gotoxy(c, r); printf("%s", Mensaje);
}

void PonMensajeCentrado(int r,int col, char *Mensaje)
{
    int c = col-(strlen(Mensaje)/2);
    PonMensaje(c, r, Mensaje);
}
void recuadro(int c1, int r1, int c2, int r2)
{    
    PonMensaje(c1, r1, "╔");
    PonMensaje(c2, r1, "╗");
    PonMensaje(c1, r2, "╚");
    PonMensaje(c2, r2, "╝");

  for (int x=c1+1; x<c2; x++)
    {
      PonMensaje(x, r1, "═");
      PonMensaje(x, r2, "═");
    }
  for (int x=r1+1; x<r2; x++)
    {
        PonMensaje(c1, x, "║");
        PonMensaje(c2, x, "║");
    }
}