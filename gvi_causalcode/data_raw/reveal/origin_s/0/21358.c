INDIC_TABLE_ELEMENT_TYPE hb_indic_get_categories ( hb_codepoint_t u ) {
 switch ( u >> 12 ) {
 case 0x0u : if ( hb_in_range ( u , 0x0028u , 0x003Fu ) ) return indic_table [ u - 0x0028u + indic_offset_0x0028u ] ;
 if ( hb_in_range ( u , 0x00D0u , 0x00D7u ) ) return indic_table [ u - 0x00D0u + indic_offset_0x00d0u ] ;
 if ( hb_in_range ( u , 0x0900u , 0x0DF7u ) ) return indic_table [ u - 0x0900u + indic_offset_0x0900u ] ;
 if ( unlikely ( u == 0x00A0u ) ) return _ ( CP , x ) ;
 break ;
 case 0x1u : if ( hb_in_range ( u , 0x1000u , 0x109Fu ) ) return indic_table [ u - 0x1000u + indic_offset_0x1000u ] ;
 if ( hb_in_range ( u , 0x1700u , 0x17EFu ) ) return indic_table [ u - 0x1700u + indic_offset_0x1700u ] ;
 if ( hb_in_range ( u , 0x1900u , 0x1A9Fu ) ) return indic_table [ u - 0x1900u + indic_offset_0x1900u ] ;
 if ( hb_in_range ( u , 0x1B00u , 0x1C4Fu ) ) return indic_table [ u - 0x1B00u + indic_offset_0x1b00u ] ;
 if ( hb_in_range ( u , 0x1CD0u , 0x1CF7u ) ) return indic_table [ u - 0x1CD0u + indic_offset_0x1cd0u ] ;
 break ;
 case 0x2u : if ( hb_in_range ( u , 0x2008u , 0x2017u ) ) return indic_table [ u - 0x2008u + indic_offset_0x2008u ] ;
 if ( unlikely ( u == 0x25CCu ) ) return _ ( CP , x ) ;
 break ;
 case 0xAu : if ( hb_in_range ( u , 0xA800u , 0xAAF7u ) ) return indic_table [ u - 0xA800u + indic_offset_0xa800u ] ;
 if ( hb_in_range ( u , 0xABC0u , 0xABFFu ) ) return indic_table [ u - 0xABC0u + indic_offset_0xabc0u ] ;
 break ;
 case 0x10u : if ( hb_in_range ( u , 0x10A00u , 0x10A47u ) ) return indic_table [ u - 0x10A00u + indic_offset_0x10a00u ] ;
 break ;
 case 0x11u : if ( hb_in_range ( u , 0x11000u , 0x110BFu ) ) return indic_table [ u - 0x11000u + indic_offset_0x11000u ] ;
 if ( hb_in_range ( u , 0x11100u , 0x11237u ) ) return indic_table [ u - 0x11100u + indic_offset_0x11100u ] ;
 if ( hb_in_range ( u , 0x112B0u , 0x11377u ) ) return indic_table [ u - 0x112B0u + indic_offset_0x112b0u ] ;
 if ( hb_in_range ( u , 0x11480u , 0x114DFu ) ) return indic_table [ u - 0x11480u + indic_offset_0x11480u ] ;
 if ( hb_in_range ( u , 0x11580u , 0x115C7u ) ) return indic_table [ u - 0x11580u + indic_offset_0x11580u ] ;
 if ( hb_in_range ( u , 0x11600u , 0x116CFu ) ) return indic_table [ u - 0x11600u + indic_offset_0x11600u ] ;
 break ;
 default : break ;
 }
 return _ ( x , x ) ;
 }