/*************************************************************************
【文件名】                 SearchInMemory.cpp
【功能模块和目的】         实现SearchInMemory函数的功能
【开发者及日期】           曹智昊 2022.3.9
【更改记录】               （若修改过则必需注明）
*************************************************************************/

// 哨兵
#ifndef SEARCHINMEMORY_CPP
#define SEARCHINMEMORY_CPP
#pragma once

#include "SearchInMemory.h"

// Value为从游戏显示中读到的数值；
// MemoryBegin为指向游戏内存需搜索区域的指针，其值一定是8的整数倍；
// SizeInByte为游戏内存需搜索区域的字节数，size_t是C / C++中表示字节数的类型，在32位编译中size_t是unsigned类型，用于指明数组长度或下标。
// 其余三个vector均为搜索结果，调用函数时均为空，分别存储所有：
// 内存中值可显示为Value的存储地址（指针），int型Value的指针存储于IntPtrList，
// float型Value的指针存储于FltPtrList，double型Value的指针存储于DblPtrList；
// 因为游戏内存中可能存在多个可显示为Value的内存区块，故要用Vector存储，以便后续筛选。
// 返回值，当搜索结果为空时返回false，否则为true
bool SearchInMemory(
	int Value,
	void* MemoryBegin,
	size_t SizeInByte,
	vector<int*>& IntPtrList,
	vector<float*>& FltPtrList,
	vector<double*>& DblPtrList
)
{

	// 由于不知道目标值的存储类型， 需要从头开始依次遍历所有可能
	// 每八个Byte为一大步, 四个Byte为一小步
	while (SizeInByte >= 8)
	{
		// 对Int类型的检测
		if (*(static_cast<int*>(MemoryBegin)) == Value)
		{
			IntPtrList.push_back(static_cast<int*>(MemoryBegin));
		}
		if (*(static_cast<int*>(MemoryBegin) + 1) == Value)
		{
			IntPtrList.push_back(static_cast<int*>(MemoryBegin) + 1);
		}

		// 对float, double类型的检测
		// 如果是float, double转为int， 则向零逼近
		if (Value > 0)
		{
			// 如果是float, double输出为int， 则向偶数逼近
			// 将两种情况混合起来判定，避免一个指针重复进向量
			if (Value & 1 == 0)
			{
				if ((((*(static_cast<float*>(MemoryBegin))) >= static_cast<float>(Value)) && ((*(static_cast<float*>(MemoryBegin))) < static_cast<float>(Value) + 1)) ||		// 转为int
					(((*(static_cast<float*>(MemoryBegin))) >= static_cast<float>(Value) - 0.5) && ((*(static_cast<float*>(MemoryBegin))) <= static_cast<float>(Value) + 0.5)))	// 输出整数
				{
					FltPtrList.push_back(static_cast<float*>(MemoryBegin));
				}
				if ((((*(static_cast<float*>(MemoryBegin) + 1)) >= static_cast<float>(Value)) && ((*(static_cast<float*>(MemoryBegin) + 1)) < static_cast<float>(Value) + 1)) ||			// 转为int
					(((*(static_cast<float*>(MemoryBegin) + 1)) >= static_cast<float>(Value) - 0.5) && ((*(static_cast<float*>(MemoryBegin) + 1)) <= static_cast<float>(Value) + 0.5)))		// 输出整数
				{
					FltPtrList.push_back(static_cast<float*>(MemoryBegin) + 1);
				}

				if ((((*(static_cast<double*>(MemoryBegin))) >= static_cast<double>(Value)) && ((*(static_cast<double*>(MemoryBegin))) < static_cast<double>(Value) + 1)) ||			// 转为int
					(((*(static_cast<double*>(MemoryBegin))) >= static_cast<double>(Value) - 0.5) && ((*(static_cast<double*>(MemoryBegin))) <= static_cast<double>(Value) + 0.5)))		// 输出整数
				{
					DblPtrList.push_back(static_cast<double*>(MemoryBegin));
				}
			}
			else
			{
				if ((((*(static_cast<float*>(MemoryBegin))) >= static_cast<float>(Value)) && ((*(static_cast<float*>(MemoryBegin))) < static_cast<float>(Value) + 1)) ||			// 转为int
					(((*(static_cast<float*>(MemoryBegin))) > static_cast<float>(Value) - 0.5) && ((*(static_cast<float*>(MemoryBegin))) < static_cast<float>(Value) + 0.5)))		// 输出整数
				{
					FltPtrList.push_back(static_cast<float*>(MemoryBegin));
				}
				if ((((*(static_cast<float*>(MemoryBegin) + 1)) >= static_cast<float>(Value)) && ((*(static_cast<float*>(MemoryBegin) + 1)) < static_cast<float>(Value) + 1)) ||		// 转为int
					(((*(static_cast<float*>(MemoryBegin) + 1)) > static_cast<float>(Value) - 0.5) && ((*(static_cast<float*>(MemoryBegin) + 1)) < static_cast<float>(Value) + 0.5)))	// 输出整数
				{
					FltPtrList.push_back(static_cast<float*>(MemoryBegin) + 1);
				}
					
				if ((((*(static_cast<double*>(MemoryBegin))) >= static_cast<double>(Value)) && ((*(static_cast<double*>(MemoryBegin))) < static_cast<double>(Value) + 1)) ||		// 转为int
					(((*(static_cast<double*>(MemoryBegin))) > static_cast<double>(Value) - 0.5) && ((*(static_cast<double*>(MemoryBegin))) < static_cast<double>(Value) + 0.5)))	// 输出整数
				{
					DblPtrList.push_back(static_cast<double*>(MemoryBegin));
				}
			}
		}
		else if (Value < 0)
		{
			// 如果是float, double输出为int， 则向偶数逼近
			if (Value % 2 == 0)
			{
				if ((((*(static_cast<float*>(MemoryBegin))) >= static_cast<float>(Value) - 0.5) && ((*(static_cast<float*>(MemoryBegin))) <= static_cast<float>(Value) + 0.5)) ||	// 转为int
					(((*(static_cast<float*>(MemoryBegin))) > static_cast<float>(Value) - 1) && ((*(static_cast<float*>(MemoryBegin))) <= static_cast<float>(Value))))				// 输出整数
				{
					FltPtrList.push_back(static_cast<float*>(MemoryBegin));
				}
				if ((((*(static_cast<float*>(MemoryBegin) + 1)) >= static_cast<float>(Value) - 0.5) && ((*(static_cast<float*>(MemoryBegin) + 1)) <= static_cast<float>(Value) + 0.5)) ||	// 转为int
					(((*(static_cast<float*>(MemoryBegin) + 1)) > static_cast<float>(Value) - 1) && ((*(static_cast<float*>(MemoryBegin) + 1)) <= static_cast<float>(Value))))				// 输出整数
				{
					FltPtrList.push_back(static_cast<float*>(MemoryBegin) + 1);
				}

				if ((((*(static_cast<double*>(MemoryBegin))) >= static_cast<double>(Value) - 0.5) && ((*(static_cast<double*>(MemoryBegin))) <= static_cast<double>(Value) + 0.5)) ||	// 转为int
					(((*(static_cast<double*>(MemoryBegin))) > static_cast<double>(Value) - 1) && ((*(static_cast<double*>(MemoryBegin))) <= static_cast<double>(Value))))				// 输出整数
				{
					DblPtrList.push_back(static_cast<double*>(MemoryBegin));
				}
			}
			else
			{
				if ((((*(static_cast<float*>(MemoryBegin))) > static_cast<float>(Value) - 0.5) && ((*(static_cast<float*>(MemoryBegin))) < static_cast<float>(Value) + 0.5)) ||	// 转为int
					(((*(static_cast<float*>(MemoryBegin))) > static_cast<float>(Value) - 1) && ((*(static_cast<float*>(MemoryBegin))) <= static_cast<float>(Value))))			// 输出整数
				{
					FltPtrList.push_back(static_cast<float*>(MemoryBegin));
				}
				if ((((*(static_cast<float*>(MemoryBegin) + 1)) > static_cast<float>(Value) - 0.5) && ((*(static_cast<float*>(MemoryBegin) + 1)) < static_cast<float>(Value) + 0.5)) ||		// 转为int
					(((*(static_cast<float*>(MemoryBegin) + 1)) > static_cast<float>(Value) - 1) && ((*(static_cast<float*>(MemoryBegin) + 1)) <= static_cast<float>(Value))))				// 输出整数
				{
					FltPtrList.push_back(static_cast<float*>(MemoryBegin) + 1);
				}

				if ((((*(static_cast<double*>(MemoryBegin))) > static_cast<double>(Value) - 0.5) && ((*(static_cast<double*>(MemoryBegin))) < static_cast<double>(Value) + 0.5)) ||		// 转为int
					(((*(static_cast<double*>(MemoryBegin))) > static_cast<double>(Value) - 1) && ((*(static_cast<double*>(MemoryBegin))) <= static_cast<double>(Value))))				// 输出整数
				{
					DblPtrList.push_back(static_cast<double*>(MemoryBegin));
				}
			}

		}
		else
		{
			if ((((*(static_cast<float*>(MemoryBegin))) >= static_cast<float>(Value) - 0.5) && ((*(static_cast<float*>(MemoryBegin))) <= static_cast<float>(Value) + 0.5)) ||	// 转为int
				(((*(static_cast<float*>(MemoryBegin))) > -1) && ((*(static_cast<float*>(MemoryBegin))) < 1)))																	// 输出整数
			{
				FltPtrList.push_back(static_cast<float*>(MemoryBegin));
			}
			if ((((*(static_cast<float*>(MemoryBegin) + 1)) >= static_cast<float>(Value) - 0.5) && ((*(static_cast<float*>(MemoryBegin) + 1)) <= static_cast<float>(Value) + 0.5)) ||	// 转为int
				(((*(static_cast<float*>(MemoryBegin) + 1)) > -1) && ((*(static_cast<float*>(MemoryBegin) + 1)) < 1)))																	// 输出整数
			{
				FltPtrList.push_back(static_cast<float*>(MemoryBegin) + 1);
			}

			if ((((*(static_cast<double*>(MemoryBegin))) >= static_cast<double>(Value) - 0.5) && ((*(static_cast<double*>(MemoryBegin))) <= static_cast<double>(Value) + 0.5)) ||	// 转为int
				(((*(static_cast<double*>(MemoryBegin))) > -1) && ((*(static_cast<double*>(MemoryBegin))) < 1)))																	// 输出整数
			{
				DblPtrList.push_back(static_cast<double*>(MemoryBegin));
			}

		}

		// 检测完之后让待检测位数减八， 待检测指针加八
		SizeInByte -= 8;
		MemoryBegin = static_cast<void*>(static_cast<double*>(MemoryBegin) + 1);
	}

	// 如果还剩四个字节， 则进行 int 和 float 的检测
	if (SizeInByte >= 4)
	{
		// 对Int类型的检测
		if (*(static_cast<int*>(MemoryBegin)) == Value)
		{
			IntPtrList.push_back(static_cast<int*>(MemoryBegin));
		}

		// 对float, double类型的检测
		// 如果是float, double转为int， 则向零逼近
		if (Value > 0)
		{
			// 如果是float, double输出为int， 则向偶数逼近
			// 将两种情况混合起来判定，避免一个指针重复进向量
			if (Value & 1 == 0)
			{
				if ((((*(static_cast<float*>(MemoryBegin))) >= static_cast<float>(Value)) && ((*(static_cast<float*>(MemoryBegin))) < static_cast<float>(Value) + 1)) ||		// 转为int
					(((*(static_cast<float*>(MemoryBegin))) >= static_cast<float>(Value) - 0.5) && ((*(static_cast<float*>(MemoryBegin))) <= static_cast<float>(Value) + 0.5)))	// 输出整数
				{
					FltPtrList.push_back(static_cast<float*>(MemoryBegin));
				}
			}
			else
			{
				if ((((*(static_cast<float*>(MemoryBegin))) >= static_cast<float>(Value)) && ((*(static_cast<float*>(MemoryBegin))) < static_cast<float>(Value) + 1)) ||			// 转为int
					(((*(static_cast<float*>(MemoryBegin))) > static_cast<float>(Value) - 0.5) && ((*(static_cast<float*>(MemoryBegin))) < static_cast<float>(Value) + 0.5)))		// 输出整数
				{
					FltPtrList.push_back(static_cast<float*>(MemoryBegin));
				}
			}
		}
		else if (Value < 0)
		{
			// 如果是float, double输出为int， 则向偶数逼近
			if (Value % 2 == 0)
			{
				if ((((*(static_cast<float*>(MemoryBegin))) >= static_cast<float>(Value) - 0.5) && ((*(static_cast<float*>(MemoryBegin))) <= static_cast<float>(Value) + 0.5)) ||	// 转为int
					(((*(static_cast<float*>(MemoryBegin))) > static_cast<float>(Value) - 1) && ((*(static_cast<float*>(MemoryBegin))) <= static_cast<float>(Value))))				// 输出整数
				{
					FltPtrList.push_back(static_cast<float*>(MemoryBegin));
				}
			}
			else
			{
				if ((((*(static_cast<float*>(MemoryBegin))) > static_cast<float>(Value) - 0.5) && ((*(static_cast<float*>(MemoryBegin))) < static_cast<float>(Value) + 0.5)) ||	// 转为int
					(((*(static_cast<float*>(MemoryBegin))) > static_cast<float>(Value) - 1) && ((*(static_cast<float*>(MemoryBegin))) <= static_cast<float>(Value))))			// 输出整数
				{
					FltPtrList.push_back(static_cast<float*>(MemoryBegin));
				}
			}

		}
		else
		{
			if ((((*(static_cast<float*>(MemoryBegin))) >= static_cast<float>(Value) - 0.5) && ((*(static_cast<float*>(MemoryBegin))) <= static_cast<float>(Value) + 0.5)) ||	// 转为int
				(((*(static_cast<float*>(MemoryBegin))) > -1) && ((*(static_cast<float*>(MemoryBegin))) < 1)))																	// 输出整数
			{
				FltPtrList.push_back(static_cast<float*>(MemoryBegin));
			}
		}
	}
	
	return !(IntPtrList.empty() && FltPtrList.empty() && DblPtrList.empty());
}

#endif // SEARCHINMEMORY_CPP