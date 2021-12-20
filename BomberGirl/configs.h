#pragma once

namespace Bombergirl
{
#pragma region Window
	const auto DEFAULT_WINDOW_WIDTH = 1920;
	const auto DEFAULT_WINDOW_HEIGHT = 1080;
	const auto GAME_FPS = 60;
	const auto GAME_TITLE = "Bombergirl";
#pragma endregion

////////////////////////////
#pragma region Font
	const auto GARAMOND_FONT_PATH = "./assets/fonts/garamond.ttf";
	const auto CONTROL_FONT_PATH = "./assets/fonts/control.ttf";
#pragma endregion

////////////////////////////
#pragma region Intro
	const auto INTRO_SCREEN_TIME = 2.f;
	const auto INTRO_LOGO_PATH = "./assets/textures/logo/bomb_logo.png";

#pragma endregion

////////////////////////////
#pragma region Menu
	const auto MENU_BACKGROUND_PATH = "./assets/textures/backgrounds/background_menu.jpg";
	const auto MENU_SYSTEM_PATH = "./assets/textures/img/system/Window.png";
#pragma endregion

////////////////////////////
#pragma region Character
	const auto CHARACTER_TEXTURE_PATH = "./assets/textures/players/faces/";
	const auto CHARACTER_NUMBER_OF = 4;
	const auto CHARACTER_BORDER_SELECT_RED = "./assets/textures/borders/red_border.png";
	const auto CHARACTER_BORDER_SELECT_BLUE = "./assets/textures/borders/blue_border.png";
#pragma endregion

#pragma region About
	const auto TEXT_MOVE_SPEED = 150;
	const auto PRESS_ENTER_TEXT_AFFECT_SPEED = 300.f;
	const auto GEAR_ROTATE_SPEED = 40.f;
	const auto ABOUT_TEXT_IMAGE = "./assets/textures/img/system/about_text_image.png";
	const auto GROUP_ABOUT_IMAGE = "./assets/textures/img/system/group.png";
	const auto LIGHT_ABOUT_IMAGE = "./assets/textures/img/system/light.png";
	const auto LEFT_GEAR_ABOUT_IMAGE = "./assets/textures/img/system/left_gear.png";
	const auto RIGHT_GEAR_ABOUT_IMAGE = "./assets/textures/img/system/right_gear.png";
#pragma endregion

#pragma region Game
	const auto PLAYER_SHADOW_PATH = "./assets/textures/players/shadow.png";
	const auto PLAYER_MOVEMENT_TEXTURE_PATH = "./assets/textures/players/movements/";
	const auto BACKGROUND_TILESETS_PATH = "./assets/textures/tilesets/Dungeon_A5.png";
	const auto MAP_BACKGROUND_TEXTURE_PATH = "./assets/textures/backgrounds/map_background.png";
	const auto BOMB_TEXTURE_PATH = "./assets/textures/tilesets/bomb.png";
	const auto BARREL_TEXTURE_PATH = "./assets/textures/tilesets/barrel.png";
	const auto EXPLOSION_TEXTURE_PATH = "./assets/textures/tilesets/explosion.png";
	const auto FLAME_TEXTURE_PATH = "./assets/textures/tilesets/flame.png";
	const auto ITEM_TEXTURE_PATH = "./assets/textures/tilesets/items.png";
	const auto GAMESTATE_BACKGROUND_PATH = "./assets/textures/backgrounds/background_gamestate.jpg";
	const auto TIMER_ICON_PATH = "./assets/textures/icon/timer_icon.png";
	const auto TILE_SIZE = 48;
	const auto WORLD_WIDTH = 720;
	const auto WORLD_HEIGHT = 720;
	const auto PLAYER_DEFAULT_SPEED = 150.f;
	const auto PLAYER_DEFAULT_BOMB_RANGE = 2;
	const auto PLAYER_DEFAULT_BOMBS = 2;
	const auto ITEM_OCCURRENCE_RATE = 0.3f;
	const auto BARREL_OCCURRENCE_RATE = 0.6f;
	//Time
	const auto FLAME_EXISTING_TIME = 0.3f;
	const auto TRANSITION_PICKUP_TIME = 2.f;
	const auto ITEM_EXISTING_TIME = 6.f;
	const auto TIME_DELAY_SET_UP_BOMB = 0.1f;
	const auto TIME_PER_ROUND = 12.f;
#pragma endregion

#pragma region Sound
	const auto INTRO_SOUND = "./assets/sounds/intro.wav";
	const auto MENU_SOUND = "./assets/sounds/main_menu.wav";
	const auto SELECT_SOUND = "./assets/sounds/select_click.wav";
	const auto CONFIRM_SOUND = "./assets/sounds/confirm.wav";
	const auto CHARACTER_CONFIRM_SOUND = "./assets/sounds/select_character.wav";
	const auto SET_BOMB_SOUND = "./assets/sounds/bombset.wav";
	const auto GAME_SOUND = "./assets/sounds/game.wav";
	const auto EXPLOSION_SOUND = "./assets/sounds/bomb.wav";
	const auto GET_ITEM_INCREASEBOMBRANGE_SOUND = "./assets/sounds/get_item_IncreaseBombRange.wav";
	const auto GET_ITEM_INCREASEBOMBCOUNT_SOUND = "./assets/sounds/get_item_IncreaseBombCount.wav";
	const auto GET_ITEM_INCREASESPEED_SOUND = "./assets/sounds/get_item_IncreaseSpeed.wav";
	const auto TICK_SOUND = "./assets/sounds/tick.wav";
	const auto HIT_SOUND = "./assets/sounds/hit.wav";
	const auto WIN_SOUND = "./assets/sounds/win.wav";
#pragma endregion
}