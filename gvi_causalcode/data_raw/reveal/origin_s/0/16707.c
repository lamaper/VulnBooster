static void get_name_from_fullpropspec ( struct CFullPropSpec * v , char * out , int bufsize ) {
 struct GuidPropertySet * pset = GuidPropertySet_find_guid ( & v -> guid ) ;
 const char * id_str , * guid_str ;
 char * dest = out ;
 id_str = pset ? try_val_to_str ( v -> u . propid , pset -> id_map ) : NULL ;
 if ( id_str ) {
 g_snprintf ( dest , bufsize , "%s" , id_str ) ;
 }
 else {
 guid_str = guids_get_guid_name ( & v -> guid ) ;
 if ( guid_str ) {
 g_snprintf ( dest , bufsize , "\"%s\"" , guid_str ) ;
 }
 else {
 guid_str = guid_to_str ( wmem_packet_scope ( ) , & v -> guid ) ;
 g_snprintf ( dest , bufsize , "{
%s}
" , guid_str ) ;
 }
 if ( v -> kind == PRSPEC_LPWSTR ) {
 g_snprintf ( dest , bufsize , "%s \"%s\"" , guid_str , v -> u . name ) ;
 }
 else if ( v -> kind == PRSPEC_PROPID ) {
 g_snprintf ( dest , bufsize , "%s 0x%08x" , guid_str , v -> u . propid ) ;
 }
 else {
 g_snprintf ( dest , bufsize , "%s <INVALID>" , dest ) ;
 }
 }
 }