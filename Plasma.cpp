// Plasma.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <time.h>
#include <SFML/Graphics.hpp>
#include <thread>
#define _CRT_SECURE_NO_WARNINGS


#define dist(a, b, c, d) sqrt(double(a - c) * (a - c) + (b - d) * (b - d))

int main()
{

	sf::Image* imagePtr;
	sf::Image image;
	imagePtr = new sf::Image();
	image.create(256, 256, sf::Color::Blue);
	//imagePtr->create(256, 256, sf::Color::Blue);

	for (int i = 0; i < image.getSize().x; i++) {
		for (int j = 0; j < image.getSize().y; j++) {
			//int color_v = int(128 + 128 * sin(i / 8.0));
			//int color_v = int(128 + 128 * sin((i + j) / 8.0));
			//int color_v = int(128 + 128 * sin(sqrt((i - image.getSize().x /2.0) * (i - image.getSize().x /2.0) + (j - image.getSize().y /2.0) * (j - image.getSize().y /2.0)) / 8.0));
			int color_v = int(128 + (128 * sin(i / 8.0)) + 128 + (128.0 * sin(j / 8.0))) / 2;

			image.setPixel(i, j, sf::Color::Color(color_v, color_v, color_v));
		}
	}

	sf::Texture texture;
	texture.loadFromImage(image);

	sf::Sprite sprite;
	sprite.setTexture(texture);

	sf::RenderWindow window(sf::VideoMode(256, 256), "Plasma", sf::Style::Close);
	std::time_t result = std::time(nullptr);
	int count = 10;

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}

		count += 10;

		for (int i = 0; i < image.getSize().x; i++) {
			for (int j = 0; j < image.getSize().y; j++) {
				double value = sin(dist(i + count, j, 128.0, 128.0) / 8.0)
					+ sin(dist(i, j, 64.0, 64.0) / 8.0)
					+ sin(dist(i, j + count / 7, 192.0, 64) / 7.0)
					+ sin(dist(i, j, 192.0, 100, 0) / 8.0);


				int color_v = int((4 + value)) * 32;
				//std::cout << color_v << std::endl;
				image.setPixel(i, j, sf::Color::Color(color_v, color_v * 2, 255 - color_v));
				//imagePtr->setPixel(i, j, sf::Color::Color(color_v, color_v * 2, 255 - color_v));
			}
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
		//texture.loadFromImage(*imagePtr);
		texture.update(image);

		window.clear();
		window.draw(sprite);
		window.display();
	}
}
