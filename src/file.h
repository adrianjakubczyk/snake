#include<stdio.h>
#include "snake_and_food.h"
#pragma once
#pragma warning(disable:4996)
#ifndef FILE_H
#define FILE_H

void saveToFile(int records_number, struct ranking_record *records, struct ranking_record player);

void readFromFile(int *records_number, struct ranking_record **records);

#endif