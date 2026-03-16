char * get_relid_attribute_name ( Oid relid , AttrNumber attnum ) {
 char * attname ;
 attname = get_attname ( relid , attnum ) ;
 if ( attname == NULL ) elog ( ERROR , "cache lookup failed for attribute %d of relation %u" , attnum , relid ) ;
 return attname ;
 }