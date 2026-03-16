static gboolean is_writeable_response ( guint8 opcode ) {
 return ( opcode == ATT_OPCODE_WRITE_RESPONSE || opcode == ATT_OPCODE_WRITE_PREPARE_RESPONSE ) ;
 }