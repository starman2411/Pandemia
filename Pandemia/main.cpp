#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include "constants.h"
#include "Field.h"
#include "functions.h"
#include "Person.h"
#include "Plot.h"
#include "Society.h"
#include <cstring>
#include <SFML/Audio.hpp>

using namespace std;
using namespace sf;
int main()
{


    bool buttontrigger = false;
    if (number_of_run==0) communicating_with_user();
    number_of_run++;
    string str1="Results/";
    string str3=".txt";
    ofstream outfile;
    outfile.open(str1 + name_of_file + str3);
    outfile<<"time"<<" "<<"infected"<<" "<<"recovered"<<endl;

    int time_of_program = 0;
    Music music;
    music.openFromFile("music.ogg");


    sf::RenderWindow window(sf::VideoMode(width, heigh), "Model of the epidemic");
    sf::RenderWindow statistic_window(sf::VideoMode(50, 260), "Statistics");
    sf::RenderWindow graph_window(sf::VideoMode(graph_width, graph_heigh), "Graph");
    Vector2<int> v;

    vector<Person> haos;

    for (int i = 0;i < population; i++)
        haos.push_back(Person(2,2,2));

    haos[50].update_status(1);
    Society society(users_recovery_time, users_infecting_distance, users_infecting_prob, &haos);

    Field graphs;
    Plot plot_infected(graphs,Color::Red);
    Plot plot_recovered(graphs,Color::White,1);

    window.setFramerateLimit(frame_limit);
    if (music_flag) music.play();
    while (window.isOpen())
    {
        v = window.getPosition();
        v.x -= statistic_window.getSize().x;
        statistic_window.setPosition(v);
        v = window.getPosition();
        v.x += width;
        graph_window.setPosition(v);
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)

                window.close();

        }
        window.clear();
        statistic_window.clear();
        graph_window.clear();


        if(buttontrigger == false)
            while(Keyboard::isKeyPressed(Keyboard::Space))
            buttontrigger = true;

        if(buttontrigger == true){
        while(!Keyboard::isKeyPressed(Keyboard::Space)){};
        while(Keyboard::isKeyPressed(Keyboard::Space)){};
        }
        buttontrigger = false;

        time_of_program++;
        if(hubwork) society.hub(window, users_infecting_prob_H, users_number_of_people_H, users_time_H);
        society.infection();
        society.run(window);

        plot_infected.add_point(time_of_program,society.get_infected()*100/population);
        plot_recovered.add_point(time_of_program,society.get_recovered()*100/population);
        graphs.draw(graph_window);

        society.statistics(statistic_window, "arial.ttf");
        window.display();
        statistic_window.display();
        graph_window.display();
        outfile<<time_of_program<<","<<society.get_infected()<<","<<society.get_recovered()<<endl;
    }
    statistic_window.close();
    graph_window.close();

    outfile.close();

    char repeat;
    cout << "repeat? (Y|N): " << endl;
        cin >> repeat;
        if((repeat == 'Y')||(repeat == 'y')) {

                main();}
    return 0;
}
