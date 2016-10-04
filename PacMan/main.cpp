#include <SFML/Graphics.hpp>
#include <stdio.h>

using namespace sf;

const int H = 22;//����� � ������ ��� �����
const int W = 19;

Sprite heroSprite;

//0 - ������
//E - ���
//W - ������� �����
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

//��������� ���������� ������
struct TileSize
{
	int width = 16;
	int height = 16;
};

//��������� ���������� �����
struct PlayerSize
{
	int width = 12;
	int height = 15;
};

TileSize ts;
PlayerSize ps;

//�������� ���������
float dx = 0.1, dy = 0.1; 

//���������� ���������
float X = 17, Y = 17;

//������� ������
float currentFrame = 0;

class Enemy
{
private:
	float dxEnemy, dyEnemy;
	float XEnemy, YEnemy;	//���������� �����
	float currentFrameEnemy;
	bool alive;
public:
	Sprite enemySprite;
	Enemy(Texture &enemyTexture, int X, int Y) //�������� � ��������� ���������� �������� ����� �� �����
	{
		XEnemy = X;
		YEnemy = Y;
		enemySprite.setTexture(enemyTexture);//��������� �������� � ������
		enemySprite.setTextureRect(IntRect(457,65,13,13)); //�������� �������� ����� �� ��������
		enemySprite.setPosition(X, Y);//������������� ��������� ��������� ����� �� �����
		currentFrameEnemy = dxEnemy = dyEnemy = 0;
	};
	void update(float time)
	{
		findEnemyDirection();
		animationEnemy(time);
		XEnemy += dxEnemy*time;
		Collision(0);

		YEnemy += dyEnemy*time;
		Collision(1);
		
		if ((YEnemy / ts.height) > 0 && (XEnemy / ts.width) > 0)
		enemySprite.setPosition(XEnemy, YEnemy);
		dxEnemy = dyEnemy = 0;
	}
	void Collision(int dir)		//��������� ������������
	{
		if ((XEnemy / ts.width) > 0 && (YEnemy / ts.height) > 0)
		{
			for (int i = YEnemy / ts.height; i < (YEnemy + ps.height) / ts.height; i++)
			{
				for (int j = XEnemy / ts.width; j < (XEnemy + ps.width) / ts.width; j++)
				{
					if (TileMap[i][j] == '0')
					{
						if (dxEnemy > 0 && dir == 0)
							XEnemy = j * ts.width - ps.width;

						if (dxEnemy < 0 && dir == 0)
							XEnemy = j * ts.width + ts.width;

						//���� dir == 1 �� �� ��������� �� ��� 0�
						if (dyEnemy > 0 && dir == 1)
						{
							YEnemy = i * ts.height - ps.height;
							dyEnemy = 0;
						}
						if (dyEnemy < 0 && dir == 1)
						{
							YEnemy = i * ts.height + ts.height;
							dyEnemy = 0;
						}
					}
				}
			}
		}
	}
	void findEnemyDirection()	//����� ����������� �������� �����
	{
		if (X >= XEnemy)
		{
			if (Y < YEnemy)
			{
				if (X == XEnemy)
				{
					dyEnemy -= 0.1;//8
				}
				else
				{
					dxEnemy += 0.1;//4
					dyEnemy -= 0.1;
				}
			}
			else
			{
				if (X == XEnemy)
				{
					dyEnemy += 0.1;//6
				}
				else
				{
					dxEnemy += 0.1;
					dyEnemy += 0.1;//1
				}
			}
		}
		else
		{
			if (Y >= YEnemy)
			{
				if (Y == YEnemy)
				{
					dxEnemy -= 0.1; //7
				}
				else
				{
					dxEnemy -= 0.1;//2
					dyEnemy += 0.1;
				}
			}
			else
			{
				if (Y == YEnemy)
				{
					dxEnemy -= 0.1;//5
				}
				else
				{
					dxEnemy -= 0.1;//3
					dyEnemy -= 0.1;
				}
			}
		}
	}
	void animationEnemy(float time)
	{
		currentFrameEnemy += 0.005*time; //������ ��� ����������� �� "������". ���������� ������� �� ����� �������� ������������ ������� � ��������. ������� 0.005 ����� �������� �������� ��������
		if (currentFrameEnemy > 0 && currentFrameEnemy <= 1)
		{
			enemySprite.setTextureRect(IntRect(457, 65, 13, 13));
		}
		else if (currentFrameEnemy > 1 && currentFrameEnemy <= 2)
		{
			enemySprite.setTextureRect(IntRect(473, 65, 13, 13));
		}
		else if (currentFrameEnemy > 2 && currentFrameEnemy <= 3)
		{
			enemySprite.setTextureRect(IntRect(489, 65, 13, 13));
		}
		else if (currentFrameEnemy > 3 && currentFrameEnemy <= 4)
		{
			enemySprite.setTextureRect(IntRect(505, 65, 13, 13));
		}
		else if (currentFrameEnemy > 4 && currentFrameEnemy <= 5)
		{
			enemySprite.setTextureRect(IntRect(521, 65, 13, 13));
		}
		else if (currentFrameEnemy > 5 && currentFrameEnemy <= 6)
		{
			enemySprite.setTextureRect(IntRect(537, 65, 13, 13));
		}
		else if (currentFrameEnemy > 6 && currentFrameEnemy <= 7)
		{
			enemySprite.setTextureRect(IntRect(553, 65, 13, 13));
		}
		else if (currentFrameEnemy > 7 && currentFrameEnemy <= 8)
		{
			enemySprite.setTextureRect(IntRect(569, 65, 13, 13));
		}
		else if (currentFrameEnemy > 8)
		{
			currentFrameEnemy -= 8; // ���� ������ � ���������� ����� - ������������ �����.	
			enemySprite.setTextureRect(IntRect(457, 65, 13, 13));
		}
	}
};

