#pragma once 

//=========================================================

#define SET_BIT(REG, BITNO) ((*(REG)) |=  (1 << (BITNO)))
#define CLEAR_BIT(REG, BITNO) ((*(REG)) &= ~(1 << (BITNO)))
#define CHECK_BIT(REG, BITNO) ((*(REG)) & (1 << BITNO))

//=========================================================

#define MODIFY_REG(REG, MODIFYMASK, VALUE) ((*(REG)) |= ((MODIFYMASK) & (VALUE)))
#define SUPER_MODIFY_REG(REG, MODIFYMASK, VALUE, OFFSET) ((*(REG)) |= (((MODIFYMASK) & (VALUE)) << (OFFSET)))

#define PUPER_MODIFY_REG(REG, MODIFYMASK, VALUE, OFFSET)    \
                                                            \
    do                                                      \
    {                                                       \
        (*(REG)) &= ~((MODIFYMASK) << OFFSET);              \
        (*(REG)) |= (((MODIFYMASK) & (VALUE)) << OFFSET);   \
                                                            \
    } while (0);
    

#define CHECK_REG(REG, MODIFYMASK) ((*(REG)) & (MODIFYMASK))
#define SUPER_CHECK_REG(REG, MODIFYMASK, OFFSET) ((*(REG)) & ((MODIFYMASK) << (OFFSET)) >> OFFSET)