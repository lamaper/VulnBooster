static gboolean call_list_find ( call_list * list , guint16 scallno ) {
 for ( ;
 list ;
 list = list -> next ) {
 if ( list -> scallno == scallno ) {
 return TRUE ;
 }
 }
 return FALSE ;
 }