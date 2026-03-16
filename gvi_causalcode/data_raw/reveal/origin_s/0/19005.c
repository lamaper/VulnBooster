static gboolean is_readable_request ( guint8 opcode ) {
 return ( opcode == ATT_OPCODE_READ_REQUEST || opcode == ATT_OPCODE_READ_BLOB_REQUEST || opcode == ATT_OPCODE_READ_BY_TYPE_REQUEST || opcode == ATT_OPCODE_READ_MULTIPLE_REQUEST ) ;
 }