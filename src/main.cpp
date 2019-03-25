#include "main.h"
#include "timer.h"
#include "wall.h"
#include "fire_brick.h"
#include "rocket.h"
#include "coin.h"
#include "boomerang.h"
#include "player.h"
#include "collision.h"
#include "powerup.h"
#include "magnet.h"

//Variable Initialisations
GLFWwindow* window;
GLFWmonitor* monitor;
Wall wall1;
float speed = 0.03, pos, pos1, dist = 1.0, score = 0;
float zoom = 1.0, wall_wid = 2.0, wall_len = 2.0;
int screen_length = 1366, screen_width = 720;
int coin1_cnt = 0, coin2_cnt = 0, balloon_cnt = 0, angle = 0;
Background bg;
GLuint MatrixID1, MatrixID2, programID1, programID2;
FireBeam beam = FireBeam(-2.0, 0.0, 0.0);
FireLine line = FireLine(0.0, 0.0, 0.0);
Boomerang boom1 = Boomerang(0.0, 0.0, 0.0);
Player player = Player(-0.3, -0.6, 0.0);
Shield shield = Shield(0.0, 0.0, 0.0);
Coin coin1[500], coin2[200];
int coin_collected = 0, life_count = 0, coin_cnt;
const float *color;
bool jump = false, right = false, attract = false, safe = false, slow = false;
Heart heart = Heart(0.0, 0.0, 0.0);
Magnet magnet1 = Magnet(1.0, 0.0, 0.0);
WaterBalloon balloon = WaterBalloon(0.0, 0.0, 0.0);
TimeBomb Time = TimeBomb(0.5, 0.0, 0.0);

Timer t60(1.0 / 60);
Timer tsafe(15.0);
Timer bomb_time(20.0);

void all_move_left()
{
    dist += speed;
	
	wall1.move_left(speed);
	line.move_left(speed);
	shield.move_left(speed);
	heart.move_left(speed);
	magnet1.move_left(speed);
	balloon.move_left(speed);
	Time.move_left(speed);
	for(int i = 0; i < coin1_cnt; i++)
		coin1[i].move_left(speed);
	for(int i = 0; i < coin2_cnt; i++)
		coin2[i].move_left(speed);

	pos -= speed;
	pos1 -= speed;
	score += speed;

}

void set_position()
{
	line.set_position(0.0, 0.45, 0.0);
	boom1.set_position(0.0, -0.5, 0.0);
	shield.set_position(3.0, 0.0, 0.0);
	heart.set_position(5.0, 0.0, 0.0);
	boom1.set_position(2.6, 0.0, 0.0);
	//balloon.water.position = player.man.position;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if(jump)
		player.jump(speed);

    if (key == GLFW_KEY_Q && action == GLFW_PRESS)
    	exit(0);

    else if (key == GLFW_KEY_RIGHT){
    	if(player.man.position.x >= -0.3){
	    	all_move_left();
	    }
		else
			player.man.position.x += speed;
    }
    else if(key == GLFW_KEY_LEFT){
    	if(player.man.position.x > -0.94)
    		player.man.position.x -= speed;
    }
    //printf("%f %f\n", pos, pos1);
    else if(key == GLFW_KEY_SPACE){
    		player.jump(speed);
    		jump = true;
    	if(action == GLFW_RELEASE){
    		jump = false;
    	}
    }
    else if(key == GLFW_KEY_X and action == GLFW_RELEASE){
    	//balloon.release_balloon();
    	if(balloon_cnt > 0){
    		if(!balloon.press)
    			balloon_cnt--;
    			
    		balloon.press = true;
    		printf("%d\n", balloon_cnt);
    	}
    	if(balloon_cnt <= 0){
    		if(!safe)
    		color = brown;
	   	else
    		color = green;
    	player.change_color(color);
    	}
    }
}

