/*******************************************************************
*   File name:    DIO_Cfg.c
*   Author:       Ibrahim Saad
*   Description:  This file contains all configurations to deal with DIO peripheral
*                 features in ATmega32
*   Version: v1.0
*******************************************************************/

#include "DIO_Cfg.h"

const DIO_strPinCfg_t DIO_strPinCfg [32] = {
    /*PORTA:  Pin Direction,  Pull up/pull down*/
    /*PIN 0*/ {DIO_DIR_OUTPUT, DIO_INPUT_PULL_UP},
    /*PIN 1*/ {DIO_DIR_OUTPUT, DIO_INPUT_PULL_UP},
    /*PIN 2*/ {DIO_DIR_OUTPUT, DIO_INPUT_PULL_UP},
    /*PIN 3*/ {DIO_DIR_OUTPUT, DIO_INPUT_PULL_UP},
    /*PIN 4*/ {DIO_DIR_OUTPUT, DIO_INPUT_PULL_UP},
    /*PIN 5*/ {DIO_DIR_OUTPUT, DIO_INPUT_PULL_UP},
    /*PIN 6*/ {DIO_DIR_OUTPUT, DIO_INPUT_PULL_UP},
    /*PIN 7*/ {DIO_DIR_OUTPUT, DIO_INPUT_PULL_UP},

    /*PORTB:  Pin Direction,  Pull up/pull down*/
    /*PIN 8*/ {DIO_DIR_OUTPUT, DIO_INPUT_PULL_UP},
    /*PIN 9*/ {DIO_DIR_OUTPUT, DIO_INPUT_PULL_UP},
    /*PIN 10*/ {DIO_DIR_OUTPUT, DIO_INPUT_PULL_UP},
    /*PIN 11*/ {DIO_DIR_OUTPUT, DIO_INPUT_PULL_UP},
    /*PIN 12*/ {DIO_DIR_OUTPUT, DIO_INPUT_PULL_UP},
    /*PIN 13*/ {DIO_DIR_OUTPUT, DIO_INPUT_PULL_UP},
    /*PIN 14*/ {DIO_DIR_OUTPUT, DIO_INPUT_PULL_UP},
    /*PIN 15*/ {DIO_DIR_OUTPUT, DIO_INPUT_PULL_UP},

    /*PORTC:  Pin Direction,  Pull up/pull down*/
    /*PIN 16*/ {DIO_DIR_OUTPUT, DIO_INPUT_PULL_UP},
    /*PIN 17*/ {DIO_DIR_OUTPUT, DIO_INPUT_PULL_UP},
    /*PIN 18*/ {DIO_DIR_OUTPUT, DIO_INPUT_PULL_UP},
    /*PIN 19*/ {DIO_DIR_OUTPUT, DIO_INPUT_PULL_UP},
    /*PIN 20*/ {DIO_DIR_OUTPUT, DIO_INPUT_PULL_UP},
    /*PIN 21*/ {DIO_DIR_OUTPUT, DIO_INPUT_PULL_UP},
    /*PIN 22*/ {DIO_DIR_OUTPUT, DIO_INPUT_PULL_UP},
    /*PIN 23*/ {DIO_DIR_OUTPUT, DIO_INPUT_PULL_UP},

    /*PORTD:  Pin Direction,  Pull up/pull down*/
    /*PIN 24*/ {DIO_DIR_OUTPUT, DIO_INPUT_PULL_UP},
    /*PIN 25*/ {DIO_DIR_OUTPUT, DIO_INPUT_PULL_UP},
    /*PIN 26*/ {DIO_DIR_OUTPUT, DIO_INPUT_PULL_UP},
    /*PIN 27*/ {DIO_DIR_OUTPUT, DIO_INPUT_PULL_UP},
    /*PIN 28*/ {DIO_DIR_OUTPUT, DIO_INPUT_PULL_UP},
    /*PIN 29*/ {DIO_DIR_OUTPUT, DIO_INPUT_PULL_UP},
    /*PIN 30*/ {DIO_DIR_OUTPUT, DIO_INPUT_PULL_UP},
    /*PIN 31*/ {DIO_DIR_OUTPUT, DIO_INPUT_PULL_UP}
};
