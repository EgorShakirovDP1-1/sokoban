#define SFML_NO_DEPRECATED_WARNINGS

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdio.h>

using namespace sf;
using namespace std;

#define SIZEX 12
#define SIZEY 12
#define SIZEF 48

char board[SIZEX][SIZEY] = {
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
        { 1, 0, 0, 0, 0, 4, 4, 4, 0, 0, 0, 1 },
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
        { 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1 },
        { 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1 },
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
        { 1, 0, 0, 2, 0, 1, 0, 0, 0, 0, 0, 1 },
        { 1, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 1 },
        { 1, 0, 0, 0, 2, 1, 0, 0, 0, 0, 0, 1 },
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
};
Vector2i human_vect(6, 9);

Sprite box;
Sprite place;
Sprite human;
Sprite wall;
Sprite pustoi;

vector <Vector2i> boxes;
vector <Vector2i> places;

void loadPosition()
{
    for (int i = 0; i < SIZEX; i++)
    {
        for (int j = 0; j < SIZEY; j++)
        {
            if (board[i][j] == 1)
            {
                wall.setPosition(i * SIZEF, j * SIZEF);
            }
            else
            if (board[i][j] == 2)
            {
                boxes.push_back(Vector2i(i, j));
                box.setPosition(i * SIZEF, j * SIZEF);
            }
            else
            if (board[i][j] == 4)
            {
                place.setPosition(i * SIZEF, j * SIZEF);
            }
            else
            if (board[i][j] == 0)
                pustoi.setPosition(i * SIZEF, j * SIZEF);
        }
    }
    human.setPosition(human_vect.x * SIZEF, human_vect.y * SIZEF);

}

int main(int argv, char *argc[])
{

    RenderWindow window(VideoMode(SIZEX * SIZEF, SIZEY * SIZEF), "Sokoban!");
    window.setFramerateLimit(60);

    Texture t2, t7;
    t2.loadFromFile("images/background.jpg");
    t7.loadFromFile("images/figures.png");

    box.setTexture(t7);		box.setTextureRect(IntRect(0, 0, SIZEF, SIZEF));
    place.setTexture(t7);   place.setTextureRect(IntRect(SIZEF, 0, SIZEF, SIZEF));
    human.setTexture(t7);   human.setTextureRect(IntRect(2 * SIZEF, 0, SIZEF, SIZEF));
    wall.setTexture(t7);    wall.setTextureRect(IntRect(3 * SIZEF, 0, SIZEF, SIZEF));
    pustoi.setTexture(t7);   pustoi.setTextureRect(IntRect(4 * SIZEF, 0, SIZEF, SIZEF));

    loadPosition();

    //int even = 0;
    while (window.isOpen())
    {
        Event e;
        while (window.pollEvent(e))
        {
            if (e.type == Event::Closed)
                window.close();
            if (e.type == Event::KeyPressed){
                if(Keyboard::isKeyPressed(sf::Keyboard::Up) && board[human_vect.x][human_vect.y - 1] != 1){
                    human_vect.y -= 1;

                }
                if(Keyboard::isKeyPressed(sf::Keyboard::Down) && board[human_vect.x][human_vect.y + 1] != 1){
                    human_vect.y += 1;

                }
                if(Keyboard::isKeyPressed(sf::Keyboard::Left) && board[human_vect.x -1 ][human_vect.y] != 1){
                    human_vect.x -= 1;

                }
                if(Keyboard::isKeyPressed(sf::Keyboard::Right) && board[human_vect.x + 1][human_vect.y] != 1){
                    human_vect.x += 1;

                }
            }

            loadPosition();
        }
        window.clear();

        for (int i = 0; i < SIZEX; i++)
        {
            for (int j = 0; j < SIZEY; j++)
            {
                if (board[i][j] == 1)
                {
                    wall.setPosition(i * SIZEF, j * SIZEF);
                    window.draw(wall);
                }
                else
                if (board[i][j] == 2)
                {
                    box.setPosition(i * SIZEF, j * SIZEF);
                    window.draw(box);
                }
                else
                if (board[i][j] == 4)
                {
                    place.setPosition(i * SIZEF, j * SIZEF);
                    window.draw(place);
                }
                else
                if (board[i][j] == 0)
                {
                    pustoi.setPosition(i * SIZEF, j * SIZEF);
                    window.draw(pustoi);
                }
            }
        }
        window.draw(human);
        window.display();
    }
    return 0;
}
