#pragma once
#include <conio.h>
#include <iostream>
#include <iomanip>
#include "board.h"
#define BOARDLEN 8
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
using namespace std;

class Player
{
public:
	Player();
	Player(int, Board&);
	bool OnMove(Board&, Position&, Position&);
	void OnPromote(Board& board);
	bool islegalPosition(Position);
	Position findKing(Board&);
	int camp;
};

Player::Player()
{
	camp = 0;
}
Player::Player(int c, Board& board)
{

	camp = c;
	
	
}
bool Player::OnMove(Board& board, Position& start, Position& end)
{
	if (!islegalPosition(start) || !islegalPosition(end))
		return 0;
	piece backup_chosen = board.board[start.x][start.y];
	piece& chosen = board.board[start.x][start.y];
	piece backup_destination = board.board[end.x][end.y];
	piece& destination = board.board[end.x][end.y];
	
	if (destination.camp == chosen.camp && (destination.pieceId == ROOK && chosen.pieceId == KING) && chosen.camp == camp)
	{
		piece tmp = chosen;
		chosen = destination;
		destination = tmp;
		destination._position = end;
		chosen._position = start;
		destination.moved = 1;
		chosen.moved = 1;
		board.setAvailablePath();
		return 1;
	}
	if (camp == destination.camp || chosen.camp != camp || (start.x == end.x && start.y == end.y))//end cant be alley, start cant be enemy
		return 0;
	for (auto element : chosen.availablemove)
	{
		if (end.x == element.x && end.y == element.y)
		{
			destination = chosen;
			destination._position = end;
			destination.moved = true;
			chosen = piece();
			board.setAvailablePath();
			board.setAvailablePath();
			if (board.isThreatened(findKing(board), camp))
			{
				cout << "protect the king!\n";
				destination = backup_destination;
				chosen = backup_chosen;
				return 0;
			}
			return 1;
		}
	}
	for (auto element : chosen.attack)
	{
		if (end.x == element.x && end.y == element.y && destination.pieceId != null && destination.camp != camp)
		{
			destination = chosen;
			destination._position = end;
			destination.moved = true;
			chosen = piece();
			board.setAvailablePath();
			board.setAvailablePath();
			if (board.isThreatened(findKing(board), camp))
			{
				cout << "protect the king!\n";
				destination = backup_destination;
				chosen = backup_chosen;
				return 0;
			}
			return 1;

		}
	}
	board.print();

	return 0;
}
void Player::OnPromote(Board& board)
{
	int side = (camp == 0) ? 0 : 7;
	for (int i = 0; i < BOARDLEN; i++)
	{
		if (board.board[side][i].pieceId == 6) {
			char promoteType;
			cout << "Select promotion type('q'ueen, 'r'ook, 'b'ishop or 'k'night):";
			cin >> promoteType;
			while (true) {
				if (promoteType == 'q' || promoteType == 'Q') {
					board.board[side][i].pieceId = QUEEN;
					board.board[side][i].camp = camp;
					board.board[side][i].promotePiece = 1;
					break;
				}
				else if (promoteType == 'r' || promoteType == 'R') {
					board.board[side][i].pieceId = ROOK;
					board.board[side][i].camp = camp;
					board.board[side][i].promotePiece = 1;

					break;
				}
				else if (promoteType == 'b' || promoteType == 'B') {
					board.board[side][i].pieceId = BISHOP;
					board.board[side][i].promotePiece = 1;
					board.board[side][i].camp = camp;
					break;
				}
				else if (promoteType == 'k' || promoteType == 'K') {
					board.board[side][i].pieceId = KNIGHT;
					board.board[side][i].promotePiece = 1;
					board.board[side][i].camp = camp;
					break;
				}
				else {
					cout << "Choose again:";
					cin >> promoteType;
				}
			}
			board.print(board.board[side][i]._position);
		}
	}
	
}

bool Player::islegalPosition(Position p)
{
	if (p.x >= 0 && p.x < BOARDLEN && p.y >= 0 && p.y < BOARDLEN)
	{
		return 1;
	}
	return 0;
}
Position Player::findKing(Board& board)
{
	Position king;
	for (int i = 0; i < BOARDLEN; i++)
	{
		for (int j = 0; j < BOARDLEN; j++)
		{
			if (board.board[i][j].pieceId == KING && board.board[i][j].camp == camp)
				king = board.board[i][j]._position;
		}
	}
	return king;
}

