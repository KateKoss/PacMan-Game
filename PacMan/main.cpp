#include <SFML/Graphics.hpp>
#include <stdio.h>

using namespace sf;

const int H = 22;//ечеек в памяти для карты
const int W = 19;

Sprite heroSprite;

//0 - стенка
//E - еда
//W - большие точки
String TileMap[H] = {
	"0000000000000000000",
	"0EEEEEEEE0EEEEEEEE0",
	"0E00E000E0E000E00E0",
	"0W00E000E0E000E00W0",
	"0EEEEEEEEEEEEEEEEE0",
	"0E00E0E00000E0E00E0",
	"0EEEE0EEE0EEE0EEEE0",
	"0000E000 0 000E0000",
	"0000E0       0E0000",
	"0000E0 00000 0E0000",
	"0   E  00000  E   0",
	"0000E0 00000 0E0000",
	"0000E0       0E0000",
	"0000E0 00000 0E0000",
	"0EEEEEEEE0EEEEEEEE0",
	"0E00E000E0E000E00E0",
	"0WE0EEEEE EEEEE0EW0",
	"00E0E0E00000E0E0E00",
	"0EEEE0EEE0EEE0EEEE0",
	"0E000000E0E000000E0",
	"0EEEEEEEEEEEEEEEEE0",
	"0000000000000000000",
};

//структура параметров плитки
struct TileSize
{
	int width = 16;
	int height = 16;
};

//структура параметров героя
struct PlayerSize
{
	int width = 12;
	int height = 15;
};

TileSize ts;
PlayerSize ps;

//скорость персонажа
float dx = 0.1, dy = 0.1; 

//координати персонажа
float X = 17, Y = 17;

//текущий спрайт
float currentFrame = 0;

