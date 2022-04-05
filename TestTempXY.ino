#include <HardwareSerial.h>
#include <ModbusMaster.h>
#include "REG_Meter.h"

// instantiate ModbusMaster object
ModbusMaster node;
HardwareSerial MySerial(2);


float Temp1 = 0.0;
float Humi1 = 0.0;
float Temp2 = 0.0;
float Humi2 = 0.0;
float Temp3 = 0.0;
float Humi3 = 0.0;
float Temp4 = 0.0;
float Humi4 = 0.0;



void setup()
{
  // use Serial (port 0); initialize Modbus communication baud rate
  Serial.begin(115200);
  MySerial.begin(9600, SERIAL_8N1, 16, 17);

  // communicate witModbus slave ID 2 over Serial (port 0)
  //node.begin(1, MySerial);
  /*node.setTransmitBuffer(0x00, 0x0000);
    node.writeMultipleCoils(0, 6);
    delay(100);
    node.setTransmitBuffer(0x00, 0x003F);
    node.writeMultipleCoils(0, 6);
    delay(100);
    node.setTransmitBuffer(0x00, 0x0000);
    node.writeMultipleCoils(0, 6);
    delay(100);

    node.begin(2, MySerial);
    node.setTransmitBuffer(0x00, 0x0000);
    node.writeMultipleCoils(0, 6);
    delay(100);
    node.setTransmitBuffer(0x00, 0x003F);
    node.writeMultipleCoils(0, 6);
    delay(100);
    node.setTransmitBuffer(0x00, 0x0000);
    node.writeMultipleCoils(0, 6);
    delay(100);*/
}

bool state = true;

void loop()
{
  static uint32_t i;
  uint8_t j, result;
  uint16_t data[6];
  uint32_t value = 0;
  //i++;
  /*
    node.begin(2, Serial2);
      node.writeSingleCoil(0, state);
      delay(100);
      node.writeSingleCoil(1, state);
      delay(100);
      node.writeSingleCoil(2, state);
      delay(100);
      node.writeSingleCoil(3, state);
      delay(100);*/
  //node.writeSingleCoil(4, state);
  //delay(100);
  //node.writeSingleCoil(5, state);
  //delay(100);

  /*node.begin(2, MySerial);
    node.writeSingleCoil(0, state);
    delay(100);
    node.writeSingleCoil(1, state);
    delay(100);
    node.writeSingleCoil(2, state);
    delay(100);
    node.writeSingleCoil(3, state);
    delay(100);
    node.writeSingleCoil(4, state);
    delay(100);
    node.writeSingleCoil(5, state);
    delay(100);*/

  //state = !state;


  // slave: read (6) 16-bit registers starting at register 2 to RX buffer
//  result = node.readInputRegisters(1, 2);
//
//  // do something with data if read is successful
//  if (result == node.ku8MBSuccess)
//  {
//    for (j = 0; j < 2; j++)
//    {
//      data[j] = node.getResponseBuffer(j);
//    }
//  }

//  value = data[0];
//  value = value << 16;
//  value = value + data[1];
//  Temp1 = HexTofloat(value);

  for (j = 0; j < 2; j++)
  {
    Serial.print(data[j] * 0.1);
    Serial.print("\t");
  }

//  Serial.print("\t");
//  Serial.print("Temp: ");
//  Serial.print(Temp1);
//  Serial.println();

  GET_METER();

  Temp1 = (DATA_METER_TH1[0] / 10.0);
  Humi1 = (DATA_METER_TH1[1] / 10.0);

  Serial.print(Temp1);
  Serial.print("\t");
  Serial.println(Humi1);
  /*
    Temp2 = (DATA_METER_TH2[0] / 10.0);
    Humi2 = (DATA_METER_TH2[1] / 10.0);

    Temp3 = (DATA_METER_TH3[0] / 10.0);
    Humi3 = (DATA_METER_TH3[1] / 10.0);

    Temp4 = (DATA_METER_TH4[0] / 10.0);
    Humi4 = (DATA_METER_TH4[1] / 10.0);*/
    delay(200);
}

void GET_METER()
{ // Update read all data
  delay(100);
  for (int i = 0; i < Total_of_Reg_TH ; i++)
  {
    DATA_METER_TH1 [i] = Read_Meter_TH(THID1_meter, Reg_addr_TH[i]);
  }
  /*
    delay(100);
    for (int i = 0; i < Total_of_Reg_TH ; i++)
    {
      DATA_METER_TH2 [i] = Read_Meter_TH(THID2_meter, Reg_addr_TH[i]);
    }

    delay(100);
    for (int i = 0; i < Total_of_Reg_TH ; i++)
    {
      DATA_METER_TH3 [i] = Read_Meter_TH(THID3_meter, Reg_addr_TH[i]);
    }

    delay(100);
    for (int i = 0; i < Total_of_Reg_TH ; i++)
    {
      DATA_METER_TH4 [i] = Read_Meter_TH(THID4_meter, Reg_addr_TH[i]);
    }
    delay(100);*/
}

long Read_Meter_TH(char addr , int  REG)
{
  uint8_t result;
  int data = 0;

  node.begin(addr, MySerial);

  result = node.readInputRegisters (REG, 1);

  delay(100);
  if (result == node.ku8MBSuccess)
  {
    data = node.getResponseBuffer(0);

    //Serial.println("Connec modbus Ok.");
    return data;
  } else
  {
    Serial.print("Connec modbus ID: 1 Temp Sensor fail. REG >>> "); Serial.println(REG); // Debug
    delay(100);
    return 0;
  }
}

float HexTofloat(uint32_t x)
{
  return (*(float*)&x);
}