void mouse_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	static float factor = 0.02;
	if(yoffset > 0){
		//Zoom out
		zoom += factor;
		if(zoom > 1.0)
			zoom = 1.0;
		bg.reshapeWindow(window, screen_length, screen_width, zoom);
	}
	else{
		//Zoom in
		zoom -= factor;
		bg.reshapeWindow(window, screen_length, screen_width, zoom);
	}
}

int create_coin(Coin coin[], float start, float end, float dist, const float color[])
{
	int k = 0;
	for(float i = dist; i < dist + start + 0.2; i+=0.1){
		for(float j = 0; j < end + 0.2; j+=0.1){
			coin[k] = Coin(color, i, j, 0.0);
			coin[k++].create_coin();
		}
	}
	return k;
}

void coin_on_screen(Coin coin[], int coin_cnt, GLuint MatrixID)
{
	for(int i = 0; i < coin_cnt; i++)
		coin[i].render_coin(bg, MatrixID);
}

void check_collsion_on_screen()
{
	//Beam Collision
	if(coll_player_beam(player, beam) and !safe){
		printf("Beam collision\n");
		if(life_count > 0){
			safe = true;	
			life_count--;
			if(!tsafe.processTick())
				safe = true;			
		}
		else if(!life_count or !safe)
			exit(EXIT_BEAM);
		else{
		}
	}
	//Boomerang Collision
	if(coll_player_boom(player, boom1) and !safe){
		printf("Boom collision\n");
		if(life_count > 0){
			life_count--;
			safe = true;
			if(!tsafe.processTick())
				safe = true;
		}
		else if(!life_count or !safe)
			exit(EXIT_BOOM);
		else{
		}
	}
	//Line Collision
	if(coll_player_line(player, line) and !safe){
		printf("Line collision\n");
		if(life_count > 0){
			life_count--;
			safe = true;
			if(!tsafe.processTick())
				safe = true;
		}
		else if(!life_count or !safe){
			printf("%d\n", safe);
			exit(EXIT_LINE);
		}
		else{
		}
	}

	//Shield Collision
	if(coll_player_shield(player, shield) or safe){
		safe = true;
		if(!tsafe.processTick()){
			player.change_color(green);
			shield.cover.position.x = player.man.position.x;
			shield.cover.position.y = player.man.position.y + 0.03;
			shield.cover.position.z = player.man.position.z;
		}
		else{
			shield.cover.position.x = -1.4;
			shield.cover.position.y = -1.4;
			shield.cover.position.z = 0.0;
			safe = false;
			player.change_color(color);
		}
	}

	//Coin Collision
	for(int i = 0; i < coin1_cnt; i++){
		if(coll_player_coin(player, coin1[i])){
			coin_collected++;
			score += 10;
			coin1[i].coin.position = vec3(-2.0, -2.0, 0.0);
		}
	}

	for(int i = 0; i < coin2_cnt; i++){
		if(coll_player_coin(player, coin2[i])){
			coin_collected++;
			score += 30;
			coin2[i].coin.position = vec3(-2.0, -2.0, 0.0);
		}
	}

	//Heart Collision
	if(coll_player_heart(player, heart)){
		score += 100;
		life_count++;
		heart.life.position = vec3(-2.0, -2.0, 0.0);
	}

	//Magnetic Region
	if(player_near_magnet(player, magnet1)){
		attract = true;
		if(player.man.position.y < magnet1.magnet.position.y-0.2)
			player.man.position.y += 0.001;
		if(player.man.position.x < magnet1.magnet.position.x)
			player.man.position.x += 0.001;
		else if(player.man.position.x > magnet1.magnet.position.x)
			player.man.position.x -= 0.001;

		speed = 0.02;
	}
	else{
		attract = false;
		speed = 0.03;
	}

	//Water Balloon Icon Collision
	if(coll_player_icon(player, balloon)){
		balloon_cnt += 4;
		color = blue;
		player.change_color(color);
		balloon.icon_position = vec3(-2.0, -2.0, -2.0);
	}
	
	//Destory Boomerang
	if(coll_balloon_boom(balloon, boom1)){
		score += 100;
		boom1.set_position(-2.0, -2.0, 0.0);
		balloon.water.position = vec3(-2.0, -2.0, -2.0);
	}

	//Bomb Collison
	if(coll_player_bomb(player, Time) or slow){
		Time.bomb.position = vec3(-2.0, -2.0, 0.0);
		if(!bomb_time.processTick()){
			speed = Time.bomb_effect();
			slow = true;
		}
		else{
			slow = false;
			speed = 0.03;
		}
	}
	//printf("%f\n", speed);
}

