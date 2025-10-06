#include "datetime.h"
#include <time.h>

Data getDataAtual() {
    time_t agora;
    struct tm *data_local;
    Data d;

    time(&agora);
    data_local = localtime(&agora);

    d.dia = data_local->tm_mday;
    d.mes = data_local->tm_mon + 1;
    d.ano = data_local->tm_year + 1900;

    return d;
}
