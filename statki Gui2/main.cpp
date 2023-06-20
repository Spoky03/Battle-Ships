#include "display.cpp"
int main()
{
    int roundCount=statki();
    int boardPositionCount = boardState->size();
    sf::RenderWindow window(sf::VideoMode(sizeWindow, sizeWindow+50), "Statki");
    //window display loop
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (boardState->at(stateIndex).round==roundCount)
            {
                window.clear();
                win(window, roundCount);
                window.display();
            }
            
                if (event.type == sf::Event::Closed) {window.close();} //window close event handling
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) and stateIndex > 0){
                stateIndex--;
                window.clear();
                drawBoard(window, boardState->at(stateIndex).tab, n);
                window.display();
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) and stateIndex < boardPositionCount-1){
                stateIndex++;
                window.clear();
                drawBoard(window, boardState->at(stateIndex).tab, n);
                window.display();
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){window.close();}      
        }       
        
    }
    delete[] boardState;
    return 0;
}
