static gint pad_according_to_type ( gint offset , gint field_starting_offset , gint max_offset , guint8 type ) {
 switch ( type ) {
 case ARG_BYTE : break ;
 case ARG_DOUBLE : case ARG_UINT64 : case ARG_INT64 : case ARG_STRUCT : case ARG_DICT_ENTRY : offset = round_to_8byte ( offset , field_starting_offset ) ;
 break ;
 case ARG_SIGNATURE : break ;
 case ARG_HANDLE : break ;
 case ARG_INT32 : case ARG_UINT32 : case ARG_BOOLEAN : offset = round_to_4byte ( offset , field_starting_offset ) ;
 break ;
 case ARG_INT16 : case ARG_UINT16 : offset = round_to_2byte ( offset , field_starting_offset ) ;
 break ;
 case ARG_STRING : break ;
 case ARG_VARIANT : break ;
 case ARG_OBJ_PATH : break ;
 default : break ;
 }
 if ( offset > max_offset ) {
 offset = max_offset ;
 }
 return offset ;
 }