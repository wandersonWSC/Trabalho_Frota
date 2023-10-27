#include <stdio.h>
#include <conio.h>

int multiplica(int N1, int N2)
{
  int resultado;
  resultado = N1 * N2;
  return (resultado);
}

int multiplicax(int Y1, int Y2)
{
  int resultado = 0;
  resultado = Y1 * Y2;
  return (resultado);
}

void msg_em_desenvolvimento()
{
  int sleep_seconds = 1;

  printf("\n============================");
  printf("\nOp��o em desenvolvimento...\n");
  printf("============================");
  sleep(sleep_seconds);
}
