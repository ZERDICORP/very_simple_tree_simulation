#include "tools.h"

void drawPattern(sf::RenderWindow& window, float fAngle, float& fY, float& fX, float fLength, float fWidth, sf::Color color)
{
	float fWidthHalf = fWidth / 2;

	float fSin = sin(fAngle) * fWidthHalf;
	float fCos = cos(fAngle) * fWidthHalf;

	sf::ConvexShape convex;
	convex.setFillColor(color);
	convex.setPointCount(4);
	convex.setPoint(0, sf::Vector2f(fX + fSin, fY - fCos));
	convex.setPoint(1, sf::Vector2f(fX - fSin, fY + fCos));
	
	fY += sin(fAngle) * fLength;
	fX += cos(fAngle) * fLength;

	convex.setPoint(2, sf::Vector2f(fX - fSin, fY + fCos));
	convex.setPoint(3, sf::Vector2f(fX + fSin, fY - fCos));

	window.draw(convex);
}

void displayConsoleInformation(std::map<std::string, float>& cfg)
{
	system("cls");

	std::cout << "# " << mTitle << " #" << std::endl;
	std::cout << "\n[!] keyboard buttons for control:" << std::endl;
	std::cout << "\t [ ESC ] - exit;" << std::endl;
	std::cout << "\t [ R ] - restart simulation;" << std::endl;
	std::cout << "\n[!] note: visit a \"" << mConfigPath << "\" file to change simulation configuration;" << std::endl;
	std::cout << "\n[!] current configuration:" << std::endl;
	
	for (std::map<std::string, float>::iterator p = cfg.begin(); p != cfg.end(); p++)
		std::cout << "\t" << p -> first << " = " << p -> second << ";" << std::endl;
}

std::map<std::string, float> readConfig(std::string sConfigPath)
{
	std::map<std::string, float> cfg;

	zer::File file(sConfigPath);
	file.read({zer::file::Modifier::lines});

	for (int i = 0; i < file.linesLen(); ++i)
	{
		std::string sLine = file.lineAt(i);
		if (sLine.find(" = ") != std::string::npos)
		{
			std::vector<std::string> lineParts = zer::athm::split(sLine, " = ");
			cfg[lineParts[0]] = stof(lineParts[1]);
		}
	}

	return cfg;
}

EVENT_CODE eventListener(sf::RenderWindow& window)
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			return CLOSE_EVENT_CODE;
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
				return CLOSE_EVENT_CODE;
			if (event.key.code == sf::Keyboard::R)
				return RESTART_EVENT_CODE;
		}
	}
	return NULL_EVENT_CODE;
}

int main()
{
	zer::athm::rand_init();

	sf::RenderWindow window(sf::VideoMode(mWW, mWH), mTitle);
	
	return init(window);
}