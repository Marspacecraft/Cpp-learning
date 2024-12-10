
#include <iostream>
#include "ccout.h"


class A
{
	public:
	A(int a):_a(a)
	{}
	int _a;
};

std::ostream& operator<<(std::ostream & out, const A& a)
{
	out << a._a;
	return out;
}

int main()
{
	//ccout.font(f_color::RED) << A(1) << "\tHello\t"<< "\n";
	//ccout.font(f_color::HOLD) << A(1)<< "\tHello\t"<< "\n";
	//ccout.font(f_color::NONE) << A(1)<< "\tHello\t"<< "\n";

	//ccout.font(f_backcolor::RED) << A(1) << "\tHello\t"<< "\n";
	//ccout.font(f_backcolor::HOLD) << A(1)<< "\tHello\t"<< "\n";
	//ccout.font(f_backcolor::NONE) << A(1)<< "\tHello\t"<< "\n";

	//ccout.font(f_cmd::LIGHTUP) << A(1) << "\tHello\t"<< "\n";
	//ccout.font(f_cmd::HOLD) << A(1)<< "\tHello\t"<< "\n";
	//ccout.font(f_cmd::ITALICS) << A(1)<< "\tHello\t"<< "\n";

	//ccout.font(f_cmd::LIGHTUP,f_color::RED) << A(1) << "\tHello\t"<< "\n";
	//ccout.font(f_cmd::HOLD,f_color::GREEN) << A(1)<< "\tHello\t"<< "\n";
	//ccout.font(f_cmd::ITALICS,f_color::BLUE) << A(1)<< "\tHello\t"<< "\n";

	//ccout.font(f_color::RED,f_backcolor::BLUE) << A(1) << "\tHello\t"<< "\n";
	//ccout.font(f_color::HOLD,f_backcolor::YELLOW) << A(1)<< "\tHello\t"<< "\n";
	//ccout.font(f_color::NONE,f_backcolor::HOLD) << A(1)<< "\tHello\t"<< "\n";

	//ccout.font(f_cmd::UNDERSCORE|f_cmd::ITALICS,f_color::RED,f_backcolor::NONE) << A(1) << "\tHello\t"<< "\n";
	//ccout.font(f_cmd::UNDERSCORE,f_color::HOLD,f_backcolor::YELLOW) << A(1)<< "\tHello\t"<< "\n";
	//ccout.font(f_cmd::HOLD,f_color::NONE,f_backcolor::HOLD) << A(1)<< "\tHello\t"<< "\n";

    int i;
	for(i=0;i<30;i++)
		ccout.command(cc_command::BEEP); 



	return 0;
}