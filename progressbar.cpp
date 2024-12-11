
#include "./progressbar.h"

void progressbar::clear()
{
    ccout.cursor(c_cmd::SET_x_y,_x,_y);
    for(int i=0;i<_length;i++)
    {
        ccout << " ";
        if(!_horizon)
        {
            ccout.cursor(c_cmd::MOVE_DOWN_n,1);
            ccout.cursor(c_cmd::MOVE_LEFT_n,1);
        }
    }
}

static inline void BarShow_Horiz(b_block type,int x,int y,int n,b_color color)
{
    ccout.block(type,x,y,n,color);   
}
static inline void BarShow_Vert(b_block type,int x,int y,int n,b_color color)
{
    ccout.cursor(c_cmd::SET_x_y,x,y);    

    for(int i=0;i<n;i++)
    {
        ccout.block(type,color);
        ccout.cursor(c_cmd::MOVE_UP_n,1);
        ccout.cursor(c_cmd::MOVE_LEFT_n,1);
    }
}

 void progressbar::percentage(int per)
 {
    static int _per = 0;
    per = per%101;

    int count = 8 * _length * per / 100;
    int fullcout = count / 8;
    int halfcout = count % 8;
    b_color color = b_color::NONE;

    if(_per > per)
        clear();

    _per = per;
    
    if(_color)
    {
        if(fullcout <= (_length/3))
            color = b_color::RED;
        else if(fullcout <= (2*_length/3))
            color = b_color::YELLOW;
        else  
            color = b_color::GREEN;
    }

    if(_horizon)
    {
        BarShow_Horiz(b_block::BLOCK_LEFT_8_8,_x,_y,fullcout,color);
        if(halfcout)
            BarShow_Horiz(static_cast<b_block>(static_cast<int>(b_block::BLOCK_LEFT_1_8)+halfcout-1),
                _x+fullcout,_y,1,color);
    }
    else
    {
        BarShow_Vert(b_block::BLOCK_LEFT_8_8,_x,_y+_length,fullcout,color);
        if(halfcout)
            BarShow_Vert(static_cast<b_block>(static_cast<int>(b_block::BLOCK_DOWN_1_8)+halfcout-1),
                _x,_y+_length-fullcout,1,color);
    }

    ccout.command(cc_command::FLUSH);

 }

 /*
 #include <iostream>
#include <unistd.h>
#include "ccout.h"
#include "progressbar.h"

using namespace std;


int main()
{
	ccout.command(cc_command::ECHO_DISABLE);
	ccout.cursor(c_cmd::HIDE);

	progressbar e(11,12,10,0,1);

	for(int i=0;i<=100;i++)
	{
		e.percentage(i);
		usleep(200000);
	}
	for(int i=100;i>=0;i--)
	{
		e.percentage(i);
		usleep(200000);
	}


	ccout.cursor(c_cmd::SHOW);
	ccout.command(cc_command::ECHO_ENABLE);
	return 0;
}
 */
