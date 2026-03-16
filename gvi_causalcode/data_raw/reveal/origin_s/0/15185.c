static struct curl_httppost * AddHttpPost ( char * name , size_t namelength , char * value , size_t contentslength , char * buffer , size_t bufferlength , char * contenttype , long flags , struct curl_slist * contentHeader , char * showfilename , char * userp , struct curl_httppost * parent_post , struct curl_httppost * * httppost , struct curl_httppost * * last_post ) {
 struct curl_httppost * post ;
 post = calloc ( 1 , sizeof ( struct curl_httppost ) ) ;
 if ( post ) {
 post -> name = name ;
 post -> namelength = ( long ) ( name ? ( namelength ? namelength : strlen ( name ) ) : 0 ) ;
 post -> contents = value ;
 post -> contentslength = ( long ) contentslength ;
 post -> buffer = buffer ;
 post -> bufferlength = ( long ) bufferlength ;
 post -> contenttype = contenttype ;
 post -> contentheader = contentHeader ;
 post -> showfilename = showfilename ;
 post -> userp = userp , post -> flags = flags ;
 }
 else return NULL ;
 if ( parent_post ) {
 post -> more = parent_post -> more ;
 parent_post -> more = post ;
 }
 else {
 if ( * last_post ) ( * last_post ) -> next = post ;
 else ( * httppost ) = post ;
 ( * last_post ) = post ;
 }
 return post ;
 }