#pragma once
#include "Player.h"
#include <fstream>
#include "Viewer.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
class GameManager
{
public:
	GameManager();
	int run();
	bool isGameOver();
	void movePicture();
	void ProcessInput();
	void Display();
	Position start;
	Position end;
private:
	int check;
	Player players[2];
	int current_player;
	//Viewer viewer;
	Board board;
	sf::Texture texture;
	sf::Texture whitepawn_texture;
	sf::Texture blackpawn_texture;
	sf::Texture blackrook_texture;
	sf::Texture whiterook_texture;
	sf::Texture whiteknight_texture;
	sf::Texture blackbishop_texture;
	sf::Texture whiteking_texture;
	sf::Texture blackknight_texture;
	sf::Texture whitebishop_texture;
	sf::Texture blackqueen_texture;
	sf::Texture whitequeen_texture;
	sf::Texture blackking_texture;

	sf::Sprite white_pawn[8];
	sf::Sprite black_pawn[8];
	sf::Sprite sprite;
	sf::Sprite white_rook[2];
	sf::Sprite black_rook[2];
	sf::Sprite white_knight[2];
	sf::Sprite black_knight[2];

	sf::Sprite white_bishop[2];
	sf::Sprite black_bishop[2];

	sf::Sprite white_king;
	sf::Sprite black_king;
	sf::Sprite white_queen;
	sf::Sprite black_queen;
	sf::RenderWindow window;


};
void GameManager::Display()
{

	window.clear();
	window.draw(sprite);
	window.draw(white_rook[0]);
	window.draw(white_rook[1]);
	window.draw(black_rook[0]);
	window.draw(black_rook[1]);
	window.draw(white_knight[0]);
	window.draw(white_knight[1]);
	window.draw(black_knight[0]);
	window.draw(black_knight[1]);
	window.draw(white_bishop[0]);
	window.draw(white_bishop[1]);
	window.draw(black_bishop[0]);
	window.draw(black_bishop[1]);
	window.draw(white_king);
	window.draw(black_king);
	window.draw(white_queen);
	window.draw(black_queen);
	for (int i = 0; i < 8; i++)
	{
		window.draw(white_pawn[i]);
		window.draw(black_pawn[i]);
	}
	window.display();
}

void GameManager::ProcessInput()
{
	sf::Event event;
	Position p;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window.close();
	}

	if (event.type == sf::Event::MouseButtonPressed)
	{
		if (event.mouseButton.button == sf::Mouse::Left)
		{
			p.y = event.mouseButton.x / 112.5f;
			p.x = event.mouseButton.y / 112.5f;
			if (!check)
			{
				start = p;
				board.print(start);
			}
			else
			{
				end = p;
				if (players[current_player].OnMove(board, start, end))
				{
					current_player ^= 1;
					movePicture();
				}
			}
			cout<< p.x << " " << p.y << endl;
			check = check ^ 1;

		}
	}
	
}
void GameManager::movePicture()
{
	for (int i = 0 ; i < BOARDLEN ; i++)
	{
		for (int j = 0 ; j < BOARDLEN ; j++)
		{
			if (board.board[i][j].pieceId == PAWN && board.board[i][j].camp == 0)
			{
				white_pawn[board.board[i][j].pieceIndex].setPosition(j * 112.5f, i * 112.5f);
			}
			if (board.board[i][j].pieceId == PAWN && board.board[i][j].camp == 1)
			{
				black_pawn[board.board[i][j].pieceIndex].setPosition(j * 112.5f, i * 112.5f);
			}
			if (board.board[i][j].pieceId == ROOK && board.board[i][j].camp == 0)
			{
				white_rook[board.board[i][j].pieceIndex].setPosition(j * 112.5f, i * 112.5f);
			}
			if (board.board[i][j].pieceId == ROOK && board.board[i][j].camp == 1)
			{
				black_rook[board.board[i][j].pieceIndex].setPosition(j * 112.5f, i * 112.5f);
			}
			if (board.board[i][j].pieceId == KNIGHT && board.board[i][j].camp == 0)
			{
				white_knight[board.board[i][j].pieceIndex].setPosition(j * 112.5f, i * 112.5f);
			}
			if (board.board[i][j].pieceId == KNIGHT && board.board[i][j].camp == 1)
			{
				black_knight[board.board[i][j].pieceIndex].setPosition(j * 112.5f, i * 112.5f);
			}
			if (board.board[i][j].pieceId == BISHOP && board.board[i][j].camp == 0)
			{
				white_bishop[board.board[i][j].pieceIndex].setPosition(j * 112.5f, i * 112.5f);
			}
			if (board.board[i][j].pieceId == BISHOP && board.board[i][j].camp == 1)
			{
				black_bishop[board.board[i][j].pieceIndex].setPosition(j * 112.5f, i * 112.5f);
			}

			if (board.board[i][j].pieceId == KING && board.board[i][j].camp == 0)
			{
				white_king.setPosition(j * 112.5f, i * 112.5f);
			}
			if (board.board[i][j].pieceId == KING && board.board[i][j].camp == 1)
			{
				black_king.setPosition(j * 112.5f, i * 112.5f);
			}

			if (board.board[i][j].pieceId == QUEEN && board.board[i][j].camp == 0)
			{
				white_queen.setPosition(j * 112.5f, i * 112.5f);
			}
			if (board.board[i][j].pieceId == QUEEN && board.board[i][j].camp == 1)
			{
				black_queen.setPosition(j * 112.5f, i * 112.5f);
			}
		}
	}
}

