MIMEField * mime_hdr_field_find ( MIMEHdrImpl * mh , const char * field_name_str , int field_name_len ) {
 HdrTokenHeapPrefix * token_info ;
 const bool is_wks = hdrtoken_is_wks ( field_name_str ) ;
 ink_assert ( field_name_len >= 0 ) ;


 token_info = hdrtoken_wks_to_prefix ( field_name_str ) ;
 if ( ( token_info -> wks_info . mask ) && ( ( mh -> m_presence_bits & token_info -> wks_info . mask ) == 0 ) ) {


 }
 int32_t slot_id = token_info -> wks_info . slotid ;
 if ( slot_id != MIME_SLOTID_NONE ) {
 uint32_t slotnum = mime_hdr_get_accelerator_slotnum ( mh , slot_id ) ;
 if ( slotnum != MIME_FIELD_SLOTNUM_UNKNOWN ) {
 MIMEField * f = _mime_hdr_field_list_search_by_slotnum ( mh , slotnum ) ;
 ink_assert ( ( f == nullptr ) || f -> is_live ( ) ) ;


 }
 else {


 }
 MIMEField * f = _mime_hdr_field_list_search_by_wks ( mh , token_info -> wks_idx ) ;
 ink_assert ( ( f == nullptr ) || f -> is_live ( ) ) ;


 }
 else {
 MIMEField * f = _mime_hdr_field_list_search_by_string ( mh , field_name_str , field_name_len ) ;
 ink_assert ( ( f == nullptr ) || f -> is_live ( ) ) ;


 }
 }