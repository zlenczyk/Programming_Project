#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Button {
public:
	bool clicked{};

	Button() {}

	Button(std::string t, sf::Vector2f size, int charSize, sf::Color bgColor, sf::Color textColor) {
		text.setString(t);
		text.setFillColor(textColor);
		text.setCharacterSize(charSize);
		button.setSize(size);
		button.setFillColor(bgColor);
		clicked = false;

	}

	/*Button(int size, sf::Vector2f pos, sf::Color bgColor) {
		button2.setRadius(size);
		button2.setFillColor(bgColor);
		button2.setPosition(pos);
	}*/

	void setFont(sf::Font& font) {
		text.setFont(font);
	}

	/*bool setClick(bool tf) {
		if (clicked == true) {
			clicked = false;
		}
		else {
			clicked = true;
		}
		return tf;
	}*/

	void setBackColor(sf::Color color) {
		button.setFillColor(color);
	}

	void setTextColor(sf::Color color) {
		text.setFillColor(color);
	}

	void setOutlineColor(sf::Color color) {
		button.setOutlineColor(color);
	}

	void setOutlineThickness(float t) {
		button.setOutlineThickness(t);
	}

	void setPosition(sf::Vector2f pos) {
		button.setPosition(pos);
	//	float xPos = (pos.x + button.getLocalBounds().width / 4) - (text.getLocalBounds().width / 2);
	//	float yPos = (pos.y + button.getLocalBounds().height / 4) - (text.getLocalBounds().height / 2);
	//	text.setPosition({ xPos,yPos });
	}

	void setTextPosition(sf::Vector2f pos) {
		text.setPosition(pos);
	}

	void drawTo(sf::RenderWindow& window) {
		window.draw(button);
		window.draw(text);
	}

	bool isMouseOver(sf::RenderWindow& window) {
		int mouseX = sf::Mouse::getPosition(window).x;
		int mouseY = sf::Mouse::getPosition(window).y;

		float btnPosX = button.getPosition().x;
		float btnPosY = button.getPosition().y;

		float btnPosWidth = button.getPosition().x + button.getLocalBounds().width;
		float btnPosHeight = button.getPosition().y + button.getLocalBounds().height;

		if (mouseX < btnPosWidth && mouseX > btnPosX && mouseY < btnPosHeight && mouseY > btnPosY) {
			return true;
		}
		return false;
	}

/*	bool isClicked() {
		if (clicked == true) {
			clicked = false;
			return true;
		}
		else {
			clicked = true;
			return false;
		}
	}*/

	private:
	sf::RectangleShape button;
	sf::Text text;
};
