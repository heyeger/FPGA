
#pragma once

#ifndef SCU_GIC_H_
#define SCU_GIC_H_

#include <xscugic.h>
#include <xparameters.h>

#define XPAR_FABRIC_SPI_INTR_OFFSET 32

extern XScuGic ScuGic;	


void ScuGic_Init();

#endif