void random_render(GLuint MatrixID)
{
	float random_x = 0.0, random_y = 0.0;
	int dir;
	//Line
	if((int)dist % 9 == 0){
		random_x = (float)(rand() % 5) + 1.5;
		random_y = (float)(rand() % 5) * 0.2;

		line.set_position(random_x, random_y, 0.0);
	}

	//Beam
	if((int)dist % 20 == 0){ 
		random_y = (float)(rand() % 1) + 1.4;
		dir = (rand() % 2);
		if(dir)
			beam.set_position(0.0, -random_y, 0.0, dir);
		else
			beam.set_position(0.0, random_y, 0.0, dir);
		//printf("ra = %f %d\n", random_y, dir);
	}
	
	//Coins
	if((int)dist % 5 == 0){
		random_x = (float)(rand() % 6)/10;
		random_y = (float)(rand() % 6)/10;

		coin1_cnt = create_coin(coin1, random_x, random_y, 1.6, gold);
		coin_on_screen(coin1, coin1_cnt, MatrixID);
		//printf("coin = %d %f\n",coin1_cnt, random_x);
	}
	if((int)dist % 10 == 0){
		random_x = (float)(rand() % 4)/10;
		random_y = (float)(rand() % 4)/10;
		coin2_cnt = create_coin(coin2, random_x, random_y, 2.5, olive);
		coin_on_screen(coin2, coin2_cnt, MatrixID);
		//printf("coin = %d %f\n",coin2_cnt, random_x);

	}
	//printf("dist = %f\n", dist);
	//Boomerang
	if((int)dist % 15 == 0){
		random_y  = (float)(rand() % 10) - 3;
		boom1.set_position(2.6, random_y/10, 0.0);
		boom1.out = false;
		//printf("boom = %f %f\n", boom1.boom.position.y, boom1.boom.position.x);
	}

	//Shield and Heart
	if((int)dist % 50 == 0){
	//	dist = 0.0;
		dir = rand() % 2;
		if(dir)
			shield.set_position(1.4, 0.0, 0.0);
		else
			heart.set_position(1.4, 0.0, 0.0);
	}
	//Water Balloon
	if((int)dist % 30 == 0){
		random_y = (float)(rand() % 5) * 0.2;
		balloon.icon_position = vec3(1.3, random_y, 0.0);
	}

	//Magnet
	if((int)dist % 50 == 0){
		random_y = (float)(rand() % 5) * 0.2;
		magnet1.magnet.position = vec3(1.3, random_y, 0.0);
	}
	
	//Time Bomb
	if((int)dist % 40 == 0){
		random_y = (float)(rand() % 5) * 0.2;
		Time.bomb.position = vec3(1.3, random_y, 0.0);
	}
	if(dist > 1000)
		dist = 0.0;
}


int main()
{
	//Initialising background class

	//Setting up OpenGl tools
	window = bg.create_window(screen_length, screen_width);
	if(window == NULL){
		printf("Window not created\n");
		exit(3);
	}

	color = brown;
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);

	GLuint vao1;
	glGenVertexArrays(1, &vao1);
	glBindVertexArray(vao1);

	programID1 = LoadShaders( "../src/Wall.vert", "../src/Wall.frag" );
	MatrixID1 = glGetUniformLocation(programID1, "tex0");
	programID2 = LoadShaders( "../src/Object.vert", "../src/Object.frag" );
	MatrixID2 = glGetUniformLocation(programID2, "tex1");

	initText2D( "../lib/Holstein.DDS" );
	
	char Score[50], Coins[50], lives[50];
	
	wall1 = Wall(wall_len, wall_wid, 0.0, 0.0, 0.0);
	wall1.create_wall("../Wall.bmp", programID1);
