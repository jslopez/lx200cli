/** 
 * \file conversions.h
 * Headers for conversions operations.
 *
 * \author Joao Lopez <jslopez@csrg.inf.utfsm.cl>
 */

#ifndef _CONVERSIONS_H_
#define _CONVERSIONS_H_

#include <stdio.h>
#include <string.h>

/** 
 * Convert sexagesimal string to double.
 * @param sexaStr Original string
 * @returns converted Value converted.
 */
double sexa2double(const char *sexaStr);

#endif
