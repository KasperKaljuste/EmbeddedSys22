/*
 * ball_game.h
 *
 *  Created on: 8 Dec 2022
 *      Author: kasperk
 */

#ifndef INC_BALL_GAME_H_
#define INC_BALL_GAME_H_

#include "joystick.h"
#include "stdbool.h"
#include "stdio.h"

typedef struct {
    uint16_t x;
    uint16_t y;
    uint16_t radius;
    uint16_t speed;
} ball;

typedef struct {
    uint16_t x1;
    uint16_t x2;
    uint16_t x1_len;
    uint16_t x2_len;
    uint16_t gap;
    uint16_t y;
    uint16_t speed;
} line;

typedef struct {
	uint16_t score;
	uint16_t high_score;
	uint16_t level;
} score;

typedef struct {
	uint16_t x;
	uint16_t y;
	uint8_t type; // 0 - None, 1 - Score, 2 - Speed
} powerup;


ball ball_init();
ball move_ball(ball ball, Joystick_ud_lr joystick, int16_t move_speed);
line create_line(line line);
line move_line(line line);
bool check_collision(ball ball, line line);
powerup create_powerup(powerup powerup);
bool check_powerup_collision(ball ball, powerup powerup);
#endif /* INC_BALL_GAME_H_ */