/*
	coin1_cnt = create_coin(coin1, 0.2, 0.6, 0.0);
	coin2_cnt = create_coin(coin2, 0.2, 0.6, 0.0);*/
	beam.create_block();
	line.create_block();
	boom1.create_boom();
	player.create_player();
	shield.create_shield();
	heart.create_heart();
	magnet1.create_magnet();
	balloon.create_balloon();
	Time.create_bomb();
	/*wall2 = Wall(1.0, 2.0, 0.5, 0.0, 0.0);
	wall2.create_wall("../wall.bmp", programID1);
*/	
	set_position();

	pos = wall1.wall.position.x;
	pos1 = pos + 1.9;
	float random  = 0.0;
	bool loop = false;
	while(!loop){
		angle = (angle + 1) % 360;
		sprintf(Score, "Score %.0f", score);
		sprintf(Coins, "Coins %d", coin_collected);
		sprintf(lives, "Lives %d", life_count);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		printText2D(Score, 350, 550, 20);
		printText2D(Coins, 100, 550, 20);	
		printText2D(lives, 600, 550, 20);	

		if (t60.processTick()) {
			glUseProgram(programID2);
			beam.render_block(bg, MatrixID2);
			boom1.render_boom(bg, MatrixID2, angle/2);
			player.render_player(bg, MatrixID2);
			line.render_block(bg, MatrixID2);
			shield.render_shield(bg, MatrixID2);
			heart.render_heart(bg, MatrixID2);
			magnet1.render_magnet(bg, MatrixID2);
			Time.render_bomb(bg, MatrixID2);
			balloon.render_balloon(bg, MatrixID2,player);
			coin_on_screen(coin1, coin1_cnt, MatrixID2);
			coin_on_screen(coin2, coin2_cnt, MatrixID2);

			random_render(MatrixID2);
/*			if(line.fire.position.x < -1.8){
				random = (float)(rand() % 5) + 3;
				line1.set_position(random, 0.0, 0.0);
				//set_position(random);
			}*/
			glUseProgram(0);
			
			glUseProgram(programID1);
			wall1.render_wall(bg, wall1.img, MatrixID1);
			wall1.set_position(pos1, 0.0, 0.0);
			wall1.render_wall(bg, wall1.img, MatrixID1);
			wall1.set_position(pos, 0.0, 0.0);

			glUseProgram(0);
			float temp = 1.85;
			if((pos1 + pos) * 100000000 <= -200000000.0){
				if(pos > pos1)
					pos1 = temp;
				else
					pos = temp;
			}
			check_collsion_on_screen();

			if(glfwSetKeyCallback(window, key_callback) and !jump and !attract)
    			player.fall(speed);

			glfwSetScrollCallback(window, mouse_callback);
			glfwSwapBuffers(window);
		}
		glfwPollEvents();
		loop = glfwWindowShouldClose(window);
	}

	glDeleteVertexArrays(1, &vao1);

	glDeleteBuffers(1, &(wall1.wall.vertexbuffer));
	glDeleteBuffers(1, &(wall1.texbuffer));
	/*glDeleteBuffers(1, &(rocket1.rocket.vertexbuffer));
	glDeleteBuffers(1, &(rocket1.rocket.texbuffer));
*/
	glDeleteProgram(programID1);
	glDeleteProgram(programID2);
	glDeleteTextures(1, &(wall1.img));
	//glDeleteTextures(1, &(rocket1.rocket.img));

	glfwTerminate();

	exit(0);
}