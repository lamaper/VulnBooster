struct im_connection * purple_ic_by_pa ( PurpleAccount * pa ) {
 GSList * i ;
 struct purple_data * pd ;
 for ( i = purple_connections ;
 i ;
 i = i -> next ) {
 pd = ( ( struct im_connection * ) i -> data ) -> proto_data ;
 if ( pd -> account == pa ) {
 return i -> data ;
 }
 }
 return NULL ;
 }