#ifndef __ZS_REGISTER_H__
#define __ZS_REGISTER_H__

#include "../../zs_register_conf.h"

#define zs_register_foreach(x, list) \
    for (x = list; x != NULL; x = x->next)

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
    zs_reg_data_t *reg_data_list;  /* register data pointer */
    struct _zs_reg *next;    /* next register pointer */
    ZS_REGISTER_ADDR_TYPE addr;  /* register address */
} zs_reg_t;


typedef struct _zs_register
{
    zs_reg_t *reg_list;            /* register pointer */
} zs_register_t;


zs_reg_data_t *zs_register_reg_data_init(zs_reg_data_t *reg_data, uint32_t offset_addr);
zs_reg_t *zs_register_reg_init(zs_reg_t *reg, char *name, uint32_t addr);

int zs_register_registered_reg(zs_register_t *register_handle, char *name, uint32_t addr);
int zs_register_registered_reg_data(zs_register_t *register_handle, char *name, uint32_t offset_addr, uint32_t data_len);

zs_reg_t *zs_register_reg_get_for_name(zs_register_t *register_handle, char *name);
zs_reg_data_t *zs_register_reg_data_get_for_addr(zs_register_t *register_handle, uint32_t addr);
zs_reg_data_t *zs_register_reg_data_get_for_offset_addr(zs_reg_data_t *reg, uint32_t offset_addr);
int zs_register_reg_data_set_data(zs_reg_data_t *reg_data, uint32_t offset_addr, void *data, uint32_t data_len);
int zs_register_reg_data_get_data(zs_reg_data_t *reg_data, uint32_t offset_addr, void *data, uint32_t data_len);

#endif /* __ZS_REGISTER_H__ */
