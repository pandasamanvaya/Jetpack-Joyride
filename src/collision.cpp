#include "collision.h"


bool detect_collision(bounding_box_t a, bounding_box_t b) {
    return (abs(a.x - b.x) * 2 < (a.width + b.width)) &&
           (abs(a.y - b.y) * 2 < (a.height + b.height));
}

bool coll_player_line(Player player, FireLine line)
{
	bounding_box_t a, b;
	a.x = player.man.position.x;
	a.y = player.man.position.y;
	b.x = line.fire.position.x;
	b.y = line.fire.position.y;

	a.width = 0.1;
	a.height = 0.35;
	b.width = 0.46;
	b.height = 0.02;

	return(detect_collision(a, b));
}

bool coll_player_beam(Player player, FireBeam beam)
{

	bounding_box_t a, b;
	a.x = beam.fire.position.x;
	a.y = beam.fire.position.y;
	b.x = player.man.position.x;
	b.y = player.man.position.y;

	a.width = 1.2;
	a.height = 0.03;
	b.width = 0.1;
	b.height = 0.35;

	return(detect_collision(a, b));	
}

bool coll_player_boom(Player player, Boomerang Boom)
{

	bounding_box_t a, b;
	a.x = player.man.position.x;
	a.y = player.man.position.y;
	b.x = Boom.boom.position.x;
	b.y = Boom.boom.position.y;

	a.width = 0.1;
	a.height = 0.35;
	b.width = 0.05;
	b.height = 0.2;

	return(detect_collision(a, b));
}


bool coll_player_shield(Player player, Shield shield)
{

	bounding_box_t a, b;
	a.x = player.man.position.x;
	a.y = player.man.position.y;
	b.x = shield.cover.position.x;
	b.y = shield.cover.position.y;

	a.width = 0.1;
	a.height = 0.35;
	b.width = 0.15;
	b.height = 0.35;

	return(detect_collision(a, b));
}


bool coll_player_coin(Player player, Coin coin)
{

	bounding_box_t a, b;
	a.x = player.man.position.x;
	a.y = player.man.position.y;
	b.x = coin.coin.position.x;
	b.y = coin.coin.position.y;

	a.width = 0.1;
	a.height = 0.35;
	b.width = 0.02;
	b.height = 0.02;

	return(detect_collision(a, b));
}

bool coll_player_heart(Player player, Heart heart)
{

	bounding_box_t a, b;
	a.x = player.man.position.x;
	a.y = player.man.position.y;
	b.x = heart.life.position.x;
	b.y = heart.life.position.y;

	a.width = 0.1;
	a.height = 0.35;
	b.width = 0.02;
	b.height = 0.02;

	return(detect_collision(a, b));
}

bool player_near_magnet(Player player, Magnet magnet)
{

	bounding_box_t a, b;
	a.x = player.man.position.x;
	a.y = player.man.position.y;
	b.x = magnet.magnet.position.x;
	b.y = magnet.magnet.position.y-0.2;

	a.width = 0.1;
	a.height = 0.35;
	b.width = 0.3;
	b.height = 1.0 + b.y + 0.2;

	return(detect_collision(a, b));
}

bool coll_player_icon(Player player, WaterBalloon water)
{

	bounding_box_t a, b;
	a.x = player.man.position.x;
	a.y = player.man.position.y;
	b.x = water.icon_position.x;
	b.y = water.icon_position.y;

	a.width = 0.1;
	a.height = 0.35;
	b.width = 0.08;
	b.height = 0.08;

	return(detect_collision(a, b));
}

bool coll_balloon_boom(WaterBalloon water, Boomerang boom)
{

	bounding_box_t a, b;
	a.x = boom.boom.position.x;
	a.y = boom.boom.position.y;
	b.x = water.water.position.x;
	b.y = water.water.position.y;

	a.width = 0.05;
	a.height = 0.2;
	b.width = 0.08;
	b.height = 0.08;

	return(detect_collision(a, b));
}

bool coll_player_bomb(Player player, TimeBomb bomb)
{

	bounding_box_t a, b;
	a.x = player.man.position.x;
	a.y = player.man.position.y;
	b.x = bomb.bomb.position.x;
	b.y = bomb.bomb.position.y;

	a.width = 0.1;
	a.height = 0.35;
	b.width = 0.1;
	b.height = 0.1;

	return(detect_collision(a, b));
}