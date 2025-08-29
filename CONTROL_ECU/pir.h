/*
 * pir.h
 *
 *  Created on: 1 Nov 2024
 *      Author: farah
 */

#ifndef PIR_H_
#define PIR_H_

#include "std_types.h"

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

/*
 * Description :
 * Initialises PIR sensor
 */
void PIR_init(void);

/*
 * Description :
 * returns PIR sensor state
 */
uint8 PIR_getState(void);

#endif /* PIR_H_ */
