/*
 * Queue.h
 *
 *  Created on: 6 may. 2026
 *      Author: danie
 */

#ifndef SRC_MODULOS_X_QUEUE_QUEUE_H_
#define SRC_MODULOS_X_QUEUE_QUEUE_H_
#include "LPC845.h"
template <typename tipo>

class Queue {
private:
	uint32_t in_queue;
	uint32_t out_queue;
	uint32_t cont_queue;
	uint32_t max_queue;

	tipo *pQueue;

public:
	Queue(uint32_t MAX_QUEUE = 50){
		in_queue = 0;
		out_queue = 0;
		cont_queue = 0;
		max_queue = MAX_QUEUE;
		pQueue = new tipo[MAX_QUEUE];
	}
	virtual ~Queue(){
		delete []pQueue;
	}
	bool Push(tipo &dato){
		bool salida = false;
		if (!Llena()){
			pQueue [in_queue] = dato;
			in_queue ++;
			in_queue %= max_queue; //si lleg al maximo se resetea
			cont_queue++;
			salida = true;
		}
		return salida;
	}
	bool Pop(tipo &dato){
		bool salida = false;
		if(!Vacia()){
			dato = pQueue[out_queue];
			out_queue ++;
			out_queue %= max_queue; //si lleg al maximo se resetea
			cont_queue--;
			salida = true;
		}
		return salida;
	}

	Queue& operator=(Queue &q){
		if(q.max_queue > max_queue){
			delete []pQueue;
			pQueue = new tipo [q.max_queue];
			max_queue = q.max_queue;
		}
		for(uint32_t i=0;i< q.max_queue; i++){
			pQueue[i] = q.pQueue[i];
			in_queue = q.in_queue;
			out_queue = q.out_queue;
			cont_queue = q.cont_queue;

		}return *this;
	}

	Queue operator<<(tipo &dato){
		Push(dato);
		return *this;
	}
	Queue operator>>(tipo &dato){
			Pop(dato);
			return *this;
		}
private:
	bool Llena (void){
		return(max_queue > cont_queue)? false : true;
	}
	bool Vacia (void){
		return(cont_queue == 0)? true : false;
	}
};


#endif /* SRC_MODULOS_X_QUEUE_QUEUE_H_ */
