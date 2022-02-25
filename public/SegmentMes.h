/*
This file is part of XSuNet Project.
Copyright (c) 2021-2022 SuYichen.
*/
#pragma once
#include "RecvTaskInfo.h"
#include "stdio.h"
#include <iostream>
#include <vector>

struct SegmentMes
{
	std::string MesID;
	int Section;
	int SectionNum;
	RecvTaskInfo Rinfo;
};

class SegmentMesQueue
{
public:
	
private:
	std::vector<SegmentMes> SementMeses;
};