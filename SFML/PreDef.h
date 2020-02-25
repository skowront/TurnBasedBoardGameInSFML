#pragma once

//file contains predefined constants that are not loaded from config file or are defaults

#define WINDOWSIZEX 1200
#define WINDOWSIZEY 1000
#define MENUX 200

#define MAIN_BUTTONS_COUNT 4

#define BTNTYPESCOUNT 6
#define FIELDCOUNT 10

#define EXQUIT 0
#define EXNULLPTR 1


#pragma region Paths
#define CONFIG_PATH "config.ini"
#pragma endregion

//BUTTON DEFAULTS
#define BUTTON_SIZE_DEF 120
//~BUTTON DEFAULTS

//UNIT DEFAULTS
#define	UNIT_POWER 1

#define UNIT_SIZE_DEF 30
//~UNIT DEFAULTS

//FIELD DEFAULTS
#define BRD_OFFSET 190
#define FIELD_SIZE_DEF 40
//~FIELD DEFAULTS

//TURNBTN
#define TURNBTN_TITLE "End of turn"
#define RESULT_TITLE "RESULT:\n"
//~TURNBTN


//enum defining direction of adding structures
enum enumDownRight
{
	down = 0,
	right = 1
};


//enum defining names for players
enum enumTurn
{
	none_player = 0,
	player1 = 1,
	player2 = 2
};

//enum defining used indexes, so they could be distinguished
enum enumINDEX
{
	row_index = 0,
	column_index = 1,
	board_row_index = 2,
	board_column_index = 3,
};

