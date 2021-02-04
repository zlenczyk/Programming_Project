#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>
#include <list>

class Drawing {
public:
	Drawing() {
	}

	std::vector<sf::CircleShape> colors;
	std::vector<sf::RectangleShape> rects;
	std::vector<sf::CircleShape> cirs;
	std::vector<sf::CircleShape> dots;


	std::vector<std::vector<int>> c =
	{
		{0,0,0},         //czarny
		{255,105,180},   //rozowy
		{255,0,0},       //czerwony
		{139,69,19},     //brazowy
		{255,127,0},     //pomaranczowy
		{255,255,0},     //zolty
		{0,255,0},       //zielony
		{0,191,255},     //niebieski
		{0,0,255},       //granatowy
		{125,38,205},    //fioletowy
		{255,255,255},   //bialy
	};

	void draw_colors(float krok) {
		for (int i = 0; i < 11; i += 2)
		{
			sf::CircleShape color1(30);
			sf::CircleShape color2(30);
			color1.setPosition(757.5, float(8.5) + krok);  //13
			color1.setFillColor(sf::Color(c[i][0], c[i][1], c[i][2]));
			color1.setOutlineColor(sf::Color::Black);
			color1.setOutlineThickness(-2);
			if (i < 10) {
				color2.setPosition(832.5, float(8.5) + krok);
				color2.setFillColor(sf::Color(c[i+1][0], c[i+1][1], c[i+1][2]));
				color2.setOutlineColor(sf::Color::Black);
				color2.setOutlineThickness(-2);
			}

			colors.push_back(color1);
			if (i < 10) {
				colors.push_back(color2);
			}
			krok += 77;  //86
		}
	}

	void tools(float radius, float x, float y, float thick) {
		sf::CircleShape shape(radius);
		shape.setPosition(x,y);
		shape.setOutlineColor(sf::Color::Black);
		shape.setOutlineThickness(thick);
		cirs.push_back(shape);
	}

	void bars(sf::RectangleShape shape, float w, float h, float x, float y, int r, int g, int b) {
		shape.setPosition(x, y);
		shape.setFillColor(sf::Color(r, g, b));
		shape.setSize(sf::Vector2f(w,h));
		rects.push_back(shape);
	}

	void lines(sf::Vertex name[], float x, float y, float x1, float y1) {
		name[0] = sf::Vertex(sf::Vector2f(x, y), sf::Color::Black);
		name[1] = sf::Vertex(sf::Vector2f(x1, y1), sf::Color::Black);
	}

	void round(sf::CircleShape shape, float x, float y, int r, int g, int b, int r1, int g1, int b1, float thick) {
		shape.setPosition(x, y);
		shape.setFillColor(sf::Color(r, g, b));
		shape.setOutlineColor(sf::Color(r1,g1,b1));
		shape.setOutlineThickness(thick);
		dots.push_back(shape);
	}

private:

};