#include <iostream>
#include <string>
#include "code.cpp"
#include <SFML/Graphics.hpp>
//SFML statki
//render window
int stateIndex = 0;
void drawBoard (sf::RenderWindow &window, int board[n][n], int n)
{
    int N = sizeWindow/n;
    sf::RectangleShape rectangle(sf::Vector2f(sizeWindow/n,sizeWindow/n));
    rectangle.setFillColor(sf::Color::Transparent);
    rectangle.setOutlineColor(sf::Color::Black);
    rectangle.setOutlineThickness(1);
    //round counter text
    sf::Font font;
    font.loadFromFile("arial.ttf");
    sf::Text text;
    text.setFont(font);
    text.setString("Round:  "+ std::to_string(boardState->at(stateIndex).round)+ "                                             Stefan Grzelec 2023");
    text.setCharacterSize(36);
    text.setFillColor(sf::Color::Green);
    text.setPosition(0, sizeWindow);
    window.draw(text);
    // draw window
    for (int i = 0; i <n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            //each number in board array is a color
            rectangle.setPosition(  i * N, j * N);
            if (board[i][j] == 1)
            {
                rectangle.setFillColor(sf::Color::Black);
            }
            else if (board[i][j] == 2)
            {
                rectangle.setFillColor(sf::Color::Red);
            }
            else if (board[i][j] == 3)
            {
                rectangle.setFillColor(sf::Color::Blue);
            }
            else
            {
                rectangle.setFillColor(sf::Color::White);
            }
            window.draw(rectangle);
        }
    }
//win text
}
void win(sf::RenderWindow &window, int roundCount){
        sf::Font font;
        font.loadFromFile("arial.ttf");
        sf::Text winText;
        winText.setFont(font);
        winText.setString("Win in: " + std::to_string(roundCount) + " rounds");
        winText.setCharacterSize(36);
        winText.setFillColor(sf::Color::Magenta);
        winText.setPosition(600, sizeWindow);
        window.draw(winText);
}

  
//Stefan Grzelec 2023

