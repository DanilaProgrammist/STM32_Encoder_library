/*
 * encoder_lib.h
 *
 *  Created on: 16 дек. 2024 г.
 *      Author: Kuliev
 */

#ifndef INC_ENCODER_LIB_H_
#define INC_ENCODER_LIB_H_
#include "encoder_lib.h"
#include "main.h"
typedef enum {
	NONE,
	RIGHT,
	LEFT
}Encoder_Turn;
typedef struct{
	GPIO_TypeDef* ENC1_Port;
	GPIO_TypeDef* ENC2_Port;
	GPIO_TypeDef* BUTT_Port;
	uint16_t ENC1_Pin;
	uint16_t ENC2_Pin;
	uint16_t BUTT_Pin;

	uint8_t btnState;
	uint8_t btnFlag;
	long debounceTimer;

}Encoder;
void EncInit(GPIO_TypeDef* _ENC1_Port, uint16_t _ENC1_Pin, GPIO_TypeDef* _ENC2_Port, uint16_t _ENC2_Pin, GPIO_TypeDef* _Button_Port, uint16_t _Button_Pin);
uint8_t isButtPush();
uint8_t isButtHold();
uint8_t isTurnRightPush();
uint8_t isTurnLeftPush();
uint8_t isRight();
uint8_t isLeft();
#endif /* INC_ENCODER_LIB_H_ */
