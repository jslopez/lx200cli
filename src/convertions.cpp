/** 
 * \file convertions.cpp
 * 
 * Converts values received to values that allows mathematical operations.
 * 
 * \author Joao Lopez <jslopez@csrg.inf.utfsm.cl>
 */
#include "convertions.h"

double sexa2double(const char *sexaStr)
{
	double converted = 0;
        double x = 0, y = 0, z = 0;
        char str[128];
        char *sign;

        strncpy (str, sexaStr, sizeof(str)-1);
        str[sizeof(str)-1] = '\0';
        sign = strchr(str, '-');
        if (sign)
            *sign = ' ';

        sscanf (str, "%lf%*[^0-9]%lf%*[^0-9]%lf", &x, &y, &z);
        converted = x + y/60 + z/3600;

        if (sign)
            converted *= -1;

	return converted;
}
