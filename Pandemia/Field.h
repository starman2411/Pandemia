#ifndef FIELD_H_INCLUDED
#define FIELD_H_INCLUDED
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;
class Field {
private:
    int trigger,trigger2,x0,y0,active_sprite;
    float increase;
    Image background1, background2;
    Texture texture1,texture2;
    Sprite sprite1, sprite2;
public:
    Field(){
    active_sprite=1;
    x0 = 0;
    y0 = graph_heigh;
    trigger=0;
    trigger2=0;
    increase=graph_heigh/100.0;
    sprite1.setPosition(0,0);
    sprite2.setPosition(graph_width,0);
    background1.create(graph_width,graph_heigh+1, Color::Black);
    background2.create(graph_width,graph_heigh+1, Color::Black);
    }

    void add_column_down(int x, int y, Color color)
    {
        if (x + x0 >= graph_width) trigger = 1;
                if ((trigger == 1)&&(trigger2 == 0)){
            active_sprite=2;
            trigger2=1;
        }
        if (active_sprite == 1) {
                for (int i=0;i<y*increase;++i){
                background1.setPixel(x0 + x%graph_width,y0 - i,color);}
            }


        if (active_sprite == 2) {
                for (int i=0;i<y*increase;++i){
                background2.setPixel(x0 + x%graph_width,y0 - i,color);}
            }
            }

        void add_column_up(int x, int y, Color color)
    {
        if (x + x0>=graph_width) trigger=1;
        if (active_sprite == 1) {
                for (int i=0;i<y*increase;++i){
                background1.setPixel(x0 + x%graph_width,i,color);}
            }


        if (active_sprite == 2)
            for (int i=0;i<y*increase;++i)
                background2.setPixel(x0 + x%graph_width,i,color);

        }

    void draw(RenderWindow& window){

        texture1.loadFromImage(background1);
        texture2.loadFromImage(background2);
        sprite1.setTexture(texture1);
        sprite2.setTexture(texture2);

        if (trigger != 0){
            sprite1.move(-1,0);
            sprite2.move(-1,0);}
        if (sprite1.getPosition().x <= -graph_width) {
            sprite1.setPosition(graph_width,0);
            if (active_sprite == 1) {
                    active_sprite=2;}
            else {
                    active_sprite=1;}
            background1.create(graph_width,graph_heigh+1, Color::Black);

        }
        if (sprite2.getPosition().x<=-graph_width) {
            sprite2.setPosition(graph_width,0);
        if (active_sprite==1) {active_sprite=2;}else {active_sprite=1;}
            background2.create(graph_width,graph_heigh+1, Color::Black);

        }
        window.draw(sprite1);
        window.draw(sprite2);
    }

};



#endif // FIELD_H_INCLUDED
