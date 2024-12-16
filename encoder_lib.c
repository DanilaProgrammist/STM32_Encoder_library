/*
 * encoder_lib.c
 *
 *  Created on: 16 дек. 2024 г.
 *      Author: Kuliev
 */
#include "encoder_lib.h"
#include "stdio.h"
#include "main.h"
Encoder encoder;
Encoder_Turn enc_turn;
void EncInit(GPIO_TypeDef* _ENC1_Port, uint16_t _ENC1_Pin, GPIO_TypeDef* _ENC2_Port, uint16_t _ENC2_Pin, GPIO_TypeDef* _Button_Port, uint16_t _Button_Pin){
	encoder.ENC1_Port = _ENC1_Port;
	encoder.ENC2_Port = _ENC2_Port;
	encoder.BUTT_Port = _Button_Port;
	encoder.ENC1_Pin = _ENC1_Pin;
	encoder.ENC2_Pin = _ENC2_Pin;
	encoder.BUTT_Pin = _Button_Pin;
	encoder.btnFlag = 0;
	encoder.debounceTimer = 0;

	enc_turn = NONE;
}
Encoder_Turn isEncTurn(){
	if (HAL_GPIO_ReadPin(encoder.ENC1_Port, encoder.ENC1_Pin) == GPIO_PIN_RESET){
		if (HAL_GPIO_ReadPin(encoder.ENC2_Port, encoder.ENC2_Pin) == GPIO_PIN_RESET){
			while(HAL_GPIO_ReadPin(encoder.ENC2_Port, encoder.ENC2_Pin) == GPIO_PIN_RESET){};
			enc_turn = LEFT;
			while(HAL_GPIO_ReadPin(encoder.ENC1_Port, encoder.ENC1_Pin) == GPIO_PIN_RESET){};
			HAL_Delay(10);
		}
		else if (HAL_GPIO_ReadPin(encoder.ENC2_Port, encoder.ENC2_Pin) == GPIO_PIN_SET){
			while(HAL_GPIO_ReadPin(encoder.ENC2_Port, encoder.ENC2_Pin) == GPIO_PIN_SET){};
			enc_turn = RIGHT;
			while(HAL_GPIO_ReadPin(encoder.ENC1_Port, encoder.ENC1_Pin) == GPIO_PIN_RESET){};
			while(HAL_GPIO_ReadPin(encoder.ENC2_Port, encoder.ENC2_Pin) == GPIO_PIN_RESET){};
			HAL_Delay(10);

		}
	}
	return enc_turn;
}
uint8_t isButtPush(){
	encoder.btnState = !HAL_GPIO_ReadPin(encoder.BUTT_Port, encoder.BUTT_Pin);
	if (encoder.btnState && !encoder.btnFlag){
		encoder.btnFlag = 1;
	}
	if (!encoder.btnState && encoder.btnFlag){
		encoder.btnFlag = 0;
		HAL_Delay(50);
		return 1;
	}
	return 0;
}
uint8_t isButtHold(){
	return HAL_GPIO_ReadPin(encoder.BUTT_Port, encoder.BUTT_Pin);
}
uint8_t isTurnRightPush(){
	if (isEncTurn() == RIGHT && !isButtHold()){
		enc_turn = NONE;
		return 1;
	}
	return 0;
}
uint8_t isTurnLeftPush(){
	if (isEncTurn() == LEFT && !isButtHold()){
		enc_turn = NONE;
		return 1;
	}
	return 0;
}
uint8_t isRight(){
	if (isEncTurn() == RIGHT){
		enc_turn = NONE;
		return 1;
	}
	return 0;
}
uint8_t isLeft(){
	if (isEncTurn() == LEFT){
		enc_turn = NONE;
		return 1;
	}
	return 0;
}
