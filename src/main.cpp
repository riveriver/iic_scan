#include <Arduino.h>
#include "BQ25896.h"

const byte IO_EN = 18;
BQ25896  battery_charging;
TwoWire Wire_1 = TwoWire(0);

void setup() {
  byte error;
  pinMode(IO_EN, OUTPUT);
  digitalWrite(IO_EN, HIGH);
  Serial.begin(115200);
  Serial.println("Serial System Begin !");
  Wire_1.begin(8, 9,400000U);
  Wire_1.beginTransmission(0x6A);
  error = Wire_1.endTransmission();
  if(error == 0){
    Serial.println("wire transmission success");
  }else{
    Serial.printf("Wire_1 transmission returned error %d",error);
    Serial.println("");
  }
  // Wire_1.beginTransmission(0x4B);
  // error = Wire_1.endTransmission();
  // if(error == 0){
  //   Serial.println("wire transmission success");
  // }else{
  //   Serial.printf("Wire_1 transmission returned error %d",error);
  //   Serial.println("");
  // }
  battery_charging.begin(&Wire_1);
}

void loop() {
  /* 001 */
  // Serial.println("Running!");
  // delay(1000);
  /* 002 */
  battery_charging.properties();
  Serial.println("Battery Management System Parameter : \n===============================================================");
  Serial.print("VBUS : "); Serial.println(battery_charging.getVBUS());
  Serial.print("VSYS : "); Serial.println(battery_charging.getVSYS());
  Serial.print("VBAT : "); Serial.println(battery_charging.getVBAT());
  Serial.print("ICHG : "); Serial.println(battery_charging.getICHG(),4);
  Serial.print("TSPCT : "); Serial.println(battery_charging.getTSPCT());
  Serial.print("Temperature : "); Serial.println(battery_charging.getTemperature());
  
  Serial.print("FS_Current Limit : "); Serial.println(battery_charging.getFast_Charge_Current_Limit());
  Serial.print("IN_Current Limit : "); Serial.println(battery_charging.getInput_Current_Limit());
  Serial.print("PRE_CHG_Current Limit : "); Serial.println(battery_charging.getPreCharge_Current_Limit());
  Serial.print("TERM_Current Limit : "); Serial.println(battery_charging.getTermination_Current_Limit());

  Serial.print("Charging Status : "); Serial.println(battery_charging.getCHG_STATUS()==BQ25896::CHG_STAT::NOT_CHARGING?" not charging":
                                                          (battery_charging.getCHG_STATUS()==BQ25896::CHG_STAT::PRE_CHARGE ?" pre charging":
                                                          (battery_charging.getCHG_STATUS()==BQ25896::CHG_STAT::FAST_CHARGE?" Fast charging":"charging done"))); 
  
  Serial.print("VBUS Status : "); Serial.println(battery_charging.getVBUS_STATUS()==BQ25896::VBUS_STAT::NO_INPUT?" not input":
                                                          (battery_charging.getVBUS_STATUS()==BQ25896::VBUS_STAT::USB_HOST ?" USB host":
                                                          (battery_charging.getVBUS_STATUS()==BQ25896::VBUS_STAT::ADAPTER?" Adapter":"OTG")));
  
  Serial.print("VSYS Status : "); Serial.println(battery_charging.getVSYS_STATUS()==BQ25896::VSYS_STAT::IN_VSYSMIN?" In VSYSMIN regulation (BAT < VSYSMIN)":
                                                      "Not in VSYSMIN regulation (BAT > VSYSMIN)");
  
  Serial.print("Temperature rank : "); Serial.println(battery_charging.getTemp_Rank()==BQ25896::TS_RANK::NORMAL?" Normal":
                                                          (battery_charging.getTemp_Rank()==BQ25896::TS_RANK::WARM ?" Warm":
                                                          (battery_charging.getTemp_Rank()==BQ25896::TS_RANK::COOL?" Cool":
                                                          (battery_charging.getTemp_Rank()==BQ25896::TS_RANK::COLD?" Cold":"HOT"))));
  
  Serial.print("Charger fault status  : "); Serial.println(battery_charging.getCHG_Fault_STATUS()==BQ25896::CHG_FAULT::NORMAL?" Normal":
                                                          (battery_charging.getCHG_Fault_STATUS()==BQ25896::CHG_FAULT::INPUT_FAULT ?" Input Fault":
                                                          (battery_charging.getCHG_Fault_STATUS()==BQ25896::CHG_FAULT::THERMAL_SHUTDOWN?" Thermal Shutdown":"TIMER_EXPIRED")));
  
  Serial.print("[WATCHDOG_FAULT]"); Serial.println(battery_charging.WATCHDOG_FAULT_ == BQ25896::WATCHDOG_FAULT::NORMAL ? "NORMAL" : "TIMER_EXPIRATION ");
  Serial.print("[BOOST_FAULT]"); Serial.println(battery_charging.BOOST_FAULT_ == BQ25896::BOOST_FAULT::NORMAL ? "NORMAL" : "FAULT");
  Serial.print("[BAT_FAULT]"); Serial.println(battery_charging.BAT_FAULT_  == BQ25896::BAT_FAULT ::NORMAL ? "NORMAL" : "BATOVP");
  Serial.print("[CHG_STAT]"); Serial.println(battery_charging.CHRG_FAULT_  == BQ25896::CHRG_FAULT ::NORMAL  ? "NORMAL" :
                                            (battery_charging.CHRG_FAULT_  == BQ25896::CHRG_FAULT ::INPUT_FAULT   ? "INPUT_FAULT " :
                                            (battery_charging.CHRG_FAULT_  == BQ25896::CHRG_FAULT ::THERMAL_SHUTDOWN   ? "THERMAL_SHUTDOWN " : "TIMER_EXPIRATION ")));
  /* 003 */
  // byte error, address;
  // int nDevices;
  // Serial.println("Scanning...");
  // nDevices = 0;
  // for (address = 1; address < 127; address++ ){
  //   // The i2c_scanner uses the return value of
  //   // the Write.endTransmisstion to see if
  //   // a device did acknowledge to the address.
  //   Wire_1.beginTransmission(address);
  //   error = Wire_1.endTransmission();
  //   if (error == 0){
  //     Serial.print("I2C device found at address 0x");
  //     if (address < 16)
  //       Serial.print("0");
  //     Serial.print(address, HEX);
  //     Serial.println(" !");
  //     nDevices++;
  //   }else if (error == 4){
  //     Serial.print("Unknow error at address 0x");
  //     if (address < 16)
  //       Serial.print("0");
  //     Serial.println(address, HEX);
  //   }
  // }
  // if (nDevices == 0)
  //   Serial.println("No I2C devices found\n");
  // else
  //   Serial.println("done\n");
  delay(1000); // wait 5 seconds for next scan
}
