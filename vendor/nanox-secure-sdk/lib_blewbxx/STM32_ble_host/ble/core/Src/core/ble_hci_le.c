/******************************************************************************
 * @file    ble_hci_le.c
 * @author  MCD Application Team
 * @date    07 September 2018
 * @brief   Source file for ble api STM32WB (hci_le)
 *          Auto-generated file: do not edit!
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2018 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under Ultimate Liberty license
 * SLA0044, the "License"; You may not use this file except in compliance with
 * the License. You may obtain a copy of the License at:
 *                             www.st.com/SLA0044
 *
 ******************************************************************************
 */

#include "ble_hci_le.h"
tBleStatus hci_disconnect(uint16_t Connection_Handle,
                          uint8_t Reason)
{
  struct hci_request rq;
  uint8_t cmd_buffer[258];
  hci_disconnect_cp0 *cp0 = (hci_disconnect_cp0*)(cmd_buffer);
  tBleStatus status = 0;
  uint8_t index_input = 0;
  cp0->Connection_Handle = htob(Connection_Handle, 2);
  index_input += 2;
  cp0->Reason = htob(Reason, 1);
  index_input += 1;
  Osal_MemSet(&rq, 0, sizeof(rq));
  rq.ogf = 0x01;
  rq.ocf = 0x006;
  rq.event = 0x0F;
  rq.cparam = cmd_buffer;
  rq.clen = index_input;
  rq.rparam = &status;
  rq.rlen = 1;
  if (hci_send_req(&rq, FALSE) < 0)
    return BLE_STATUS_TIMEOUT;
  if (status) {
    return status;
  }
  return BLE_STATUS_SUCCESS;
}
tBleStatus hci_read_remote_version_information(uint16_t Connection_Handle)
{
  struct hci_request rq;
  uint8_t cmd_buffer[258];
  hci_read_remote_version_information_cp0 *cp0 = (hci_read_remote_version_information_cp0*)(cmd_buffer);
  tBleStatus status = 0;
  uint8_t index_input = 0;
  cp0->Connection_Handle = htob(Connection_Handle, 2);
  index_input += 2;
  Osal_MemSet(&rq, 0, sizeof(rq));
  rq.ogf = 0x01;
  rq.ocf = 0x01d;
  rq.event = 0x0F;
  rq.cparam = cmd_buffer;
  rq.clen = index_input;
  rq.rparam = &status;
  rq.rlen = 1;
  if (hci_send_req(&rq, FALSE) < 0)
    return BLE_STATUS_TIMEOUT;
  if (status) {
    return status;
  }
  return BLE_STATUS_SUCCESS;
}
tBleStatus hci_set_event_mask(uint8_t Event_Mask[8])
{
  struct hci_request rq;
  uint8_t cmd_buffer[258];
  hci_set_event_mask_cp0 *cp0 = (hci_set_event_mask_cp0*)(cmd_buffer);
  tBleStatus status = 0;
  uint8_t index_input = 0;
  Osal_MemCpy((void *) &cp0->Event_Mask, (const void *) Event_Mask, 8);
  index_input += 8;
  Osal_MemSet(&rq, 0, sizeof(rq));
  rq.ogf = 0x03;
  rq.ocf = 0x001;
  rq.cparam = cmd_buffer;
  rq.clen = index_input;
  rq.rparam = &status;
  rq.rlen = 1;
  if (hci_send_req(&rq, FALSE) < 0)
    return BLE_STATUS_TIMEOUT;
  if (status) {
    return status;
  }
  return BLE_STATUS_SUCCESS;
}
tBleStatus hci_reset(void)
{
  struct hci_request rq;
  tBleStatus status = 0;
  Osal_MemSet(&rq, 0, sizeof(rq));
  rq.ogf = 0x03;
  rq.ocf = 0x003;
  rq.rparam = &status;
  rq.rlen = 1;
  if (hci_send_req(&rq, FALSE) < 0)
    return BLE_STATUS_TIMEOUT;
  if (status) {
    return status;
  }
  return BLE_STATUS_SUCCESS;
}
tBleStatus hci_read_transmit_power_level(uint16_t Connection_Handle,
                                         uint8_t Type,
                                         uint8_t *Transmit_Power_Level)
{
  struct hci_request rq;
  uint8_t cmd_buffer[258];
  hci_read_transmit_power_level_cp0 *cp0 = (hci_read_transmit_power_level_cp0*)(cmd_buffer);
  hci_read_transmit_power_level_rp0 resp;
  Osal_MemSet(&resp, 0, sizeof(resp));
  uint8_t index_input = 0;
  cp0->Connection_Handle = htob(Connection_Handle, 2);
  index_input += 2;
  cp0->Type = htob(Type, 1);
  index_input += 1;
  Osal_MemSet(&rq, 0, sizeof(rq));
  rq.ogf = 0x03;
  rq.ocf = 0x02d;
  rq.cparam = cmd_buffer;
  rq.clen = index_input;
  rq.rparam = &resp;
  rq.rlen = sizeof(resp);
  if (hci_send_req(&rq, FALSE) < 0)
    return BLE_STATUS_TIMEOUT;
  if (resp.Status) {
    return resp.Status;
  }
  *Transmit_Power_Level = btoh(resp.Transmit_Power_Level, 1);
  return BLE_STATUS_SUCCESS;
}
tBleStatus hci_read_local_version_information(uint8_t *HCI_Version,
                                              uint16_t *HCI_Revision,
                                              uint8_t *LMP_PAL_Version,
                                              uint16_t *Manufacturer_Name,
                                              uint16_t *LMP_PAL_Subversion)
{
  struct hci_request rq;
  hci_read_local_version_information_rp0 resp;
  Osal_MemSet(&resp, 0, sizeof(resp));
  Osal_MemSet(&rq, 0, sizeof(rq));
  rq.ogf = 0x04;
  rq.ocf = 0x001;
  rq.rparam = &resp;
  rq.rlen = sizeof(resp);
  if (hci_send_req(&rq, FALSE) < 0)
    return BLE_STATUS_TIMEOUT;
  if (resp.Status) {
    return resp.Status;
  }
  *HCI_Version = btoh(resp.HCI_Version, 1);
  *HCI_Revision = btoh(resp.HCI_Revision, 2);
  *LMP_PAL_Version = btoh(resp.LMP_PAL_Version, 1);
  *Manufacturer_Name = btoh(resp.Manufacturer_Name, 2);
  *LMP_PAL_Subversion = btoh(resp.LMP_PAL_Subversion, 2);
  return BLE_STATUS_SUCCESS;
}
tBleStatus hci_read_local_supported_commands(uint8_t Supported_Commands[64])
{
  struct hci_request rq;
  hci_read_local_supported_commands_rp0 resp;
  Osal_MemSet(&resp, 0, sizeof(resp));
  Osal_MemSet(&rq, 0, sizeof(rq));
  rq.ogf = 0x04;
  rq.ocf = 0x002;
  rq.rparam = &resp;
  rq.rlen = sizeof(resp);
  if (hci_send_req(&rq, FALSE) < 0)
    return BLE_STATUS_TIMEOUT;
  if (resp.Status) {
    return resp.Status;
  }
  Osal_MemCpy((void *) Supported_Commands, (const void *) resp.Supported_Commands, 64);
  return BLE_STATUS_SUCCESS;
}
tBleStatus hci_read_local_supported_features(uint8_t LMP_Features[8])
{
  struct hci_request rq;
  hci_read_local_supported_features_rp0 resp;
  Osal_MemSet(&resp, 0, sizeof(resp));
  Osal_MemSet(&rq, 0, sizeof(rq));
  rq.ogf = 0x04;
  rq.ocf = 0x003;
  rq.rparam = &resp;
  rq.rlen = sizeof(resp);
  if (hci_send_req(&rq, FALSE) < 0)
    return BLE_STATUS_TIMEOUT;
  if (resp.Status) {
    return resp.Status;
  }
  Osal_MemCpy((void *) LMP_Features, (const void *) resp.LMP_Features, 8);
  return BLE_STATUS_SUCCESS;
}
tBleStatus hci_read_bd_addr(uint8_t BD_ADDR[6])
{
  struct hci_request rq;
  hci_read_bd_addr_rp0 resp;
  Osal_MemSet(&resp, 0, sizeof(resp));
  Osal_MemSet(&rq, 0, sizeof(rq));
  rq.ogf = 0x04;
  rq.ocf = 0x009;
  rq.rparam = &resp;
  rq.rlen = sizeof(resp);
  if (hci_send_req(&rq, FALSE) < 0)
    return BLE_STATUS_TIMEOUT;
  if (resp.Status) {
    return resp.Status;
  }
  Osal_MemCpy((void *) BD_ADDR, (const void *) resp.BD_ADDR, 6);
  return BLE_STATUS_SUCCESS;
}
tBleStatus hci_read_rssi(uint16_t Connection_Handle,
                         uint8_t *RSSI)
{
  struct hci_request rq;
  uint8_t cmd_buffer[258];
  hci_read_rssi_cp0 *cp0 = (hci_read_rssi_cp0*)(cmd_buffer);
  hci_read_rssi_rp0 resp;
  Osal_MemSet(&resp, 0, sizeof(resp));
  uint8_t index_input = 0;
  cp0->Connection_Handle = htob(Connection_Handle, 2);
  index_input += 2;
  Osal_MemSet(&rq, 0, sizeof(rq));
  rq.ogf = 0x05;
  rq.ocf = 0x005;
  rq.cparam = cmd_buffer;
  rq.clen = index_input;
  rq.rparam = &resp;
  rq.rlen = sizeof(resp);
  if (hci_send_req(&rq, FALSE) < 0)
    return BLE_STATUS_TIMEOUT;
  if (resp.Status) {
    return resp.Status;
  }
  *RSSI = btoh(resp.RSSI, 1);
  return BLE_STATUS_SUCCESS;
}
tBleStatus hci_le_set_event_mask(uint8_t LE_Event_Mask[8])
{
  struct hci_request rq;
  uint8_t cmd_buffer[258];
  hci_le_set_event_mask_cp0 *cp0 = (hci_le_set_event_mask_cp0*)(cmd_buffer);
  tBleStatus status = 0;
  uint8_t index_input = 0;
  Osal_MemCpy((void *) &cp0->LE_Event_Mask, (const void *) LE_Event_Mask, 8);
  index_input += 8;
  Osal_MemSet(&rq, 0, sizeof(rq));
  rq.ogf = 0x08;
  rq.ocf = 0x001;
  rq.cparam = cmd_buffer;
  rq.clen = index_input;
  rq.rparam = &status;
  rq.rlen = 1;
  if (hci_send_req(&rq, FALSE) < 0)
    return BLE_STATUS_TIMEOUT;
  if (status) {
    return status;
  }
  return BLE_STATUS_SUCCESS;
}
tBleStatus hci_le_read_buffer_size(uint16_t *HC_LE_ACL_Data_Packet_Length,
                                   uint8_t *HC_Total_Num_LE_ACL_Data_Packets)
{
  struct hci_request rq;
  hci_le_read_buffer_size_rp0 resp;
  Osal_MemSet(&resp, 0, sizeof(resp));
  Osal_MemSet(&rq, 0, sizeof(rq));
  rq.ogf = 0x08;
  rq.ocf = 0x002;
  rq.rparam = &resp;
  rq.rlen = sizeof(resp);
  if (hci_send_req(&rq, FALSE) < 0)
    return BLE_STATUS_TIMEOUT;
  if (resp.Status) {
    return resp.Status;
  }
  *HC_LE_ACL_Data_Packet_Length = btoh(resp.HC_LE_ACL_Data_Packet_Length, 2);
  *HC_Total_Num_LE_ACL_Data_Packets = btoh(resp.HC_Total_Num_LE_ACL_Data_Packets, 1);
  return BLE_STATUS_SUCCESS;
}
tBleStatus hci_le_read_local_supported_features(uint8_t LE_Features[8])
{
  struct hci_request rq;
  hci_le_read_local_supported_features_rp0 resp;
  Osal_MemSet(&resp, 0, sizeof(resp));
  Osal_MemSet(&rq, 0, sizeof(rq));
  rq.ogf = 0x08;
  rq.ocf = 0x003;
  rq.rparam = &resp;
  rq.rlen = sizeof(resp);
  if (hci_send_req(&rq, FALSE) < 0)
    return BLE_STATUS_TIMEOUT;
  if (resp.Status) {
    return resp.Status;
  }
  Osal_MemCpy((void *) LE_Features, (const void *) resp.LE_Features, 8);
  return BLE_STATUS_SUCCESS;
}
tBleStatus hci_le_set_random_address(uint8_t Random_Address[6])
{
  struct hci_request rq;
  uint8_t cmd_buffer[258];
  hci_le_set_random_address_cp0 *cp0 = (hci_le_set_random_address_cp0*)(cmd_buffer);
  tBleStatus status = 0;
  uint8_t index_input = 0;
  Osal_MemCpy((void *) &cp0->Random_Address, (const void *) Random_Address, 6);
  index_input += 6;
  Osal_MemSet(&rq, 0, sizeof(rq));
  rq.ogf = 0x08;
  rq.ocf = 0x005;
  rq.cparam = cmd_buffer;
  rq.clen = index_input;
  rq.rparam = &status;
  rq.rlen = 1;
  if (hci_send_req(&rq, FALSE) < 0)
    return BLE_STATUS_TIMEOUT;
  if (status) {
    return status;
  }
  return BLE_STATUS_SUCCESS;
}
tBleStatus hci_le_set_advertising_parameters(uint16_t Advertising_Interval_Min,
                                             uint16_t Advertising_Interval_Max,
                                             uint8_t Advertising_Type,
                                             uint8_t Own_Address_Type,
                                             uint8_t Peer_Address_Type,
                                             uint8_t Peer_Address[6],
                                             uint8_t Advertising_Channel_Map,
                                             uint8_t Advertising_Filter_Policy)
{
  struct hci_request rq;
  uint8_t cmd_buffer[258];
  hci_le_set_advertising_parameters_cp0 *cp0 = (hci_le_set_advertising_parameters_cp0*)(cmd_buffer);
  tBleStatus status = 0;
  uint8_t index_input = 0;
  cp0->Advertising_Interval_Min = htob(Advertising_Interval_Min, 2);
  index_input += 2;
  cp0->Advertising_Interval_Max = htob(Advertising_Interval_Max, 2);
  index_input += 2;
  cp0->Advertising_Type = htob(Advertising_Type, 1);
  index_input += 1;
  cp0->Own_Address_Type = htob(Own_Address_Type, 1);
  index_input += 1;
  cp0->Peer_Address_Type = htob(Peer_Address_Type, 1);
  index_input += 1;
  Osal_MemCpy((void *) &cp0->Peer_Address, (const void *) Peer_Address, 6);
  index_input += 6;
  cp0->Advertising_Channel_Map = htob(Advertising_Channel_Map, 1);
  index_input += 1;
  cp0->Advertising_Filter_Policy = htob(Advertising_Filter_Policy, 1);
  index_input += 1;
  Osal_MemSet(&rq, 0, sizeof(rq));
  rq.ogf = 0x08;
  rq.ocf = 0x006;
  rq.cparam = cmd_buffer;
  rq.clen = index_input;
  rq.rparam = &status;
  rq.rlen = 1;
  if (hci_send_req(&rq, FALSE) < 0)
    return BLE_STATUS_TIMEOUT;
  if (status) {
    return status;
  }
  return BLE_STATUS_SUCCESS;
}
tBleStatus hci_le_read_advertising_channel_tx_power(uint8_t *Transmit_Power_Level)
{
  struct hci_request rq;
  hci_le_read_advertising_channel_tx_power_rp0 resp;
  Osal_MemSet(&resp, 0, sizeof(resp));
  Osal_MemSet(&rq, 0, sizeof(rq));
  rq.ogf = 0x08;
  rq.ocf = 0x007;
  rq.rparam = &resp;
  rq.rlen = sizeof(resp);
  if (hci_send_req(&rq, FALSE) < 0)
    return BLE_STATUS_TIMEOUT;
  if (resp.Status) {
    return resp.Status;
  }
  *Transmit_Power_Level = btoh(resp.Transmit_Power_Level, 1);
  return BLE_STATUS_SUCCESS;
}
tBleStatus hci_le_set_advertising_data(uint8_t Advertising_Data_Length,
                                       uint8_t Advertising_Data[31])
{
  struct hci_request rq;
  uint8_t cmd_buffer[258];
  hci_le_set_advertising_data_cp0 *cp0 = (hci_le_set_advertising_data_cp0*)(cmd_buffer);
  tBleStatus status = 0;
  uint8_t index_input = 0;
  cp0->Advertising_Data_Length = htob(Advertising_Data_Length, 1);
  index_input += 1;
  Osal_MemCpy((void *) &cp0->Advertising_Data, (const void *) Advertising_Data, 31);
  index_input += 31;
  Osal_MemSet(&rq, 0, sizeof(rq));
  rq.ogf = 0x08;
  rq.ocf = 0x008;
  rq.cparam = cmd_buffer;
  rq.clen = index_input;
  rq.rparam = &status;
  rq.rlen = 1;
  if (hci_send_req(&rq, FALSE) < 0)
    return BLE_STATUS_TIMEOUT;
  if (status) {
    return status;
  }
  return BLE_STATUS_SUCCESS;
}
tBleStatus hci_le_set_scan_response_data(uint8_t Scan_Response_Data_Length,
                                         uint8_t Scan_Response_Data[31])
{
  struct hci_request rq;
  uint8_t cmd_buffer[258];
  hci_le_set_scan_response_data_cp0 *cp0 = (hci_le_set_scan_response_data_cp0*)(cmd_buffer);
  tBleStatus status = 0;
  uint8_t index_input = 0;
  cp0->Scan_Response_Data_Length = htob(Scan_Response_Data_Length, 1);
  index_input += 1;
  Osal_MemCpy((void *) &cp0->Scan_Response_Data, (const void *) Scan_Response_Data, 31);
  index_input += 31;
  Osal_MemSet(&rq, 0, sizeof(rq));
  rq.ogf = 0x08;
  rq.ocf = 0x009;
  rq.cparam = cmd_buffer;
  rq.clen = index_input;
  rq.rparam = &status;
  rq.rlen = 1;
  if (hci_send_req(&rq, FALSE) < 0)
    return BLE_STATUS_TIMEOUT;
  if (status) {
    return status;
  }
  return BLE_STATUS_SUCCESS;
}
tBleStatus hci_le_set_advertise_enable(uint8_t Advertising_Enable)
{
  struct hci_request rq;
  uint8_t cmd_buffer[258];
  hci_le_set_advertise_enable_cp0 *cp0 = (hci_le_set_advertise_enable_cp0*)(cmd_buffer);
  tBleStatus status = 0;
  uint8_t index_input = 0;
  cp0->Advertising_Enable = htob(Advertising_Enable, 1);
  index_input += 1;
  Osal_MemSet(&rq, 0, sizeof(rq));
  rq.ogf = 0x08;
  rq.ocf = 0x00a;
  rq.cparam = cmd_buffer;
  rq.clen = index_input;
  rq.rparam = &status;
  rq.rlen = 1;
  if (hci_send_req(&rq, FALSE) < 0)
    return BLE_STATUS_TIMEOUT;
  if (status) {
    return status;
  }
  return BLE_STATUS_SUCCESS;
}
tBleStatus hci_le_set_scan_parameters(uint8_t LE_Scan_Type,
                                      uint16_t LE_Scan_Interval,
                                      uint16_t LE_Scan_Window,
                                      uint8_t Own_Address_Type,
                                      uint8_t Scanning_Filter_Policy)
{
  struct hci_request rq;
  uint8_t cmd_buffer[258];
  hci_le_set_scan_parameters_cp0 *cp0 = (hci_le_set_scan_parameters_cp0*)(cmd_buffer);
  tBleStatus status = 0;
  uint8_t index_input = 0;
  cp0->LE_Scan_Type = htob(LE_Scan_Type, 1);
  index_input += 1;
  cp0->LE_Scan_Interval = htob(LE_Scan_Interval, 2);
  index_input += 2;
  cp0->LE_Scan_Window = htob(LE_Scan_Window, 2);
  index_input += 2;
  cp0->Own_Address_Type = htob(Own_Address_Type, 1);
  index_input += 1;
  cp0->Scanning_Filter_Policy = htob(Scanning_Filter_Policy, 1);
  index_input += 1;
  Osal_MemSet(&rq, 0, sizeof(rq));
  rq.ogf = 0x08;
  rq.ocf = 0x00b;
  rq.cparam = cmd_buffer;
  rq.clen = index_input;
  rq.rparam = &status;
  rq.rlen = 1;
  if (hci_send_req(&rq, FALSE) < 0)
    return BLE_STATUS_TIMEOUT;
  if (status) {
    return status;
  }
  return BLE_STATUS_SUCCESS;
}
tBleStatus hci_le_set_scan_enable(uint8_t LE_Scan_Enable,
                                  uint8_t Filter_Duplicates)
{
  struct hci_request rq;
  uint8_t cmd_buffer[258];
  hci_le_set_scan_enable_cp0 *cp0 = (hci_le_set_scan_enable_cp0*)(cmd_buffer);
  tBleStatus status = 0;
  uint8_t index_input = 0;
  cp0->LE_Scan_Enable = htob(LE_Scan_Enable, 1);
  index_input += 1;
  cp0->Filter_Duplicates = htob(Filter_Duplicates, 1);
  index_input += 1;
  Osal_MemSet(&rq, 0, sizeof(rq));
  rq.ogf = 0x08;
  rq.ocf = 0x00c;
  rq.cparam = cmd_buffer;
  rq.clen = index_input;
  rq.rparam = &status;
  rq.rlen = 1;
  if (hci_send_req(&rq, FALSE) < 0)
    return BLE_STATUS_TIMEOUT;
  if (status) {
    return status;
  }
  return BLE_STATUS_SUCCESS;
}
tBleStatus hci_le_create_connection(uint16_t LE_Scan_Interval,
                                    uint16_t LE_Scan_Window,
                                    uint8_t Initiator_Filter_Policy,
                                    uint8_t Peer_Address_Type,
                                    uint8_t Peer_Address[6],
                                    uint8_t Own_Address_Type,
                                    uint16_t Conn_Interval_Min,
                                    uint16_t Conn_Interval_Max,
                                    uint16_t Conn_Latency,
                                    uint16_t Supervision_Timeout,
                                    uint16_t Minimum_CE_Length,
                                    uint16_t Maximum_CE_Length)
{
  struct hci_request rq;
  uint8_t cmd_buffer[258];
  hci_le_create_connection_cp0 *cp0 = (hci_le_create_connection_cp0*)(cmd_buffer);
  tBleStatus status = 0;
  uint8_t index_input = 0;
  cp0->LE_Scan_Interval = htob(LE_Scan_Interval, 2);
  index_input += 2;
  cp0->LE_Scan_Window = htob(LE_Scan_Window, 2);
  index_input += 2;
  cp0->Initiator_Filter_Policy = htob(Initiator_Filter_Policy, 1);
  index_input += 1;
  cp0->Peer_Address_Type = htob(Peer_Address_Type, 1);
  index_input += 1;
  Osal_MemCpy((void *) &cp0->Peer_Address, (const void *) Peer_Address, 6);
  index_input += 6;
  cp0->Own_Address_Type = htob(Own_Address_Type, 1);
  index_input += 1;
  cp0->Conn_Interval_Min = htob(Conn_Interval_Min, 2);
  index_input += 2;
  cp0->Conn_Interval_Max = htob(Conn_Interval_Max, 2);
  index_input += 2;
  cp0->Conn_Latency = htob(Conn_Latency, 2);
  index_input += 2;
  cp0->Supervision_Timeout = htob(Supervision_Timeout, 2);
  index_input += 2;
  cp0->Minimum_CE_Length = htob(Minimum_CE_Length, 2);
  index_input += 2;
  cp0->Maximum_CE_Length = htob(Maximum_CE_Length, 2);
  index_input += 2;
  Osal_MemSet(&rq, 0, sizeof(rq));
  rq.ogf = 0x08;
  rq.ocf = 0x00d;
  rq.event = 0x0F;
  rq.cparam = cmd_buffer;
  rq.clen = index_input;
  rq.rparam = &status;
  rq.rlen = 1;
  if (hci_send_req(&rq, FALSE) < 0)
    return BLE_STATUS_TIMEOUT;
  if (status) {
    return status;
  }
  return BLE_STATUS_SUCCESS;
}
tBleStatus hci_le_create_connection_cancel(void)
{
  struct hci_request rq;
  tBleStatus status = 0;
  Osal_MemSet(&rq, 0, sizeof(rq));
  rq.ogf = 0x08;
  rq.ocf = 0x00e;
  rq.rparam = &status;
  rq.rlen = 1;
  if (hci_send_req(&rq, FALSE) < 0)
    return BLE_STATUS_TIMEOUT;
  if (status) {
    return status;
  }
  return BLE_STATUS_SUCCESS;
}
tBleStatus hci_le_read_white_list_size(uint8_t *White_List_Size)
{
  struct hci_request rq;
  hci_le_read_white_list_size_rp0 resp;
  Osal_MemSet(&resp, 0, sizeof(resp));
  Osal_MemSet(&rq, 0, sizeof(rq));
  rq.ogf = 0x08;
  rq.ocf = 0x00f;
  rq.rparam = &resp;
  rq.rlen = sizeof(resp);
  if (hci_send_req(&rq, FALSE) < 0)
    return BLE_STATUS_TIMEOUT;
  if (resp.Status) {
    return resp.Status;
  }
  *White_List_Size = btoh(resp.White_List_Size, 1);
  return BLE_STATUS_SUCCESS;
}
tBleStatus hci_le_clear_white_list(void)
{
  struct hci_request rq;
  tBleStatus status = 0;
  Osal_MemSet(&rq, 0, sizeof(rq));
  rq.ogf = 0x08;
  rq.ocf = 0x010;
  rq.rparam = &status;
  rq.rlen = 1;
  if (hci_send_req(&rq, FALSE) < 0)
    return BLE_STATUS_TIMEOUT;
  if (status) {
    return status;
  }
  return BLE_STATUS_SUCCESS;
}
tBleStatus hci_le_add_device_to_white_list(uint8_t Address_Type,
                                           uint8_t Address[6])
{
  struct hci_request rq;
  uint8_t cmd_buffer[258];
  hci_le_add_device_to_white_list_cp0 *cp0 = (hci_le_add_device_to_white_list_cp0*)(cmd_buffer);
  tBleStatus status = 0;
  uint8_t index_input = 0;
  cp0->Address_Type = htob(Address_Type, 1);
  index_input += 1;
  Osal_MemCpy((void *) &cp0->Address, (const void *) Address, 6);
  index_input += 6;
  Osal_MemSet(&rq, 0, sizeof(rq));
  rq.ogf = 0x08;
  rq.ocf = 0x011;
  rq.cparam = cmd_buffer;
  rq.clen = index_input;
  rq.rparam = &status;
  rq.rlen = 1;
  if (hci_send_req(&rq, FALSE) < 0)
    return BLE_STATUS_TIMEOUT;
  if (status) {
    return status;
  }
  return BLE_STATUS_SUCCESS;
}
tBleStatus hci_le_remove_device_from_white_list(uint8_t Address_Type,
                                                uint8_t Address[6])
{
  struct hci_request rq;
  uint8_t cmd_buffer[258];
  hci_le_remove_device_from_white_list_cp0 *cp0 = (hci_le_remove_device_from_white_list_cp0*)(cmd_buffer);
  tBleStatus status = 0;
  uint8_t index_input = 0;
  cp0->Address_Type = htob(Address_Type, 1);
  index_input += 1;
  Osal_MemCpy((void *) &cp0->Address, (const void *) Address, 6);
  index_input += 6;
  Osal_MemSet(&rq, 0, sizeof(rq));
  rq.ogf = 0x08;
  rq.ocf = 0x012;
  rq.cparam = cmd_buffer;
  rq.clen = index_input;
  rq.rparam = &status;
  rq.rlen = 1;
  if (hci_send_req(&rq, FALSE) < 0)
    return BLE_STATUS_TIMEOUT;
  if (status) {
    return status;
  }
  return BLE_STATUS_SUCCESS;
}
tBleStatus hci_le_connection_update(uint16_t Connection_Handle,
                                    uint16_t Conn_Interval_Min,
                                    uint16_t Conn_Interval_Max,
                                    uint16_t Conn_Latency,
                                    uint16_t Supervision_Timeout,
                                    uint16_t Minimum_CE_Length,
                                    uint16_t Maximum_CE_Length)
{
  struct hci_request rq;
  uint8_t cmd_buffer[258];
  hci_le_connection_update_cp0 *cp0 = (hci_le_connection_update_cp0*)(cmd_buffer);
  tBleStatus status = 0;
  uint8_t index_input = 0;
  cp0->Connection_Handle = htob(Connection_Handle, 2);
  index_input += 2;
  cp0->Conn_Interval_Min = htob(Conn_Interval_Min, 2);
  index_input += 2;
  cp0->Conn_Interval_Max = htob(Conn_Interval_Max, 2);
  index_input += 2;
  cp0->Conn_Latency = htob(Conn_Latency, 2);
  index_input += 2;
  cp0->Supervision_Timeout = htob(Supervision_Timeout, 2);
  index_input += 2;
  cp0->Minimum_CE_Length = htob(Minimum_CE_Length, 2);
  index_input += 2;
  cp0->Maximum_CE_Length = htob(Maximum_CE_Length, 2);
  index_input += 2;
  Osal_MemSet(&rq, 0, sizeof(rq));
  rq.ogf = 0x08;
  rq.ocf = 0x013;
  rq.event = 0x0F;
  rq.cparam = cmd_buffer;
  rq.clen = index_input;
  rq.rparam = &status;
  rq.rlen = 1;
  if (hci_send_req(&rq, FALSE) < 0)
    return BLE_STATUS_TIMEOUT;
  if (status) {
    return status;
  }
  return BLE_STATUS_SUCCESS;
}
tBleStatus hci_le_set_host_channel_classification(uint8_t LE_Channel_Map[5])
{
  struct hci_request rq;
  uint8_t cmd_buffer[258];
  hci_le_set_host_channel_classification_cp0 *cp0 = (hci_le_set_host_channel_classification_cp0*)(cmd_buffer);
  tBleStatus status = 0;
  uint8_t index_input = 0;
  Osal_MemCpy((void *) &cp0->LE_Channel_Map, (const void *) LE_Channel_Map, 5);
  index_input += 5;
  Osal_MemSet(&rq, 0, sizeof(rq));
  rq.ogf = 0x08;
  rq.ocf = 0x014;
  rq.cparam = cmd_buffer;
  rq.clen = index_input;
  rq.rparam = &status;
  rq.rlen = 1;
  if (hci_send_req(&rq, FALSE) < 0)
    return BLE_STATUS_TIMEOUT;
  if (status) {
    return status;
  }
  return BLE_STATUS_SUCCESS;
}
tBleStatus hci_le_read_channel_map(uint16_t Connection_Handle,
                                   uint8_t LE_Channel_Map[5])
{
  struct hci_request rq;
  uint8_t cmd_buffer[258];
  hci_le_read_channel_map_cp0 *cp0 = (hci_le_read_channel_map_cp0*)(cmd_buffer);
  hci_le_read_channel_map_rp0 resp;
  Osal_MemSet(&resp, 0, sizeof(resp));
  uint8_t index_input = 0;
  cp0->Connection_Handle = htob(Connection_Handle, 2);
  index_input += 2;
  Osal_MemSet(&rq, 0, sizeof(rq));
  rq.ogf = 0x08;
  rq.ocf = 0x015;
  rq.cparam = cmd_buffer;
  rq.clen = index_input;
  rq.rparam = &resp;
  rq.rlen = sizeof(resp);
  if (hci_send_req(&rq, FALSE) < 0)
    return BLE_STATUS_TIMEOUT;
  if (resp.Status) {
    return resp.Status;
  }
  Osal_MemCpy((void *) LE_Channel_Map, (const void *) resp.LE_Channel_Map, 5);
  return BLE_STATUS_SUCCESS;
}
tBleStatus hci_le_read_remote_used_features(uint16_t Connection_Handle)
{
  struct hci_request rq;
  uint8_t cmd_buffer[258];
  hci_le_read_remote_used_features_cp0 *cp0 = (hci_le_read_remote_used_features_cp0*)(cmd_buffer);
  tBleStatus status = 0;
  uint8_t index_input = 0;
  cp0->Connection_Handle = htob(Connection_Handle, 2);
  index_input += 2;
  Osal_MemSet(&rq, 0, sizeof(rq));
  rq.ogf = 0x08;
  rq.ocf = 0x016;
  rq.event = 0x0F;
  rq.cparam = cmd_buffer;
  rq.clen = index_input;
  rq.rparam = &status;
  rq.rlen = 1;
  if (hci_send_req(&rq, FALSE) < 0)
    return BLE_STATUS_TIMEOUT;
  if (status) {
    return status;
  }
  return BLE_STATUS_SUCCESS;
}
tBleStatus hci_le_encrypt(uint8_t Key[16],
                          uint8_t Plaintext_Data[16],
                          uint8_t Encrypted_Data[16])
{
  struct hci_request rq;
  uint8_t cmd_buffer[258];
  hci_le_encrypt_cp0 *cp0 = (hci_le_encrypt_cp0*)(cmd_buffer);
  hci_le_encrypt_rp0 resp;
  Osal_MemSet(&resp, 0, sizeof(resp));
  uint8_t index_input = 0;
  Osal_MemCpy((void *) &cp0->Key, (const void *) Key, 16);
  index_input += 16;
  Osal_MemCpy((void *) &cp0->Plaintext_Data, (const void *) Plaintext_Data, 16);
  index_input += 16;
  Osal_MemSet(&rq, 0, sizeof(rq));
  rq.ogf = 0x08;
  rq.ocf = 0x017;
  rq.cparam = cmd_buffer;
  rq.clen = index_input;
  rq.rparam = &resp;
  rq.rlen = sizeof(resp);
  if (hci_send_req(&rq, FALSE) < 0)
    return BLE_STATUS_TIMEOUT;
  if (resp.Status) {
    return resp.Status;
  }
  Osal_MemCpy((void *) Encrypted_Data, (const void *) resp.Encrypted_Data, 16);
  return BLE_STATUS_SUCCESS;
}
tBleStatus hci_le_rand(uint8_t Random_Number[8])
{
  struct hci_request rq;
  hci_le_rand_rp0 resp;
  Osal_MemSet(&resp, 0, sizeof(resp));
  Osal_MemSet(&rq, 0, sizeof(rq));
  rq.ogf = 0x08;
  rq.ocf = 0x018;
  rq.rparam = &resp;
  rq.rlen = sizeof(resp);
  if (hci_send_req(&rq, FALSE) < 0)
    return BLE_STATUS_TIMEOUT;
  if (resp.Status) {
    return resp.Status;
  }
  Osal_MemCpy((void *) Random_Number, (const void *) resp.Random_Number, 8);
  return BLE_STATUS_SUCCESS;
}
tBleStatus hci_le_start_encryption(uint16_t Connection_Handle,
                                   uint8_t Random_Number[8],
                                   uint16_t Encrypted_Diversifier,
                                   uint8_t Long_Term_Key[16])
{
  struct hci_request rq;
  uint8_t cmd_buffer[258];
  hci_le_start_encryption_cp0 *cp0 = (hci_le_start_encryption_cp0*)(cmd_buffer);
  tBleStatus status = 0;
  uint8_t index_input = 0;
  cp0->Connection_Handle = htob(Connection_Handle, 2);
  index_input += 2;
  Osal_MemCpy((void *) &cp0->Random_Number, (const void *) Random_Number, 8);
  index_input += 8;
  cp0->Encrypted_Diversifier = htob(Encrypted_Diversifier, 2);
  index_input += 2;
  Osal_MemCpy((void *) &cp0->Long_Term_Key, (const void *) Long_Term_Key, 16);
  index_input += 16;
  Osal_MemSet(&rq, 0, sizeof(rq));
  rq.ogf = 0x08;
  rq.ocf = 0x019;
  rq.event = 0x0F;
  rq.cparam = cmd_buffer;
  rq.clen = index_input;
  rq.rparam = &status;
  rq.rlen = 1;
  if (hci_send_req(&rq, FALSE) < 0)
    return BLE_STATUS_TIMEOUT;
  if (status) {
    return status;
  }
  return BLE_STATUS_SUCCESS;
}
tBleStatus hci_le_long_term_key_request_reply(uint16_t Connection_Handle,
                                              uint8_t Long_Term_Key[16])
{
  struct hci_request rq;
  uint8_t cmd_buffer[258];
  hci_le_long_term_key_request_reply_cp0 *cp0 = (hci_le_long_term_key_request_reply_cp0*)(cmd_buffer);
  hci_le_long_term_key_request_reply_rp0 resp;
  Osal_MemSet(&resp, 0, sizeof(resp));
  uint8_t index_input = 0;
  cp0->Connection_Handle = htob(Connection_Handle, 2);
  index_input += 2;
  Osal_MemCpy((void *) &cp0->Long_Term_Key, (const void *) Long_Term_Key, 16);
  index_input += 16;
  Osal_MemSet(&rq, 0, sizeof(rq));
  rq.ogf = 0x08;
  rq.ocf = 0x01a;
  rq.cparam = cmd_buffer;
  rq.clen = index_input;
  rq.rparam = &resp;
  rq.rlen = sizeof(resp);
  if (hci_send_req(&rq, FALSE) < 0)
    return BLE_STATUS_TIMEOUT;
  if (resp.Status) {
    return resp.Status;
  }
  return BLE_STATUS_SUCCESS;
}
tBleStatus hci_le_long_term_key_requested_negative_reply(uint16_t Connection_Handle)
{
  struct hci_request rq;
  uint8_t cmd_buffer[258];
  hci_le_long_term_key_requested_negative_reply_cp0 *cp0 = (hci_le_long_term_key_requested_negative_reply_cp0*)(cmd_buffer);
  hci_le_long_term_key_requested_negative_reply_rp0 resp;
  Osal_MemSet(&resp, 0, sizeof(resp));
  uint8_t index_input = 0;
  cp0->Connection_Handle = htob(Connection_Handle, 2);
  index_input += 2;
  Osal_MemSet(&rq, 0, sizeof(rq));
  rq.ogf = 0x08;
  rq.ocf = 0x01b;
  rq.cparam = cmd_buffer;
  rq.clen = index_input;
  rq.rparam = &resp;
  rq.rlen = sizeof(resp);
  if (hci_send_req(&rq, FALSE) < 0)
    return BLE_STATUS_TIMEOUT;
  if (resp.Status) {
    return resp.Status;
  }
  return BLE_STATUS_SUCCESS;
}
tBleStatus hci_le_read_supported_states(uint8_t LE_States[8])
{
  struct hci_request rq;
  hci_le_read_supported_states_rp0 resp;
  Osal_MemSet(&resp, 0, sizeof(resp));
  Osal_MemSet(&rq, 0, sizeof(rq));
  rq.ogf = 0x08;
  rq.ocf = 0x01c;
  rq.rparam = &resp;
  rq.rlen = sizeof(resp);
  if (hci_send_req(&rq, FALSE) < 0)
    return BLE_STATUS_TIMEOUT;
  if (resp.Status) {
    return resp.Status;
  }
  Osal_MemCpy((void *) LE_States, (const void *) resp.LE_States, 8);
  return BLE_STATUS_SUCCESS;
}
tBleStatus hci_le_receiver_test(uint8_t RX_Frequency)
{
  struct hci_request rq;
  uint8_t cmd_buffer[258];
  hci_le_receiver_test_cp0 *cp0 = (hci_le_receiver_test_cp0*)(cmd_buffer);
  tBleStatus status = 0;
  uint8_t index_input = 0;
  cp0->RX_Frequency = htob(RX_Frequency, 1);
  index_input += 1;
  Osal_MemSet(&rq, 0, sizeof(rq));
  rq.ogf = 0x08;
  rq.ocf = 0x01d;
  rq.cparam = cmd_buffer;
  rq.clen = index_input;
  rq.rparam = &status;
  rq.rlen = 1;
  if (hci_send_req(&rq, FALSE) < 0)
    return BLE_STATUS_TIMEOUT;
  if (status) {
    return status;
  }
  return BLE_STATUS_SUCCESS;
}
tBleStatus hci_le_transmitter_test(uint8_t TX_Frequency,
                                   uint8_t Length_Of_Test_Data,
                                   uint8_t Packet_Payload)
{
  struct hci_request rq;
  uint8_t cmd_buffer[258];
  hci_le_transmitter_test_cp0 *cp0 = (hci_le_transmitter_test_cp0*)(cmd_buffer);
  tBleStatus status = 0;
  uint8_t index_input = 0;
  cp0->TX_Frequency = htob(TX_Frequency, 1);
  index_input += 1;
  cp0->Length_Of_Test_Data = htob(Length_Of_Test_Data, 1);
  index_input += 1;
  cp0->Packet_Payload = htob(Packet_Payload, 1);
  index_input += 1;
  Osal_MemSet(&rq, 0, sizeof(rq));
  rq.ogf = 0x08;
  rq.ocf = 0x01e;
  rq.cparam = cmd_buffer;
  rq.clen = index_input;
  rq.rparam = &status;
  rq.rlen = 1;
  if (hci_send_req(&rq, FALSE) < 0)
    return BLE_STATUS_TIMEOUT;
  if (status) {
    return status;
  }
  return BLE_STATUS_SUCCESS;
}
tBleStatus hci_le_test_end(uint16_t *Number_Of_Packets)
{
  struct hci_request rq;
  hci_le_test_end_rp0 resp;
  Osal_MemSet(&resp, 0, sizeof(resp));
  Osal_MemSet(&rq, 0, sizeof(rq));
  rq.ogf = 0x08;
  rq.ocf = 0x01f;
  rq.rparam = &resp;
  rq.rlen = sizeof(resp);
  if (hci_send_req(&rq, FALSE) < 0)
    return BLE_STATUS_TIMEOUT;
  if (resp.Status) {
    return resp.Status;
  }
  *Number_Of_Packets = btoh(resp.Number_Of_Packets, 2);
  return BLE_STATUS_SUCCESS;
}
tBleStatus hci_le_set_data_length(uint16_t Connection_Handle,
                                  uint16_t TxOctets,
                                  uint16_t TxTime)
{
  struct hci_request rq;
  uint8_t cmd_buffer[258];
  hci_le_set_data_length_cp0 *cp0 = (hci_le_set_data_length_cp0*)(cmd_buffer);
  hci_le_set_data_length_rp0 resp;
  Osal_MemSet(&resp, 0, sizeof(resp));
  uint8_t index_input = 0;
  cp0->Connection_Handle = htob(Connection_Handle, 2);
  index_input += 2;
  cp0->TxOctets = htob(TxOctets, 2);
  index_input += 2;
  cp0->TxTime = htob(TxTime, 2);
  index_input += 2;
  Osal_MemSet(&rq, 0, sizeof(rq));
  rq.ogf = 0x08;
  rq.ocf = 0x022;
  rq.cparam = cmd_buffer;
  rq.clen = index_input;
  rq.rparam = &resp;
  rq.rlen = sizeof(resp);
  if (hci_send_req(&rq, FALSE) < 0)
    return BLE_STATUS_TIMEOUT;
  if (resp.Status) {
    return resp.Status;
  }
  return BLE_STATUS_SUCCESS;
}
tBleStatus hci_le_read_suggested_default_data_length(uint16_t *SuggestedMaxTxOctets,
                                                     uint16_t *SuggestedMaxTxTime)
{
  struct hci_request rq;
  hci_le_read_suggested_default_data_length_rp0 resp;
  Osal_MemSet(&resp, 0, sizeof(resp));
  Osal_MemSet(&rq, 0, sizeof(rq));
  rq.ogf = 0x08;
  rq.ocf = 0x023;
  rq.rparam = &resp;
  rq.rlen = sizeof(resp);
  if (hci_send_req(&rq, FALSE) < 0)
    return BLE_STATUS_TIMEOUT;
  if (resp.Status) {
    return resp.Status;
  }
  *SuggestedMaxTxOctets = btoh(resp.SuggestedMaxTxOctets, 2);
  *SuggestedMaxTxTime = btoh(resp.SuggestedMaxTxTime, 2);
  return BLE_STATUS_SUCCESS;
}
tBleStatus hci_le_write_suggested_default_data_length(uint16_t SuggestedMaxTxOctets,
                                                      uint16_t SuggestedMaxTxTime)
{
  struct hci_request rq;
  uint8_t cmd_buffer[258];
  hci_le_write_suggested_default_data_length_cp0 *cp0 = (hci_le_write_suggested_default_data_length_cp0*)(cmd_buffer);
  tBleStatus status = 0;
  uint8_t index_input = 0;
  cp0->SuggestedMaxTxOctets = htob(SuggestedMaxTxOctets, 2);
  index_input += 2;
  cp0->SuggestedMaxTxTime = htob(SuggestedMaxTxTime, 2);
  index_input += 2;
  Osal_MemSet(&rq, 0, sizeof(rq));
  rq.ogf = 0x08;
  rq.ocf = 0x024;
  rq.cparam = cmd_buffer;
  rq.clen = index_input;
  rq.rparam = &status;
  rq.rlen = 1;
  if (hci_send_req(&rq, FALSE) < 0)
    return BLE_STATUS_TIMEOUT;
  if (status) {
    return status;
  }
  return BLE_STATUS_SUCCESS;
}
tBleStatus hci_le_read_local_p256_public_key(void)
{
  struct hci_request rq;
  tBleStatus status = 0;
  Osal_MemSet(&rq, 0, sizeof(rq));
  rq.ogf = 0x08;
  rq.ocf = 0x025;
  rq.event = 0x0F;
  rq.rparam = &status;
  rq.rlen = 1;
  if (hci_send_req(&rq, FALSE) < 0)
    return BLE_STATUS_TIMEOUT;
  if (status) {
    return status;
  }
  return BLE_STATUS_SUCCESS;
}
tBleStatus hci_le_generate_dhkey(uint8_t Remote_P256_Public_Key[64])
{
  struct hci_request rq;
  uint8_t cmd_buffer[258];
  hci_le_generate_dhkey_cp0 *cp0 = (hci_le_generate_dhkey_cp0*)(cmd_buffer);
  tBleStatus status = 0;
  uint8_t index_input = 0;
  Osal_MemCpy((void *) &cp0->Remote_P256_Public_Key, (const void *) Remote_P256_Public_Key, 64);
  index_input += 64;
  Osal_MemSet(&rq, 0, sizeof(rq));
  rq.ogf = 0x08;
  rq.ocf = 0x026;
  rq.event = 0x0F;
  rq.cparam = cmd_buffer;
  rq.clen = index_input;
  rq.rparam = &status;
  rq.rlen = 1;
  if (hci_send_req(&rq, FALSE) < 0)
    return BLE_STATUS_TIMEOUT;
  if (status) {
    return status;
  }
  return BLE_STATUS_SUCCESS;
}
tBleStatus hci_le_add_device_to_resolving_list(uint8_t Peer_Identity_Address_Type,
                                               uint8_t Peer_Identity_Address[6],
                                               uint8_t Peer_IRK[16],
                                               uint8_t Local_IRK[16])
{
  struct hci_request rq;
  uint8_t cmd_buffer[258];
  hci_le_add_device_to_resolving_list_cp0 *cp0 = (hci_le_add_device_to_resolving_list_cp0*)(cmd_buffer);
  tBleStatus status = 0;
  uint8_t index_input = 0;
  cp0->Peer_Identity_Address_Type = htob(Peer_Identity_Address_Type, 1);
  index_input += 1;
  Osal_MemCpy((void *) &cp0->Peer_Identity_Address, (const void *) Peer_Identity_Address, 6);
  index_input += 6;
  Osal_MemCpy((void *) &cp0->Peer_IRK, (const void *) Peer_IRK, 16);
  index_input += 16;
  Osal_MemCpy((void *) &cp0->Local_IRK, (const void *) Local_IRK, 16);
  index_input += 16;
  Osal_MemSet(&rq, 0, sizeof(rq));
  rq.ogf = 0x08;
  rq.ocf = 0x027;
  rq.cparam = cmd_buffer;
  rq.clen = index_input;
  rq.rparam = &status;
  rq.rlen = 1;
  if (hci_send_req(&rq, FALSE) < 0)
    return BLE_STATUS_TIMEOUT;
  if (status) {
    return status;
  }
  return BLE_STATUS_SUCCESS;
}
tBleStatus hci_le_remove_device_from_resolving_list(uint8_t Peer_Identity_Address_Type,
                                                    uint8_t Peer_Identity_Address[6])
{
  struct hci_request rq;
  uint8_t cmd_buffer[258];
  hci_le_remove_device_from_resolving_list_cp0 *cp0 = (hci_le_remove_device_from_resolving_list_cp0*)(cmd_buffer);
  tBleStatus status = 0;
  uint8_t index_input = 0;
  cp0->Peer_Identity_Address_Type = htob(Peer_Identity_Address_Type, 1);
  index_input += 1;
  Osal_MemCpy((void *) &cp0->Peer_Identity_Address, (const void *) Peer_Identity_Address, 6);
  index_input += 6;
  Osal_MemSet(&rq, 0, sizeof(rq));
  rq.ogf = 0x08;
  rq.ocf = 0x028;
  rq.cparam = cmd_buffer;
  rq.clen = index_input;
  rq.rparam = &status;
  rq.rlen = 1;
  if (hci_send_req(&rq, FALSE) < 0)
    return BLE_STATUS_TIMEOUT;
  if (status) {
    return status;
  }
  return BLE_STATUS_SUCCESS;
}
tBleStatus hci_le_clear_resolving_list(void)
{
  struct hci_request rq;
  tBleStatus status = 0;
  Osal_MemSet(&rq, 0, sizeof(rq));
  rq.ogf = 0x08;
  rq.ocf = 0x029;
  rq.rparam = &status;
  rq.rlen = 1;
  if (hci_send_req(&rq, FALSE) < 0)
    return BLE_STATUS_TIMEOUT;
  if (status) {
    return status;
  }
  return BLE_STATUS_SUCCESS;
}
tBleStatus hci_le_read_resolving_list_size(uint8_t *Resolving_List_Size)
{
  struct hci_request rq;
  hci_le_read_resolving_list_size_rp0 resp;
  Osal_MemSet(&resp, 0, sizeof(resp));
  Osal_MemSet(&rq, 0, sizeof(rq));
  rq.ogf = 0x08;
  rq.ocf = 0x02a;
  rq.rparam = &resp;
  rq.rlen = sizeof(resp);
  if (hci_send_req(&rq, FALSE) < 0)
    return BLE_STATUS_TIMEOUT;
  if (resp.Status) {
    return resp.Status;
  }
  *Resolving_List_Size = btoh(resp.Resolving_List_Size, 1);
  return BLE_STATUS_SUCCESS;
}
tBleStatus hci_le_read_peer_resolvable_address(uint8_t Peer_Identity_Address_Type,
                                               uint8_t Peer_Identity_Address[6],
                                               uint8_t Peer_Resolvable_Address[6])
{
  struct hci_request rq;
  uint8_t cmd_buffer[258];
  hci_le_read_peer_resolvable_address_cp0 *cp0 = (hci_le_read_peer_resolvable_address_cp0*)(cmd_buffer);
  hci_le_read_peer_resolvable_address_rp0 resp;
  Osal_MemSet(&resp, 0, sizeof(resp));
  uint8_t index_input = 0;
  cp0->Peer_Identity_Address_Type = htob(Peer_Identity_Address_Type, 1);
  index_input += 1;
  Osal_MemCpy((void *) &cp0->Peer_Identity_Address, (const void *) Peer_Identity_Address, 6);
  index_input += 6;
  Osal_MemSet(&rq, 0, sizeof(rq));
  rq.ogf = 0x08;
  rq.ocf = 0x02b;
  rq.cparam = cmd_buffer;
  rq.clen = index_input;
  rq.rparam = &resp;
  rq.rlen = sizeof(resp);
  if (hci_send_req(&rq, FALSE) < 0)
    return BLE_STATUS_TIMEOUT;
  if (resp.Status) {
    return resp.Status;
  }
  Osal_MemCpy((void *) Peer_Resolvable_Address, (const void *) resp.Peer_Resolvable_Address, 6);
  return BLE_STATUS_SUCCESS;
}
tBleStatus hci_le_read_local_resolvable_address(uint8_t Peer_Identity_Address_Type,
                                                uint8_t Peer_Identity_Address[6],
                                                uint8_t Local_Resolvable_Address[6])
{
  struct hci_request rq;
  uint8_t cmd_buffer[258];
  hci_le_read_local_resolvable_address_cp0 *cp0 = (hci_le_read_local_resolvable_address_cp0*)(cmd_buffer);
  hci_le_read_local_resolvable_address_rp0 resp;
  Osal_MemSet(&resp, 0, sizeof(resp));
  uint8_t index_input = 0;
  cp0->Peer_Identity_Address_Type = htob(Peer_Identity_Address_Type, 1);
  index_input += 1;
  Osal_MemCpy((void *) &cp0->Peer_Identity_Address, (const void *) Peer_Identity_Address, 6);
  index_input += 6;
  Osal_MemSet(&rq, 0, sizeof(rq));
  rq.ogf = 0x08;
  rq.ocf = 0x02c;
  rq.cparam = cmd_buffer;
  rq.clen = index_input;
  rq.rparam = &resp;
  rq.rlen = sizeof(resp);
  if (hci_send_req(&rq, FALSE) < 0)
    return BLE_STATUS_TIMEOUT;
  if (resp.Status) {
    return resp.Status;
  }
  Osal_MemCpy((void *) Local_Resolvable_Address, (const void *) resp.Local_Resolvable_Address, 6);
  return BLE_STATUS_SUCCESS;
}
tBleStatus hci_le_set_address_resolution_enable(uint8_t Address_Resolution_Enable)
{
  struct hci_request rq;
  uint8_t cmd_buffer[258];
  hci_le_set_address_resolution_enable_cp0 *cp0 = (hci_le_set_address_resolution_enable_cp0*)(cmd_buffer);
  tBleStatus status = 0;
  uint8_t index_input = 0;
  cp0->Address_Resolution_Enable = htob(Address_Resolution_Enable, 1);
  index_input += 1;
  Osal_MemSet(&rq, 0, sizeof(rq));
  rq.ogf = 0x08;
  rq.ocf = 0x02d;
  rq.cparam = cmd_buffer;
  rq.clen = index_input;
  rq.rparam = &status;
  rq.rlen = 1;
  if (hci_send_req(&rq, FALSE) < 0)
    return BLE_STATUS_TIMEOUT;
  if (status) {
    return status;
  }
  return BLE_STATUS_SUCCESS;
}
tBleStatus hci_le_set_resolvable_private_address_timeout(uint16_t RPA_Timeout)
{
  struct hci_request rq;
  uint8_t cmd_buffer[258];
  hci_le_set_resolvable_private_address_timeout_cp0 *cp0 = (hci_le_set_resolvable_private_address_timeout_cp0*)(cmd_buffer);
  tBleStatus status = 0;
  uint8_t index_input = 0;
  cp0->RPA_Timeout = htob(RPA_Timeout, 2);
  index_input += 2;
  Osal_MemSet(&rq, 0, sizeof(rq));
  rq.ogf = 0x08;
  rq.ocf = 0x02e;
  rq.cparam = cmd_buffer;
  rq.clen = index_input;
  rq.rparam = &status;
  rq.rlen = 1;
  if (hci_send_req(&rq, FALSE) < 0)
    return BLE_STATUS_TIMEOUT;
  if (status) {
    return status;
  }
  return BLE_STATUS_SUCCESS;
}
tBleStatus hci_le_read_maximum_data_length(uint16_t *supportedMaxTxOctets,
                                           uint16_t *supportedMaxTxTime,
                                           uint16_t *supportedMaxRxOctets,
                                           uint16_t *supportedMaxRxTime)
{
  struct hci_request rq;
  hci_le_read_maximum_data_length_rp0 resp;
  Osal_MemSet(&resp, 0, sizeof(resp));
  Osal_MemSet(&rq, 0, sizeof(rq));
  rq.ogf = 0x08;
  rq.ocf = 0x02f;
  rq.rparam = &resp;
  rq.rlen = sizeof(resp);
  if (hci_send_req(&rq, FALSE) < 0)
    return BLE_STATUS_TIMEOUT;
  if (resp.Status) {
    return resp.Status;
  }
  *supportedMaxTxOctets = btoh(resp.supportedMaxTxOctets, 2);
  *supportedMaxTxTime = btoh(resp.supportedMaxTxTime, 2);
  *supportedMaxRxOctets = btoh(resp.supportedMaxRxOctets, 2);
  *supportedMaxRxTime = btoh(resp.supportedMaxRxTime, 2);
  return BLE_STATUS_SUCCESS;
}
tBleStatus hci_le_read_phy(uint16_t Connection_Handle,
                           uint8_t *TX_PHY,
                           uint8_t *RX_PHY)
{
  struct hci_request rq;
  uint8_t cmd_buffer[258];
  hci_le_read_phy_cp0 *cp0 = (hci_le_read_phy_cp0*)(cmd_buffer);
  hci_le_read_phy_rp0 resp;
  Osal_MemSet(&resp, 0, sizeof(resp));
  uint8_t index_input = 0;
  cp0->Connection_Handle = htob(Connection_Handle, 2);
  index_input += 2;
  Osal_MemSet(&rq, 0, sizeof(rq));
  rq.ogf = 0x08;
  rq.ocf = 0x030;
  rq.cparam = cmd_buffer;
  rq.clen = index_input;
  rq.rparam = &resp;
  rq.rlen = sizeof(resp);
  if (hci_send_req(&rq, FALSE) < 0)
    return BLE_STATUS_TIMEOUT;
  if (resp.Status) {
    return resp.Status;
  }
  *TX_PHY = btoh(resp.TX_PHY, 1);
  *RX_PHY = btoh(resp.RX_PHY, 1);
  return BLE_STATUS_SUCCESS;
}
tBleStatus hci_le_set_default_phy(uint8_t ALL_PHYS,
                                  uint8_t TX_PHYS,
                                  uint8_t RX_PHYS)
{
  struct hci_request rq;
  uint8_t cmd_buffer[258];
  hci_le_set_default_phy_cp0 *cp0 = (hci_le_set_default_phy_cp0*)(cmd_buffer);
  tBleStatus status = 0;
  uint8_t index_input = 0;
  cp0->ALL_PHYS = htob(ALL_PHYS, 1);
  index_input += 1;
  cp0->TX_PHYS = htob(TX_PHYS, 1);
  index_input += 1;
  cp0->RX_PHYS = htob(RX_PHYS, 1);
  index_input += 1;
  Osal_MemSet(&rq, 0, sizeof(rq));
  rq.ogf = 0x08;
  rq.ocf = 0x031;
  rq.cparam = cmd_buffer;
  rq.clen = index_input;
  rq.rparam = &status;
  rq.rlen = 1;
  if (hci_send_req(&rq, FALSE) < 0)
    return BLE_STATUS_TIMEOUT;
  if (status) {
    return status;
  }
  return BLE_STATUS_SUCCESS;
}
tBleStatus hci_le_set_phy(uint16_t Connection_Handle,
                          uint8_t ALL_PHYS,
                          uint8_t TX_PHYS,
                          uint8_t RX_PHYS,
                          uint16_t PHY_options)
{
  struct hci_request rq;
  uint8_t cmd_buffer[258];
  hci_le_set_phy_cp0 *cp0 = (hci_le_set_phy_cp0*)(cmd_buffer);
  tBleStatus status = 0;
  uint8_t index_input = 0;
  cp0->Connection_Handle = htob(Connection_Handle, 2);
  index_input += 2;
  cp0->ALL_PHYS = htob(ALL_PHYS, 1);
  index_input += 1;
  cp0->TX_PHYS = htob(TX_PHYS, 1);
  index_input += 1;
  cp0->RX_PHYS = htob(RX_PHYS, 1);
  index_input += 1;
  cp0->PHY_options = htob(PHY_options, 2);
  index_input += 2;
  Osal_MemSet(&rq, 0, sizeof(rq));
  rq.ogf = 0x08;
  rq.ocf = 0x032;
  rq.event = 0x0F;
  rq.cparam = cmd_buffer;
  rq.clen = index_input;
  rq.rparam = &status;
  rq.rlen = 1;
  if (hci_send_req(&rq, FALSE) < 0)
    return BLE_STATUS_TIMEOUT;
  if (status) {
    return status;
  }
  return BLE_STATUS_SUCCESS;
}
tBleStatus hci_le_enhanced_receiver_test(uint8_t RX_Frequency,
                                         uint8_t PHY,
                                         uint8_t Modulation_Index)
{
  struct hci_request rq;
  uint8_t cmd_buffer[258];
  hci_le_enhanced_receiver_test_cp0 *cp0 = (hci_le_enhanced_receiver_test_cp0*)(cmd_buffer);
  tBleStatus status = 0;
  uint8_t index_input = 0;
  cp0->RX_Frequency = htob(RX_Frequency, 1);
  index_input += 1;
  cp0->PHY = htob(PHY, 1);
  index_input += 1;
  cp0->Modulation_Index = htob(Modulation_Index, 1);
  index_input += 1;
  Osal_MemSet(&rq, 0, sizeof(rq));
  rq.ogf = 0x08;
  rq.ocf = 0x033;
  rq.cparam = cmd_buffer;
  rq.clen = index_input;
  rq.rparam = &status;
  rq.rlen = 1;
  if (hci_send_req(&rq, FALSE) < 0)
    return BLE_STATUS_TIMEOUT;
  if (status) {
    return status;
  }
  return BLE_STATUS_SUCCESS;
}
tBleStatus hci_le_enhanced_transmitter_test(uint8_t TX_Frequency,
                                            uint8_t Length_Of_Test_Data,
                                            uint8_t Packet_Payload,
                                            uint8_t PHY)
{
  struct hci_request rq;
  uint8_t cmd_buffer[258];
  hci_le_enhanced_transmitter_test_cp0 *cp0 = (hci_le_enhanced_transmitter_test_cp0*)(cmd_buffer);
  tBleStatus status = 0;
  uint8_t index_input = 0;
  cp0->TX_Frequency = htob(TX_Frequency, 1);
  index_input += 1;
  cp0->Length_Of_Test_Data = htob(Length_Of_Test_Data, 1);
  index_input += 1;
  cp0->Packet_Payload = htob(Packet_Payload, 1);
  index_input += 1;
  cp0->PHY = htob(PHY, 1);
  index_input += 1;
  Osal_MemSet(&rq, 0, sizeof(rq));
  rq.ogf = 0x08;
  rq.ocf = 0x034;
  rq.cparam = cmd_buffer;
  rq.clen = index_input;
  rq.rparam = &status;
  rq.rlen = 1;
  if (hci_send_req(&rq, FALSE) < 0)
    return BLE_STATUS_TIMEOUT;
  if (status) {
    return status;
  }
  return BLE_STATUS_SUCCESS;
}
