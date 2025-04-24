#ifndef __ZS_REGISTER_H__
#define __ZS_REGISTER_H__

#include "../../zs_register_conf.h"


typedef struct _zs_reg_data
{
    ZS_REGISTER_DATA_TYPE *data;  /* data pointer */
    struct _zs_reg_data *next;    /* next data pointer */
    uint16_t capacity;            /* data capacity */
    uint16_t nums;                /* data nums */
    ZS_REGISTER_ADDR_TYPE offset_addr;  /* register offset address */
}zs_reg_data_t;


typedef struct _zs_reg
{
    char *name;               /* register name */
    zs_reg_data_t *reg_data;  /* register data pointer */
    ZS_REGISTER_ADDR_TYPE addr;  /* register address */
} zs_reg_t;


typedef struct _zs_register
{
    zs_reg_t *reg;            /* register pointer */
} zs_register_t;





#endif /* __ZS_REGISTER_H__ */
