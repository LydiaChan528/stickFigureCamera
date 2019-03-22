#include "glextra.h"
#include "stickFigure.h"
#include "math.h"
#include "printf.h"
#include <stdbool.h>

#define THERMAL_SCREEN_SIZE 29
#define CANVAS_SCREEN_SIZE 150
#define CANVAS_BACKGROUND_COLOR GL_WHITE
#define CANVAS_DRAW_COLOR GL_BLACK

#define min(x, y) ((x) < (y) ? (x) : (y))
#define max(x, y) ((x) > (y) ? (x) : (y))

// struct Player{
//   struct Circle head;
//   struct Line torso;
//   struct Line leftArm;
//   struct Line rightArm;
//   struct Line leftLeg;
//   struct Line rightLeg;
// };

//struct Player player;


static void stickFigure_buildArms(int maxLen, int minLen, struct Line* armLength, int* leftWid, int* rightWid) {
	struct Point leftArmPoint = armLength->one;
	struct Point rightArmPoint = armLength->two;

	int leftArmLength = (player.head.center.x - leftArmPoint.x);
	int rightArmLength = (player.head.center.y - rightArmPoint.x);

	*leftWid = min(max(minLen, leftArmLength), maxLen);
	*rightWid = min(max(minLen, rightArmLength), maxLen);
}

static int inScreenBounds(int num) {
	return (num <= CANVAS_SCREEN_SIZE) && (num >= 0);
}

static void stickFigure_buildBody(int base_length, struct Line* armLength) {
	//initialize player torso and legs
	//person's height changes based on length of torso
	int leg_length = (2*base_length);
	int leg_width = (base_length+1);
	int torso_length = (gl_get_width() - player.head.center.y) - (3*base_length);
	if (torso_length < 0) {
		leg_length = ((gl_get_width() - player.head.center.y - base_length)/2);
		torso_length = ((gl_get_width() - player.head.center.y - base_length) - leg_length);
	}

	struct Point headTorso = {player.head.center.x, player.head.center.y + base_length};
	struct Point torsoLeg = {headTorso.x, headTorso.y + torso_length};

	struct Point leftLegEnd = {torsoLeg.x - leg_width, torsoLeg.y + leg_length};
	struct Point rightLegEnd = {torsoLeg.x + leg_width, torsoLeg.y + leg_length};

	struct Line torsoLine = { headTorso, torsoLeg };
	player.torso = torsoLine;
	struct Line leftLegLine = { torsoLeg, leftLegEnd };
	player.leftLeg = leftLegLine;
	struct Line rightLegLine = { torsoLeg, rightLegEnd };
	player.rightLeg = rightLegLine;

	//initialize player arms
	int arm_pos = torso_length/4;

	//set player arms
	int arm_length = (2*leg_length/3); //default
	int arm_width = leg_width; //default
	int sum = (arm_length + arm_width);

	int rightArmWid = arm_width;
	int leftArmWid = arm_width;

	// if (inScreenBounds(armLength->one.x) && inScreenBounds(armLength->one.y) && inScreenBounds(armLength->two.x) && inScreenBounds(armLength->two.y)) {
	// 	stickFigure_buildArms(sum, arm_width, armLength, &leftArmWid, &rightArmWid);
	// }

	int rightArmLen = (sum - rightArmWid);
	int leftArmLen = (sum - leftArmWid);

	printf("ARM wid = %d, %d\n", rightArmWid, leftArmWid);
	printf("ARM len = %d, %d\n", rightArmLen, leftArmLen);

	struct Point torsoArm = {headTorso.x, headTorso.y + arm_pos};
	struct Point leftArmEnd = {torsoArm.x - rightArmWid, torsoArm.y + rightArmLen};
	struct Point rightArmEnd = {torsoArm.x + leftArmWid, torsoArm.y + leftArmLen};

	struct Line leftArmLine = {torsoArm, leftArmEnd};
	player.leftArm = leftArmLine;
	struct Line rightArmLine = {torsoArm, rightArmEnd};
	player.rightArm = rightArmLine;
}

void stickFigure_init(struct Circle* personHead, struct Line* armLength) {
	//center the stickFigure by interpolation
	int base_length = 5; //radius, length that body is based on

	//initialize player head
	int figureHeadX = (gl_get_width() * personHead->center.x / THERMAL_SCREEN_SIZE);
	int figureHeadY = (2*gl_get_width()/3 + (personHead->center.y - personHead->radius) + base_length);
	struct Point figureHeadCenter = {figureHeadX, figureHeadY};
	struct Circle figureHead = {figureHeadCenter, base_length};
	player.head = figureHead;

	stickFigure_buildBody(base_length, armLength);
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

