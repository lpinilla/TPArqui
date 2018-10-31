#ifndef INTERRUPS_H_
#define INTERRUPS_H_

#include <idt_loader.h>

void _irq00_handler(void);
/*void _irq01Handler(void);
void _irq02Handler(void);
void _irq03Handler(void);
void _irq04Handler(void);
void _irq05Handler(void);*/

//void _exception0Handler(void);

//void _cli(void);

void _sti(void);

void _hlt(void);

void pic_master_mask(uint8_t mask);

void pic_slave_mask(uint8_t mask);

//Termina la ejecución de la cpu.
void haltcpu(void);

#endif /* INTERRUPS_H_ */