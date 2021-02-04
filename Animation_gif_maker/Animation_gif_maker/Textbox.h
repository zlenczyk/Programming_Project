#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>

#define DELETE_KEY 8
#define ENTER_KEY 13
#define ESCAPE_KEY 27

class Textbox {
public:
	Textbox() {}
	Textbox(int size, sf::Color color, bool sel) {
		textbox.setCharacterSize(size);
		textbox.setFillColor(color);
		isSelected = sel;
		if (sel) {
			textbox.setString("_");
		}
		else {
			textbox.setString("");
		}
	}

	void setText(std::string s) {
		textbox.setString(s);
	}

	void setFont(sf::Font &font) {
		textbox.setFont(font);
	}

	void setPosition(sf::Vector2f pos) {
		textbox.setPosition(pos);
	}

	void setLimit(bool ToF) {
		hasLimit = ToF;
	}

	void setLimit(bool ToF, int lim) {
		hasLimit = ToF;
		limit = lim-1;
	}

	void setSelected(bool sel) {
		isSelected = sel;
		if (!sel) {
			std::string t = text.str();
			std::string newT = "";
			for (int i = 0; i < t.length(); i++) {
				newT += t[i];
			}
			textbox.setString(newT);
		}
	}

	std::string getText() {
		//return text.str();
		return textbox.getString();
	}



	void drawTo(sf::RenderWindow &window) {
		window.draw(textbox);
	}

	void typenOn(sf::Event input) {
		if (isSelected) {
			int charTyped = input.text.unicode;
			if (charTyped < 58 && charTyped >47 || charTyped == 8 || charTyped == 13 || charTyped == 27) {               //47, 58
				if (hasLimit) {
					if (text.str().length() <= limit) {
						inputLogic(charTyped);
					}
					else if (text.str().length() > limit && charTyped == DELETE_KEY) {
						deleteLastChar();
					}
				}
				else {
					inputLogic(charTyped);
				}
			}
		}
	}

private:
	sf::Text textbox;
	std::ostringstream text;
	bool isSelected = false;
	bool hasLimit = false;
	int limit{};

	void inputLogic(int charTyped) {
		if (text.str().length() < 3) {
			if (charTyped != DELETE_KEY && charTyped != ENTER_KEY && charTyped != ESCAPE_KEY) {
				text << static_cast<char>(charTyped);
			}
			else if (charTyped == DELETE_KEY) {
				if (text.str().length() > 0) {
					deleteLastChar();
				}
			}
			textbox.setString(text.str() + "_");
			if (charTyped == ENTER_KEY) {
				textbox.setString(text.str().substr(0, text.str().length()));
			}
		}
		else {
			if (charTyped == DELETE_KEY) {
				if (text.str().length() > 0) {
					deleteLastChar();
				}
			}
			if (charTyped == ENTER_KEY) {
				textbox.setString(text.str().substr(0, text.str().length()));
			}
		}
	}

	void deleteLastChar() {
		std::string t = text.str();
		std::string newT = "";
		for (int i = 0; i < t.length()-1; i++) {
			newT += t[i];
		}
		text.str("");
		text << newT;

		textbox.setString(text.str());
	}

};