#include <SFML/Graphics.hpp>
#include "ResourceMgr.h"
#include "Player.h"

int main()
{
    ResourceMgr::GetInstance()->LoadAll();
    Player player;
    player.Init();
    sf::RenderWindow window(sf::VideoMode(512, 512), "Demo Animation");

    Clock clock;
    while (window.isOpen())
    {
        Time dt = clock.restart();
        sf::Event event;
        while (window.pollEvent(event))
        {
            player.UpdateInput(event);
            if (event.type == sf::Event::Closed)
                window.close();
        }
       
        player.Update(dt.asSeconds());

        window.clear();
        player.Draw(window);
        window.display();
    }
    ResourceMgr::GetInstance()->ReleaseAll();;
    return 0;
}