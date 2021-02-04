#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>
#include <list>
#include "Textbox.h"
#include "Button.h"
#include "Drawing.h"
#include <fstream>
#include <cstdlib>
#include <direct.h>
#include "Gifs.h"
#include <string> 
#include <stdio.h>
#include <cstdio>
#include "Magick++.h"

#ifdef _WIN32
	#include <windows.h>

	void sleep(unsigned milliseconds)
	{
		Sleep(milliseconds);
	}
#endif

using namespace std;

sf::RenderWindow window(sf::VideoMode(900, 662), "Title");

vector<Magick::Image> fram;

bool click; 
bool click2;
bool yes;
bool yes2;
int curr_f;
int set;
string str;


Drawing one;
Gifs gif;

string s2;
float x, y;
int r, g, b;
int r1, g1, b1;
int draw;
float paint_thick;
std::list <sf::CircleShape>::iterator iter;
sf::RenderTexture tex;

std::list<sf::CircleShape> circles;
vector<Button> buttons;
Textbox current(15, sf::Color::Black, false);
Textbox after_f(15, sf::Color::Black, false);

void update()
{
	iter = circles.begin();

	while (iter != circles.end())
	{
		window.draw(*iter);
		iter++;
	}
}

void up(string file)
{
	if (!tex.create(900, 661))
	{
		cout << "error" << endl;
	}
	tex.clear(sf::Color(r1, g1, b1));
	sf::Texture t;
	if (!t.loadFromFile(file))
		cout << "error_copy" << endl;
	else {
		sf::Sprite sprite;
		sprite.setTexture(t);
		tex.draw(sprite);
	}
	std::list <sf::CircleShape>::iterator iter;
	iter = circles.begin();
	while (iter != circles.end())
	{
		tex.draw(*iter);
		iter++;
	}
	tex.display();

}

void add(sf::CircleShape shape)
{
	circles.push_back(shape);
}

void onMouseMovedButton() {
	for (int i = 0; i < buttons.size(); i++) {
		if (buttons[i].isMouseOver(window)) {
			if (i >= 0 && i <= 3) { buttons[i].setBackColor(sf::Color::White); }
			else if (i == 4 || i == 5 || i == 10 || i == 11) { buttons[i].setBackColor(sf::Color(156, 156, 156)); }
			else if (i >= 6 && i <= 8) {
				buttons[i].setBackColor(sf::Color::White);
				one.dots[i - 6].setFillColor(sf::Color::Black);
			}
			else if (i == 9) { buttons[i].setBackColor(sf::Color(164, 255, 182)); }
		}
		else {
			if (buttons[i].clicked == true) {
				if (i >= 0 && i <= 3 || i == 9) { buttons[i].setBackColor(sf::Color::White); }
				else if (i == 4 || i == 5 || i == 10 || i == 11) { buttons[i].setBackColor(sf::Color(156, 156, 156)); }
				else {
					buttons[i].setBackColor(sf::Color(192, 192, 192));
					one.dots[i - 6].setFillColor(sf::Color::Black);
				}
			}
			else {
				if (i >= 0 && i <= 3) { buttons[i].setBackColor(sf::Color(231, 230, 242)); }
				else if (i == 4 || i == 5 || i == 10 || i == 11) { buttons[i].setBackColor(sf::Color(192, 192, 192)); }
				else if (i >= 6 && i <= 8) {
					buttons[i].setBackColor(sf::Color(192, 192, 192));
					one.dots[i - 6].setFillColor(sf::Color::White);
				}
				else if(i==9) { buttons[i].setBackColor(sf::Color::White); }
			}
		}
	}

}

float t[5] = {2,5,12,22};

int n_images = 0; // id ostatniego zdjecia;

