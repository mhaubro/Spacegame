#include "Game.h"

#include "UI.h"
#include "Graphics.h"
#include "Sprite.h"
#include "Chunk.h"
#include "Input.h"
#include "World.h"
#include "player.h"
#include "PhysicsObject.h"

Vector2f startpos = Vector2f();
Vector2f startvel = Vector2f();

Vector2f vec = Vector2f();

Game::Game() :
		running(false), score(42), p(), ph(1, 1, vec, vec) {
	maxHealth = 1000;
	maxEnergy = 1000;

	health = maxHealth/3;
	energy = maxEnergy/2;
	//ph = PhysicsObject(1, 1, vec, vec);
}

void Game::run() {
	running = true;
	Timer t;
	t.start();//HUSK AT STARTE TIMER
	float currtime = t.read();
	float lasttime = 0;
	float dt = 0;
	Input in = Input();
	UI ui = UI(this);
	GD.ClearColorRGB(BLACK);

	GD.SaveContext();

	World world = World();
	Vector2f groundNormal = Vector2f();

	Sprite sprite = Sprite(1, 128, 128, 1);

	while (running) {

		in.pull();
		GD.Clear();

		score++;
		p.angle += in.getRotation() * 0.001;

		while (p.angle > PI2)
			p.angle -= PI2;
		while (p.angle < 0)
			p.angle += PI2;

		if (in.getThrottle()) {
			ph.velocity += FromAngle(0.01, p.angle);
			Vector2f throttle = FromAngle((float)30 ,p.angle);//Tilføjer en kraft på 30 newton i den vinkel
			ph.addForce(throttle);
			GD.cmd_text(70, 70, 16, OPT_SIGNED, "touch");
		}
		ph.addAcceleration(Vector2f(0, -GRAVITY));

		//Time registering and change of state
		currtime = t.read();
		dt = currtime - lasttime;

		ph.changeState(dt);
		lasttime = currtime;
		//End of time.

		float groundHeight = world.getHeight(ph.position.x);

		if (ph.position.y < groundHeight) {
			ph.position.y = groundHeight;
			ph.velocity.x *= .5;
			ph.velocity.y *= -.5;
		}
		if (ph.position.y > 50) {
			ph.position.y = 50;
			ph.velocity.x *= .5;
			ph.velocity.y *= -.5;
		}

		world.update(ph.position.x);
		p.height = ph.position.y - groundHeight;

		cam.follow(ph.position,ph.velocity);

		world.render();

		world.getNormal(ph.position.x, groundNormal);
		renderVector2f(groundNormal, ph.position.x, groundHeight, 1.5);

		GD.Begin(POINTS);
		GD.PointSize(16 * 4);
		GD.ColorRGB(RED);

		cam.Vertex2f(ph.position.x,groundHeight);


		GD.RestoreContext();

		GD.Begin(BITMAPS);
		sprite.render(ph.position.x, ph.position.y, p.angle + PI / 2, .5, 0);
		GD.RestoreContext();

		ui.render();

		GD.swap();
	}
}