int GameManager::run()
{
		
	bool check = 0;
	while (window.isOpen()) {

		ProcessInput();
		Display();
	}
	return 0;
}

GameManager::GameManager()
{
	check = 0;
	window.create(sf::VideoMode(900, 900), "SFML Window");
	board = Board();
	//viewer = Viewer();
	players[0] = Player(0, board);
	players[1] = Player(1, board);
	current_player = 0;
	start.x = 0;
	start.y = 0;
	end.x = 0;
	end.y = 0;

	if (!texture.loadFromFile("board.png"))
		std::cout << "Error loading file" << std::endl;

	sprite.setTexture(texture);

	if(!whiterook_texture.loadFromFile("whiterook.png"))
		std::cout << "Error loading file" << std::endl;
	if (!blackrook_texture.loadFromFile("blackrook.png"))
		std::cout << "Error loading file" << std::endl;
	if (!whiteknight_texture.loadFromFile("whiteknight.png"))
		std::cout << "Error loading file" << std::endl;
	if (!blackknight_texture.loadFromFile("blackknight.png"))
		std::cout << "Error loading file" << std::endl;
	if (!whitebishop_texture.loadFromFile("whitebishop.png"))
		std::cout << "Error loading file" << std::endl;
	if (!blackbishop_texture.loadFromFile("blackbishop.png"))
		std::cout << "Error loading file" << std::endl;
	if (!whiteking_texture.loadFromFile("whiteking.png"))
		std::cout << "Error loading file" << std::endl;
	if (!blackking_texture.loadFromFile("blackking.png"))
		std::cout << "Error loading file" << std::endl;
	if (!whitequeen_texture.loadFromFile("whitequeen.png"))
		std::cout << "Error loading file" << std::endl;
	if (!blackqueen_texture.loadFromFile("blackqueen.png"))
		std::cout << "Error loading file" << std::endl;
	if (!whitepawn_texture.loadFromFile("whitepawn.png"))
		std::cout << "Error loading file" << std::endl;
	if (!blackpawn_texture.loadFromFile("blackpawn.png"))
		std::cout << "Error loading file" << std::endl;


	white_rook[0] = sf::Sprite(whiterook_texture);
	white_rook[0].setPosition(sf::Vector2f(0.f, 800.f));
	white_rook[1] = sf::Sprite(whiterook_texture);
	white_rook[1].setPosition(sf::Vector2f(800.f, 800.f));

	black_rook[0] = sf::Sprite(blackrook_texture);
	black_rook[0].setPosition(sf::Vector2f(0.f, 0.f));
	black_rook[1] = sf::Sprite(blackrook_texture);
	black_rook[1].setPosition(sf::Vector2f(800.f, 0.f));


	white_knight[0] = sf::Sprite(whiteknight_texture);
	white_knight[0].setPosition(sf::Vector2f(112.f, 800.f));
	white_knight[1] = sf::Sprite(whiteknight_texture);
	white_knight[1].setPosition(sf::Vector2f(676.f, 800.f));

	black_knight[0] = sf::Sprite(blackknight_texture);
	black_knight[0].setPosition(sf::Vector2f(112.f, 0.f));
	black_knight[1] = sf::Sprite(blackknight_texture);
	black_knight[1].setPosition(sf::Vector2f(676.f, 0.f));

	white_bishop[0] = sf::Sprite(whitebishop_texture);
	white_bishop[0].setPosition(sf::Vector2f(224.f, 800.f));
	white_bishop[1] = sf::Sprite(whitebishop_texture);
	white_bishop[1].setPosition(sf::Vector2f(564.f, 800.f));

	black_bishop[0] = sf::Sprite(blackbishop_texture);
	black_bishop[0].setPosition(sf::Vector2f(224.f, 0.f));
	black_bishop[1] = sf::Sprite(blackbishop_texture);
	black_bishop[1].setPosition(sf::Vector2f(564.f, 0.f));

	white_king = sf::Sprite(whiteking_texture);
	white_king.setPosition(sf::Vector2f(448.f, 800.f));

	black_king = sf::Sprite(blackking_texture);
	black_king.setPosition(sf::Vector2f(448.f, 0.f));

	white_queen = sf::Sprite(whitequeen_texture);
	white_queen.setPosition(sf::Vector2f(336.f, 800.f));

	black_queen = sf::Sprite(blackqueen_texture);
	black_queen.setPosition(sf::Vector2f(336.f, 0.f));
	for (int i = 0; i < 8; i++)
	{
		white_pawn[i] = sf::Sprite(whitepawn_texture);
		white_pawn[i].setPosition(sf::Vector2f(0 + i * 112, 688.f));
	}

	for (int i = 0; i < 8; i++)
	{
		black_pawn[i] = sf::Sprite(blackpawn_texture);
		black_pawn[i].setPosition(sf::Vector2f(0 + i * 112, 112.f));
	}



}




bool GameManager::isGameOver()
{
	Board temp = board;
	for (int i = 0; i < 2; i++)
	{
		if (!players[i].isThreatened(board, players[i].findKing(board)))
			break;
		for (int j = 0; j < BOARDLEN; j++)
		{
			for (int k = 0; k < BOARDLEN; k++)
			{
				if (board.board[j][k].camp == players[i].camp)
				{
					for (auto element : board.board[j][k].availablemove)
					{
						if (players[current_player].OnMove(temp, temp.board[j][k]._position, element))
						{
							if (!players[i].isThreatened(temp, players[i].findKing(board)))
								return 0;
							temp = board;
						}
					}
				}
			}
		}
	}
	return 1;

}
 