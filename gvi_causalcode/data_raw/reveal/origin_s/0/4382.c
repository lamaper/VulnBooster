static gboolean is_writeable_request ( guint8 opcode ) {
 return ( opcode == ATT_OPCODE_WRITE_REQUEST || opcode == ATT_OPCODE_WRITE_PREPARE_REQUEST ) ;
 }