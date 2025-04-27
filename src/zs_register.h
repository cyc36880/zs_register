#ifndef __ZS_REGISTER_H__
#define __ZS_REGISTER_H__

#include "../../zs_register_conf.h"

#if ZS_REGISTER_LOG_LEVEL > 0
#define ZS_REGISTER_LOG(...) \
    do { \
        printf("%s:%d: ", __FILE__, __LINE__); \
        printf(__VA_ARGS__); \
        printf("\n"); \
    } while (0);
#else
    #define ZS_REGISTER_LOG(...)
#endif

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

int zs_register_reg_data_get_capacity_for_addr(zs_register_t *register_handle, uint32_t addr, uint32_t *capacity);
int zs_register_reg_data_get_data_nums_for_addr(zs_register_t *register_handle, uint32_t addr, uint32_t *data_nums);
int zs_register_reg_data_set_data_for_addr(zs_register_t *register_handle, uint32_t addr, void *data, uint32_t data_len);
int zs_register_reg_data_get_data_for_addr(zs_register_t *register_handle, uint32_t addr, void *data);
int zs_register_reg_data_set_data_byte_for_addr(zs_register_t *register_handle, uint32_t addr, uint8_t index, uint8_t data);
int zs_register_reg_data_get_data_byte_for_addr(zs_register_t *register_handle, uint32_t addr, uint8_t index);

zs_reg_data_t *zs_register_reg_data_get_for_offset_addr(zs_reg_t *reg, uint32_t offset_addr);
zs_reg_t *zs_register_reg_get_for_name(zs_register_t *register_handle, char *name);
zs_reg_data_t *zs_register_reg_data_get_for_addr(zs_register_t *register_handle, uint32_t addr);

#endif /* __ZS_REGISTER_H__ */
