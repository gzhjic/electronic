
#ifndef ADC_H_
#define ADC_H_

#include <avr/io.h>

void ADC_Init(void);
unsigned int ADC_Read(void);

#endif /* ADC_H_ */