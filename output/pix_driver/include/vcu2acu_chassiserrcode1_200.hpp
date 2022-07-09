/******************************************************************************
 fulongma
 *****************************************************************************/

#pragma once

#include "Byte.hpp"
#include <iostream>

class Vcu2acuchassiserrcode1200 {
public:
    static  int32_t ID;
    Vcu2acuchassiserrcode1200();
    void Parse();
    void update_bytes(uint8_t bytes_data[8]);
    // singal
    bool bms_communicationfault;
    bool chassisemergencysta;
    bool leadacidbatterylow;
    bool controlercommunicationfault;
    bool chassiscrashsta;
    bool eps_rearcommunicationfault;
    bool eps_frontcommunicationfault;
    bool eds_rrcommunicationfault;
    bool eds_rfcommunicationfault;
    bool eds_lrcommunicationfault;
    bool eds_lfcommunicationfault;
    bool ebs_communicationfault;
    int chassisvcuothererr;
    

private:
    uint8_t bytes[8];
    
  // config detail: {'bit': 7, 'is_signed_var': False, 'len': 1, 'name': 'BMS_CommunicationFault', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'bool'}
  bool BMSCommunicationFault();

  // config detail: {'bit': 10, 'is_signed_var': False, 'len': 1, 'name': 'ChassisEmergencySta', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'bool'}
  bool ChassisEmergencySta();

  // config detail: {'bit': 11, 'is_signed_var': False, 'len': 1, 'name': 'LeadacidBatteryLow', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'bool'}
  bool LeadacidBatteryLow();

  // config detail: {'bit': 8, 'is_signed_var': False, 'len': 1, 'name': 'ControlerCommunicationFault', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'bool'}
  bool ControlerCommunicationFault();

  // config detail: {'bit': 9, 'is_signed_var': False, 'len': 1, 'name': 'ChassisCrashSta', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'bool'}
  bool ChassisCrashSta();

  // config detail: {'bit': 6, 'is_signed_var': False, 'len': 1, 'name': 'EPS_RearCommunicationFault', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'bool'}
  bool EPSRearCommunicationFault();

  // config detail: {'bit': 5, 'is_signed_var': False, 'len': 1, 'name': 'EPS_FrontCommunicationFault', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'bool'}
  bool EPSFrontCommunicationFault();

  // config detail: {'bit': 3, 'is_signed_var': False, 'len': 1, 'name': 'EDS_RrCommunicationFault', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'bool'}
  bool EDSRrCommunicationFault();

  // config detail: {'bit': 2, 'is_signed_var': False, 'len': 1, 'name': 'EDS_RfCommunicationFault', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'bool'}
  bool EDSRfCommunicationFault();

  // config detail: {'bit': 1, 'is_signed_var': False, 'len': 1, 'name': 'EDS_LrCommunicationFault', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'bool'}
  bool EDSLrCommunicationFault();

  // config detail: {'bit': 0, 'is_signed_var': False, 'len': 1, 'name': 'EDS_LfCommunicationFault', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'bool'}
  bool EDSLfCommunicationFault();

  // config detail: {'bit': 4, 'is_signed_var': False, 'len': 1, 'name': 'EBS_CommunicationFault', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'bool'}
  bool EBSCommunicationFault();

  // config detail: {'bit': 23, 'is_signed_var': False, 'len': 8, 'name': 'ChassisVcuOtherErr', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
  int ChassisVcuOtherErr();
};



