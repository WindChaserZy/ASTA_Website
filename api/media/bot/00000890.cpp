/*************************************************************************
���ļ�����                 SearchInMemory.cpp
������ģ���Ŀ�ġ�         ʵ��SearchInMemory�����Ĺ���
�������߼����ڡ�           ����� 2022.3.9
�����ļ�¼��               �����޸Ĺ������ע����
*************************************************************************/

// �ڱ�
#ifndef SEARCHINMEMORY_CPP
#define SEARCHINMEMORY_CPP
#pragma once

#include "SearchInMemory.h"

// ValueΪ����Ϸ��ʾ�ж�������ֵ��
// MemoryBeginΪָ����Ϸ�ڴ������������ָ�룬��ֵһ����8����������
// SizeInByteΪ��Ϸ�ڴ�������������ֽ�����size_t��C / C++�б�ʾ�ֽ��������ͣ���32λ������size_t��unsigned���ͣ�����ָ�����鳤�Ȼ��±ꡣ
// ��������vector��Ϊ������������ú���ʱ��Ϊ�գ��ֱ�洢���У�
// �ڴ���ֵ����ʾΪValue�Ĵ洢��ַ��ָ�룩��int��Value��ָ��洢��IntPtrList��
// float��Value��ָ��洢��FltPtrList��double��Value��ָ��洢��DblPtrList��
// ��Ϊ��Ϸ�ڴ��п��ܴ��ڶ������ʾΪValue���ڴ����飬��Ҫ��Vector�洢���Ա����ɸѡ��
// ����ֵ�����������Ϊ��ʱ����false������Ϊtrue
bool SearchInMemory(
	int Value,
	void* MemoryBegin,
	size_t SizeInByte,
	vector<int*>& IntPtrList,
	vector<float*>& FltPtrList,
	vector<double*>& DblPtrList
)
{

	// ���ڲ�֪��Ŀ��ֵ�Ĵ洢���ͣ� ��Ҫ��ͷ��ʼ���α������п���
	// ÿ�˸�ByteΪһ��, �ĸ�ByteΪһС��
	while (SizeInByte >= 8)
	{
		// ��Int���͵ļ��
		if (*(static_cast<int*>(MemoryBegin)) == Value)
		{
			IntPtrList.push_back(static_cast<int*>(MemoryBegin));
		}
		if (*(static_cast<int*>(MemoryBegin) + 1) == Value)
		{
			IntPtrList.push_back(static_cast<int*>(MemoryBegin) + 1);
		}

		// ��float, double���͵ļ��
		// �����float, doubleתΪint�� ������ƽ�
		if (Value > 0)
		{
			// �����float, double���Ϊint�� ����ż���ƽ�
			// �����������������ж�������һ��ָ���ظ�������
			if (Value & 1 == 0)
			{
				if ((((*(static_cast<float*>(MemoryBegin))) >= static_cast<float>(Value)) && ((*(static_cast<float*>(MemoryBegin))) < static_cast<float>(Value) + 1)) ||		// תΪint
					(((*(static_cast<float*>(MemoryBegin))) >= static_cast<float>(Value) - 0.5) && ((*(static_cast<float*>(MemoryBegin))) <= static_cast<float>(Value) + 0.5)))	// �������
				{
					FltPtrList.push_back(static_cast<float*>(MemoryBegin));
				}
				if ((((*(static_cast<float*>(MemoryBegin) + 1)) >= static_cast<float>(Value)) && ((*(static_cast<float*>(MemoryBegin) + 1)) < static_cast<float>(Value) + 1)) ||			// תΪint
					(((*(static_cast<float*>(MemoryBegin) + 1)) >= static_cast<float>(Value) - 0.5) && ((*(static_cast<float*>(MemoryBegin) + 1)) <= static_cast<float>(Value) + 0.5)))		// �������
				{
					FltPtrList.push_back(static_cast<float*>(MemoryBegin) + 1);
				}

				if ((((*(static_cast<double*>(MemoryBegin))) >= static_cast<double>(Value)) && ((*(static_cast<double*>(MemoryBegin))) < static_cast<double>(Value) + 1)) ||			// תΪint
					(((*(static_cast<double*>(MemoryBegin))) >= static_cast<double>(Value) - 0.5) && ((*(static_cast<double*>(MemoryBegin))) <= static_cast<double>(Value) + 0.5)))		// �������
				{
					DblPtrList.push_back(static_cast<double*>(MemoryBegin));
				}
			}
			else
			{
				if ((((*(static_cast<float*>(MemoryBegin))) >= static_cast<float>(Value)) && ((*(static_cast<float*>(MemoryBegin))) < static_cast<float>(Value) + 1)) ||			// תΪint
					(((*(static_cast<float*>(MemoryBegin))) > static_cast<float>(Value) - 0.5) && ((*(static_cast<float*>(MemoryBegin))) < static_cast<float>(Value) + 0.5)))		// �������
				{
					FltPtrList.push_back(static_cast<float*>(MemoryBegin));
				}
				if ((((*(static_cast<float*>(MemoryBegin) + 1)) >= static_cast<float>(Value)) && ((*(static_cast<float*>(MemoryBegin) + 1)) < static_cast<float>(Value) + 1)) ||		// תΪint
					(((*(static_cast<float*>(MemoryBegin) + 1)) > static_cast<float>(Value) - 0.5) && ((*(static_cast<float*>(MemoryBegin) + 1)) < static_cast<float>(Value) + 0.5)))	// �������
				{
					FltPtrList.push_back(static_cast<float*>(MemoryBegin) + 1);
				}
					
				if ((((*(static_cast<double*>(MemoryBegin))) >= static_cast<double>(Value)) && ((*(static_cast<double*>(MemoryBegin))) < static_cast<double>(Value) + 1)) ||		// תΪint
					(((*(static_cast<double*>(MemoryBegin))) > static_cast<double>(Value) - 0.5) && ((*(static_cast<double*>(MemoryBegin))) < static_cast<double>(Value) + 0.5)))	// �������
				{
					DblPtrList.push_back(static_cast<double*>(MemoryBegin));
				}
			}
		}
		else if (Value < 0)
		{
			// �����float, double���Ϊint�� ����ż���ƽ�
			if (Value % 2 == 0)
			{
				if ((((*(static_cast<float*>(MemoryBegin))) >= static_cast<float>(Value) - 0.5) && ((*(static_cast<float*>(MemoryBegin))) <= static_cast<float>(Value) + 0.5)) ||	// תΪint
					(((*(static_cast<float*>(MemoryBegin))) > static_cast<float>(Value) - 1) && ((*(static_cast<float*>(MemoryBegin))) <= static_cast<float>(Value))))				// �������
				{
					FltPtrList.push_back(static_cast<float*>(MemoryBegin));
				}
				if ((((*(static_cast<float*>(MemoryBegin) + 1)) >= static_cast<float>(Value) - 0.5) && ((*(static_cast<float*>(MemoryBegin) + 1)) <= static_cast<float>(Value) + 0.5)) ||	// תΪint
					(((*(static_cast<float*>(MemoryBegin) + 1)) > static_cast<float>(Value) - 1) && ((*(static_cast<float*>(MemoryBegin) + 1)) <= static_cast<float>(Value))))				// �������
				{
					FltPtrList.push_back(static_cast<float*>(MemoryBegin) + 1);
				}

				if ((((*(static_cast<double*>(MemoryBegin))) >= static_cast<double>(Value) - 0.5) && ((*(static_cast<double*>(MemoryBegin))) <= static_cast<double>(Value) + 0.5)) ||	// תΪint
					(((*(static_cast<double*>(MemoryBegin))) > static_cast<double>(Value) - 1) && ((*(static_cast<double*>(MemoryBegin))) <= static_cast<double>(Value))))				// �������
				{
					DblPtrList.push_back(static_cast<double*>(MemoryBegin));
				}
			}
			else
			{
				if ((((*(static_cast<float*>(MemoryBegin))) > static_cast<float>(Value) - 0.5) && ((*(static_cast<float*>(MemoryBegin))) < static_cast<float>(Value) + 0.5)) ||	// תΪint
					(((*(static_cast<float*>(MemoryBegin))) > static_cast<float>(Value) - 1) && ((*(static_cast<float*>(MemoryBegin))) <= static_cast<float>(Value))))			// �������
				{
					FltPtrList.push_back(static_cast<float*>(MemoryBegin));
				}
				if ((((*(static_cast<float*>(MemoryBegin) + 1)) > static_cast<float>(Value) - 0.5) && ((*(static_cast<float*>(MemoryBegin) + 1)) < static_cast<float>(Value) + 0.5)) ||		// תΪint
					(((*(static_cast<float*>(MemoryBegin) + 1)) > static_cast<float>(Value) - 1) && ((*(static_cast<float*>(MemoryBegin) + 1)) <= static_cast<float>(Value))))				// �������
				{
					FltPtrList.push_back(static_cast<float*>(MemoryBegin) + 1);
				}

				if ((((*(static_cast<double*>(MemoryBegin))) > static_cast<double>(Value) - 0.5) && ((*(static_cast<double*>(MemoryBegin))) < static_cast<double>(Value) + 0.5)) ||		// תΪint
					(((*(static_cast<double*>(MemoryBegin))) > static_cast<double>(Value) - 1) && ((*(static_cast<double*>(MemoryBegin))) <= static_cast<double>(Value))))				// �������
				{
					DblPtrList.push_back(static_cast<double*>(MemoryBegin));
				}
			}

		}
		else
		{
			if ((((*(static_cast<float*>(MemoryBegin))) >= static_cast<float>(Value) - 0.5) && ((*(static_cast<float*>(MemoryBegin))) <= static_cast<float>(Value) + 0.5)) ||	// תΪint
				(((*(static_cast<float*>(MemoryBegin))) > -1) && ((*(static_cast<float*>(MemoryBegin))) < 1)))																	// �������
			{
				FltPtrList.push_back(static_cast<float*>(MemoryBegin));
			}
			if ((((*(static_cast<float*>(MemoryBegin) + 1)) >= static_cast<float>(Value) - 0.5) && ((*(static_cast<float*>(MemoryBegin) + 1)) <= static_cast<float>(Value) + 0.5)) ||	// תΪint
				(((*(static_cast<float*>(MemoryBegin) + 1)) > -1) && ((*(static_cast<float*>(MemoryBegin) + 1)) < 1)))																	// �������
			{
				FltPtrList.push_back(static_cast<float*>(MemoryBegin) + 1);
			}

			if ((((*(static_cast<double*>(MemoryBegin))) >= static_cast<double>(Value) - 0.5) && ((*(static_cast<double*>(MemoryBegin))) <= static_cast<double>(Value) + 0.5)) ||	// תΪint
				(((*(static_cast<double*>(MemoryBegin))) > -1) && ((*(static_cast<double*>(MemoryBegin))) < 1)))																	// �������
			{
				DblPtrList.push_back(static_cast<double*>(MemoryBegin));
			}

		}

		// �����֮���ô����λ�����ˣ� �����ָ��Ӱ�
		SizeInByte -= 8;
		MemoryBegin = static_cast<void*>(static_cast<double*>(MemoryBegin) + 1);
	}

	// �����ʣ�ĸ��ֽڣ� ����� int �� float �ļ��
	if (SizeInByte >= 4)
	{
		// ��Int���͵ļ��
		if (*(static_cast<int*>(MemoryBegin)) == Value)
		{
			IntPtrList.push_back(static_cast<int*>(MemoryBegin));
		}

		// ��float, double���͵ļ��
		// �����float, doubleתΪint�� ������ƽ�
		if (Value > 0)
		{
			// �����float, double���Ϊint�� ����ż���ƽ�
			// �����������������ж�������һ��ָ���ظ�������
			if (Value & 1 == 0)
			{
				if ((((*(static_cast<float*>(MemoryBegin))) >= static_cast<float>(Value)) && ((*(static_cast<float*>(MemoryBegin))) < static_cast<float>(Value) + 1)) ||		// תΪint
					(((*(static_cast<float*>(MemoryBegin))) >= static_cast<float>(Value) - 0.5) && ((*(static_cast<float*>(MemoryBegin))) <= static_cast<float>(Value) + 0.5)))	// �������
				{
					FltPtrList.push_back(static_cast<float*>(MemoryBegin));
				}
			}
			else
			{
				if ((((*(static_cast<float*>(MemoryBegin))) >= static_cast<float>(Value)) && ((*(static_cast<float*>(MemoryBegin))) < static_cast<float>(Value) + 1)) ||			// תΪint
					(((*(static_cast<float*>(MemoryBegin))) > static_cast<float>(Value) - 0.5) && ((*(static_cast<float*>(MemoryBegin))) < static_cast<float>(Value) + 0.5)))		// �������
				{
					FltPtrList.push_back(static_cast<float*>(MemoryBegin));
				}
			}
		}
		else if (Value < 0)
		{
			// �����float, double���Ϊint�� ����ż���ƽ�
			if (Value % 2 == 0)
			{
				if ((((*(static_cast<float*>(MemoryBegin))) >= static_cast<float>(Value) - 0.5) && ((*(static_cast<float*>(MemoryBegin))) <= static_cast<float>(Value) + 0.5)) ||	// תΪint
					(((*(static_cast<float*>(MemoryBegin))) > static_cast<float>(Value) - 1) && ((*(static_cast<float*>(MemoryBegin))) <= static_cast<float>(Value))))				// �������
				{
					FltPtrList.push_back(static_cast<float*>(MemoryBegin));
				}
			}
			else
			{
				if ((((*(static_cast<float*>(MemoryBegin))) > static_cast<float>(Value) - 0.5) && ((*(static_cast<float*>(MemoryBegin))) < static_cast<float>(Value) + 0.5)) ||	// תΪint
					(((*(static_cast<float*>(MemoryBegin))) > static_cast<float>(Value) - 1) && ((*(static_cast<float*>(MemoryBegin))) <= static_cast<float>(Value))))			// �������
				{
					FltPtrList.push_back(static_cast<float*>(MemoryBegin));
				}
			}

		}
		else
		{
			if ((((*(static_cast<float*>(MemoryBegin))) >= static_cast<float>(Value) - 0.5) && ((*(static_cast<float*>(MemoryBegin))) <= static_cast<float>(Value) + 0.5)) ||	// תΪint
				(((*(static_cast<float*>(MemoryBegin))) > -1) && ((*(static_cast<float*>(MemoryBegin))) < 1)))																	// �������
			{
				FltPtrList.push_back(static_cast<float*>(MemoryBegin));
			}
		}
	}
	
	return !(IntPtrList.empty() && FltPtrList.empty() && DblPtrList.empty());
}

#endif // SEARCHINMEMORY_CPP