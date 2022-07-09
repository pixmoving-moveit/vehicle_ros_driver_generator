/******************************************************************************
 fulongma
 *****************************************************************************/
#include "vcu2acu_chassiserrcode1_200.hpp"


Vcu2acuchassiserrcode1200::Vcu2acuchassiserrcode1200() {}
int32_t Vcu2acuchassiserrcode1200::ID = 0x200;

void Vcu2acuchassiserrcode1200::update_bytes(uint8_t bytes_data[8])
{
  for(uint i=0;i<8;i++)
  {
    bytes[i] = bytes_data[i];
  }
}

void Vcu2acuchassiserrcode1200::Parse() {
  bms_communicationfault = BMSCommunicationFault();
  chassisemergencysta = ChassisEmergencySta();
  leadacidbatterylow = LeadacidBatteryLow();
  controlercommunicationfault = ControlerCommunicationFault();
  chassiscrashsta = ChassisCrashSta();
  eps_rearcommunicationfault = EPSRearCommunicationFault();
  eps_frontcommunicationfault = EPSFrontCommunicationFault();
  eds_rrcommunicationfault = EDSRrCommunicationFault();
  eds_rfcommunicationfault = EDSRfCommunicationFault();
  eds_lrcommunicationfault = EDSLrCommunicationFault();
  eds_lfcommunicationfault = EDSLfCommunicationFault();
  ebs_communicationfault = EBSCommunicationFault();
  chassisvcuothererr = ChassisVcuOtherErr();
}


// config detail: {'bit': 7, 'is_signed_var': False, 'len': 1, 'name': 'BMS_CommunicationFault', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'bool'}
bool Vcu2acuchassiserrcode1200::BMSCommunicationFault() {
  Byte t0(*(bytes + 0));
  int32_t x = t0.get_byte(7, 1);

  bool ret = x;
  return ret;
}

// config detail: {'bit': 10, 'is_signed_var': False, 'len': 1, 'name': 'ChassisEmergencySta', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'bool'}
bool Vcu2acuchassiserrcode1200::ChassisEmergencySta() {
  Byte t0(*(bytes + 1));
  int32_t x = t0.get_byte(2, 1);

  bool ret = x;
  return ret;
}

// config detail: {'bit': 11, 'is_signed_var': False, 'len': 1, 'name': 'LeadacidBatteryLow', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'bool'}
bool Vcu2acuchassiserrcode1200::LeadacidBatteryLow() {
  Byte t0(*(bytes + 1));
  int32_t x = t0.get_byte(3, 1);

  bool ret = x;
  return ret;
}

// config detail: {'bit': 8, 'is_signed_var': False, 'len': 1, 'name': 'ControlerCommunicationFault', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'bool'}
bool Vcu2acuchassiserrcode1200::ControlerCommunicationFault() {
  Byte t0(*(bytes + 1));
  int32_t x = t0.get_byte(0, 1);

  bool ret = x;
  return ret;
}

// config detail: {'bit': 9, 'is_signed_var': False, 'len': 1, 'name': 'ChassisCrashSta', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'bool'}
bool Vcu2acuchassiserrcode1200::ChassisCrashSta() {
  Byte t0(*(bytes + 1));
  int32_t x = t0.get_byte(1, 1);

  bool ret = x;
  return ret;
}

// config detail: {'bit': 6, 'is_signed_var': False, 'len': 1, 'name': 'EPS_RearCommunicationFault', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'bool'}
bool Vcu2acuchassiserrcode1200::EPSRearCommunicationFault() {
  Byte t0(*(bytes + 0));
  int32_t x = t0.get_byte(6, 1);

  bool ret = x;
  return ret;
}

// config detail: {'bit': 5, 'is_signed_var': False, 'len': 1, 'name': 'EPS_FrontCommunicationFault', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'bool'}
bool Vcu2acuchassiserrcode1200::EPSFrontCommunicationFault() {
  Byte t0(*(bytes + 0));
  int32_t x = t0.get_byte(5, 1);

  bool ret = x;
  return ret;
}

// config detail: {'bit': 3, 'is_signed_var': False, 'len': 1, 'name': 'EDS_RrCommunicationFault', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'bool'}
bool Vcu2acuchassiserrcode1200::EDSRrCommunicationFault() {
  Byte t0(*(bytes + 0));
  int32_t x = t0.get_byte(3, 1);

  bool ret = x;
  return ret;
}

// config detail: {'bit': 2, 'is_signed_var': False, 'len': 1, 'name': 'EDS_RfCommunicationFault', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'bool'}
bool Vcu2acuchassiserrcode1200::EDSRfCommunicationFault() {
  Byte t0(*(bytes + 0));
  int32_t x = t0.get_byte(2, 1);

  bool ret = x;
  return ret;
}

// config detail: {'bit': 1, 'is_signed_var': False, 'len': 1, 'name': 'EDS_LrCommunicationFault', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'bool'}
bool Vcu2acuchassiserrcode1200::EDSLrCommunicationFault() {
  Byte t0(*(bytes + 0));
  int32_t x = t0.get_byte(1, 1);

  bool ret = x;
  return ret;
}

// config detail: {'bit': 0, 'is_signed_var': False, 'len': 1, 'name': 'EDS_LfCommunicationFault', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'bool'}
bool Vcu2acuchassiserrcode1200::EDSLfCommunicationFault() {
  Byte t0(*(bytes + 0));
  int32_t x = t0.get_byte(0, 1);

  bool ret = x;
  return ret;
}

// config detail: {'bit': 4, 'is_signed_var': False, 'len': 1, 'name': 'EBS_CommunicationFault', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'bool'}
bool Vcu2acuchassiserrcode1200::EBSCommunicationFault() {
  Byte t0(*(bytes + 0));
  int32_t x = t0.get_byte(4, 1);

  bool ret = x;
  return ret;
}

// config detail: {'bit': 23, 'is_signed_var': False, 'len': 8, 'name': 'ChassisVcuOtherErr', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
int Vcu2acuchassiserrcode1200::ChassisVcuOtherErr() {
  Byte t0(*(bytes + 2));
  int32_t x = t0.get_byte(0, 8);

  int ret = x;
  return ret;
}

