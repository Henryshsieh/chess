#pragma once
class Viewer
{
public:
	void drawTarget();
	void movePicture(Board&);
	void movePicture(Board&, Position, Player);
	void Display();
	void showcheck();
	sf::RenderWindow window;
	Viewer();
protected:
private:
	Board board;
	sf::Texture texture;
	sf::Texture checktexture;
	sf::Texture transparent;
	sf::Texture target_texture;
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

	sf::Sprite check;
	sf::Sprite target[64];
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
};
void Viewer::showcheck()
{
	check.setPosition(400, 400);
	for (int i = 0 ; i < 8000;i++)
	{
		window.draw(check);
		window.display();
		//Display();
	}
}
Viewer::Viewer()
{
	window.create(sf::VideoMode(900, 900), "SFML Window");
	if (!texture.loadFromFile("board.png"))
		std::cout << "Error loading file" << std::endl;
	if (!target_texture.loadFromFile("target.png"))
		std::cout << "Error loading file" << std::endl;
	for (int i = 0; i < 64; i++)
	{
		target[i] = sf::Sprite(target_texture);

	}
	sprite.setTexture(texture);
	if (!transparent.loadFromFile("transparent.png"))
	{
		std::cout << "Error loading file" << std::endl;
	}
	if (!whiterook_texture.loadFromFile("check.png"))
		std::cout << "Error loading file" << std::endl;
	if (!whiterook_texture.loadFromFile("whiterook.png"))
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


	check= sf::Sprite(checktexture);
	white_rook[0] = sf::Sprite(whiterook_texture);
	white_rook[1] = sf::Sprite(whiterook_texture);

	black_rook[0] = sf::Sprite(blackrook_texture);
	black_rook[1] = sf::Sprite(blackrook_texture);


	white_knight[0] = sf::Sprite(whiteknight_texture);
	white_knight[1] = sf::Sprite(whiteknight_texture);

	black_knight[0] = sf::Sprite(blackknight_texture);
	black_knight[1] = sf::Sprite(blackknight_texture);

	white_bishop[0] = sf::Sprite(whitebishop_texture);
	white_bishop[1] = sf::Sprite(whitebishop_texture);

	black_bishop[0] = sf::Sprite(blackbishop_texture);
	black_bishop[1] = sf::Sprite(blackbishop_texture);

	white_king = sf::Sprite(whiteking_texture);

	black_king = sf::Sprite(blackking_texture);

	white_queen = sf::Sprite(whitequeen_texture);

	black_queen = sf::Sprite(blackqueen_texture);
	for (int i = 0; i < 8; i++)
	{
		white_pawn[i] = sf::Sprite(whitepawn_texture);
	}

	for (int i = 0; i < 8; i++)
	{
		black_pawn[i] = sf::Sprite(blackpawn_texture);
	}


	movePicture(board);
}

void Viewer::Display()
{

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
	drawTarget();
	window.display();
}
void Viewer::drawTarget()
{
	for (int i = 0; i < 64; i++)
	{
		window.draw(target[i]);
	}

}