void onClickedButton() {
	for (int i = 0; i < buttons.size(); i++) {
		if (buttons[i].isMouseOver(window)) {
			if (buttons[i].clicked == false) {
				if (i >= 0 && i <= 3) {
					buttons[0].clicked = false;
					buttons[1].clicked = false;
					buttons[2].clicked = false;
					buttons[3].clicked = false;
					buttons[i].clicked = true;
					paint_thick = t[i];
				}
				else if (i == 4 || i == 5) {
					buttons[4].clicked = false;
					buttons[5].clicked = false;
					buttons[i].clicked = true;
				}
				else if (i > 5 && i < 9) {
					buttons[6].clicked = false;
					buttons[7].clicked = false;
					buttons[8].clicked = false;
					buttons[i].clicked = true;
					if (i == 8) {
						buttons[12].clicked = false;
						click2 = true; click = false;
						after_f.setText("_");
						after_f.setSelected(true);
						if (buttons[4].clicked == true) { set = 1; }
						else if (buttons[5].clicked == true) { set = 2; }
					}
				}
				else if (i == 9) {
					if (buttons[4].clicked == true) {            // jesli klikniety NEW
						if (buttons[6].clicked == true) { // jesli po aktualnej klatce
							string s1 = "C:/Users/Administrator/source/repos/Animation_gif_maker/x64/Debug/frames/" + to_string(curr_f) + ".jpg";
							for (int i = n_images; i > curr_f ; i--) {
								sf::Image image;
								string s2 = "C:/Users/Administrator/source/repos/Animation_gif_maker/x64/Debug/frames/" + to_string(i) + ".jpg";
								string s3 = "C:/Users/Administrator/source/repos/Animation_gif_maker/x64/Debug/frames/" + to_string(i+1) + ".jpg";
								if (!image.loadFromFile(s2))
									cout << "error_copy" << endl;
								if (image.saveToFile(s3))
								{
									std::cout << "new saved to " << std::endl;
								}
							}
							string s = "C:/Users/Administrator/source/repos/Animation_gif_maker/x64/Debug/frames/" + to_string(curr_f+1) + ".jpg";
							remove(s.c_str());
							n_images++;
							up(s1);
							sleep(1000);
							gif.take_screenshot(window, s1, tex);  //nasz screenshot zapisujemy z id wiekszym o 1 od naszej aktualnej klatki
							sleep(2000);
							curr_f += 1;
							current.setText(to_string(curr_f));
							yes = false;
							r1 = g1 = b1 = 255;
							circles.clear();
							buttons[4].clicked = false;
							buttons[6].clicked = false;
							cout << "aktualna" << curr_f << endl;
							cout << "indeks wszystkich"<<n_images << endl;
						}
						else if (buttons[7].clicked == true) { // jesli po wszystkich
							n_images++;   // max id wszystkich istniejacych klatek wzrasta o 1;
							string s1 = "C:/Users/Administrator/source/repos/Animation_gif_maker/x64/Debug/frames/" + to_string(curr_f) + ".jpg";
							sleep(1000);
							up(s1);
							sleep(1000);
							gif.take_screenshot(window, s1, tex);
							sleep(2000);
							circles.clear();
							curr_f = n_images;
							r1 = g1 = b1 = 255;
							yes = false;
							current.setText(to_string(curr_f));
							buttons[4].clicked = false;
							buttons[7].clicked = false;
							cout << "aktualna" << curr_f << endl;
							cout << "indeks wszystkich" << n_images << endl;
						}
						else if (buttons[8].clicked == true)
						{
							set = 1;
							yes = false;
						}
					}
					else if (buttons[5].clicked == true) {   // jesli klikniety COPY
						if (buttons[6].clicked == true) { // jesli po aktualnej klatce
							string s1 = "C:/Users/Administrator/source/repos/Animation_gif_maker/x64/Debug/frames/" + to_string(curr_f) + ".jpg";
							for (int i = n_images; i > curr_f; i--) {
								sf::Image image;
								string s2 = "C:/Users/Administrator/source/repos/Animation_gif_maker/x64/Debug/frames/" + to_string(i) + ".jpg";
								string s3 = "C:/Users/Administrator/source/repos/Animation_gif_maker/x64/Debug/frames/" + to_string(i + 1) + ".jpg";
								if (!image.loadFromFile(s2))
									cout << "error_copy" << endl;
								if (image.saveToFile(s3))
								{
									std::cout << "new saved to " << std::endl;
								}
							}
							string s = "C:/Users/Administrator/source/repos/Animation_gif_maker/x64/Debug/frames/" + to_string(curr_f + 1) + ".jpg";
							remove(s.c_str());
							n_images++;
							sleep(1000);
							up(s1);
							sleep(1000);
							gif.take_screenshot(window,s1,tex);
							gif.copy_frame(curr_f, s1);
							curr_f ++;
							current.setText(to_string(curr_f));
							sleep(2000);
							window.clear(sf::Color::White);
							//circles.clear();
							buttons[5].clicked = false;
							buttons[6].clicked = false;
							cout << "aktualna" << curr_f << endl;
							cout << "indeks wszystkich" << n_images << endl;
						}
						else if (buttons[7].clicked == true) { // po wszystkich
							string s1 = "C:/Users/Administrator/source/repos/Animation_gif_maker/x64/Debug/frames/" + to_string(curr_f) + ".jpg";
							sleep(1000);
							up(s1);
							gif.take_screenshot(window, s1, tex);
							gif.copy_frame(n_images, s1);
							n_images++;
							curr_f = n_images;
							current.setText(to_string(curr_f));
							sleep(2000);
							window.clear(sf::Color::White);
							//circles.clear();
							buttons[5].clicked = false;
							buttons[7].clicked = false;
							cout << "aktualna" << curr_f << endl;
							cout << "indeks wszystkich" << n_images << endl;
						}
						else if (buttons[8].clicked == true)
						{
							set = 2;
						}
					}
				}
				else if (i == 10) { // button delete
				    cout << n_images;
				    cout << curr_f;
					if (curr_f > n_images) {
						buttons[i].setBackColor(sf::Color(255,48,48));
						sleep(1000);
						buttons[i].setBackColor(sf::Color(192, 192, 192));
					}
					else {
						if (curr_f == n_images) {  // jezeli jestesmy na ostatniej klatce
							string filename = "C:/Users/Administrator/source/repos/Animation_gif_maker/x64/Debug/frames/"+to_string(n_images) + ".jpg";
							if (remove(filename.c_str()) != 0) {
								cout << "File deletion failed" << endl;
								buttons[i].setBackColor(sf::Color(255, 48, 48));
								sleep(1000);
								buttons[i].setBackColor(sf::Color(192, 192, 192));
							}
							else {
								cout << "File deleted successfully";
								buttons[i].setBackColor(sf::Color(144, 238, 144));
								sleep(1000);
								buttons[i].setBackColor(sf::Color(192, 192, 192));
								n_images -= 1;
								current.setText(to_string(curr_f));
								buttons[i].clicked = false;
							}
						}
						else {
							string filename = "C:/Users/Administrator/source/repos/Animation_gif_maker/x64/Debug/frames/" + to_string(n_images) + ".jpg";
							for (int i = curr_f+1; i <= n_images; i++) {
								sf::Image image;
								string s2 = "C:/Users/Administrator/source/repos/Animation_gif_maker/x64/Debug/frames/" + to_string(i) + ".jpg";
								string s3 = "C:/Users/Administrator/source/repos/Animation_gif_maker/x64/Debug/frames/" + to_string(i - 1) + ".jpg";
								if (!image.loadFromFile(s2))
									cout << "error_copy" << endl;
								if (image.saveToFile(s3))
								{
									std::cout << "new saved to " << std::endl;
								}
							}
							if (remove(filename.c_str()) != 0) {
								cout << "File deletion failed" << endl;
								buttons[i].setBackColor(sf::Color(255, 48, 48));
								sleep(1000);
								buttons[i].setBackColor(sf::Color(192, 192, 192));
							}
							else {
								cout << "File deleted successfully";
								buttons[i].setBackColor(sf::Color(144, 238, 144));
								sleep(1000);
								buttons[i].setBackColor(sf::Color(192, 192, 192));
								n_images = -1;
								current.setText(to_string(curr_f));
								buttons[i].clicked = false;
							}

						}
					}
				}
				else if (i == 11) {
					string s1 = "C:/Users/Administrator/source/repos/Animation_gif_maker/x64/Debug/frames/" + to_string(curr_f) + ".jpg";
					up(s1);
					sleep(1000);
					gif.take_screenshot(window, s1, tex);
					cout << n_images;
					cout << curr_f;
					sleep(2000);
					for (int i = 0; i <= n_images; i++) {
						string s= "C:/Users/Administrator/source/repos/Animation_gif_maker/x64/Debug/frames/" + to_string(i) + ".jpg";
						Magick::Image img;
						try {
							img.read(s);
						}
						catch (Magick::Exception& error_)
						{
							cout << "Caught exception: " << error_.what() << endl;
						}
						//img.crop(Magick::Geometry("899x660"));
						img.animationDelay(50);
						fram.push_back(img);
					}
					Magick::writeImages(fram.begin(), fram.end(), "C:/Users/Administrator/source/repos/Animation_gif_maker/x64/Debug/gifs/your.gif");
				}
				else if (i == 12) { buttons[8].clicked = false; 
				current.setText("_"); 
				click = true; 
				click2 = false;
				current.setSelected(true); }
			}
		}
	}
}


