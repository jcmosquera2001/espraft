#include "Database.hpp"
#include "FS.h"

using namespace locke;

int Database::get(void *record, char* file_name, uint32_t pos, size_t size)
{
  //File f = SD.open(file_name, 0X01);
  File f = SPIFFS.open(file_name, "r");
  f.seek(pos);
  int result = f.read((uint8_t *)record, size);
  f.close();

  // Serial.print("get from: ");
  // Serial.println(file_name);
  // for (int i = 0; i < size; i++) Serial.print(((char *)record)[i], HEX);
  // Serial.println();

  return result;
}

int Database::set(void *record, char* file_name, uint32_t pos, size_t size)
{
  //File f = SD.open(file_name, 0X02 | 0x0200);
  File f = SPIFFS.open(file_name, "r+");
  f.seek(pos);
  int result = f.write((const uint8_t *)record, size);
  f.close();
  
  // Serial.print("set to: ");
  // Serial.println(file_name);
  // for (int i = 0; i < size; i++) Serial.print(((char *)record)[i], HEX);
  // Serial.println();

  return result;
}
