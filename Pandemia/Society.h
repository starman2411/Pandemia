#ifndef SOCIETY_H_INCLUDED
#define SOCIETY_H_INCLUDED

#include <SFML/Graphics.hpp>

class Society{
private:
    vector<Person> all;
    int infected;
    int recovered;
    int healthy;
    int max_infected;
    float max_R;
    int max_D;
    int rec_time;
    int distance;
    int inf_percent;
    int hubshift;
    int timer;
    int counter;
    int last_amount_of_infected;
    int last_speed_of_growth;
    double R;

public:
    Society(int recovery_time, int infecting_distance, int infecting_percent, vector<Person> *vec){
    rec_time = recovery_time;
    distance = infecting_distance;
    inf_percent = infecting_percent;
    infected = 1;
    recovered = 0;
    max_infected=0;
    max_R=0;
    R=0;
    max_D=0;
    counter=0;
    last_speed_of_growth=0;
    last_amount_of_infected=0;
    healthy = population - 1;
    all = *vec;
    hubshift = 0;
    timer = 0;
    }

    double get_R(){return R;}

    int get_infected(){
       return infected;
    }

    int get_recovered(){
        return recovered;
        }

    int get_healthy(){
        return healthy;
        }

    void infection(){
        int p = 0;
        int n = 0;
        bool flag = false;
        vector<Person>::iterator fi;
        vector<Person>::iterator si;
        for(fi = all.begin(); fi != all.end(); ++fi){
            for(si = all.begin(); si != all.end(); ++si)
                    if((fi->get_status() == 0)&&
                       (si->get_status() == 1)&&
                       (abs(si->get_x() - fi->get_x()) <= distance)&&
                       (abs(si->get_y() - fi->get_y()) <= distance)&&
                       (probability(inf_percent) == true))
                        {fi->update_status(1);
                        si->set_amount_of_infected(si->get_amount_of_infected() + 1);
                        infected++; healthy--;
                        si->set_infect(true);}

            if((fi->get_status() == 1)&&(fi->get_time_of_infection() >= rec_time)) {fi->update_status(2); recovered++;infected--;}
            if((fi->get_status() == 4)&&(fi->get_time_of_infection() >= rec_time)) {fi->update_status(5); recovered++;infected--;}
            flag = false;
        }

        for(fi = all.begin(); fi != all.end(); ++fi)
            if(fi->get_infect()) {p += fi->get_amount_of_infected(); n++;}

        if((n != 0 )&&(p != 0)) R = p  * 1.0  / n;
    }

    void run(RenderWindow& window){
        vector<Person>::iterator it;
        for(it = all.begin(); it != all.end(); it++)
            it->mooving(window);
    }

    void statistics(RenderWindow& window, string file){
        counter++;
        Font font;
        string s = "R = ";
        string h = "D = ";
        string j= "max = ";
        string k= "max R = ";
        string l="max D = ";



        font.loadFromFile(file);
        Text H(translator(healthy)+"  ("+translator(healthy*100/population)+"%)", font, 20);
        Text I(translator(infected)+"  ("+translator(infected*100/population)+"%)", font, 20);
        Text R(translator(recovered)+"  ("+translator(recovered*100/population)+"%)", font, 20);
        Text Re(s + Rtranslator(this->get_R()), font, 20);
        Text speed_of_growth(h+translator(last_speed_of_growth),font,20);

        if ((last_speed_of_growth!=(infected-last_amount_of_infected))&&(counter>=20)){
            last_speed_of_growth=infected-last_amount_of_infected;
            speed_of_growth.setString(h+translator(last_speed_of_growth));
            counter=0;
        }
        last_amount_of_infected=infected;

        if (infected>max_infected) max_infected=infected;
        if (get_R()>max_R) max_R=get_R();
        if (last_speed_of_growth>max_D) max_D=last_speed_of_growth;

        Text I_max(j+translator(max_infected)+"  ("+translator(max_infected*100/population)+"%)", font, 20);
        Text Re_max(k+Rtranslator(max_R), font, 20);
        Text speed_of_growth_max(l+translator(max_D),font,20);

        H.setColor(Color::Green);
        I.setColor(Color::Red);
        R.setColor(Color::White);
        Re.setColor(Color::White);
        speed_of_growth.setColor(Color::White);
        I_max.setColor(Color::Red);
        Re_max.setColor(Color::White);
        speed_of_growth_max.setColor(Color::White);


        if(healthy <= 0) H.setString("0 (0%)");
        if(recovered <= 0) R.setString("0 (0%)");
        if(infected <= 0) I.setString("0 (0%)");
        if(this->get_R() <= 0) Re.setString("R = 0");
        if((last_speed_of_growth) == 0) speed_of_growth.setString("D = 0");


        H.setPosition(10, 10);
        I.setPosition(10, 30);
        R.setPosition(10, 50);
        Re.setPosition(10, 80);
        speed_of_growth.setPosition(10, 110);
        I_max.setPosition(10, 160);
        Re_max.setPosition(10, 190);
        speed_of_growth_max.setPosition(10, 220);

        window.draw(H);
        window.draw(I);
        window.draw(R);
        window. draw(Re);
        window. draw(speed_of_growth);
        window.draw(I_max);
        window. draw(Re_max);
        window. draw(speed_of_growth_max);

        }

    void hub(RenderWindow& window, int infecting_percent, int quantity, int t){

        RectangleShape square(Vector2f(hubside, hubside));
        square.setPosition(width / 2, heigh / 2);
        square.setOrigin(hubside / 2, hubside / 2);
        square.setOutlineThickness(1);
        square.setOutlineColor(Color::White);
        square.setFillColor(Color::Black);
        window.draw(square);

        if(timer % t == 0){
        for(int i = hubshift; i < hubshift + quantity; i++){
            if(all[i % population].get_status() == 0) all[i % population].update_status(3);
            if(all[i % population].get_status() == 1) all[i % population].update_status(4);
            if(all[i % population].get_status() == 2) all[i % population].update_status(5);
        }

        if(hubshift > 0) if(all[hubshift - 1].get_status() == 3) all[hubshift - 1].update_status(0);
        if(hubshift > 0) if(all[hubshift - 1].get_status() == 4) all[hubshift - 1].update_status(1);
        if(hubshift > 0) if(all[hubshift - 1].get_status() == 5) all[hubshift - 1].update_status(2);


        hubshift = (hubshift + 1) % (population + 1);
        }

         for(int i = hubshift - 1; i < hubshift - 1 + quantity; i++){
                for(int j = hubshift; j < hubshift + quantity; j++)
                if((all[i].get_status() == 3)&&
                (all[j].get_status() == 4)&&
                (abs(all[i].get_x() - all[j].get_x()) <= distance)&&
                (abs(all[i].get_y() - all[j].get_y()) <= distance)&&
                (probability(infecting_percent) == true)) {all[i].update_status(4); healthy--;infected++;}
        }

        timer++;
    }
};

#endif // SOCIETY_H_INCLUDED
