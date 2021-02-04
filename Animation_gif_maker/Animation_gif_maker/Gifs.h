#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>
#include <list>
#include <direct.h>
#include <string>

using namespace std;

class Gifs {
public:
    Gifs() {
    }

    void take_screenshot(const sf::RenderWindow& window, const std::string& filename, const sf::RenderTexture& tex)
    {
        const sf::Texture& texture = tex.getTexture();
        //texture.create(window.getSize().x, window.getSize().y);
        //texture.update(window);
        //texture.update(tex.getTexture());
        if (texture.copyToImage().saveToFile(filename))
        {
            std::cout << "screenshot saved to " << filename << std::endl;
        }
        else
        {
            // Error handling
        }

    }

    void copy_frame(int n_images, const std::string& filename)
    {
        sf::Image image;
        string s = "C:/Users/Administrator/source/repos/Animation_gif_maker/x64/Debug/frames/" + to_string(n_images+1) + ".jpg";
        if (!image.loadFromFile(filename))
            cout << "error_copy" << endl;
        if (image.saveToFile(s))
        {
            std::cout << "copy saved to " << filename << std::endl;
        }
        else
        {
            // Error handling
        }

    }

    void go_to_frame() {

    }

};