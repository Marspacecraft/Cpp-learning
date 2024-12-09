
#include <iostream>
#include <unistd.h>


enum class cfont:int
{
	NONE=0,     	// 默认
	HOLD=1,			// 保持
	BLOCK=30,      	// 黑
	RED=31,      	// 红
	GREEN=32,      	// 绿
	YELLOW=33,    	// 黄
	BLUE=34,      	// 蓝
	PURPLE=35,    	// 粉
	CYAN=36,      	// 青
	WHITE=37,      	// 灰
};

enum class cbackgroud:int
{
	NONE=0,     	// 默认
	HOLD=1,			// 保持
	BLOCK=40,      	// 黑
	RED=41,      	// 红
	GREEN=42,      	// 绿
	YELLOW=43,   	// 黄
	BLUE=44,      	// 蓝
	PURPLE=45,    	// 粉
	CYAN=46,      	// 青
	WHITE=47,      	// 灰
};

class ccmd
{
public:
	typedef unsigned int ccmd_type;
	static const ccmd_type NONE=0;						//默认
	static const ccmd_type DEFAULT=0x00001 << 0;		// 取消格式
	static const ccmd_type LIGHTUP=0x00001 << 1;		// 高亮 
	static const ccmd_type LIGHTDOWN=0x00001 << 2;		// 变暗
	static const ccmd_type ITALICS=0x00001 << 3;		// 斜体
	static const ccmd_type UNDERSCORE=0x00001 << 4;		// 下划线
	static const ccmd_type BLINK=0x00001 << 5;			// 闪烁
	static const ccmd_type FASTBLINK=0x00001 << 6;		// 快闪
	static const ccmd_type REFLECT=0x00001 << 7;		// 反显
	static const ccmd_type BLANKING=0x00001 << 8;		// 消隐
	static const ccmd_type SLASH=0x00001 << 9;			// 中横线
	static const ccmd_type HOLD=0xffffff;				// 保持
};

class colorcout
{
public:
	
	static  colorcout& GetInstance()
	{
		static colorcout _ccout;
		return _ccout;
	}
	// 设置字体颜色
	colorcout& color(cfont);
	// 设置字体背景颜色
	colorcout& color(cbackgroud);
	// 设置命令
	colorcout& color(ccmd::ccmd_type);
	// 设置字体和背景颜色
	colorcout& color(cfont,cbackgroud);
	// 设置命令和字体颜色
	colorcout& color(ccmd::ccmd_type,cfont);
	// 设置命令字体和背景颜色
	colorcout& color(ccmd::ccmd_type,cfont,cbackgroud);

	template<class TT>
	friend colorcout& operator<<(colorcout& out,const TT& a);

	std::string GetCmd()
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

	// 输出一个色块
	colorcout& colorblock(cbackgroud color)
	{
		if(cbackgroud::BLOCK <= color)
		{
			std::cout << "\033[0;" << static_cast<int>(color) << "m "<<"\033[0m" ;
		}

		return *this;
	}

private:
	colorcout() = default;
	cfont _font;
	cbackgroud _bkgd;
	ccmd::ccmd_type _cmd;

};

colorcout& colorcout::color(cfont font)
{
	static colorcout fontcout;
	if(cfont::HOLD == font)
		return fontcout;
	fontcout._font = font;
	fontcout._bkgd = cbackgroud::NONE;
	fontcout._cmd = ccmd::NONE;
	return fontcout;
}

colorcout& colorcout::color(cbackgroud bkgd)
{
	static colorcout fontcout;
	if(cbackgroud::HOLD == bkgd)
		return fontcout;
	fontcout._font = cfont::NONE;
	fontcout._bkgd = bkgd;
	fontcout._cmd = ccmd::NONE;
	return fontcout;
}

colorcout& colorcout::color(ccmd::ccmd_type cmd)
{
	static colorcout fontcout;
	if(ccmd::HOLD == cmd)
		return fontcout;
	fontcout._font = cfont::NONE;
	fontcout._bkgd = cbackgroud::NONE;
	fontcout._cmd = cmd;
	return fontcout;
}

