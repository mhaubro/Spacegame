#pragma once
#include <vector>

#include <sstream>
#include "Game.h"
#include "myassets.h"
#include "UI.h"
#include "Graphics.h"
#include "Sprite.h"
#include "Chunk.h"
#include "Input.h"
#include "World.h"
#include "PhysicsObject.h"
#include "BackGround.h"
#include "Polygon.h"
#include "bullet.h"
#include "Player.h"
#include "PhysicsObject.h"
#include "BackGround.h"
#include "Polygon.h"
#include "Mathematics.h"
#include "GameTimer.h"
#include "Animation.h"


Player player;
vector<bullet> shots;
vector<particle> particles;

Vector2f startpos = Vector2f();
Vector2f startvel = Vector2f();

Game::Game() :
		running(false), score(42) {
	maxHealth = 1000;
	maxEnergy = 1000;

	health = maxHealth;
	energy = maxEnergy;
}

void Game::runtest(){
	GD.ClearColorRGB(0x103000);
	GD.Clear();
	std::vector<bullet> shots;
	Vector2f v1 = Vector2f(5, 5);
	Vector2f v2 = Vector2f(3, 3);
	Vector2f v3 = Vector2f(2, 2);
	Vector2f v4 = Vector2f(3, 7);

	bullet a = bullet(v1, v2, 8, 0xffffff);
	bullet b = bullet(v2, v3, 8, 0xffffff);
	bullet c = bullet(v3, v4, 8, 0xffffff);
	bullet d = bullet(v4, v1, 8, 0xffffff);
	shots.push_back(a);
	shots.push_back(b);
	shots.push_back(c);
	shots.push_back(d);


	while (true){
		GD.Clear();
		GD.Begin(POINTS);
		//GD.PointSize(10);
		//GD.Vertex2ii(50, 50);
		for (std::vector<bullet>::iterator it = shots.begin(); it != shots.end(); it++){
			it->render();
		}
		GD.swap();
	}

}

