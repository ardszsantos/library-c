#include "time_utils.h"

void getCurrentDate(int *dia, int *mes, int *ano) {
  time_t t = time(NULL);

  struct tm tm = *localtime(&t);

  *dia = tm.tm_mday;
  *mes = tm.tm_mon + 1;
  *ano = tm.tm_year + 1900; 
}