colorcout& colorcout::color(cfont font,cbackgroud bkgd)
{
	static colorcout fontcout;
	if(cfont::HOLD != font)
		fontcout._font = font;
	
	if(cbackgroud::HOLD != bkgd)
		fontcout._bkgd = bkgd;
	fontcout._cmd = ccmd::NONE;
	return fontcout;
}

colorcout& colorcout::color(ccmd::ccmd_type cmd,cfont font)
{
	static colorcout fontcout;
	if(cfont::HOLD != font)
		fontcout._font = font;
	fontcout._bkgd = cbackgroud::NONE;
	if(ccmd::HOLD != cmd)
		fontcout._cmd = cmd;
	return fontcout;
}

colorcout& colorcout::color(ccmd::ccmd_type cmd,cfont font,cbackgroud bkgd)
{
	static colorcout fontcout;
	if(cfont::HOLD != font)
		fontcout._font = font;
	if(cbackgroud::HOLD != bkgd)
		fontcout._bkgd = bkgd;
	if(ccmd::HOLD != cmd)
		fontcout._cmd = cmd;
	return fontcout;
}

template<class T>
colorcout& operator<<(colorcout& out,const T& a)
{
	std::cout <<"\033[" << out.GetCmd();
	if(cbackgroud::BLOCK <= out._bkgd)
	{
		std::cout << ";" << static_cast<int>(out._bkgd);
	}
	if(cfont::BLOCK <= out._font)
	{
		std::cout << ";" << static_cast<int>(out._font);
	}

	std::cout << "m" << a <<"\033[0m";

	return out;
}

colorcout& operator<<(colorcout& out,colorcout& a)
{
	return a;
}

static colorcout& ccout = colorcout::GetInstance();

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
	//ccout.color(cfont::RED) << A(1) << "\tHello\t"<< "\n";
	//ccout.color(cfont::HOLD) << A(1)<< "\tHello\t"<< "\n";
	//ccout.color(cfont::NONE) << A(1)<< "\tHello\t"<< "\n";

	//ccout.color(cbackgroud::RED) << A(1) << "\tHello\t"<< "\n";
	//ccout.color(cbackgroud::HOLD) << A(1)<< "\tHello\t"<< "\n";
	//ccout.color(cbackgroud::NONE) << A(1)<< "\tHello\t"<< "\n";

	//ccout.color(ccmd::LIGHTUP) << A(1) << "\tHello\t"<< "\n";
	//ccout.color(ccmd::HOLD) << A(1)<< "\tHello\t"<< "\n";
	//ccout.color(ccmd::ITALICS) << A(1)<< "\tHello\t"<< "\n";

	//ccout.color(ccmd::LIGHTUP,cfont::RED) << A(1) << "\tHello\t"<< "\n";
	//ccout.color(ccmd::HOLD,cfont::GREEN) << A(1)<< "\tHello\t"<< "\n";
	//ccout.color(ccmd::ITALICS,cfont::BLUE) << A(1)<< "\tHello\t"<< "\n";

	//ccout.color(cfont::RED,cbackgroud::BLUE) << A(1) << "\tHello\t"<< "\n";
	//ccout.color(cfont::HOLD,cbackgroud::YELLOW) << A(1)<< "\tHello\t"<< "\n";
	//ccout.color(cfont::NONE,cbackgroud::HOLD) << A(1)<< "\tHello\t"<< "\n";

	//ccout.color(ccmd::UNDERSCORE|ccmd::ITALICS,cfont::RED,cbackgroud::NONE) << A(1) << "\tHello\t"<< "\n";
	//ccout.color(ccmd::UNDERSCORE,cfont::HOLD,cbackgroud::YELLOW) << A(1)<< "\tHello\t"<< "\n";
	//ccout.color(ccmd::HOLD,cfont::NONE,cbackgroud::HOLD) << A(1)<< "\tHello\t"<< "\n";

	//ccout << A(1) << "Hello World!\n";

	ccout.color(cfont::BLUE) << "Hello" << ccout.colorblock(cbackgroud::CYAN)<< ccout.color(cfont::RED) << "World!\n"
		<< ccout << "MarSpaceCraft\n"; 

	return 0;
}