#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;

const int H = 22;//22 19
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
	int width = 12;//12
	int height = 15;//15
};

TileSize ts;
PlayerSize ps;

float dx = 0.1, dy = 0.1; 
float X = 17, Y = 17;	//координати персонажа

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
					//если dir == 0 то мы двигаемся по оси 0Х
					if (dx > 0 && dir == 0)		
						X = j * ts.width - ps.width;

					if (dx < 0 && dir == 0)
						X = j * ts.width + ts.width;						

					//если dir == 1 то мы двигаемся по оси 0Х
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

int main(int argc, char *argv[])
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
	heroSprite.setTextureRect(IntRect(455, 0, ps.width, ps.height));
	heroSprite.setPosition(X, Y);
	
	Texture mapTexture;
	mapTexture.loadFromFile("images/Pac_Man_Sprites1.png");
	Sprite mapSprite;	
	mapSprite.setTexture(mapTexture);
	mapSprite.setTextureRect(IntRect(614, 20, 16, 16));//607, 21, 16, 16//ts.width, ts.height
	
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
				heroSprite.setTextureRect(IntRect(461, 17, 9, 13));				
			}
			else if (currentFrame > 1 && currentFrame <= 2)
			{
				heroSprite.setTextureRect(IntRect(474, 17, 13, 13));				
			}
			else if (currentFrame > 2)
			{
				currentFrame -= 2; // если пришли к второму кадру - откидываемся назад.	
				heroSprite.setTextureRect(IntRect(461, 17, 9, 13));
			}
			dx = -0.1;
			dy = 0;
		}
		else if (Keyboard::isKeyPressed(Keyboard::Right))
		{
			currentFrame += 0.005*time; //служит для прохождения по "кадрам". переменная доходит до двухх суммируя произведение времени и скорости. изменив 0.005 можно изменить скорость анимации
			if (currentFrame > 0 && currentFrame <= 1)
			{
				heroSprite.setTextureRect(IntRect(457, 1, 9, 13));
			}
			else if (currentFrame > 1 && currentFrame <= 2)
			{
				heroSprite.setTextureRect(IntRect(472, 1, 13, 13));
			}
			else if (currentFrame > 2)
			{
				currentFrame -= 2; // если пришли к второму кадру - откидываемся назад.	
				heroSprite.setTextureRect(IntRect(457, 1, 9, 13));
			}
			dx = 0.1;
			dy = 0;
		}
		else if (Keyboard::isKeyPressed(Keyboard::Up))
		{
			currentFrame += 0.005*time;
			if (currentFrame > 0 && currentFrame <= 1)
			{
				heroSprite.setTextureRect(IntRect(457, 37, 13, 9));
			}
			else if (currentFrame > 1 && currentFrame <= 2)
			{
				heroSprite.setTextureRect(IntRect(473, 34, 13, 13));
			}
			else if (currentFrame > 2)
			{
				currentFrame -= 2;
				heroSprite.setTextureRect(IntRect(457, 37, 13, 9));
			}
			dy = -0.1;
			dx = 0;
		}
		else if (Keyboard::isKeyPressed(Keyboard::Down))
		{
			currentFrame += 0.005*time;
			if (currentFrame > 0 && currentFrame <= 1)
			{
				heroSprite.setTextureRect(IntRect(457, 49, 13, 9));
			}
			else if (currentFrame > 1 && currentFrame <= 2)
			{
				heroSprite.setTextureRect(IntRect(473, 49, 13, 13));
			}
			else if (currentFrame > 2)
			{
				currentFrame -= 2;
				heroSprite.setTextureRect(IntRect(457, 49, 13, 9));
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
				{
					mapSprite.setPosition(j * ts.width, i * ts.width);
					window.draw(mapSprite);
					continue;
				}
				if (TileMap[i][j] == ' ')
				{
					rectangle.setFillColor(Color::Black);	
				}
					
				if (TileMap[i][j] == 'e')
				{
					rectangle.setFillColor(Color::Black);
				}
				rectangle.setPosition(j * ts.width, i * ts.height);
				window.draw(rectangle);
			}
		}
		
		update(time);
		//window.draw(s); //если убрать комментарии наложится карта
		window.draw(heroSprite);
		
		window.display();		
	}

	return 0;
}