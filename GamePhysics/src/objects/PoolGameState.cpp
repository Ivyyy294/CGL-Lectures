#include "PoolGameState.h"

bool PoolGameState::gameOver = false;
int PoolGameState::fullBallCounter = 0;
int PoolGameState::halfBallCounter = 0;
bool PoolGameState::fullBallTurn = true;

void PoolGameState::Reset()
{
	PoolGameState::gameOver = false;
	PoolGameState::fullBallCounter = 0;
	PoolGameState::halfBallCounter = 0;
	PoolGameState::fullBallTurn = true;
}
