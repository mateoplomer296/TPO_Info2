/*
 * RemotoConfig.cpp
 *
 *  Created on: 30 oct 2026
 *      Author: elPapu777
 */

#include <stdint.h>
#include "Inicializar.h"
#include <ModoRemoto/MaquinaEstadosUart.h>

#define TamTrama 128


enum estados {RESET, ESPERANDO_TRAMA, ESPERANDO_DATO};

void ProcesarTrama(uint8_t*trama, uint8_t tamanio);

void ProcesarTrama(uint8_t*trama, uint8_t tamanio)
{

	if(tamanio < 6)
	        return;

	    uint8_t tipo = trama[0];
	    if((tipo != 'T' && tipo != 'P') || trama[1] != '|')
	        return;

	    uint8_t i = 2;
	    uint16_t id = 0;
	    while(trama[i] >= '0' && trama[i] <= '9')
	    {
	        id = id * 10 + (trama[i] - '0');
	        i++;
	    }
	    if(trama[i] != '|')
	        return;
	    i++;

	    uint16_t valor = 0;
	    while(trama[i] >= '0' && trama[i] <= '9')
	    {
	        valor = valor * 10 + (trama[i] - '0');
	        i++;
	    }
	    if(trama[i] != '|')
	        return;


	    if(tipo == 'T')
	    {
	        Synth.remoteTecla(id,valor);
	    }
	    else
	    {
	        Synth.remotePote(id,valor);
	    }
}

void MaquinaEstadosUart(void)
{
	static uint8_t estado = ESPERANDO_TRAMA;
	uint8_t dato = 0;
	static uint8_t u = 0;
	static uint8_t trama[TamTrama + 1]={0};
	while(uart0.popRx(&dato))
	{
		switch(estado)
		{
			case ESPERANDO_TRAMA:
				if(dato=='$')
				{
					estado=ESPERANDO_DATO;
					u=0;
				}
				break;
			case ESPERANDO_DATO:
				if(dato=='#')
				{
					estado=ESPERANDO_TRAMA;
					trama[u]='\0';
					ProcesarTrama(trama,u);// mando la trama completa con el \0
					break;
				}
				if(u>=TamTrama)
				{
					estado=ESPERANDO_TRAMA;
					break;
				}
				else
				{
					trama[u]=dato;
					u++;
				}
				break;
		}
	}

}


