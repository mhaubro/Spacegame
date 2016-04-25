#include "Physicstest.h"
#include "Graphics.h"
#include <time.h>
#include <string.h>
#include "Input.h"
#include "PhysicsConstants.h"

void Physicstest::run(){
	int pointsize = UNIT*16;
	Vector2f position = Vector2f(UNIT*0+pointsize,UNIT*272-pointsize);
	Vector2f velocity = Vector2f(36*UNIT,-36*UNIT);
	Vector2f acceleration = Vector2f(0*UNIT, GRAVITY*UNIT);
	//cam.Vertex2f()
	set_time(0);

	GD.ClearColorRGB(BLACK);
	char str[6];
	Input in = Input();
	Timer t;
	t.start();
	float lasttime = t.read();
	float currtime;
	while(1){
		//GDINIT
		in.pull();
		GD.Clear();
		GD.SaveContext();

		//DOSTUFF
		GD.ColorRGB(0xffffff);
		GD.PointSize(pointsize);
		GD.Begin(POINTS);
		GD.Vertex2f(position.x, position.y);
		currtime = t.read();
		float dt = currtime - lasttime;
		if (dt > 1 or dt < -1){//Since it may overflow
			dt = 0;
		}
		checkCollision(position, velocity, pointsize);
		position.x += (velocity.x*dt);
		position.y += (velocity.y*dt);
		velocity.x += (acceleration.x*dt);
		velocity.y += (acceleration.y*dt);
		lasttime = currtime;

		GD.ColorRGB(WHITE);
		sprintf(str, "%f", t.read());
		GD.cmd_text(40,40,16,OPT_SIGNED, str);
		//Acceleration without gravity

		//GDFINISH
		GD.RestoreContext();
		GD.swap();
		//wait(0.1);

	}

}

void Physicstest::checkCollision(Vector2f& position, Vector2f& velocity, int pointsize){
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
}

Physicstest::Physicstest(){

}

void Physicstest::initPoints(){
	GD.SaveContext();
	GD.PointSize(UNIT);
	GD.begin(POINTS);

}

