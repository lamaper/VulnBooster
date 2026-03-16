static gsize label_fill_descr ( char * label_str , gsize pos , const header_field_info * hfinfo , const char * text , const char * descr ) {
 gsize name_pos ;
 name_pos = pos = label_concat ( label_str , pos , hfinfo -> name ) ;
 pos = label_concat ( label_str , pos , ": " ) ;
 pos = label_concat ( label_str , pos , text ? text : "(null)" ) ;
 pos = label_concat ( label_str , pos , " (" ) ;
 pos = label_concat ( label_str , pos , descr ? descr : "(null)" ) ;
 pos = label_concat ( label_str , pos , ")" ) ;
 if ( pos >= ITEM_LABEL_LENGTH ) {
 label_mark_truncated ( label_str , name_pos ) ;
 }
 return pos ;
 }