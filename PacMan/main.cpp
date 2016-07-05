#include <SFML/Graphics.hpp>
using namespace sf;
//using namespace ;
int main()
{
	RenderWindow window(sf::VideoMode(400, 400), "PacMan"); //,Style::Fullscreen
	Image heroImage;
	heroImage.loadFromFile("images/Pac_Man_Sprites.png");
	
	Texture heroTexture;
	heroTexture.loadFromImage(heroImage);
	
	Sprite heroSprite;
	heroSprite.setTexture(heroTexture);
	heroSprite.setTextureRect(IntRect(455, 0, 12, 15));
	heroSprite.setPosition(20, 20);
	
	//Hello Kate
	Clock clock;
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
				heroSprite.move(-0.1 * time, 0);
				heroSprite.setTextureRect(IntRect(460, 16, 12, 15));
			}
			else if (currentFrame > 1 && currentFrame <= 2)
			{
				heroSprite.move(-0.1 * time, 0);
				heroSprite.setTextureRect(IntRect(472, 16, 15, 15));
			}
			else if (currentFrame > 2)
			{
				currentFrame -= 2; // если пришли к второму кадру - откидываемся назад.	
				heroSprite.move(-0.1 * time, 0);
				heroSprite.setTextureRect(IntRect(460, 16, 12, 15));
			}
		}
		else if (Keyboard::isKeyPressed(Keyboard::Right))
		{
			currentFrame += 0.005*time; //служит для прохождения по "кадрам". переменная доходит до двухх суммируя произведение времени и скорости. изменив 0.005 можно изменить скорость анимации
			if (currentFrame > 0 && currentFrame <= 1)
			{
				heroSprite.move(0.1 * time, 0);
				heroSprite.setTextureRect(IntRect(455, 0, 12, 15));
			}
			else if (currentFrame > 1 && currentFrame <= 2)
			{
				heroSprite.move(0.1 * time, 0);
				heroSprite.setTextureRect(IntRect(473, 0, 15, 15));
			}
			else if (currentFrame > 2)
			{
				currentFrame -= 2; // если пришли к второму кадру - откидываемся назад.	
				heroSprite.move(0.1 * time, 0);
				heroSprite.setTextureRect(IntRect(455 * int(currentFrame), 0, 12, 15));
			}
				
					
		}
		else if (Keyboard::isKeyPressed(Keyboard::Up))
		{
			currentFrame += 0.005*time;
			if (currentFrame > 0 && currentFrame <= 1)
			{
				heroSprite.move(0, -0.1 * time);
				heroSprite.setTextureRect(IntRect(456, 36, 15, 12));
			}
			else if (currentFrame > 1 && currentFrame <= 2)
			{
				heroSprite.move(0, -0.1 * time);
				heroSprite.setTextureRect(IntRect(473, 33, 15, 15));
			}
			else if (currentFrame > 2)
			{
				currentFrame -= 2;
				heroSprite.move(0, -0.1 * time);
				heroSprite.setTextureRect(IntRect(456, 36, 15, 12));
			}
		}
		else if (Keyboard::isKeyPressed(Keyboard::Down))
		{
			currentFrame += 0.005*time;
			if (currentFrame > 0 && currentFrame <= 1)
			{
				heroSprite.move(0, 0.1 * time);
				heroSprite.setTextureRect(IntRect(456, 48, 15, 12));
			}
			else if (currentFrame > 1 && currentFrame <= 2)
			{
				heroSprite.move(0, 0.1 * time);
				heroSprite.setTextureRect(IntRect(473, 48, 15, 15));
			}
			else if (currentFrame > 2)
			{
				currentFrame -= 2;
				heroSprite.move(0, 0.1 * time);
				heroSprite.setTextureRect(IntRect(456, 48, 15, 12));
			}
		}

		window.clear();
		window.draw(heroSprite);
		window.display();
	}

	return 0;
}