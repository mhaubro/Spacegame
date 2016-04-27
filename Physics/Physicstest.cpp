#include "Physicstest.h"

void Physicstest::run(){
	int pointsize = UNIT*16;
	float m1 = 500;
	float m2 = 5;
	Vector2f position1 = Vector2f(UNIT*50+pointsize,UNIT*(272-30)-pointsize);
	Vector2f velocity1 = Vector2f(48*UNIT,-36*UNIT);
	Vector2f position2 = Vector2f(UNIT*(480-50)-pointsize,UNIT*(272-30)-pointsize);
	Vector2f velocity2 = Vector2f(56*UNIT,-30*UNIT);

	//cam.Vertex2f()

	set_time(0);

	GD.ClearColorRGB(BLACK);
	char str[6];
	Input in = Input();
	Timer t;
	t.start();
	float lasttime = t.read();
	float currtime = 0;
	PhysicsObject ph1 = PhysicsObject(m1, pointsize, position1, velocity1);
	PhysicsObject ph2 = PhysicsObject(m2, pointsize, position2, velocity2);

	//DigitalOut D3 = DigitalOut(D3);
	//DigitalOut D7 = DigitalOut(D7);

	//D7.write(1);

	Button button = Button(A5);
	//Button button2 = Button(D6);
	Vector2f force = Vector2f(25*UNIT, -25*UNIT);

	while(1){
		runloop(in, t, &lasttime, &currtime, str, &ph1, &ph2, button, force);
	}
}

void Physicstest::runloop(Input in, Timer t, float *lasttime, float *currtime, char str[], PhysicsObject *ph1, PhysicsObject *ph2, Button button, Vector2f force){
	//GDINIT
	in.pull();
	GD.Clear();
	GD.SaveContext();

	//DOSTUFF
	GD.ColorRGB(WHITE);
	GD.Begin(POINTS);
	ph1->draw();
	ph2->draw();

	*currtime = t.read();
	float dt = *currtime - *lasttime;
	//if (dt > 1 or dt < -1){//Since it may overflow
	//	dt = 0;
	//}

	ph1->addForce(force);
	ph1->changeState(dt);
	ph1->checkBounds();
	ph2->addForce(force);
	ph2->changeState(dt);
	ph2->checkBounds();



	if ((ph1)->checkCollision(*ph2)){
		//GD.cmd_text(40,60,16,OPT_SIGNED, "COLLISSION");
		(ph1)->applyCollission(*ph2);
	}

	if (button.isPressed()){
		ph1->velocity.x += 50*UNIT*dt;
		ph1->velocity.y += 50*UNIT*dt;
		ph2->velocity += 5*UNIT*dt;
		//sprintf(str, "%f", dt);
		GD.cmd_text(40,50,16,OPT_SIGNED, "Lower button, Speed up");
	}
/*	if (button2.isPressed()){
		ph1->velocity -= 5*UNIT*dt;
		ph2->velocity -= 5*UNIT*dt;
		//sprintf(str, "%f", dt);
		GD.cmd_text(40,60,16,OPT_SIGNED, "Upper button, Speed down");
	}
*/
	*lasttime = *currtime;
//	drawText(str, t);
	sprintf(str, "%f", dt);
	GD.cmd_text(40,50,16,OPT_SIGNED, str);

	GD.swap();
}

void Physicstest::drawText(char str[], Timer t){
		sprintf(str, "%f", t.read());
		GD.cmd_text(40,40,16,OPT_SIGNED, str);
		//Acceleration without gravity
		//GDFINISH
		GD.RestoreContext();
}

/*void Physicstest::checkCollision(Vector2f& position, Vector2f& velocity, int pointsize){
	if (position.x < 0 + pointsize && velocity.x < 0){
		velocity.x = -velocity.x;
	} else if (position.x + pointsize > SCREEN_WIDTH*UNIT && (velocity.x > 0)){
		velocity.x = -velocity.x;
	}
	if (position.y < 0 + pointsize && (velocity.y < 0)){
		velocity.y = -velocity.y;
	} else if (position.y + pointsize > SCREEN_HEIGHT*UNIT && (velocity.y > 0)){
		velocity.y = -velocity.y;
	}
}*/

Physicstest::Physicstest(){

}

void Physicstest::initPoints(){
	GD.SaveContext();
	GD.PointSize(UNIT);
	GD.begin(POINTS);

}