int main(int argc, char** argv)
{
	Magick::InitializeMagick(*argv);
	Magick::Image first;
	Magick::Image last;

	string wys;
	sf::Texture t1;
	sf::Texture t2;
	string str1;
	string str11;
	string str2;
	string str22;
	sf::Sprite sprite1;
	sf::Sprite sprite2;
;

	//fs::create_directory("C:/Users/Administrator/source/repos/Animation_gif_maker/x64/Debug/frames");
	_mkdir("C:/Users/Administrator/source/repos/Animation_gif_maker/x64/Debug/frames");
	_mkdir("C:/Users/Administrator/source/repos/Animation_gif_maker/x64/Debug/gifs");
	_mkdir("C:/Users/Administrator/source/repos/Animation_gif_maker/x64/Debug/small_frames");

	curr_f = 0;
	click = false;
	yes = false;
	click2 = false;
	yes2 = false;
	paint_thick = 2;
	draw = 0;
	r = g = 255;
	g = 0;
	r1 = b1 = g1 = 255;
	float k = 77;
	int n = 4;
	int j = 70;

	//Drawing one;
	one.draw_colors(k);
	sf::Sprite sprite;
	std::vector<sf::Texture> textures;
	sf::Texture t_brush;
	sf::Texture t_bucket;
	sf::Texture t_eraser;
	sf::Texture t;
	textures.push_back(t_brush);
	textures.push_back(t_bucket);
	textures.push_back(t_eraser);
	textures[0].loadFromFile("res/img/brush.png");
	textures[1].loadFromFile("res/img/bucket.png");
	textures[2].loadFromFile("res/img/eraser.png");

	one.tools(30, 757.5, 8.5, -2);
	one.tools(30, 832.5, 8.5, -2);
	one.tools(30, 832.5, 469, -2);

	sf::RectangleShape right;
	sf::RectangleShape left;
	sf::RectangleShape bottom;
	sf::RectangleShape thick1;
	sf::RectangleShape thick2;
	sf::RectangleShape thick3;
	sf::RectangleShape thick4;

	one.bars(right, 150, 539, 750, 0, 231, 230, 242);
	one.bars(left, 150, 539, 0, 0, 231, 230, 242);
	one.bars(bottom, 900, 123, 0, 539, 231, 230, 242);
	one.bars(thick1, 100, 4, 25, 11, 0, 0, 0);
	one.bars(thick2, 100, 10, 25, 25, 0, 0, 0);
	one.bars(thick3, 100, 25, 25, 45, 0, 0, 0);
	one.bars(thick4, 100, 45, 25, 80, 0, 0, 0);

	sf::Vertex line1[2];
	sf::Vertex line2[2];
	sf::Vertex line3[2];
	sf::Vertex line_above_delete[2];
	sf::Vertex line_below_thick[2];
	sf::Vertex line_above_text_frame[2];

	one.lines(line1, 150, 0, 150, 539);
	one.lines(line2, 750, 0, 750, 539);
	one.lines(line3, 0, 539, 900, 539);
	one.lines(line_above_delete, 0, 393, 150, 393);
	one.lines(line_below_thick, 0, 136, 150, 136);
	one.lines(line_above_text_frame, 0, 166, 150, 166);

	sf::CircleShape dot_c(5);
	sf::CircleShape dot_a(5);
	sf::CircleShape dot_f(5);

	one.round(dot_c, 20, 240, 255, 255, 255, 0, 0, 0, -1);
	one.round(dot_a, 20, 270, 255, 255, 255, 0, 0, 0, -1);
	one.round(dot_f, 20, 300, 255, 255, 255, 0, 0, 0, -1);

	sf::Font arial;
	arial.loadFromFile("arial.ttf");
	sf::Font arial_bold;
	arial_bold.loadFromFile("arial_bold.ttf");
	//Textbox textbox1(15, sf::Color::Black, false);
	//textbox1.setFont(arial);
	//textbox1.setPosition({ 62,320 });
	//textbox1.setLimit(true, 3);

	current.setText("0");
	current.setFont(arial);
	current.setPosition({ 106,141 });
	current.setLimit(true, 4);

	after_f.setText("0");
	after_f.setFont(arial);
	after_f.setPosition({ 62,320 });
	after_f.setLimit(true, 4);

	// przyciski grubosci pisaka
	buttons.push_back(Button("", { 150,14 }, 15, sf::Color(231, 230, 242), sf::Color::Black));
	buttons.back().setPosition({ 0,6 });
	buttons.push_back(Button("", { 150,20 }, 15, sf::Color(231, 230, 242), sf::Color::Black));
	buttons.back().setPosition({ 0,20 });
	buttons.push_back(Button("", { 150,35 }, 15, sf::Color(231, 230, 242), sf::Color::Black));
	buttons.back().setPosition({ 0,40 });
	buttons.push_back(Button("", { 150,55 }, 15, sf::Color(231, 230, 242), sf::Color::Black));
	buttons.back().setPosition({ 0,75 });

	// przyciski nowej klatki i kopiowania klatki
	buttons.push_back(Button("NEW", { 61,30 }, 15, sf::Color(192, 192, 192), sf::Color::Black));
	buttons.back().setPosition({ 12,195 });
	buttons.back().setTextPosition({ 25,200 });
	buttons.back().setFont(arial_bold);

	buttons.push_back(Button("COPY", { 61,30 }, 15, sf::Color(192, 192, 192), sf::Color::Black));
	buttons.back().setPosition({ 76,195 });
	buttons.back().setTextPosition({ 84,200 });
	buttons.back().setFont(arial_bold);

	//przyciski obslugujace dodanie nowej klatki
	buttons.push_back(Button("after current", { 126,30 }, 15, sf::Color(192, 192, 192), sf::Color::Black));
	buttons.back().setPosition({ 12,229 });
	buttons.back().setTextPosition({ 40,234 });
	buttons.back().setFont(arial);

	buttons.push_back(Button("after all", { 126,30 }, 15, sf::Color(192, 192, 192), sf::Color::Black));
	buttons.back().setPosition({ 12,259 });
	buttons.back().setTextPosition({ 53,264 });
	buttons.back().setFont(arial);

	buttons.push_back(Button("after frame", { 126,60 }, 15, sf::Color(192, 192, 192), sf::Color::Black));
	buttons.back().setPosition({ 12,289 });
	buttons.back().setTextPosition({ 43,294 });
	buttons.back().setFont(arial);

	buttons.push_back(Button("OK", { 40,25 }, 15, sf::Color::White, sf::Color::Black));
	buttons.back().setPosition({ 55,358 });
	buttons.back().setTextPosition({ 63,361 });
	buttons.back().setFont(arial_bold);
	buttons.back().setOutlineColor(sf::Color::Black);
	buttons.back().setOutlineThickness(-1);

	buttons.push_back(Button("delete\nframe", { 110,60 }, 20, sf::Color(192, 192, 192), sf::Color::Black));
	buttons.back().setPosition({ 20,402 });
	buttons.back().setTextPosition({ 47,407 });
	buttons.back().setFont(arial);

	buttons.push_back(Button("export\n   gif", { 110,60 }, 20, sf::Color(192, 192, 192), sf::Color::Black));
	buttons.back().setPosition({ 20,470 });
	buttons.back().setTextPosition({ 47,474 });
	buttons.back().setFont(arial);

	buttons.push_back(Button("", { 50,23 }, 20, sf::Color::White, sf::Color::Black));
	buttons.back().setPosition({ 95,139 });
	buttons.back().setOutlineColor(sf::Color::Black);
	buttons.back().setOutlineThickness(-1);


	sf::RectangleShape frame_number(sf::Vector2f(65, 27));
	frame_number.setFillColor(sf::Color::White);
	frame_number.setOutlineColor(sf::Color(150, 150, 150));
	frame_number.setOutlineThickness(-3);
	frame_number.setPosition({ 42,316 });   //+30,+28

	Button* paint = new Button[14];
	float m = 0;
	for (int i = 0; i < 14; i += 2) {
		paint[i] = Button("", { 75,77 }, 15, sf::Color(231, 230, 242), sf::Color::Black);
		paint[i + 1] = paint[i];
		paint[i].setPosition({ 750, m });
		paint[i + 1].setPosition({ 825, m });
		m += 77;
	}

	sf::Text frame;
	frame.setCharacterSize(18);
	frame.setFont(arial);
	frame.setFillColor(sf::Color::Black);
	frame.setPosition(47, 169);
	frame.setString("Frame: ");

	sf::Text go_to;
	go_to.setCharacterSize(15);
	go_to.setFont(arial);
	go_to.setFillColor(sf::Color::Black);
	go_to.setPosition(7, 141);
	go_to.setString("Go to frame:");


	while (window.isOpen())
	{
		sf::Event event;

		window.clear(sf::Color(r1, g1, b1));

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
			// jezeli kliknelismy w wybor numeru ramki i nie chemy sie przeniesc do aktualnej ramki albo do ramki poza zakresem istniejacych
			string nowy = current.getText().substr(0, (current.getText().length()-1));
			string nowy2 = after_f.getText().substr(0, (after_f.getText().length() - 1));
			//string nowy = current.getText();
			if (click == true && (nowy == to_string(curr_f) || nowy > to_string(n_images))) {
				buttons[12].clicked = false;
				click = false;
				current.setSelected(false);
				current.setText(to_string(curr_f));
			}
			if (click == true && nowy!=to_string(curr_f) && nowy<=to_string(n_images)) {
				//up();
				string s1 = "C:/Users/Administrator/source/repos/Animation_gif_maker/x64/Debug/frames/" + to_string(curr_f) + ".jpg";
				s2 = "C:/Users/Administrator/source/repos/Animation_gif_maker/x64/Debug/frames/" + nowy + ".jpg";
				up(s1);
				gif.take_screenshot(window,s1,tex);
				curr_f = atoi(nowy.c_str());
				circles.clear();
				yes2 = false;
				yes = true;
				buttons[12].clicked = false;
				cout << "aktualna" << curr_f << endl;
				cout << "indeks wszystkich" << n_images << endl;
				current.setSelected(false);
				click = false;
				current.setText(to_string(curr_f));
				//window.draw(sprite);
			}
			else if (click2 == true && nowy2 <= to_string(n_images)) {
				n_images++;
				//int n = atoi(nowy2.c_str())+1;
				string s1 = "C:/Users/Administrator/source/repos/Animation_gif_maker/x64/Debug/frames/" + to_string(curr_f) + ".jpg";
				//string s2 = "C:/Users/Administrator/source/repos/Animation_gif_maker/x64/Debug/frames/" + to_string(n) + ".jpg";
				int p = curr_f;
				up(s1);
				curr_f = atoi(nowy2.c_str()) + 1;
				string s = "C:/Users/Administrator/source/repos/Animation_gif_maker/x64/Debug/frames/" + to_string(curr_f) + ".jpg";
				gif.take_screenshot(window, s1, tex);
				for (int i = n_images-1; i >= curr_f; i--) {
					sf::Image image;
					string s2 = "C:/Users/Administrator/source/repos/Animation_gif_maker/x64/Debug/frames/" + to_string(i) + ".jpg";
					string s3 = "C:/Users/Administrator/source/repos/Animation_gif_maker/x64/Debug/frames/" + to_string(i + 1) + ".jpg";
					if (!image.loadFromFile(s2))
						cout << "error_copy" << endl;
					if (image.saveToFile(s3))
					{
						std::cout << "new saved to " << std::endl;
					}
				}
				//string ss= "C:/Users/Administrator/source/repos/Animation_gif_maker/x64/Debug/frames/" + to_string(n_images) + ".jpg";
				string ss= "C:/Users/Administrator/source/repos/Animation_gif_maker/x64/Debug/frames/" + to_string(p) + ".jpg";
				remove(s.c_str());
				if (set == 2) {
					gif.copy_frame(curr_f-1, ss);
					current.setText(to_string(curr_f));
					set = 0;
					yes2 = true;
				}
				if (set == 1) {
					circles.clear();
					r1 = g1 = b1 = 255;
					current.setText(to_string(curr_f));
					set = 0;
					yes2 = false;
				}
				after_f.setText(to_string(curr_f));
				yes = false;
				//str = "C:/Users/Administrator/source/repos/Animation_gif_maker/x64/Debug/frames/" + to_string(n_images) + ".jpg";
				str = "C:/Users/Administrator/source/repos/Animation_gif_maker/x64/Debug/frames/" + to_string(n_images) + ".jpg";
				wys = "C:/Users/Administrator/source/repos/Animation_gif_maker/x64/Debug/frames/" + to_string(p) + ".jpg";
				buttons[8].clicked = false;
				after_f.setSelected(false);
				click2 = false;


			}
			//current.setSelected(false);
			//textbox1.setSelected(true);
		}

		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case::sf::Event::Closed:
				window.close();
				break;
			case::sf::Event::TextEntered:
				if (click == true) { current.typenOn(event); }
				if (click2 == true) { after_f.typenOn(event); }
				//textbox1.typenOn(event);
				break;
			case::sf::Event::MouseMoved:
				onMouseMovedButton();
				for (int i = 0; i < 14; i++) {
					if (paint[i].isMouseOver(window)) {
						paint[i].setBackColor(sf::Color(156, 156, 156));
					}
					else {
						if (paint[i].clicked == true) {
							paint[i].setBackColor(sf::Color(156, 156, 156));
						}
						else {
							paint[i].setBackColor(sf::Color(231, 230, 242));
						}
					}
				}
				break;
			case::sf::Event::MouseButtonPressed:
				if (event.mouseButton.button == sf::Mouse::Left) {
					onClickedButton();
					for (int i = 0; i < 14; i++) {
						if (paint[i].isMouseOver(window)) {
							if (paint[i].clicked == false) {
								if (i == 0 || i == 1 || i == 13) {
									paint[0].clicked = false;
									paint[1].clicked = false;
									paint[13].clicked = false;
									paint[i].clicked = true;
								}
								else if (i > 1 && i < 13) {
									for (int j = 2; j < 13; j++) {
										paint[j].clicked = false;
									}
									paint[i].clicked = true;
								}
							}
							if(paint[0].clicked == true){
								int j = 0;
								for (int k = 2; k < 13; k++) {
									if (paint[k].clicked == true) { j = k; break; }
									j = 0;
								}
								if (j != 0) {
									r = one.c[j - 2][0];
									g = one.c[j - 2][1];
									b = one.c[j - 2][2];
									draw = 0;
								}
							}
							if (paint[1].clicked == true) {
								int j = 0;
								for (int k = 2; k < 13; k++) {
									if (paint[k].clicked == true) { j = k; break; }
									j = 0;
								}
								if (j != 0) {
									r1 = one.c[j - 2][0];
									g1 = one.c[j - 2][1];
									b1 = one.c[j - 2][2];
									draw = 1;
								}
							}
							if (paint[13].clicked == true) {
								int j = 0;
								for (int k = 2; k < 13; k++) {
									if (paint[k].clicked == true) { j = k; break; }
									j = 0;
								}
								if (j != 0) {
									r = r1;
									g = g1;
									b = b1;
									draw = 2;
								}
							}
						}
					}
				}

			}
		}

			for (std::vector<sf::RectangleShape>::iterator it = one.rects.begin(); it != one.rects.end() - 4; ++it)
			{
				window.draw(*it);
			}


			for (int i = 0; i < 14; i++) {
				paint[i].drawTo(window);
			}

			for (std::vector<sf::CircleShape>::iterator it = one.colors.begin(); it != one.colors.end(); ++it)
			{
				window.draw(*it);
			}

			for (int i = 0; i < 3; i++) { one.cirs[i].setTexture(&textures[i]); }


			for (std::vector<sf::CircleShape>::iterator it = one.cirs.begin(); it != one.cirs.end(); ++it)
			{
				window.draw(*it);
			}

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				x = (float)sf::Mouse::getPosition((window)).x;
				y = (float)sf::Mouse::getPosition((window)).y;


				if (x > 150 && x < 750 && y < 540)
				{
					sf::CircleShape point(paint_thick);
					if (draw == 2) {
						//r = r1;
						//g = g1;
						//b = b1;
						point.setPosition(x, y);
						point.setFillColor(sf::Color(r, g, b));
						add(point);
					}
					else if (draw == 0)
					{
						point.setPosition(x, y);
						point.setFillColor(sf::Color(r, g, b));
						add(point);
					}

				}

				/*			if (x > 750)
							{
								if (y < 43 && x < 825) {
									double distance = sqrt(pow((x - brush.getPosition().x), 2) + pow((y - brush.getPosition().y), 2));
									if (distance <= 30) { draw = 0; }
								}
								if (y < 43 && x > 825) {
									double distance = sqrt(pow((x - bucket.getPosition().x), 2) + pow((y - bucket.getPosition().y), 2));
									if (distance <= 30) { draw = 1; }
								}
								if (y > 516 && x > 825) {
									double distance = sqrt(pow((x - eraser.getPosition().x), 2) + pow((y - eraser.getPosition().y), 2));
									if (distance <= 30) { draw = 2; }
								}
								else {
									for (int i = 0; i < 11; i++)
									{
										double distance = sqrt(pow((x - colors[i].getPosition().x), 2) + pow((y - colors[i].getPosition().y), 2));
										if (distance <= 30) {
											if (draw == 0) {
												r = c[i][0];
												g = c[i][1];
												b = c[i][2];
												break;
											}
											else if (draw==1)
											{
												r1 = c[i][0];
												g1 = c[i][1];
												b1 = c[i][2];
												break;
											}
										}
									}
								}
							} */
			}


			window.draw(line_above_delete, 2, sf::Lines);
			window.draw(line_below_thick, 2, sf::Lines);
			window.draw(line_above_text_frame, 2, sf::Lines);
			window.draw(frame);

			for (int i = 0; i < buttons.size(); i++) {
				buttons[i].drawTo(window);
			}

			for (std::vector<sf::RectangleShape>::iterator it = one.rects.begin() + 3; it != one.rects.end(); ++it)
			{
				window.draw(*it);
			}

			window.draw(frame_number);
			window.draw(go_to);
			after_f.drawTo(window);

			for (std::vector<sf::CircleShape>::iterator it = one.dots.begin(); it != one.dots.end(); ++it)
			{
				window.draw(*it);
			}

			window.draw(line1, 2, sf::Lines);
			window.draw(line2, 2, sf::Lines);
			window.draw(line3, 2, sf::Lines);
			current.drawTo(window);
			if (yes == true) {
				if (!t.loadFromFile(s2, sf::IntRect(150, 0, 599, 538))) { cout << "error_loading" << endl; }
				sprite.setTexture(t, true);
				sprite.setPosition(150, 0);
				window.draw(sprite);
			}
			if (yes2 == true) {
				if (!t.loadFromFile(wys, sf::IntRect(150, 0, 599, 538))) { cout << "error_loading" << endl; }
				sprite.setTexture(t, true);
				sprite.setPosition(150, 0);
				window.draw(sprite);
			}
			
			update();
			window.display();
		}

		return EXIT_SUCCESS;
}