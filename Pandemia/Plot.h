#ifndef PLOT_H_INCLUDED
#define PLOT_H_INCLUDED

class Plot {
private:
	Color color;
	int type;
	Field* field;
public:
	Plot(Field& a,  Color color,int type=0){
    this->color = color;
    field = &a;
    this->type=type;
	}

	void add_point(int x, int y){
	    if (type == 0) field -> add_column_down(x,y,color);
	    if (type == 1) field -> add_column_up(x,y,color);
		}
};


#endif // PLOT_H_INCLUDED
