#include <SFML\Graphics.hpp>
#include <iostream>
#include <math.h>
#include <sstream>

using namespace std;

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Game");
	window.setFramerateLimit(60);
	//window.setKeyRepeatEnabled(false);
	restart:
	//state of buttons
	bool play = true;
	bool leftArrow = false;
	bool rightArrow = false;
	bool end = false;

	//variables
	float position = 3;
	float time = 0.3;
	std::vector<float> xMove (100, 4*time);
	std::vector<float> yMove (100, 8*time + 10*time*time);
	std::string lite = "Game Over!";
	std::string again = "Press return to restart.";
	ostringstream text;
	
	int count = 0;
	int k = 0;

	//event
	sf::Event event;

	sf::Font font;
	if (font.loadFromFile("Data/ariblk.ttf") == 0)
	{
		return 1;
	}

	//Game ending.
	sf::Text over;
	over.setFont(font);
	over.setString(lite);
	over.setCharacterSize(30);
	over.setColor(sf::Color::Red);
	over.setPosition(200,200);

	sf::Text replay;
	replay.setFont(font);
	replay.setString(again);
	replay.setCharacterSize(30);
	replay.setColor(sf::Color::Green);
	replay.setPosition(225, 100);

	//Background Image
	sf::Texture background;
	if (background.loadFromFile("Data/background.png") == -1)
	{
		return 1;
	}
	
	//outer rectangle which will not move.
	sf::RectangleShape outRect;
	outRect.setSize(sf::Vector2f(600, 400));
	outRect.setPosition(100, 100);
	outRect.setOutlineThickness(3);
	outRect.setTexture(&background);

	//inner rectangle which will move.
	sf::RectangleShape inRect;
	inRect.setSize(sf::Vector2f(50, 25));
	inRect.setPosition(375, 475);
	inRect.setFillColor(sf::Color::Yellow);
	inRect.setOutlineColor(sf::Color::White);

	//ball 
	sf::CircleShape* balls = new sf::CircleShape [100];

	//game loop
	while (play)
	{
			if (count%300 == 0)
				if (k < 100)
				{
					k++;
					balls[k-1].setRadius(10);
					balls[k-1].setFillColor(sf::Color::Red);
					balls[k-1].setPosition(100, rand()%100 + 250);
				}
			count++;

			//Events
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left)
				{
					rightArrow = false;
					leftArrow = true;
				}

				if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right)
				{
				
					leftArrow = false;
					rightArrow = true;
				}

				if (event.type == sf::Event::Closed)
				{
					play = false;
				}

				if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Return)
				{
					goto restart;
				}
			}

			//Ball movement
			for (int i=0;i<k;i++)
			{
				if (balls[i].getPosition().x > 680)
				{
					if (xMove[i] > 0)
						xMove[i] = -1*xMove[i];
				}
				if (balls[i].getPosition().x < 100)
				{
					if (xMove[i] < 0)
						xMove[i] = -1*xMove[i];
				}
				if (balls[i].getPosition().y > 480)
				{
					if (yMove[i] > 0)
						yMove[i] = -1*yMove[i];		
				}
				if (balls[i].getPosition().y < 250)
				{
					if (yMove[i] < 0)
						yMove[i] = -1*yMove[i];		
				}

				balls[i].move(xMove[i], yMove[i]);
			}
				//Logic
				if (leftArrow)
				{
					if (inRect.getPosition().x > 100)
					inRect.move(-position, 0);	
					//leftArrow = false;
				}

				if (rightArrow)
				{
					if(inRect.getPosition().x < 650)
					inRect.move(position, 0);
					//rightArrow = false;
				}
			for (int i=0;i<k;i++)
			{
				if (inRect.getGlobalBounds().intersects(balls[i].getGlobalBounds()) == true && end == false)
				{
					end = true;
					text << "No. of Balls you survived: " << k;
					over.setString(text.str());
					break;
				}
			}

			//Rendering
			window.clear();
		
			if (!end)
			{
				window.draw(outRect);
				window.draw(inRect);
				for (int i=0;i<k;i++)
					window.draw(balls[i]);
			}
			else
			{
				window.draw(replay);
				window.draw(over);
			}

			window.display();
	}
	
	//clean up
	window.close();

	return 0;
}
