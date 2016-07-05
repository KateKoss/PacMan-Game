#include <SFML/Graphics.hpp>
using namespace sf;

const int H = 22;
const int W = 19;
//0 - стенка
String TileMap[H] = {
	"0000000000000000000",
	"0        0        0",
	"0 00 000 0 000 00 0",
	"0 00 000 0 000 00 0",
	"0                 0",
	"0 00 0 00000 0 00 0",
	"0    0   0   0    0",
	"0000 000 0 000 0000",
	"0000 0       0 0000",
	"0000 0 00000 0 0000",
	"0      00000      0",
	"0000 0 00000 0 0000",
	"0000 0       0 0000",
	"0000 0 00000 0 0000",
	"0        0        0",
	"0 00 000 0 000 00 0",
	"0  0           0  0",
	"00 0 0 00000 0 0 00",
	"0    0   0   0    0",
	"0 000000 0 000000 0",
	"0                 0",
	"0000000000000000000",
};


struct TileSize
{
	int width = 16;
	int height = 16;
};

struct PlayerSize
{
	int width = 12;
	int height = 15;
};

TileSize ts;
PlayerSize ps;

float dx = 0.1, dy = 0.1; 
//координати персонажа
float X = 17, Y = 17;

float currentFrame = 0;

void Collision(int dir)
{
	
	if ((Y / ts.height) > 0 && (X / ts.width) > 0)
	{
		for (int i = Y / ts.height; i < (Y + ps.height) / ts.height; i++)
			for (int j = X / ts.width; j < (X + ps.width) / ts.width; j++)
			{
				if (TileMap[i][j] == '0')
				{
					if (dx > 0 && dir == 0)
						X = j * ts.width - ps.width;

					if (dx < 0 && dir == 0)
						X = j * ts.width + ts.width;						

					if (dy > 0 && dir == 1)
					{
						Y = i * ts.height - ps.height;
						dy = 0;
					}
					if (dy < 0 && dir == 1)
					{
						Y = i * ts.height + ts.height;
						dy = 0;
					}
				}
				if (TileMap[i][j] == ' ')
				{
					TileMap[i][j] = 'e';
				}

			}
	}
}
Sprite heroSprite;
void update(float time)
{
	X += dx*time;
	Collision(0);

	Y += dy*time;
	Collision(1);
	
	if ((Y / ts.height) > 0 && (X / ts.width) > 0)
	heroSprite.setPosition(X, Y);
	dx = 0;
}

