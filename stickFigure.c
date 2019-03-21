#include "glextra.h"
#include "stickFigure.h"
#include "math.h"

#define THERMAL_SCREEN_SIZE 29
#define CANVAS_BACKGROUND_COLOR GL_WHITE
#define CANVAS_DRAW_COLOR GL_BLACK

// struct Player{
//   struct Circle head;
//   struct Line torso;
//   struct Line leftArm;
//   struct Line rightArm;
//   struct Line leftLeg;
//   struct Line rightLeg;
// };

//struct Player player;

void stickFigure_init(struct Circle* personHead, int screenSize) {
	//center the stickFigure by interpolation
	int base_length = 5; //radius, length that body is based on

	//initialize player head
	int figureHeadX = (screenSize * personHead->center.x / THERMAL_SCREEN_SIZE);
	int figureHeadY = (2*screenSize/3 + (personHead->center.y - personHead->radius) + base_length);
	struct Point figureHeadCenter = {figureHeadX, figureHeadY};
	struct Circle figureHead = {figureHeadCenter, base_length};
	player.head = figureHead;

	//initialize player torso and legs
	//person's height changes based on length of torso
	int leg_length = (2*base_length);
	int leg_width = (base_length+1);
	int torso_length = (screenSize - figureHeadY) - (3*base_length);
	if (torso_length < 0) {
		leg_length = ((screenSize - figureHeadY - base_length)/2);
		torso_length = ((screenSize - figureHeadY - base_length) - leg_length);
	}

	struct Point headTorso = {figureHeadCenter.x, figureHeadCenter.y + base_length};
	struct Point torsoLeg = {headTorso.x, headTorso.y + torso_length};

	struct Point leftLegEnd = {torsoLeg.x - leg_width, torsoLeg.y + leg_length};
	struct Point rightLegEnd = {torsoLeg.x + leg_width, torsoLeg.y + leg_length};

	struct Line torsoLine = { headTorso, torsoLeg };
	player.torso = torsoLine;
	struct Line leftLegLine = { torsoLeg, leftLegEnd };
	player.leftLeg = leftLegLine;
	struct Line rightLegLine = { torsoLeg, rightLegEnd };
	player.rightLeg = rightLegLine;

    // int axis = figureHead.center.x;
    // int head_ctr = figureHead.center.y;
    // int head_rad = figureHead.radius;//3
    // int body_lng = (4*figureHead.radius);//12
    // int leg_wid = (figureHead.radius+1);//4
    // int leg_lng = (2*figureHead.radius);//6
    // drawCircle(axis, head_ctr, head_rad, GL_BLACK);
    // gl_draw_line(axis, (head_ctr+head_rad), axis, (head_ctr+head_rad+body_lng), GL_BLACK);//torso
    // gl_draw_line(axis, (head_ctr+head_rad+body_lng), axis-leg_wid, (head_ctr+head_rad+body_lng+leg_lng), GL_BLACK);//left leg
    // gl_draw_line(axis, (head_ctr+head_rad+body_lng), axis+leg_wid, (head_ctr+head_rad+body_lng+leg_lng), GL_BLACK);//right leg
    // gl_draw_line(axis, (head_ctr+head_rad)+(body_lng/4), axis-leg_wid, (head_ctr+head_rad)+(body_lng/2)+1, GL_BLACK);//left arm
    // gl_draw_line(axis, (head_ctr+head_rad)+(body_lng/4), axis+leg_wid, (head_ctr+head_rad)+(body_lng/2)+1, GL_BLACK);//right arm
	
	//initialize player arms
	int arm_pos = torso_length/4;
	int arm_length = (2*leg_length/3); //default
	int arm_width = leg_width; //default
	struct Point torsoArm = {headTorso.x, headTorso.y + arm_pos};
	struct Point leftArmEnd = {torsoArm.x - arm_width, torsoArm.y + arm_length};
	struct Point rightArmEnd = {torsoArm.x + arm_width, torsoArm.y + arm_length};

	struct Line leftArmLine = {torsoArm, leftArmEnd};
	player.leftArm = leftArmLine;
	struct Line rightArmLine = {torsoArm, rightArmEnd};
	player.rightArm = rightArmLine;

}

void drawStickFigure() {
	//draw head
	drawCircle(player.head, CANVAS_DRAW_COLOR);

	//draw torso
	drawLine(player.torso, CANVAS_DRAW_COLOR);

	//draw legs
	drawLine(player.leftLeg, CANVAS_DRAW_COLOR);
	drawLine(player.rightLeg, CANVAS_DRAW_COLOR);

	//draw arms
	drawLine(player.leftArm, CANVAS_DRAW_COLOR);
	drawLine(player.rightArm, CANVAS_DRAW_COLOR);
}

void updateStickFigure() {
	
}
