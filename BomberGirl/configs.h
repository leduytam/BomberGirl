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
	const auto ZOMBIE_FONT_PATH = "./assets/fonts/zombiecontrol.ttf";

#pragma endregion

////////////////////////////
#pragma region Intro
	const auto INTRO_SCREEN_TIME = 1.f;
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
	const auto ABOUT_BACKGROUND_PATH = "./assets/textures/backgrounds/about_background.png";
#pragma endregion

#pragma region Game
	const auto PLAYER_SHADOW_PATH = "./assets/textures/players/shadow.png";
	const auto PLAYER_MOVEMENT_TEXTURE_PATH = "./assets/textures/players/movements/";
	const auto BACKGROUND_TILESETS_PATH = "./assets/textures/tilesets/Dungeon_A5.png";
	const auto MAP_BACKGROUND_TEXTURE_PATH = "./assets/textures/backgrounds/map_background.png";
	const auto BOMB_TEXTURE_PATH = "./assets/textures/bomb/bomb.png";
	const auto TILE_SIZE = 48;
	const auto WORLD_WIDTH = 720;
	const auto WORLD_HEIGHT = 720;
	const auto PLAYER_DEFAULT_SPEED = 150.f;
	const auto TIME_RAY_EXIST = 1.f;
	const auto CRATE_PATH = "./assets/textures/tilesets/crate.png";
#pragma endregion
}