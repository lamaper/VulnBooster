static gboolean is_readable_response ( guint8 opcode ) {
 return ( opcode == ATT_OPCODE_READ_RESPONSE || opcode == ATT_OPCODE_READ_BLOB_RESPONSE || opcode == ATT_OPCODE_READ_BY_TYPE_RESPONSE || opcode == ATT_OPCODE_READ_MULTIPLE_RESPONSE ) ;
 }