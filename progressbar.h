#ifndef _PROGRESS_BAR_H_
#define _PROGRESS_BAR_H_
#include <ccout.h>

class progressbar
{
public:
    progressbar(int x,int y,int length,bool color=false,bool horizon=true)
        :_x(x),_y(y),_length(length),_color(color),_horizon(horizon)
    {
        clear();
    };
    void percentage(int per);
private:
    void clear();
    int _x;
    int _y;
    int _length;
    bool _color;
    bool _horizon;
};



#endif

