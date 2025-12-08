#include "UI.h"
#include <iostream>

std::string toUpper(std::string s)
{
    for (char &c : s) c = toupper(c);
    return s;
}

UI::UI()
: window(sf::VideoMode(1280, 800), "SDSU maps")
{
    if (!mapTexture.loadFromFile("assets/sdsu_map.png"))
    {
        std::cout << "Failed to load map\n";
    }
    mapSprite.setTexture(mapTexture);

    buildings =
    {
        {0, "LAMDEN",      {1085, 145}, sf::Color::Cyan},
        {1, "BOOKSTORE",   {700, 300},  sf::Color::Yellow},
        {2, "MANCHESTER",  {850, 520},  sf::Color::Blue},
        {3, "ADMIN",       {300, 360},  sf::Color(255,105,180)},
        {4, "LOVE",        {480, 520},  sf::Color::Red},
        {5, "BELL",        {430, 330},  sf::Color(255,140,0)},
        {6, "STUDENT",     {1010, 350}, sf::Color::Green},
        {7, "EDU",        {800, 170},  sf::Color(255,106,33)},
    };

    graph.setSize(buildings.size());

    for (auto &b : buildings)
    {
        std::string key = toUpper(b.name);
        buildingTree.insert(key, b.id);
        graph.addBuildingCode(key, b.id);
    }

    graph.addCourseLocation("CS210", "GMCS");
    graph.addCourseLocation("CS370", "GMCS");
    graph.addCourseLocation("ART100", "ARC");
    graph.addCourseLocation("FIN240", "EBA");

    auto E = [&](int a, int b){ graph.addEdge(a,b,1); };

    E(0,7);E(0,6);E(7,1);E(1,5);E(1,4);E(5,3);E(3,4);E(4,2);E(2,0);
    E(1,2);E(7,6);E(2,7);E(1,6);E(4,5);E(3,0);E(1,0);E(2,6);E(3,6);

    walker.setRadius(12);
    walker.setOrigin(4,4);
    walker.setFillColor(sf::Color::Black);

    clock.restart();
}

int UI::detectClick(const sf::Vector2f &m) const
{
    for (int i = 0; i < buildings.size(); i++)
    {
        sf::Vector2f p = buildings[i].position;
        float dx = m.x - p.x;
        float dy = m.y - p.y;
        if (dx*dx + dy*dy < 25*25) return i;
    }
    return -1;
}

void UI::handleClick(int idx)
{
    if (idx == -1) return;

    if (selectedA == -1)
    {
        selectedA = idx;
    }
    else if (selectedB == -1)
    {
        history.push(selectedA);
        selectedB = idx;
    }
    else
    {
        history.push(selectedA);
        history.push(selectedB);

        selectedA = idx;
        selectedB = -1;
    }

    if (selectedA != -1 && selectedB != -1)
    {
        activePath = graph.shortestPath(selectedA, selectedB);
        if (activePath.size() >= 2)
        {
            animating = true;
            t = 0.f;
            pathPos = 0;
            walker.setPosition(buildings[activePath[0]].position);
        }
    }
}

void UI::undo()
{
    if (history.empty())
    {
        std::cout << "No previous destinations in history.\n";
        return;
    }

    if (selectedA != -1 && selectedB != -1)
    {
        selectedB = -1;
        activePath.clear();
        animating = false;

        if (!history.empty())
        {
            selectedA = history.top();
            history.pop();
        }

        std::cout << "Undo → Cleared destination, back to start: " << selectedA << "\n";
    }

    else if (selectedA != -1)
    {
        if (!history.empty())
        {
            selectedA = history.top();
            history.pop();
            std::cout << "Undo → Back to: " << selectedA << "\n";
        }
        else
        {
            selectedA = -1;
            std::cout << "Undo → Cleared selection\n";
        }
    }
}

