static void k12_dump_src_setting ( gpointer k _U_ , gpointer v , gpointer p ) {
 k12_src_desc_t * src_desc = ( k12_src_desc_t * ) v ;
 wtap_dumper * wdh = ( wtap_dumper * ) p ;
 guint32 len ;
 guint offset ;
 guint i ;
 int errxxx ;
 union {
 guint8 buffer [ 8192 ] ;
 struct {
 guint32 len ;
 guint32 type ;
 guint32 unk32_1 ;
 guint32 input ;
 guint16 unk32_2 ;
 guint16 color ;
 guint32 unk32_3 ;
 guint32 unk32_4 ;
 guint16 unk16_1 ;
 guint16 hwpart_len ;
 guint16 name_len ;
 guint16 stack_len ;
 struct {
 guint32 type ;
 union {
 struct {
 guint32 unk32 ;
 guint8 mask [ 32 ] ;
 }
 ds0mask ;
 struct {
 guint8 unk_data [ 16 ] ;
 guint16 vp ;
 guint16 vc ;
 }
 atm ;
 guint32 unk ;
 }
 desc ;
 }
 extra ;
 }
 record ;
 }
 obj ;
 obj . record . type = g_htonl ( K12_REC_SRCDSC ) ;
 obj . record . unk32_1 = g_htonl ( 0x00000001 ) ;
 obj . record . input = g_htonl ( src_desc -> input ) ;
 obj . record . unk32_2 = g_htons ( 0x0000 ) ;
 obj . record . color = g_htons ( 0x060f ) ;
 obj . record . unk32_3 = g_htonl ( 0x00000003 ) ;
 switch ( src_desc -> input_type ) {
 case K12_PORT_ATMPVC : obj . record . unk32_4 = g_htonl ( 0x01001400 ) ;
 break ;
 default : obj . record . unk32_4 = g_htonl ( 0x01000100 ) ;
 }
 obj . record . unk16_1 = g_htons ( 0x0000 ) ;
 obj . record . name_len = ( guint16 ) strlen ( src_desc -> input_name ) + 1 ;
 obj . record . stack_len = ( guint16 ) strlen ( src_desc -> stack_file ) + 1 ;
 obj . record . extra . type = g_htonl ( src_desc -> input_type ) ;
 switch ( src_desc -> input_type ) {
 case K12_PORT_ATMPVC : obj . record . hwpart_len = g_htons ( 0x18 ) ;
 obj . record . extra . desc . atm . vp = g_htons ( src_desc -> input_info . atm . vp ) ;
 obj . record . extra . desc . atm . vc = g_htons ( src_desc -> input_info . atm . vc ) ;
 offset = 0x3c ;
 break ;
 case K12_PORT_DS0S : obj . record . hwpart_len = g_htons ( 0x18 ) ;
 for ( i = 0 ;
 i < 32 ;
 i ++ ) {
 obj . record . extra . desc . ds0mask . mask [ i ] = ( src_desc -> input_info . ds0mask & ( 1 << i ) ) ? 0xff : 0x00 ;
 }
 offset = 0x3c ;
 break ;
 default : obj . record . hwpart_len = g_htons ( 0x08 ) ;
 offset = 0x2c ;
 break ;
 }
 memcpy ( obj . buffer + offset , src_desc -> input_name , obj . record . name_len ) ;
 memcpy ( obj . buffer + offset + obj . record . name_len , src_desc -> stack_file , obj . record . stack_len ) ;
 len = offset + obj . record . name_len + obj . record . stack_len ;
 len += ( len % 4 ) ? 4 - ( len % 4 ) : 0 ;
 obj . record . len = g_htonl ( len ) ;
 obj . record . name_len = g_htons ( obj . record . name_len ) ;
 obj . record . stack_len = g_htons ( obj . record . stack_len ) ;
 k12_dump_record ( wdh , len , obj . buffer , & errxxx ) ;
 }