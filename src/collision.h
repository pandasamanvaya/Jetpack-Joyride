#include "main.h"
#include "fire_brick.h"
#include "boomerang.h"
#include "player.h"
#include "powerup.h"
#include "coin.h"
#include "magnet.h"

bool detect_collision(bounding_box_t, bounding_box_t);
bool coll_player_line(Player, FireLine);
bool coll_player_beam(Player, FireBeam);
bool coll_player_boom(Player, Boomerang);
bool coll_player_shield(Player, Shield);
bool coll_player_coin(Player, Coin);
bool coll_player_heart(Player, Heart);
bool player_near_magnet(Player, Magnet);
bool coll_player_icon(Player, WaterBalloon);
bool coll_balloon_boom(WaterBalloon, Boomerang);
bool coll_player_bomb(Player, TimeBomb);
