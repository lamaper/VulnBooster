gboolean bluetooth_gatt_has_no_parameter ( guint8 opcode ) {
 return is_readable_request ( opcode ) || opcode == ATT_OPCODE_WRITE_RESPONSE || opcode == ATT_OPCODE_HANDLE_VALUE_CONFIRMATION ;
 }