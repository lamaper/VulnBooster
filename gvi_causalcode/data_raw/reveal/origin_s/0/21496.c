static gboolean is_long_attribute_value ( bluetooth_uuid_t uuid ) {
 switch ( uuid . bt_uuid ) {
 case 0x2901 : case 0x2A00 : case 0x2A24 : case 0x2A25 : case 0x2A26 : case 0x2A27 : case 0x2A28 : case 0x2A29 : case 0x2A4B : case 0x2A87 : case 0x2A90 : case 0x2AA4 : case 0x2AB5 : case 0x2AB6 : case 0x2AB7 : case 0x2AB9 : case 0x2ABE : return TRUE ;
 }
 return FALSE ;
 }