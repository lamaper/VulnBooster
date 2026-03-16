static FormInfo * AddFormInfo ( char * value , char * contenttype , FormInfo * parent_form_info ) {
 FormInfo * form_info ;
 form_info = calloc ( 1 , sizeof ( struct FormInfo ) ) ;
 if ( form_info ) {
 if ( value ) form_info -> value = value ;
 if ( contenttype ) form_info -> contenttype = contenttype ;
 form_info -> flags = HTTPPOST_FILENAME ;
 }
 else return NULL ;
 if ( parent_form_info ) {
 form_info -> more = parent_form_info -> more ;
 parent_form_info -> more = form_info ;
 }
 return form_info ;
 }