void UI::processSearchInput()
{
    std::string key = toUpper(typedInput);
    std::cout << "Searching for: " << key << "\n";

    int idx = graph.indexFromCourse(key);
    if (idx == -1)
        idx = buildingTree.find(key);

    if (idx == -1)
    {
        std::cout << "Unknown building: " << key << "\n";
        return;
    }

    if (selectedA == -1)
    {
        selectedA = idx;
    }
    else if (selectedB == -1)
    {
        history.push(selectedA);
        selectedB = idx;
    }
    else
    {
        history.push(selectedA);
        history.push(selectedB);
        selectedA = idx;
        selectedB = -1;
    }

    if (selectedA != -1 && selectedB != -1)
    {
        activePath = graph.shortestPath(selectedA, selectedB);
        animating = true;
        t = 0.f;
        pathPos = 0;
        walker.setPosition(buildings[activePath[0]].position);
    }
}

void UI::handleText(sf::Event &e)
{

    if (e.text.unicode == 13)
        return;
    if (e.text.unicode == 'U' || e.text.unicode == 'u')
        return;

    if (e.text.unicode == 8 && !typedInput.empty())
    {
        typedInput.pop_back();
        return;
    }

    if (e.text.unicode >= 32 && e.text.unicode <= 126)
    {
        typedInput += (char)toupper(e.text.unicode);
    }
}

void UI::processCourse()
{
    int idx = graph.indexFromCourse(typedInput);
    if (idx == -1) idx = buildingTree.find(typedInput);
    if (idx == -1) return;

    if (selectedA == -1) selectedA = idx;
    else selectedB = idx;

    if (selectedA != -1 && selectedB != -1)
    {
        activePath = graph.shortestPath(selectedA, selectedB);
        if (activePath.size() >= 2)
        {
            animating = true;
            t = 0.f;
            pathPos = 0;
            walker.setPosition(buildings[activePath[0]].position);
        }
    }
}

void UI::animateWalker(float dt)
{
    if (!animating || activePath.empty() || pathPos >= (int)activePath.size() - 1)
        return;

    int a = activePath[pathPos];
    int b = activePath[pathPos + 1];

    sf::Vector2f A = buildings[a].position;
    sf::Vector2f B = buildings[b].position;

    t += walkSpeed * dt;

    if (t >= 1.f)
    {
        t = 0.f;
        pathPos++;

        if (pathPos >= (int)activePath.size() - 1)
        {
            animating = false;
            walker.setPosition(B);

            return;
        }
    }

    walker.setPosition(A + (B - A) * t);
}

void UI::drawScene()
{
    window.clear();
    window.draw(mapSprite);

    std::vector<sf::Vector2f> pos;
    for (auto &b : buildings) pos.push_back(b.position);
    graph.drawEdges(window, pos);

    sf::Font font;
    font.loadFromFile("fonts/Arial.ttf");

    for (auto &b : buildings)
    {
        b.draw(window);
        sf::Text label(b.name, font, 14);
        label.setFillColor(sf::Color::Black);
        label.setPosition(b.position.x+10, b.position.y-10);
        window.draw(label);
    }

    float dt = clock.restart().asSeconds();
    animateWalker(dt);
    window.draw(walker);

    sf::Text t("Find BUILDING: " + typedInput, font, 18);
    t.setFillColor(sf::Color::Black);
    t.setPosition(10, 10);
    window.draw(t);

    sf::Text undoLabel("Press U to Undo", font, 18);
    undoLabel.setFillColor(sf::Color::Black);
    undoLabel.setPosition(10, 40);
    window.draw(undoLabel);

    window.display();
}

void UI::run()
{
    while (window.isOpen())
    {
        sf::Event e;
        while (window.pollEvent(e))
        {
            if (e.type == sf::Event::Closed)
                window.close();

            else if (e.type == sf::Event::KeyPressed)
            {
                if (e.key.code == sf::Keyboard::U)
                {
                    std::cout << "Undo pressed!\n";
                    undo();
                    continue;
                }
                else if (e.key.code == sf::Keyboard::Enter)
                {
                    std::cout << "Enter pressed! Processing search.\n";
                    processSearchInput();
                    typedInput.clear();
                    continue;
                }
            }
            else if (e.type == sf::Event::MouseButtonPressed &&
                     e.mouseButton.button == sf::Mouse::Left)
            {
                int idx = detectClick({(float)e.mouseButton.x, (float)e.mouseButton.y});
                handleClick(idx);
            }

            else if (e.type == sf::Event::TextEntered)
            {
                handleText(e);
            }
        }

        drawScene();
    }
}



