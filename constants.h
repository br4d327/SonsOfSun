#pragma once


static double RandomNumber(int minNum, int maxNum)
{
	return minNum + (double)rand() / (RAND_MAX + 1) * maxNum;
}