//функция столкновения со стенкой
void Collision(int dir)
{	
	if ((Y / ts.height) > 0 && (X / ts.width) > 0)//если герой в границах карты
	{
		for (int i = Y / ts.height; i < (Y + ps.height) / ts.height; i++) //для всех ближайших клеточек
			for (int j = X / ts.width; j < (X + ps.width) / ts.width; j++)
			{
				if (TileMap[i][j] == '0') //если клеточка - это стенка
				{
					//если движется по Х
					if (dx > 0 && dir == 0)
					{
						X = j * ts.width - ps.width; //если герой нактнулся на стенку, отодвигаем его 
						dx = 0;//и продолжаем двигатся по У
					}

					if (dx < 0 && dir == 0)
					{
						X = j * ts.width + ts.width;
						dx = 0;
					}

					//если движется по У
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
				//если герой прошел по коридору или сьел еду
				if (TileMap[i][j] == ' ' || TileMap[i][j] == 'E' || TileMap[i][j] == 'W')
				{
					TileMap[i][j] = 'e';//меняем обозначение на "е" - означает что он прошел этот путь
				}
			}
	}
}

void update(float time)//отвечает за обновление при движении персонажа
{
	//координата расположения персонажа = скорость * время
	X += dx*time;
	Collision(0);
	
	Y += dy*time;
	Collision(1);
	
	//если координаты в границах карты
	if ((Y / ts.height) > 0 && (X / ts.width) > 0)
		heroSprite.setPosition(X, Y);//то определяем эти координаты как место нахождения героя

	dx = 0; //натыкаясь на стенку продолжает двигатся самостоятельно вертикально
}

//функцыя проверки не выиграл ли герой еще?
bool finish()
{
	for (int i = 0; i < H; i++)
		for (int j = 0; j < W; j++)
		{
			if (TileMap[i][j] == 'E')//если на карте осталась хоть одна точка
			{
				return false;
				break;//прекаращаем проверку и продолжаем игру
			}
		}
	return true;
}

int main()
{
	RenderWindow window(sf::VideoMode(W*ts.width, H*ts.height), "PacMan"); //Style::Fullscreen

	//картинка героя
	Image heroImage;
	heroImage.loadFromFile("images/Pac_Man_Sprites.png");

	//текстура героя
	Texture heroTexture;
	heroTexture.loadFromImage(heroImage);

	//текстура карти
	Texture t;
	t.loadFromFile("images/Map.png");

	//текстура точки
	Texture point;
	point.loadFromFile("images/point.png");

	//текстура большой точки
	Texture bigPoint;
	bigPoint.loadFromFile("images/bigPoint.png");

	//текстура заставки "Победы"
	Texture win;
	win.loadFromFile("images/win.png");

	//текстура заставки "Проиграша"
	Texture gameOver;
	gameOver.loadFromFile("images/win.png");

	//спрайт карти
	Sprite s;
	s.setTexture(t);
	s.setTextureRect(IntRect(0, 0, 304, 350));
	s.setPosition(0, 4);
	
	//спрайт маленькой точечки
	Sprite eat;
	eat.setTexture(point);
	eat.setTextureRect(IntRect(0, 0, 8, 8));
	
	//спрайт большой точечки
	Sprite bigEat;
	bigEat.setTexture(bigPoint);
	bigEat.setTextureRect(IntRect(0, 0, 8, 8));

	//спрайт конца игры
	Sprite TheEnd;	

	//спрайт героя
	heroSprite.setTexture(heroTexture);
	heroSprite.setTextureRect(IntRect(455, 0, 12, 15));
	heroSprite.setPosition(X, Y);

	Clock clock;

	RectangleShape rectangle(Vector2f(ts.width, ts.height));

	//float currentFrame = 0;

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
				heroSprite.setTextureRect(IntRect(460, 16, 12, 15));				
			}
			else if (currentFrame > 1 && currentFrame <= 2)
			{
				heroSprite.setTextureRect(IntRect(472, 16, 15, 15));				
			}
			else if (currentFrame > 2)
			{
				currentFrame -= 2; // если пришли к второму кадру - откидываемся назад.					
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
				heroSprite.setTextureRect(IntRect(455, 0, 12, 15));
			}
			else if (currentFrame > 1 && currentFrame <= 2)
			{
				heroSprite.setTextureRect(IntRect(473, 0, 15, 15));
			}
			else if (currentFrame > 2)
			{
				currentFrame -= 2; // если пришли к второму кадру - откидываемся назад.				
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
				heroSprite.setTextureRect(IntRect(456, 36, 15, 12));
			}
			else if (currentFrame > 1 && currentFrame <= 2)
			{
				heroSprite.setTextureRect(IntRect(473, 33, 15, 15));
			}
			else if (currentFrame > 2)
			{
				currentFrame -= 2;				
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
				heroSprite.setTextureRect(IntRect(456, 48, 15, 12));
			}
			else if (currentFrame > 1 && currentFrame <= 2)
			{				
				heroSprite.setTextureRect(IntRect(473, 48, 15, 15));
			}
			else if (currentFrame > 2)
			{
				currentFrame -= 2;				
				heroSprite.setTextureRect(IntRect(456, 48, 15, 12));
			}
			dy = 0.1;
			dx = 0;
		}	
		
		window.clear(Color::Blue);

		//отрисовка карты
		for (int i = 0; i < H; i++)
		{
			for (int j = 0; j < W; j++)
			{
				if (TileMap[i][j] == '0')
					continue;
				if (TileMap[i][j] == ' ')
				{							
					rectangle.setFillColor(Color::Black);	
				}				

				if (TileMap[i][j] == 'e')
					rectangle.setFillColor(Color::Black);

				//сначала рисуем карту
				rectangle.setPosition(j * ts.width, i * ts.height);
				window.draw(rectangle);

				//потом саму еду
				if (TileMap[i][j] == 'E')
				{
					eat.setPosition(j * ts.width + ts.width / 4, i * ts.height + ts.height / 4);					
					window.draw(eat);
				}				

				if (TileMap[i][j] == 'W')
				{
					bigEat.setPosition(j * ts.width + ts.width / 4, i * ts.height + ts.height / 4);
					window.draw(bigEat);
				}
			}
		}		

		update(time);
		//window.draw(s); //если разкомментить будет добавлена карта
		window.draw(heroSprite);//рисуем героя
				
		if (finish())//проверяем не выграл ли герой?
		{
			//рисуем спрайт выиграша
			TheEnd.setTexture(win);
			TheEnd.setTextureRect(IntRect(0, 0, W*ts.width, H*ts.height));			
			window.draw(TheEnd);

			//выводим текст
			Font font;
			font.loadFromFile("CyrilicOld.ttf");
			Text txt;
			txt.setPosition(W*ts.width/8, H*ts.height/2);			
			txt.setFont(font);
			txt.setColor(Color::White);
			txt.setString(L"Press space bar\n to finish game.");			
			window.draw(txt);

			//если пользователь нажал кнопку закрываем игру
			if (Keyboard::isKeyPressed(Keyboard::Space))
				window.close();
		}

		window.display(); //отображаем все
	}

	return 0;
}