int main()
{
	RenderWindow window(sf::VideoMode(W*ts.width, H*ts.height), "PacMan"); //,Style::Fullscreen
	Image heroImage;
	heroImage.loadFromFile("images/Pac_Man_Sprites.png");
	
	Texture heroTexture;
	heroTexture.loadFromImage(heroImage);

	Texture t;
	t.loadFromFile("images/Map.png");

	Sprite s;
	s.setTexture(t);
	s.setTextureRect(IntRect(0, 0, 304, 350));
	s.setPosition(0, 4);
	
	heroSprite.setTexture(heroTexture);
	heroSprite.setTextureRect(IntRect(455, 0, 12, 15));
	heroSprite.setPosition(X, Y);
	
	//Hello Kate
	Clock clock;

	RectangleShape rectangle(Vector2f(ts.width, ts.height));

	float currentFrame = 0;

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}
		
		float time = clock.getElapsedTime().asMicroseconds(); //дать прошедшее время в микросекундах
		clock.restart(); //перезагружает время
		time /= 600; //скорость игры(чем меньше число - тем быстрее)

		if (Keyboard::isKeyPressed(Keyboard::Left))
		{
			currentFrame += 0.005*time; //служит для прохождения по "кадрам". переменная доходит до двухх суммируя произведение времени и скорости. изменив 0.005 можно изменить скорость анимации
			if (currentFrame > 0 && currentFrame <= 1)
			{
				//heroSprite.move(-0.1 * time, 0);
				heroSprite.setTextureRect(IntRect(460, 16, 12, 15));				
			}
			else if (currentFrame > 1 && currentFrame <= 2)
			{
				//heroSprite.move(-0.1 * time, 0);
				heroSprite.setTextureRect(IntRect(472, 16, 15, 15));				
			}
			else if (currentFrame > 2)
			{
				currentFrame -= 2; // если пришли к второму кадру - откидываемся назад.	
				//heroSprite.move(-0.1 * time, 0);
				heroSprite.setTextureRect(IntRect(460, 16, 12, 15));
			}
			dx = -0.1;
			dy = 0;
		}
		else if (Keyboard::isKeyPressed(Keyboard::Right))
		{
			currentFrame += 0.005*time; //служит для прохождения по "кадрам". переменная доходит до двухх суммируя произведение времени и скорости. изменив 0.005 можно изменить скорость анимации
			if (currentFrame > 0 && currentFrame <= 1)
			{
				//heroSprite.move(0.1 * time, 0);
				heroSprite.setTextureRect(IntRect(455, 0, 12, 15));
			}
			else if (currentFrame > 1 && currentFrame <= 2)
			{
				//heroSprite.move(0.1 * time, 0);
				heroSprite.setTextureRect(IntRect(473, 0, 15, 15));
			}
			else if (currentFrame > 2)
			{
				currentFrame -= 2; // если пришли к второму кадру - откидываемся назад.	
				//heroSprite.move(0.1 * time, 0);
				heroSprite.setTextureRect(IntRect(455 * int(currentFrame), 0, 12, 15));
			}
			dx = 0.1;
			dy = 0;
		}
		else if (Keyboard::isKeyPressed(Keyboard::Up))
		{
			currentFrame += 0.005*time;
			if (currentFrame > 0 && currentFrame <= 1)
			{
				//heroSprite.move(0, -0.1 * time);
				heroSprite.setTextureRect(IntRect(456, 36, 15, 12));
			}
			else if (currentFrame > 1 && currentFrame <= 2)
			{
				//heroSprite.move(0, -0.1 * time);
				heroSprite.setTextureRect(IntRect(473, 33, 15, 15));
			}
			else if (currentFrame > 2)
			{
				currentFrame -= 2;
				//heroSprite.move(0, -0.1 * time);
				heroSprite.setTextureRect(IntRect(456, 36, 15, 12));
			}
			dy = -0.1;
			dx = 0;
		}
		else if (Keyboard::isKeyPressed(Keyboard::Down))
		{
			currentFrame += 0.005*time;
			if (currentFrame > 0 && currentFrame <= 1)
			{
				//heroSprite.move(0, 0.1 * time);
				heroSprite.setTextureRect(IntRect(456, 48, 15, 12));
			}
			else if (currentFrame > 1 && currentFrame <= 2)
			{
				//heroSprite.move(0, 0.1 * time);
				heroSprite.setTextureRect(IntRect(473, 48, 15, 15));
			}
			else if (currentFrame > 2)
			{
				currentFrame -= 2;
				//heroSprite.move(0, 0.1 * time);
				heroSprite.setTextureRect(IntRect(456, 48, 15, 12));
			}
			dy = 0.1;
			dx = 0;
		}	
		//window.setIcon()
		window.clear(Color::Blue);

		for (int i = 0; i < H; i++)
		{
			for (int j = 0; j < W; j++)
			{
				if (TileMap[i][j] == '0')
					continue;
				if (TileMap[i][j] == ' ')
				{
					/*Texture t;
					t.loadFromFile("images/point.png");*/

					/*Sprite s;
					s.setTexture(t);
					s.setTextureRect(IntRect(0, 0, 8, 8));
					s.setPosition(24, 24);
					window.draw(s);*/
					rectangle.setFillColor(Color::Black);	
				}
					
				if (TileMap[i][j] == 'e')
					rectangle.setFillColor(Color::Black);

				rectangle.setPosition(j * ts.width, i * ts.height);
				window.draw(rectangle);
			}
		}
		
		update(time);
		//window.draw(s);
		window.draw(heroSprite);
		
		window.display();		
	}

	return 0;
}