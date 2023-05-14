#ifndef PERSON_H_INCLUDED
#define PERSON_H_INCLUDED
class Person{
    private:
        CircleShape dot;
        int x;
        int y;
        int radius;
        int probability_of_turn;
        int speed;
        int status; //1 - заражён 2-выздоровел 0 - не болел
        int time_of_infection; //время, которе он уже заражён
        int angle; //от 1 до 8
        int amount_of_infected; //сколько он заразил
        bool infect;
    public:
        Person(int radius,int speed,int probability_of_turn){
            time_of_infection = 0;
            x=rand()%width;
            y=rand()%heigh;
            this->radius=radius;
            this->speed=speed;
            this->probability_of_turn=probability_of_turn;
            status=0;
            angle=rand()%8;
            dot.setRadius(radius);
            amount_of_infected = 0;
            dot.setPosition(x,y);
            dot.setFillColor(Color::Green);
            infect = false;
        }

        int get_x() {return(x);};
        int get_y() {return(y);};
        bool get_infect(){return infect;}
        void set_infect(bool p){infect = p;}
        int get_status() {return(status);};
        int get_time_of_infection(){return (time_of_infection);};
        int get_angle(){return(angle);};
        int get_amount_of_infected(){return(amount_of_infected);};
        void set_amount_of_infected(int n){amount_of_infected = n;}

        void update_status(int new_status){//0 - healthy, 1 - infected, 2 - recovered, 3 - healthy in the hub, 4 - infected in the hub, 5 - recovered in the hub

            status = new_status;
            if ((status == 1)||(status == 4)) dot.setFillColor(Color::Red);
                else
                    if ((status == 2)||(status == 5)) dot.setFillColor(Color::White);
                        else dot.setFillColor(Color::Green);
            if((status >= 3)&&(status <= 5)) {x = width / 2; y = heigh / 2;}


        }

        void mooving(RenderWindow& window){
        int dx=0;
        int dy=0;

        if(status == 1) time_of_infection++;

        if (probability(probability_of_turn)==true){
            angle=rand()%8;
        }

        switch(angle)
        {
            case 0: dx = 0; dy = - speed;break;
            case 1: dx = speed; dy = - speed;break;
            case 2: dx = speed; dy = 0;break;
            case 3: dx = speed; dy = speed;break;
            case 4: dx = 0; dy = speed;break;
            case 5: dx = - speed; dy = speed;break;
            case 6: dx = - speed; dy = 0;break;
            case 7: dx = - speed; dy = - speed;break;

        }

         x += dx;
         y += dy;

        if (x + 2 * radius + 1 >= width) {
            switch (angle)
            {
                case 1: angle = 7;break;
                case 2: angle = 6;break;
                case 3: angle = 5;break;
            }
            x = width - 2 * radius - 1;
         }

        if (x - 1 <= 0) {
            switch (angle)
            {
                case 7: angle = 1;break;
                case 6: angle = 2;break;
                case 5: angle = 3;break;
            }
            x = 1;
         }

        if (y - 1 <= 0) {
            switch (angle)
            {
                case 7: angle = 5;break;
                case 0: angle = 4;break;
                case 1: angle = 3;break;
            }
            y = 1;
         }

        if (y + 2 * radius + 1 >= heigh) {
            switch (angle)
            {
                case 5: angle = 7; break;
                case 4: angle = 0; break;
                case 3: angle = 1; break;
            }
            y = heigh - 2 * radius - 1;
         }

         if((status >= 3)&&(status <= 5)){

            if (x + 2 * radius + 1 >= (width + hubside) / 2) {
            switch (angle)
            {
                case 1: angle = 7;break;
                case 2: angle = 6;break;
                case 3: angle = 5;break;
            }
            x = (width + hubside) / 2 - 2 * radius - 1;
         }
         if (x - 1 <= (width - hubside) / 2) {
            switch (angle)
            {
                case 7: angle = 1;break;
                case 6: angle = 2;break;
                case 5: angle = 3;break;
            }
            x = (width - hubside) / 2 + 1;
         }
        if (y - 1 <= (heigh - hubside) / 2) {
            switch (angle)
            {
                case 7: angle = 5;break;
                case 0: angle = 4;break;
                case 1: angle = 3;break;
            }
            y = (heigh - hubside) / 2 + 1;
         }

        if (y + 2 * radius + 1 >= (heigh + hubside) / 2) {
            switch (angle)
            {
                case 5: angle = 7; break;
                case 4: angle = 0; break;
                case 3: angle = 1; break;
            }
            y = (heigh + hubside) / 2 - 2 * radius - 1;
         }
         }

         dot.setPosition(x, y);
         window.draw(dot);
        };

};


#endif // PERSON_H_INCLUDED