void Viewer::movePicture(Board& board, Position p, Player player)
{
	Board temp = board;
	int index = 0;
	int used[64];
	for (int i = 0; i < 64; i++)
	{
		used[i] = 0;
	}
	for (int i = 0; i < BOARDLEN; i++)
	{
		for (int j = 0; j < BOARDLEN; j++)
		{
			for (auto element : board.board[p.x][p.y].attack)
			{
				if (i == element.x && j == element.y && board.board[i][j].camp != player.camp && board.board[i][j].pieceId != null)
				{
					target[index].setPosition(j * 112.5f, i * 112.5f);
					used[index++] = true;
					cout << endl << i << j << endl;
				}
			}
			for (auto element : board.board[p.x][p.y].availablemove)
			{

				if (i == element.x && j == element.y)
				{
					target[index].setPosition(j * 112.5f, i * 112.5f);
					used[index++] = true;
					cout << endl << i << j << endl;
				}
			}
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
	for (int i = 0; i < 64; i++)
	{
		if (!used[i])
		{
			target[i].setTexture(transparent);
		}
		else
		{
			target[i].setTexture(target_texture);

		}
	}
	
}


void Viewer::movePicture(Board& board)
{
	for (int i = 0; i < 64; i++)
	{
		target[i].setTexture(transparent);
	}
	for (int i = 0; i < 2; i++)
	{
		white_queen.setTexture(transparent);
		white_knight[i].setTexture(transparent);
		white_rook[i].setTexture(transparent);
		white_bishop[i].setTexture(transparent);
		white_king.setTexture(transparent);

		black_queen.setTexture(transparent);
		black_knight[i].setTexture(transparent);
		black_rook[i].setTexture(transparent);
		black_bishop[i].setTexture(transparent);
		black_king.setTexture(transparent);
	}
	for (int i = 0; i < 8; i++)
	{
		black_pawn[i].setTexture(transparent);
		white_pawn[i].setTexture(transparent);
	}
	for (int i = 0; i < BOARDLEN; i++)
	{
		for (int j = 0; j < BOARDLEN; j++)
		{

			if (board.board[i][j].pieceId == PAWN && board.board[i][j].camp == 0)
			{
				white_pawn[board.board[i][j].pieceIndex].setTexture(whitepawn_texture);
				white_pawn[board.board[i][j].pieceIndex].setPosition(j * 112.5f, i * 112.5f);
			}
			if (board.board[i][j].pieceId == PAWN && board.board[i][j].camp == 1)
			{
				black_pawn[board.board[i][j].pieceIndex].setTexture(blackpawn_texture);
				black_pawn[board.board[i][j].pieceIndex].setPosition(j * 112.5f, i * 112.5f);
			}
			if (board.board[i][j].pieceId == ROOK && board.board[i][j].camp == 0)
			{
				white_rook[board.board[i][j].pieceIndex].setTexture(whiterook_texture);
				white_rook[board.board[i][j].pieceIndex].setPosition(j * 112.5f, i * 112.5f);
			}
			if (board.board[i][j].pieceId == ROOK && board.board[i][j].camp == 1)
			{
				black_rook[board.board[i][j].pieceIndex].setTexture(blackrook_texture);
				black_rook[board.board[i][j].pieceIndex].setPosition(j * 112.5f, i * 112.5f);
			}
			if (board.board[i][j].pieceId == KNIGHT && board.board[i][j].camp == 0)
			{
				white_knight[board.board[i][j].pieceIndex].setTexture(whiteknight_texture);
				white_knight[board.board[i][j].pieceIndex].setPosition(j * 112.5f, i * 112.5f);
			}
			if (board.board[i][j].pieceId == KNIGHT && board.board[i][j].camp == 1)
			{
				black_knight[board.board[i][j].pieceIndex].setTexture(blackknight_texture);
				black_knight[board.board[i][j].pieceIndex].setPosition(j * 112.5f, i * 112.5f);
			}
			if (board.board[i][j].pieceId == BISHOP && board.board[i][j].camp == 0)
			{
				white_bishop[board.board[i][j].pieceIndex].setTexture(whitebishop_texture);
				white_bishop[board.board[i][j].pieceIndex].setPosition(j * 112.5f, i * 112.5f);
			}
			if (board.board[i][j].pieceId == BISHOP && board.board[i][j].camp == 1)
			{
				black_bishop[board.board[i][j].pieceIndex].setTexture(blackbishop_texture);
				black_bishop[board.board[i][j].pieceIndex].setPosition(j * 112.5f, i * 112.5f);
			}

			if (board.board[i][j].pieceId == KING && board.board[i][j].camp == 0)
			{
				white_king.setTexture(whiteking_texture);
				white_king.setPosition(j * 112.5f, i * 112.5f);
			}
			if (board.board[i][j].pieceId == KING && board.board[i][j].camp == 1)
			{
				black_king.setTexture(blackking_texture);
				black_king.setPosition(j * 112.5f, i * 112.5f);
			}

			if (board.board[i][j].pieceId == QUEEN && board.board[i][j].camp == 0)
			{
				white_queen.setTexture(whitequeen_texture);
				white_queen.setPosition(j * 112.5f, i * 112.5f);
				Display();
			}
			if (board.board[i][j].pieceId == QUEEN && board.board[i][j].camp == 1)
			{
				black_queen.setTexture(blackqueen_texture);
				black_queen.setPosition(j * 112.5f, i * 112.5f);
			}
		}
	}

}