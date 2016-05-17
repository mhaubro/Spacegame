#pragma once

#include <sstream>

#include "Game.h"
#include "myassets.h"
#include "UI.h"
#include "Graphics.h"
#include "Sprite.h"
#include "Chunk.h"
#include "Input.h"
#include "World.h"
#include "Player.h"
#include "PhysicsObject.h"
#include "BackGround.h"
#include "Polygon.h"
#include "Mathematics.h"
#include "GameTimer.h"
#include "Animation.h"

Vector2f startpos = Vector2f(0, 10);
Vector2f startvel = Vector2f(6, 4);

Game::Game() :
		running(false), score(42), ph(1, startpos, startvel) {
	maxHealth = 1000;
	maxEnergy = 1000;

	health = maxHealth;
	energy = maxEnergy;

	//ph = PhysicsObject(1, 1, vec, vec);
}

void Game::run() {
	running = true;

	Input in = Input();
	UI ui = UI(this);
	//GD.ClearColorRGB(BLACK);
	GD.ClearColorA(255);
	GD.SaveContext();

	BackGround Background = BackGround(&ph);
	//World world = World();
	Vector2f groundNormal = Vector2f();

	//
	Vector2f shape1[] = { Vector2f(-.2, .4), Vector2f(1, .1), Vector2f(1, -.1),
				Vector2f(-.2, -.4) };
		Vector2f shape2[] = { Vector2f(-.9, -.8), Vector2f(-.9, .8), Vector2f(-.1,
				.8), Vector2f(-.1, -.8) };
		Polygon poly1 = Polygon(ph.position, p.angle, 4, shape1);
		Polygon poly2 = Polygon(ph.position, p.angle, 4, shape2);

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
		p.angle += in.getRotation() * 0.001;

		while (p.angle > PI2)
			p.angle -= PI2;
		while (p.angle < 0)
			p.angle += PI2;

		if (in.getThrottle()) {
			ph.velocity += FromAngle(0.01, p.angle);
			Vector2f throttle = FromAngle(getMaxThrottle(), p.angle); //Tilføjer en kraft på 30 newton i den vinkel
			ph.addForce(throttle);
			if (energy > 1)
				energy -= 1;

		}
		ph.addAcceleration(Vector2f(0, -GRAVITY));

		//Time registering and change of state

		GD.cmd_text(4, 50, 16, OPT_SIGNED, "FPS:");
		GD.cmd_number(36, 50, 16, OPT_SIGNED, 1 / timer.getDeltaTime());

		ph.changeState();
		//End of time.

		float groundHeight = world.getHeight(ph.position.x);

		if (ph.terrainCollision(world)) {
			ph.applyTerrainCoolision(world);
		}
		if (ph.position.y > 100) {
			ph.position.y = 100;
			ph.velocity.x *= .5;
			ph.velocity.y *= -.5;
		}

		if (ph.position.x < 0) {
			ph.velocity.x *= -.1;
			ph.position.x = 0;
		}
		if (ph.position.x > 48) {
			ph.velocity.x *= -.1;
			ph.position.x = 48;
		}

		energy += .2;
		energy = clamp(energy, 0, maxEnergy);

		world.update(ph.position.x);
		p.height = ph.position.y - groundHeight;

		cam.follow(ph.position, ph.velocity);

		//Background.render();

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
		renderVector2f(temp1, ph.position.x, ph.position.y, 1);

		static Vector2f mtd = Vector2f();
		static Vector2f normal = Vector2f();
		if (Polygon::Collide(poly1, poly3, mtd) || Polygon::Collide(poly2,poly3,mtd)) {
			normal = mtd.normalized();

			ph.velocity = ph.velocity
					- (normal * (ph.velocity.dotProduct(normal) * 2));

			ph.velocity *= .4;
			ph.position += mtd;
			GD.ColorRGB(RED);

			poly1.render();
		}

		GD.cmd_text(4, 66, 16, OPT_SIGNED, "POW");
		GD.cmd_number(36, 66, 16, OPT_SIGNED, mtd.x);

		if (Polygon::TerrainCollide(poly1, world, mtd) || Polygon::TerrainCollide(poly2, world, mtd)) {
			GD.ColorRGB(BLUE);
			static Vector2f terrainNormal = Vector2f(); //vector terrain normal
			static Vector2f terrainTangent = Vector2f();

			world.getNormal(ph.position.x, terrainNormal);
			terrainTangent.x = terrainNormal.y;
			terrainTangent.y = -terrainNormal.x;

			ph.velocity = ph.velocity
					- (terrainNormal
							* (ph.velocity.dotProduct(terrainNormal) * 2));

			ph.velocity *= .4;
			//velocity = (velocity * terrainNormal * .4) + (velocity * terrainTangent*.99);

			ph.position += mtd;
		}

		poly3.render();
		GD.RestoreContext();

		GD.Begin(BITMAPS);

		//Background.render();
		anim.render(ph.position.x, ph.position.y, p.angle + PI / 2, 4);
		//sky.render(6, 6, 0, 1, 0);

		world.render();

		GD.RestoreContext();

		renderVector2f(ph.velocity, ph.position.x, ph.position.y, 1);

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
