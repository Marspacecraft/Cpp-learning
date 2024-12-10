
#include <termios.h>
#include <unistd.h>
#include "./ccout.h"

colorcout& colorcout::font(f_color font)
{
	static colorcout fontcout;
	if(f_color::HOLD == font)
		return fontcout;
	fontcout._font = font;
	fontcout._bkgd = f_backcolor::NONE;
	fontcout._cmd = f_cmd::NONE;
	return fontcout;
}

colorcout& colorcout::font(f_backcolor bkgd)
{
	static colorcout fontcout;
	if(f_backcolor::HOLD == bkgd)
		return fontcout;
	fontcout._font = f_color::NONE;
	fontcout._bkgd = bkgd;
	fontcout._cmd = f_cmd::NONE;
	return fontcout;
}

colorcout& colorcout::font(f_cmd::ccmd_type cmd)
{
	static colorcout fontcout;
	if(f_cmd::HOLD == cmd)
		return fontcout;
	fontcout._font = f_color::NONE;
	fontcout._bkgd = f_backcolor::NONE;
	fontcout._cmd = cmd;
	return fontcout;
}

colorcout& colorcout::font(f_color font,f_backcolor bkgd)
{
	static colorcout fontcout;
	if(f_color::HOLD != font)
		fontcout._font = font;
	
	if(f_backcolor::HOLD != bkgd)
		fontcout._bkgd = bkgd;
	fontcout._cmd = f_cmd::NONE;
	return fontcout;
}

colorcout& colorcout::font(f_cmd::ccmd_type cmd,f_color font)
{
	static colorcout fontcout;
	if(f_color::HOLD != font)
		fontcout._font = font;
	fontcout._bkgd = f_backcolor::NONE;
	if(f_cmd::HOLD != cmd)
		fontcout._cmd = cmd;
	return fontcout;
}

colorcout& colorcout::font(f_cmd::ccmd_type cmd,f_color font,f_backcolor bkgd)
{
	static colorcout fontcout;
	if(f_color::HOLD != font)
		fontcout._font = font;
	if(f_backcolor::HOLD != bkgd)
		fontcout._bkgd = bkgd;
	if(f_cmd::HOLD != cmd)
		fontcout._cmd = cmd;
	return fontcout;
}

std::string colorcout::GetCmd()
{
	std::string ret("0");
	if(0 == _cmd)
		return ret;
	
	for(int i=1;i<10;i++)
	{
		if(_cmd & (0x00001 << i))
		{
			ret += std::string(";")+ std::to_string(i);
		}
	}
	return ret;
}



colorcout& colorcout::cursor(c_cmd cmd)
{
	switch(cmd)
	{
		case c_cmd::HOME:
		std::cout << "\033[1G";
		break;
		case c_cmd::ENTER:
		std::cout << "\033[1E";
		break;
		case c_cmd::SHOW:
		std::cout << "\033[?25h";
		break;
		case c_cmd::HIDE:
		std::cout << "\033[?25l";
		break;
		case c_cmd::STORAGE:
		std::cout << "\033[s";
		break;
		case c_cmd::RECOVERY:
		std::cout << "\033[u";
		break;
		case c_cmd::DEL_FRONT:
		std::cout << "\033[1J";
		break;
		case c_cmd::DEL_BEHIND:
		std::cout << "\033[0J";
		break;
		case c_cmd::DEL_ALL:
		std::cout << "\033[2J";
		break;
		case c_cmd::DEL_ROW_FRONT:
		std::cout << "\033[1K";
		break;
		case c_cmd::DEL_ROW_BEHIND:
		std::cout << "\033[0K";
		break;
		case c_cmd::DEL_ROW_ALL:
		std::cout << "\033[2K";
		break;
	}

	return *this;
}

colorcout& colorcout::cursor(c_cmd cmd,int n)
{
	switch(cmd)
	{
		case c_cmd::MOVE_LEFT_n:
		std::cout << "\033[" << n << "D";
		break;
		case c_cmd::MOVE_UP_n:
		std::cout << "\033[" << n << "A";
		break;
		case c_cmd::MOVE_RIGHT_n:
		std::cout << "\033[" << n << "C";
		break;
		case c_cmd::MOVE_DOWN_n:
		std::cout << "\033[" << n << "B";
		break;
		case c_cmd::X_x:
		std::cout << "\033[" << n << "G";
		break;
		case c_cmd::Y_UP_n:
		std::cout << "\033[" << n << "F";
		break;
		case c_cmd::Y_DOWN_n:
		std::cout << "\033[" << n << "E";
		break;
	}

	return *this;
}

colorcout& colorcout::cursor(c_cmd cmd,int x,int y)
{
	switch(cmd)
	{
		case c_cmd::SET_x_y:
		std::cout << "\033[" << y << ";" << x << "H";
		break;
	}

	return *this;
}


static int set_echo_mode(int option)
{
	int err;
	struct termios term;
	if(tcgetattr(STDIN_FILENO ,&term)==-1)
		return -1;
	
	if(option)
		term.c_lflag |=(ECHO | ECHOE | ECHOK | ECHONL);
	else
		term.c_lflag &=~(ECHO | ECHOE | ECHOK | ECHONL);

	err=tcsetattr(STDIN_FILENO,TCSAFLUSH,&term);
	if(err==-1 && err==EINTR)
		return 1; 
	
	return 0;
}

colorcout& colorcout::command(cc_command cmd)
{
	switch(cmd)
	{
		case cc_command::CLS:
		cursor(c_cmd::DEL_ALL);
		break;
		case cc_command::FLUSH:
		std::cout <<std::flush;
		break;
		case cc_command::BEEP:
		std::cout << '\a';
		break;
		case cc_command::ECHO_DISABLE:
		set_echo_mode(0);
		break;
		case cc_command::ECHO_ENABLE:
		set_echo_mode(1);
		break;
	}

	return *this;
}



colorcout& colorcout::colorblock(b_color color)
{
	std::cout <<"\033[0;" <<static_cast<int>(color) << "m "<<"\033[0m";
	return *this;
}

colorcout& colorcout::colorblock(b_color color,int x,int y)
{
	cursor(c_cmd::SET_x_y,x,y);
	colorblock(color);
	return *this;
}
colorcout& colorcout::colorblock(b_color color,int x,int y,int n)
{
	std::string s("m");

	cursor(c_cmd::SET_x_y,x,y);
	std::cout <<"\033[0;" <<static_cast<int>(color);

	for(int i=0;i<n;i++)
		s.append(" ");
	std::cout << s << "\033[0m";
	return *this;
}

colorcout& colorcout::screen(s_cmd cmd)
{
	static s_cmd _cmd = s_cmd::SCREEN_RESET;

	if(_cmd == cmd)
	{
		return *this;
	}

	if(s_cmd::SCREEN_RESET == cmd)
	{
		std::cout << "\033[=" << static_cast<int>(_cmd)<<"l";
		_cmd = s_cmd::SCREEN_RESET;
		return *this;
	}

	if(s_cmd::SCREEN_RESET != _cmd)
		std::cout << "\033[=" << static_cast<int>(_cmd)<<"l";
	std::cout << "\033[=" << static_cast<int>(cmd)<<"h";
	_cmd = cmd;
	return *this;
}


colorcout& ccout = colorcout::GetInstance();
colorcout& operator<<(colorcout& out,colorcout& a)
{
	return a;
}



