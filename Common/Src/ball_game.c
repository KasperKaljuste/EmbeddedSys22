#include "ball_game.h"
#include "stdio.h"

ball ball_init(){
	ball ball;
	ball.x = BSP_LCD_GetXSize()/2;
	ball.y = 10;
	ball.radius = 10;
	ball.speed = 2;
	return ball;
}

ball move_ball(ball ball, Joystick_ud_lr joystick, int16_t move_speed){
	// Palli liigutamine
	if (ball.y >= 310){ball.y = 310;}
	else if (joystick.ud < 1900) {ball.y+=move_speed;}

	if (ball.y <= 20) {ball.y = 20;}
	else if (joystick.ud > 2400) {ball.y-=move_speed;}

	if (ball.x >= 229) {ball.x = 229;}
	else if (joystick.lr < 1900) {ball.x += move_speed;}

	if (ball.x <= ball.radius) {ball.x = ball.radius;}
	else if (joystick.lr > 2400) {ball.x -= move_speed;}

	return ball;
}

line create_line(line line){
	line.y = 320;
	line.speed = 1;
	line.x1 = 0;
	line.gap = srand(HAL_GetTick()) % 40 + 40;
	line.x1_len = srand(HAL_GetTick()) % 160;
	line.x2 = line.x1_len + line.gap;
	line.x2_len = 240 - line.x1_len - line.gap;
	return line;
}

line move_line(line line){
	if (!((line.y <= 320) && (line.y >= 0))) {
		line = create_line(line);
	}
	else {
		line.y = line.y - line.speed;
	}
	return line;
}

bool check_collision(ball ball, line line){
	if ((line.y < ball.y + ball.radius) && (line.y > ball.y - ball.radius)) {
		if((line.x1_len > ball.x - ball.radius) || (line.x2 < ball.x + ball.radius)){
			return true;
		}
	}
		return false;
}

powerup create_powerup(powerup powerup){
	powerup.type = srand(HAL_GetTick()) % 3;
	powerup.x = srand(HAL_GetTick()) % 200 + 20;
	powerup.y = srand(HAL_GetTick()) % 280 + 20;
	return powerup;
}

bool check_powerup_collision(ball ball, powerup powerup){
	if ((powerup.y < ball.y + ball.radius) && (powerup.y > ball.y - ball.radius)) {
		if ((powerup.x < ball.x + ball.radius) && (powerup.x > ball.x - ball.radius)) {
			return true;
		}
	}
	return false;
}
