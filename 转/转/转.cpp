// 转.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>

std::wstring uniCodeToUTF8(const std::wstring unicodeStr)
{
	std::wstring utf8Str;
	for (wchar_t wc : unicodeStr)
	{
		unsigned char temp;
		//00-7F范围内
		if (wc <= 0X7F)
		{
			//添加到结果字符串中
			utf8Str.push_back(static_cast<char>(wc));
		}
		//80-7FF之间
		else if (wc <= 0X7FF)
		{   //高位
			temp = static_cast<unsigned char>((wc >> 6) | 0XC0 & 0XDF);
			utf8Str.push_back(temp);
			//低位
			temp = static_cast<unsigned char>(wc & 0X3F | 0XC0 & 0XBF);
			utf8Str.push_back(temp);
		}
		//800-FFFF之间
		else if (wc <= 0XFFFF)
		{
			temp = static_cast<unsigned char>((wc >> 12) | 0XE0 & 0XEF);
			utf8Str.push_back(temp);
			temp = static_cast<unsigned char>((wc >> 6) & 0X3F | 0XC0 & 0XBF);
			utf8Str.push_back(temp);
			temp = static_cast<unsigned char>(wc & 0X3F | 0XC0 & 0XBF);
			utf8Str.push_back(temp);
		}
		//10000-10FFFF之间
		else if (wc <= 0X10FFFF)
		{
			temp = static_cast<unsigned char>((wc >> 18) | 0XF0 & 0XF7);
			utf8Str.push_back(temp);
			temp = static_cast<unsigned char>((wc >> 12) & 0X3F | 0XC0 & 0XBF);
			utf8Str.push_back(temp);
			temp = static_cast<unsigned char>((wc >> 6) & 0X3F | 0XC0 & 0XBF);
			utf8Str.push_back(temp);
			temp = static_cast<unsigned char>(wc & 0X3F | 0XC0 & 0XBF);
			utf8Str.push_back(temp);
		}
	}
	return utf8Str;
}

int main()
{
	std::wstring unicode = L"\u674E";
	std::wstring str = uniCodeToUTF8(unicode);
	std::wcout << str << std::endl;
}


// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