void Game::run() {
	running = true;

	Input in = Input();
	UI ui = UI(this);
	//GD.ClearColorRGB(BLACK);
	GD.ClearColorA(255);
	GD.SaveContext();

	BackGround Background = BackGround(&player.ph);
	//World world = World();
	Vector2f groundNormal = Vector2f();

	//
	Vector2f shape1[] = { Vector2f(-.2,.4), Vector2f(1, .1), Vector2f(1, -.1), Vector2f(-.2, -.4) };
	Vector2f shape2[] = { Vector2f(-.9, -.8), Vector2f(-.9, .8), Vector2f(-.1,
			.8), Vector2f(-.1, -.8) };
	Polygon poly1 = Polygon(player.ph.position, player.angle, 4, shape1);
	Polygon poly2 = Polygon(player.ph.position, player.angle, 4, shape2);
//	Vector2f shape1[] = { Vector2f(-.2, .4), Vector2f(1, .1), Vector2f(1, -.1),
//				Vector2f(-.2, -.4) };
//		Vector2f shape2[] = { Vector2f(-.9, -.8), Vector2f(-.9, .8), Vector2f(-.1,
//				.8), Vector2f(-.1, -.8) };
//		Polygon poly1 = Polygon(player.ph.position, player.angle, 4, shape1);
//		Polygon poly2 = Polygon(player.ph.position, player.angle, 4, shape2);

	float angle = 0;
	Vector2f poly2Pos = Vector2f(20, 10);
	Vector2f shape3[] = { Vector2f(-1, -1), Vector2f(-1, 1), Vector2f(0, 2),
				Vector2f(1, 1), Vector2f(1, -1) };
		Polygon poly3 = Polygon(poly2Pos, angle, 5, shape3);

	Sprite sprite = Sprite(SPACESHIP_HANDLE, 32, 32, 1);
	Sprite exhaust = Sprite(EXHAUST1_HANDLE, 8, 8, 1);
	Animation anim = Animation(&exhaust, .1, 4);

	while (running) {

		in.pull();
		timer.update();
		//.Clear();

		Background.render();

		score++;
		player.angle += in.getRotation() * 0.001;

		while (player.angle > PI2)
			player.angle -= PI2;
		while (player.angle < 0)
			player.angle += PI2;

		if (in.getThrottle()) {
//			player.ph.velocity += FromAngle(0.01, player.angle);
//			Vector2f throttle = FromAngle((float) 30, player.angle); //Tilføjer en kraft på 30 newton i den vinkel
//			player.ph.addForce(throttle);
			GD.cmd_text(70, 70, 16, OPT_SIGNED, "touch");
			player.ph.velocity += FromAngle(0.01, player.angle);
			Vector2f throttle = FromAngle(getMaxThrottle(), player.angle); //Tilføjer en kraft på 30 newton i den vinkel
			player.ph.addForce(throttle);
			if (energy > 1)
				energy -= 1;

		}
		player.ph.addAcceleration(Vector2f(0, -GRAVITY));

		//Time registering and change of state
		GD.cmd_text(4, 50, 16, OPT_SIGNED, "FPS:");
		GD.cmd_number(36, 50, 16, OPT_SIGNED, 1 / timer.getDeltaTime());

		player.ph.changeState();
		//End of time.

		float groundHeight = world.getHeight(player.ph.position.x);

		if (player.ph.terrainCollision(world)) {
			player.ph.applyTerrainCoolision(world);
		}
		if (player.ph.position.y > 100) {
			player.ph.position.y = 100;
			player.ph.velocity.x *= .5;
			player.ph.velocity.y *= -.5;
		}

		if (player.ph.position.x < 0) {
			player.ph.velocity.x *= -.1;
			player.ph.position.x = 0;
		}
		if (player.ph.position.x > 48) {
			player.ph.velocity.x *= -.1;
			player.ph.position.x = 48;
		}

		world.update(player.ph.position.x);
		player.height = player.ph.position.y - groundHeight;
		energy += .2;
		energy = clamp(energy, 0, maxEnergy);

		world.update(player.ph.position.x);
		player.height = player.ph.position.y - groundHeight;

		cam.follow(player.ph.position, player.ph.velocity);

		//Background.render();
		world.render();


		world.getNormal(player.ph.position.x, groundNormal);
		GD.ColorRGB(PURPLE);
		renderVector2f(groundNormal, player.ph.position.x, groundHeight, 1.5);
		Vector2f tangent = Vector2f(groundNormal.y, -groundNormal.x);
		GD.ColorRGB(ORANGE);
		renderVector2f(tangent, player.ph.position.x, groundHeight, 1.5);

		GD.Begin(POINTS);
		GD.PointSize(16 * 4);
		GD.ColorRGB(RED);

		cam.Vertex2f(player.ph.position.x, groundHeight);
		//world.getNormal(ph.position.x, groundNormal);
		//GD.ColorRGB(PURPLE);
		//renderVector2f(groundNormal, ph.position.x, groundHeight, 1.5);
		//Vector2f tangent = Vector2f(groundNormal.y, -groundNormal.x);
		//GD.ColorRGB(ORANGE);
		//renderVector2f(tangent, ph.position.x, groundHeight, 1.5);

		//GD.Begin(POINTS);
		//GD.PointSize(16 * 4);
		//GD.ColorRGB(RED);
		//cam.Vertex2f(ph.position.x, groundHeight);

		GD.RestoreContext();

		Vector2f temp1 = (Vector2f() + poly3.Position) - poly1.Position;
		renderVector2f(temp1, player.ph.position.x, player.ph.position.y, 1);

		static Vector2f mtd = Vector2f();
		static Vector2f normal = Vector2f();
		if (Polygon::Collide(poly1, poly3, mtd) || Polygon::Collide(poly2,poly3,mtd)) {
			normal = mtd.normalized();

			player.ph.velocity = player.ph.velocity - (normal * (player.ph.velocity.dotProduct(normal) * 2));

			//velocity = (velocity * terrainNormal * .4) + (velocity * terrainTangent*.99);

			player.ph.velocity *= .4;
			player.ph.position += mtd;
			GD.ColorRGB(RED);

			poly1.render();
		}
//
//			world.getNormal(player.ph.position.x, terrainNormal);
//			terrainTangent.x = terrainNormal.y;
//			terrainTangent.y = -terrainNormal.x;
//
//			player.ph.velocity = player.ph.velocity
//					- (terrainNormal
//							* (player.ph.velocity.dotProduct(terrainNormal) * 2));
//
//			player.ph.velocity *= .4;
//			//velocity = (velocity * terrainNormal * .4) + (velocity * terrainTangent*.99);
//
//			player.ph.position += temp;
//		}
		GD.cmd_text(4, 66, 16, OPT_SIGNED, "POW");
		GD.cmd_number(36, 66, 16, OPT_SIGNED, mtd.x);

		if (Polygon::TerrainCollide(poly1, world, mtd) || Polygon::TerrainCollide(poly2, world, mtd)) {
			GD.ColorRGB(BLUE);
			static Vector2f terrainNormal = Vector2f(); //vector terrain normal
			static Vector2f terrainTangent = Vector2f();

			world.getNormal(player.ph.position.x, terrainNormal);
			terrainTangent.x = terrainNormal.y;
			terrainTangent.y = -terrainNormal.x;

			player.ph.velocity = player.ph.velocity
					- (terrainNormal
							* (player.ph.velocity.dotProduct(terrainNormal) * 2));

			player.ph.velocity *= .4;
			//velocity = (velocity * terrainNormal * .4) + (velocity * terrainTangent*.99);

			player.ph.position += mtd;
		}

		poly3.render();
		GD.RestoreContext();

		GD.Begin(BITMAPS);

		anim.render(player.ph.position.x, player.ph.position.y, player.angle + PI / 2, 4);

		world.render();

		GD.RestoreContext();

		renderVector2f(player.ph.velocity, player.ph.position.x, player.ph.position.y, 1);

		ui.render();

		GD.swap();
	}

}

float Game::getMaxThrottle() {
	float max = 10;
	if (energy <= 1) {
		return 0;
	}

	float maxHeight = 30;
	float minHeight = 10;

	max *= (1
			- (clamp(cam.getY(), minHeight, maxHeight) - minHeight)
					/ (maxHeight - minHeight));

	return max;
}
