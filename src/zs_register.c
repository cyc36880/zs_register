#include "zs_register.h"
#include ZS_REGISTER_MEM_INCLUDE
#include <string.h>

#include "stdio.h"


zs_reg_data_t *zs_register_reg_data_init(zs_reg_data_t *reg_data, uint32_t offset_addr)
{
    if (NULL == reg_data) return NULL;
    memset(reg_data, 0, sizeof(zs_reg_data_t));
    reg_data->offset_addr = offset_addr;
    return reg_data;
}

zs_reg_t *zs_register_reg_init(zs_reg_t *reg, char *name, uint32_t addr)
{
    if (NULL == reg) return NULL;
    memcpy(reg->name, name, strlen(name) + 1);
    reg->addr = addr;
    return reg;
}




int zs_register_registered_reg(zs_register_t *register_handle, char *name, uint32_t addr)
{
    if (NULL == register_handle) return -1;
    zs_reg_t *reg = ZS_REGISTER_MEM_ALLOC(sizeof(zs_reg_t));
    if (NULL == reg) goto error_reg_data_alloc;
    memset(reg, 0, sizeof(zs_reg_t));

    reg->name = ZS_REGISTER_MEM_ALLOC(strlen(name) + 1);
    if (NULL == reg->name) goto error_reg_alloc;

    reg = zs_register_reg_init(reg, name, addr);
    if (NULL == reg) goto error_init_reg;

    if (NULL == register_handle->reg_list) 
    {
        register_handle->reg_list = reg;
    }
    else
    {
        zs_reg_t *tmp = register_handle->reg_list;
        while (tmp->next != NULL)
        {
            tmp = tmp->next;
        }
        tmp->next = reg;
    }
    return 0;

error_init_reg:

error_reg_alloc:
    ZS_REGISTER_MEM_FREE(reg->name);
error_reg_data_alloc:
    ZS_REGISTER_MEM_FREE(reg->reg_data_list);

    return -1;
}


int zs_register_registered_reg_data(zs_register_t *register_handle, char *name, uint32_t offset_addr, uint32_t data_len)
{
    if (NULL == register_handle) return -1;
    zs_reg_data_t *reg_data = ZS_REGISTER_MEM_ALLOC(sizeof(zs_reg_data_t));
    reg_data = zs_register_reg_data_init(reg_data, offset_addr);
    if (NULL == reg_data) goto error_reg_alloc;
    reg_data->data = ZS_REGISTER_MEM_ALLOC(sizeof(ZS_REGISTER_DATA_TYPE) * data_len);
    if (NULL == reg_data->data) goto error_reg_data_alloc;
    memset(reg_data->data, 0, sizeof(ZS_REGISTER_DATA_TYPE) * data_len);
    reg_data->next = NULL;

    reg_data->capacity = data_len; // initial 
    reg_data->offset_addr = offset_addr;

    zs_reg_t *reg = zs_register_reg_get_for_name(register_handle, name);
    if (NULL == reg) goto error_not_found;

    if (NULL == reg->reg_data_list)
    {
        reg->reg_data_list = reg_data;
    }
    else
    {
        zs_reg_data_t *tmp = reg->reg_data_list;
        while (tmp->next != NULL)
        {
            tmp = tmp->next;
        }
        tmp->next = reg_data;
    }
    return 0;

error_not_found:

error_reg_data_alloc:
    ZS_REGISTER_MEM_FREE(reg_data->data);
error_reg_alloc:
    ZS_REGISTER_MEM_FREE(reg_data);

    return -1;
}

int zs_register_reg_data_set_data_for_addr(zs_register_t *register_handle, uint32_t addr, void *data, uint32_t data_len)
{
    if (NULL == register_handle) return -1;
    zs_reg_data_t *reg_data = zs_register_reg_data_get_for_addr(register_handle, addr);
    if (NULL == reg_data) return -1;

    if (data_len > reg_data->capacity) return -1;
    memcpy(reg_data->data, data, data_len);
    reg_data->nums = data_len; // update nums

    return 0;
}

int zs_register_reg_data_get_capacity_for_addr(zs_register_t *register_handle, uint32_t addr, uint32_t *capacity)
{
    if (NULL == register_handle) return -1;
    zs_reg_data_t *reg_data = zs_register_reg_data_get_for_addr(register_handle, addr);
    if (NULL == reg_data) return -1;

    *capacity = reg_data->capacity; // update capacity
    return 0;
}

int zs_register_reg_data_get_data_nums_for_addr(zs_register_t *register_handle, uint32_t addr, uint32_t *data_nums)
{
    if (NULL == register_handle) return -1;
    zs_reg_data_t *reg_data = zs_register_reg_data_get_for_addr(register_handle, addr);
    if (NULL == reg_data) return -1;

    *data_nums = reg_data->nums; // update nums
    return 0;
}

int zs_register_reg_data_get_data_for_addr(zs_register_t *register_handle, uint32_t addr, void *data)
{
    if (NULL == register_handle) return -1;
    zs_reg_data_t *reg_data = zs_register_reg_data_get_for_addr(register_handle, addr);
    if (NULL == reg_data) return -1;

    memcpy(data, reg_data->data, reg_data->nums);

    return 0;
}

int zs_register_reg_data_set_data_byte_for_addr(zs_register_t *register_handle, uint32_t addr, uint8_t index, uint8_t data)
{
    if (NULL == register_handle) return -1;
    zs_reg_data_t *reg_data = zs_register_reg_data_get_for_addr(register_handle, addr);
    if (NULL == reg_data) return -1;

    if (index >= reg_data->capacity) return -1;
    reg_data->data[index] = data; // update data
    return 0;
}

int zs_register_reg_data_get_data_byte_for_addr(zs_register_t *register_handle, uint32_t addr, uint8_t index)
{
    if (NULL == register_handle) return -1;
    zs_reg_data_t *reg_data = zs_register_reg_data_get_for_addr(register_handle, addr);
    if (NULL == reg_data) return -1;

    if (index >= reg_data->capacity) return -1;
    return reg_data->data[index]; // update data
}

// ============================

zs_reg_t *zs_register_reg_get_for_name(zs_register_t *register_handle, char *name)
{
    if (NULL == register_handle) return NULL;
    zs_reg_t *reg = register_handle->reg_list;
    while (reg != NULL)
    {
        if (strcmp(reg->name, name) == 0)
        {
            return reg;
        }
        reg = reg->next;
    }
    return NULL;
}


zs_reg_data_t *zs_register_reg_data_get_for_offset_addr(zs_reg_t *reg, uint32_t offset_addr)
{
    if (NULL == reg) return NULL;
    zs_reg_data_t *reg_data = reg->reg_data_list;
    zs_register_foreach(reg_data, reg_data)
    {
        if (offset_addr == reg_data->offset_addr)
        {
            return reg_data;
        }
    }
    return NULL;
}

zs_reg_data_t *zs_register_reg_data_get_for_addr(zs_register_t *register_handle, uint32_t addr)
{
    if (NULL == register_handle) return NULL;
    zs_reg_t *reg = register_handle->reg_list;
    zs_register_foreach(reg, reg)
    {
        uint32_t base_addr = reg->addr;
        zs_reg_data_t *reg_data = reg->reg_data_list;
        zs_register_foreach(reg_data, reg_data)
        {
            if (addr == reg_data->offset_addr+base_addr)
            {
                return reg_data;
            }
        }
    }
    return NULL;
}