void Collision(int dir)
{	
	if ((Y / ts.height) > 0 && (X / ts.width) > 0)//���� ����� � �������� �����
	{
		for (int i = Y / ts.height; i < (Y + ps.height) / ts.height; i++) //��� ���� ��������� ��������
			for (int j = X / ts.width; j < (X + ps.width) / ts.width; j++)
			{
				if (TileMap[i][j] == '0') //���� �������� - ��� ������
				{
					//���� �������� �� �
					if (dx > 0 && dir == 0)
					{
						X = j * ts.width - ps.width; //���� ����� ��������� �� ������, ���������� ��� 
						dx = 0;//� ���������� �������� �� �
					}

					if (dx < 0 && dir == 0)
					{
						X = j * ts.width + ts.width;
						dx = 0;
					}

					//���� �������� �� �
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
				//���� ����� ������ �� �������� ��� ���� ���
				if (TileMap[i][j] == ' ' || TileMap[i][j] == 'E' || TileMap[i][j] == 'W')
				{
					TileMap[i][j] = 'e';//������ ����������� �� "�" - �������� ��� �� ������ ���� ����
				}
			}
	}
}

void update(float time)//�������� �� ���������� ��� �������� ���������
{
	//���������� ������������ ��������� = �������� * �����
	X += dx*time;
	Collision(0);
	
	Y += dy*time;
	Collision(1);
	
	//���� ���������� � �������� �����
	if ((Y / ts.height) > 0 && (X / ts.width) > 0)
		heroSprite.setPosition(X, Y);
	//dx = 0;		//��� ����� �������� ��� ��������� ����� ������� ������� ��������
	//dy = 0;
}

//������� �������� �� ������� �� ����� ���?
bool finish()
{
	for (int i = 0; i < H; i++)
		for (int j = 0; j < W; j++)
		{
			if (TileMap[i][j] == 'E')//���� �� ����� �������� ���� ���� �����
			{
				return false;
				break;//����������� �������� � ���������� ����
			}
		}
	return true;
}

int main()
{
	RenderWindow window(sf::VideoMode(W*ts.width, H*ts.height), "PacMan"); //Style::Fullscreen

	//�������� �����
	Image heroImage;
	heroImage.loadFromFile("images/Pac_Man_Sprites.png");

	//�������� �����
	Texture heroTexture;
	heroTexture.loadFromImage(heroImage);

	//�������� �����
	Texture t;
	t.loadFromFile("images/Map.png");

	//�������� �����
	Texture point;
	point.loadFromFile("images/point.png");

	//�������� ������� �����
	Texture bigPoint;
	bigPoint.loadFromFile("images/bigPoint.png");

	//�������� �������� "������"
	Texture win;
	win.loadFromFile("images/win.png");

	//�������� �������� "���������"
	Texture gameOver;
	gameOver.loadFromFile("images/win.png");

	//������ �����
	Sprite s;
	s.setTexture(t);
	s.setTextureRect(IntRect(0, 0, 304, 350));
	s.setPosition(0, 4);
	
	//������ ��������� �������
	Sprite eat;
	eat.setTexture(point);
	eat.setTextureRect(IntRect(0, 0, 8, 8));
	
	//������ ������� �������
	Sprite bigEat;
	bigEat.setTexture(bigPoint);
	bigEat.setTextureRect(IntRect(0, 0, 8, 8));

	//������ ����� ����
	Sprite TheEnd;	

	//������ �����
	heroSprite.setTexture(heroTexture);
	heroSprite.setTextureRect(IntRect(455, 0, 12, 15));
	heroSprite.setPosition(X, Y);
	//------------------------- ��� ����� ������� � ������
	Texture mapTexture;
	mapTexture.loadFromFile("images/Pac_Man_Sprites1.png");
	Sprite mapSprite;	
	mapSprite.setTexture(mapTexture);
	mapSprite.setTextureRect(IntRect(614, 20, 16, 16));//607, 21, 16, 16//ts.width, ts.height
	//---------------------
	Enemy enemy(mapTexture,17*1,17*2);		//������� �����

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
		
		float time = clock.getElapsedTime().asMicroseconds(); //���� ��������� ����� � �������������
		clock.restart(); //������������� �����
		time /= 600; //�������� ����(��� ������ ����� - ��� �������)

		if (Keyboard::isKeyPressed(Keyboard::Left))
		{
			currentFrame += 0.005*time; //������ ��� ����������� �� "������". ���������� ������� �� ����� �������� ������������ ������� � ��������. ������� 0.005 ����� �������� �������� ��������
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
				currentFrame -= 2; // ���� ������ � ������� ����� - ������������ �����.					
				heroSprite.setTextureRect(IntRect(460, 16, 12, 15));
			}
			dx = -0.1;
			dy = 0;
		}
		else if (Keyboard::isKeyPressed(Keyboard::Right))
		{
			currentFrame += 0.005*time; //������ ��� ����������� �� "������". ���������� ������� �� ����� �������� ������������ ������� � ��������. ������� 0.005 ����� �������� �������� ��������
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
				currentFrame -= 2; // ���� ������ � ������� ����� - ������������ �����.				
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
		window.clear(Color::Blue); //��� ������� ������� ���� �����, ���������� ������� �����

		//��������� �����
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
					rectangle.setFillColor(Color::Black);

				//������� ������ �����
				rectangle.setPosition(j * ts.width, i * ts.height);
				window.draw(rectangle);

				//����� ���� ���
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
			window.draw(enemy.enemySprite);	//������ �����
		}
		
		update(time);
		enemy.update(time / 2); //��������� ������������ � �������� �����
		//window.draw(s); //���� ������������� ����� ��������� �����
		window.draw(heroSprite);//������ �����
				
		if (finish())//��������� �� ������ �� �����?
		{
			//������ ������ ��������
			TheEnd.setTexture(win);
			TheEnd.setTextureRect(IntRect(0, 0, W*ts.width, H*ts.height));			
			window.draw(TheEnd);

			//������� �����
			Font font;
			font.loadFromFile("CyrilicOld.ttf");
			Text txt;
			txt.setPosition(W*ts.width/8, H*ts.height/2);			
			txt.setFont(font);
			txt.setColor(Color::White);
			txt.setString(L"Press space bar\n to finish game.");			
			window.draw(txt);

			//���� ������������ ����� ������ ��������� ����
			if (Keyboard::isKeyPressed(Keyboard::Space))
				window.close();
		}

		window.display(); //���������� ���
	}

	return 0;
}