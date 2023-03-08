/*
 * config.c
 *
 *  Created on: 6. 5. 2021
 *      Author: polasekm
 */


/* Includes ------------------------------------------------------------------*/
#include <stdlib.h> //atof, atoi

#include "kv_map.h"

//------------------------------------------------------------------------------

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/


/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/



/* Private functions ---------------------------------------------------------*/

float kv_pu8floatLE(const unsigned char *ptr)
{
  float result;
  memmove(&result, ptr, sizeof(float));
  return result;
}

void kv_floatpu8LE(unsigned char *ptr, float val)
{
  memmove(ptr, &val, sizeof(float));
}

double kv_pu8doubleLE(const unsigned char *ptr)
{
  double result;
  memmove(&result, ptr, sizeof(double));
  return result;
}

void kv_doublepu8LE(unsigned char *ptr, double val)
{
  memmove(ptr, &val, sizeof(double));
}


void kv_map_init(kv_map_t *kv_map, const kv_str_map_t *str_map, uint32_t count)
{
  kv_map->str_map = str_map;
  kv_map->count = count;
}
//-----------------------------------------------------------------------------
void kv_map_kv(const kv_map_t *kv_map, const char *key, const char *value, jsonfl_type_t val_type, uint8_t _deep_unused, uint8_t case_sensitive) //json->cfg
{
  uint32_t i;

  for(i = 0; i < kv_map->count; i++)
  {
    size_t key_len=strlen(kv_map->str_map[i].key);
    uint8_t shoda;
    if (case_sensitive)
      shoda=strncmp(kv_map->str_map[i].key, key, key_len) == 0;
    else
      shoda=strncasecmp(kv_map->str_map[i].key, key, key_len) == 0;
    if(shoda && (strchr(" :\"=\0", key[key_len])!=NULL)) //vlastne by key[key_len] mela byt vzdy 0 ale v SMSce i mezera nebo =
    {
      switch(val_type)
      {
        case JNFL_TYPE_STRING:
          if(kv_map->str_map[i].type == KV_STR_TYPE_STR) strncpy((char*)kv_map->str_map[i].addr, value, kv_map->str_map[i].len-1);


          //TODO: DOPSAT, JE POTREBA PRO ZPRACOVANI KONFIGURACE Z SMS

          ((char*)kv_map->str_map[i].addr)[kv_map->str_map[i].len - 1] = 0;
          break;

        case JNFL_TYPE_NUMBER:
          switch(kv_map->str_map[i].type)
          {
            case KV_STR_TYPE_UCHAR:
              break;

            case KV_STR_TYPE_CHAR:
              break;

            case KV_STR_TYPE_UINT_8:
              *(uint8_t*)kv_map->str_map[i].addr = (uint8_t)atoi(value);
              break;

            case KV_STR_TYPE_INT_8:
              *(int8_t*)kv_map->str_map[i].addr = (int8_t)atoi(value);
              break;

            case KV_STR_TYPE_UINT_16:
              *(uint16_t*)kv_map->str_map[i].addr = (uint16_t)atoi(value);
              break;

            case KV_STR_TYPE_INT_16:
              *(int16_t*)kv_map->str_map[i].addr = (int16_t)atoi(value);
              break;

            case KV_STR_TYPE_UINT_32:
              *(uint32_t*)kv_map->str_map[i].addr = (uint32_t)atoi(value);
              break;

            case KV_STR_TYPE_INT_32:
              *(int32_t*)kv_map->str_map[i].addr = (int32_t)atoi(value);
              break;

            case KV_STR_TYPE_UINT_64:
              *(uint64_t*)kv_map->str_map[i].addr = (uint64_t)atoi(value);
              break;

            case KV_STR_TYPE_INT_64:
              *(int64_t*)kv_map->str_map[i].addr = (int64_t)atoi(value);
              break;

            case KV_STR_TYPE_FLOAT:
              kv_floatpu8LE(kv_map->str_map[i].addr, atof(value));
              break;

            case KV_STR_TYPE_DOUBLE:
              kv_doublepu8LE(kv_map->str_map[i].addr, atof(value));
              break;

            case KV_STR_TYPE_STR:
              strncpy((char*)kv_map->str_map[i].addr, value, kv_map->str_map[i].len);
              ((char*)kv_map->str_map[i].addr)[kv_map->str_map[i].len - 1] = 0;
              break;

            case KV_STR_TYPE_BIN:
              break;

            case KV_STR_TYPE_OBJ:
              break;

            case KV_STR_TYPE_ARRAY:
              break;

            default:
              break;
          }

          break;

        case JNFL_TYPE_OBJECT:
          break;

        case JNFL_TYPE_ARRAY:
          break;

        case JNFL_TYPE_B_TRUE:
          switch(kv_map->str_map[i].type)
          {
            case KV_STR_TYPE_UCHAR:
              *(unsigned char*)kv_map->str_map[i].addr = '1';
              break;

            case KV_STR_TYPE_CHAR:
              *(char*)kv_map->str_map[i].addr = '1';
              break;

            case KV_STR_TYPE_UINT_8:
              *(uint8_t*)kv_map->str_map[i].addr = 1;
              break;

            case KV_STR_TYPE_INT_8:
              *(int8_t*)kv_map->str_map[i].addr = 1;
              break;

            case KV_STR_TYPE_UINT_16:
              *(uint16_t*)kv_map->str_map[i].addr = 1;
              break;

            case KV_STR_TYPE_INT_16:
              *(int16_t*)kv_map->str_map[i].addr = 1;
              break;

            case KV_STR_TYPE_UINT_32:
              *(uint32_t*)kv_map->str_map[i].addr = 1;
              break;

            case KV_STR_TYPE_INT_32:
              *(int32_t*)kv_map->str_map[i].addr = 1;
              break;

            case KV_STR_TYPE_UINT_64:
              *(uint64_t*)kv_map->str_map[i].addr = 1;
              break;

            case KV_STR_TYPE_INT_64:
              *(int64_t*)kv_map->str_map[i].addr = 1;
              break;

            case KV_STR_TYPE_FLOAT:
              kv_floatpu8LE(kv_map->str_map[i].addr, 1);
              break;

            case KV_STR_TYPE_DOUBLE:
              kv_doublepu8LE(kv_map->str_map[i].addr, 1);
              break;

            case KV_STR_TYPE_STR:
              strcpy((char*)kv_map->str_map[i].addr, "true");
              break;

            case KV_STR_TYPE_BIN:
              break;

            case KV_STR_TYPE_OBJ:
              break;

            case KV_STR_TYPE_ARRAY:
              break;

            default:
              break;
          }
          break;

        case JNFL_TYPE_B_FALSE:
          switch(kv_map->str_map[i].type)
          {
            case KV_STR_TYPE_UCHAR:
              *(unsigned char*)kv_map->str_map[i].addr = '0';
              break;

            case KV_STR_TYPE_CHAR:
              *(char*)kv_map->str_map[i].addr = 0;
              break;

            case KV_STR_TYPE_UINT_8:
              *(uint8_t*)kv_map->str_map[i].addr = 0;
              break;

            case KV_STR_TYPE_INT_8:
              *(int8_t*)kv_map->str_map[i].addr = 0;
              break;

            case KV_STR_TYPE_UINT_16:
              *(uint16_t*)kv_map->str_map[i].addr = 0;
              break;

            case KV_STR_TYPE_INT_16:
              *(int16_t*)kv_map->str_map[i].addr = 0;
              break;

            case KV_STR_TYPE_UINT_32:
              *(uint32_t*)kv_map->str_map[i].addr = 0;
              break;

            case KV_STR_TYPE_INT_32:
              *(int32_t*)kv_map->str_map[i].addr = 0;
              break;

            case KV_STR_TYPE_UINT_64:
              *(uint64_t*)kv_map->str_map[i].addr = 0;
              break;

            case KV_STR_TYPE_INT_64:
              *(int64_t*)kv_map->str_map[i].addr = 0;
              break;

            case KV_STR_TYPE_FLOAT:
              kv_floatpu8LE(kv_map->str_map[i].addr, 0);
              break;

            case KV_STR_TYPE_DOUBLE:
              kv_doublepu8LE(kv_map->str_map[i].addr, 0);
              break;

            case KV_STR_TYPE_STR:
              strcpy((char*)kv_map->str_map[i].addr, "false");
              break;

            case KV_STR_TYPE_BIN:
              break;

            case KV_STR_TYPE_OBJ:
              break;

            case KV_STR_TYPE_ARRAY:
              break;

            default:
              break;
          }
          break;

        case JNFL_TYPE_NULL:
          switch(kv_map->str_map[i].type)
          {
            case KV_STR_TYPE_UCHAR:
              *(unsigned char*)kv_map->str_map[i].addr = 0;
              break;

            case KV_STR_TYPE_CHAR:
              *(char*)kv_map->str_map[i].addr = 0;
              break;

            case KV_STR_TYPE_UINT_8:
              *(uint8_t*)kv_map->str_map[i].addr = 0;
              break;

            case KV_STR_TYPE_INT_8:
              *(int8_t*)kv_map->str_map[i].addr = 0;
              break;

            case KV_STR_TYPE_UINT_16:
              *(uint16_t*)kv_map->str_map[i].addr = 0;
              break;

            case KV_STR_TYPE_INT_16:
              *(int16_t*)kv_map->str_map[i].addr = 0;
              break;

            case KV_STR_TYPE_UINT_32:
              *(uint32_t*)kv_map->str_map[i].addr = 0;
              break;

            case KV_STR_TYPE_INT_32:
              *(int32_t*)kv_map->str_map[i].addr = 0;
              break;

            case KV_STR_TYPE_UINT_64:
              *(uint64_t*)kv_map->str_map[i].addr = 0;
              break;

            case KV_STR_TYPE_INT_64:
              *(int64_t*)kv_map->str_map[i].addr = 0;
              break;

            case KV_STR_TYPE_FLOAT:
              kv_floatpu8LE(kv_map->str_map[i].addr, 0);
              break;

            case KV_STR_TYPE_DOUBLE:
              kv_doublepu8LE(kv_map->str_map[i].addr, 0);
              break;

            case KV_STR_TYPE_STR:
              strcpy((char*)kv_map->str_map[i].addr, "null");
              break;

            case KV_STR_TYPE_BIN:
              break;

            case KV_STR_TYPE_OBJ:
              break;

            case KV_STR_TYPE_ARRAY:
              break;

            default:
              break;
          }

          break;

        case JNFL_TYPE_UNKNOWN:
          break;

        default:
          break;
      }

      return;
    }
  }
}
//-----------------------------------------------------------------------------
char* kv_map_json_kv(const kv_map_t *kv_map, char *json_kv, uint32_t item) //cfg[item]->json
{
  //float val_f;

  json_kv+=sprintf(json_kv, "\"%s\": ", kv_map->str_map[item].key);

  switch(kv_map->str_map[item].type)
  {
    case KV_STR_TYPE_UCHAR:
      break;

    case KV_STR_TYPE_CHAR:
      sprintf(json_kv, "\"%c\"", *(char*)kv_map->str_map[item].addr);
      break;

    case KV_STR_TYPE_UINT_8:
      sprintf(json_kv, "%u", *(uint8_t*)kv_map->str_map[item].addr);
      break;

    case KV_STR_TYPE_INT_8:
      sprintf(json_kv, "%i", *(int8_t*)kv_map->str_map[item].addr);
      break;

    case KV_STR_TYPE_UINT_16:
      sprintf(json_kv, "%u", *(uint16_t*)kv_map->str_map[item].addr);
      break;

    case KV_STR_TYPE_INT_16:
      sprintf(json_kv, "%i", *(int16_t*)kv_map->str_map[item].addr);
      break;

    case KV_STR_TYPE_UINT_32:
      sprintf(json_kv, "%lu", *(uint32_t*)kv_map->str_map[item].addr);
      break;

    case KV_STR_TYPE_INT_32:
      sprintf(json_kv, "%li", *(int32_t*)kv_map->str_map[item].addr);
      break;

    case KV_STR_TYPE_UINT_64:
      sprintf(json_kv, "%llu", *(uint64_t*)kv_map->str_map[item].addr);
      break;

    case KV_STR_TYPE_INT_64:
      sprintf(json_kv, "%lli", *(int64_t*)kv_map->str_map[item].addr);
      break;

    case KV_STR_TYPE_FLOAT:
      sprintf(json_kv, "%f", kv_pu8floatLE(kv_map->str_map[item].addr));
      break;

    case KV_STR_TYPE_DOUBLE:
      sprintf(json_kv, "%.10f", kv_pu8doubleLE(kv_map->str_map[item].addr)); //%f prints as 50.111111, %.10f as 50.1111211112
      break;

    case KV_STR_TYPE_STR:
      {
        char *writing_point;
        size_t nolimits=1000;

        strcat(json_kv, "\"");
        writing_point=json_kv+strlen(json_kv);
        json_putstring(&writing_point, &nolimits, (char*)kv_map->str_map[item].addr);
        strcat(json_kv, "\"");
      } break;

    case KV_STR_TYPE_BIN:
      break;

    case KV_STR_TYPE_OBJ:
      break;

    case KV_STR_TYPE_ARRAY:
      break;
  }

  //strcat(json_kv, ",\r\n");

  return (json_kv + strlen(json_kv));
}
//-----------------------------------------------------------------------------
