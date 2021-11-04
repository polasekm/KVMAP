/*
 * config.h
 *
 *  Created on: 6. 5. 2021
 *      Author: polasekm
 */

#ifndef KV_MAP_H_
#define KV_MAP_H_

#include <string.h>
#include <stdio.h>
#include <stdint.h>

#include "jsonfl/jsonfl.h"


/* Exported types ------------------------------------------------------------*/

//------------------------------------------------------------------------------
typedef enum
{
  KV_STR_TYPE_UCHAR        = 0,
  KV_STR_TYPE_CHAR,

  KV_STR_TYPE_UINT_8,
  KV_STR_TYPE_INT_8,

  KV_STR_TYPE_UINT_16,
  KV_STR_TYPE_INT_16,

  KV_STR_TYPE_UINT_32,
  KV_STR_TYPE_INT_32,

  KV_STR_TYPE_UINT_64,
  KV_STR_TYPE_INT_64,

  KV_STR_TYPE_FLOAT,
  KV_STR_TYPE_DOUBLE,

  KV_STR_TYPE_STR,
  KV_STR_TYPE_BIN,

  KV_STR_TYPE_OBJ,
  KV_STR_TYPE_ARRAY

} kv_str_map_type_t;
//------------------------------------------------------------------------------
typedef struct kv_str_map_ts kv_str_map_t;

struct kv_str_map_ts

{
  char *key;                  //key name

  kv_str_map_type_t type;     //value type
  uint16_t len;               //value len (if appl.)

  void (*set)(kv_str_map_t *kv_str_map, ...);      //setter fce
  void (*get)(kv_str_map_t *kv_str_map, ...);      //getter fce

  void *addr;                 //pointer to update dst. value in memory

  //void (*set)(kv_str_map_t *kv_str_map);      //setter fce
  //void (*get)(kv_str_map_t *kv_str_map);      //getter fce
};


typedef struct
{
  const kv_str_map_t *str_map;
  uint32_t count;

} kv_map_t;

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

void kv_map_init(kv_map_t *kv_map, const kv_str_map_t *str_map, uint32_t count);

void kv_map_kv(const kv_map_t *kv_map, const char *key, const char *value, jsonfl_type_t val_type, uint8_t deep);
char* kv_map_json_kv(const kv_map_t *kv_map, char *json_kv, uint32_t item);


#endif /* KV_MAP_H_ */
