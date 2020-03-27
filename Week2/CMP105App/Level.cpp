#include "Level.h"
int originalx = 0, originaly = 0;
int finalx = 0, finaly = 0;
bool gotStart = 0;


Level::Level(sf::RenderWindow* hwnd, Input* in)
{
	window = hwnd;
	input = in;

	// initialise game objects
	if (!font.loadFromFile("D:/UNI/Sem 2/Games Development/CMP105_W1/Week1/CMP105App/font/arial.ttf"))
	{
		std::cout << "Error loading font\n";
	}

	mousePosText.setFont(font);
	mousePosText.setCharacterSize(24);
	mousePosText.setFillColor(sf::Color::Red);

	circle.setRadius(100);
	circle.setFillColor(sf::Color::Magenta);
	circle.setOrigin(100, 100);
}

Level::~Level()
{
	input = nullptr;

}

// handle user input
void Level::handleInput()
{
	if (input->isKeyDown(sf::Keyboard::W))
	{
		input->setKeyUp(sf::Keyboard::W);
		std::cout << "W key was pressed\n";
	}

	if ((input->isKeyDown(sf::Keyboard::K)) & (input->isKeyDown(sf::Keyboard::L)) & (input->isKeyDown(sf::Keyboard::J)))
	{
		input->setKeyUp(sf::Keyboard::K);
		input->setKeyUp(sf::Keyboard::L);
		input->setKeyUp(sf::Keyboard::J);
		std::cout << "K, L and J keys were pressed\n";
	}

	if (input->isKeyDown(sf::Keyboard::Escape))
	{
		input->setKeyUp(sf::Keyboard::Escape);
		window->close();
	}

	if (input->isMouseLDown() && gotStart == 0)
	{
		originalx = input->getMouseX();
		originaly = input->getMouseY();
		gotStart = 1;

	}
	else if (!(input->isMouseLDown()) && gotStart == 1)
	{
		finalx = input->getMouseX();	
		finaly = input->getMouseY();
		gotStart = 0;
		std::cout << "The X distance of that drag was " << (finalx - originalx) << ", The Y distance was " << (finaly - originaly);
	}

	if (input->isMouseRDown())
	{
		circle.setPosition(input->getMouseX(), input->getMouseY());
		input->setMouseRDown(0);
	}
}

// Update game objects
void Level::update()
{
	mousePosText.setString(" Mouse X: " + std::to_string(input->getMouseX()) + "	Mouse Y: " + std::to_string(input->getMouseY()));
}

// Render level
void Level::render()
{
	beginDraw();
	window->draw(mousePosText);
	window->draw(circle);
	endDraw();
}

// Begins rendering to the back buffer. Background colour set to light blue.
void Level::beginDraw()
{
	window->clear(sf::Color(100, 149, 237));
}

// Ends rendering to the back buffer, and swaps buffer to the screen.
void Level::endDraw()
{
	window->display();
}