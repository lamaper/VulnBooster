static CURLFORMcode FormAdd ( struct curl_httppost * * httppost , struct curl_httppost * * last_post , va_list params ) {
 FormInfo * first_form , * current_form , * form = NULL ;
 CURLFORMcode return_value = CURL_FORMADD_OK ;
 const char * prevtype = NULL ;
 struct curl_httppost * post = NULL ;
 CURLformoption option ;
 struct curl_forms * forms = NULL ;
 char * array_value = NULL ;
 bool array_state = FALSE ;
 first_form = calloc ( 1 , sizeof ( struct FormInfo ) ) ;
 if ( ! first_form ) return CURL_FORMADD_MEMORY ;
 current_form = first_form ;
 while ( return_value == CURL_FORMADD_OK ) {
 if ( array_state && forms ) {
 option = forms -> option ;
 array_value = ( char * ) forms -> value ;
 forms ++ ;
 if ( CURLFORM_END == option ) {
 array_state = FALSE ;
 continue ;
 }
 }
 else {
 option = va_arg ( params , CURLformoption ) ;
 if ( CURLFORM_END == option ) break ;
 }
 switch ( option ) {
 case CURLFORM_ARRAY : if ( array_state ) return_value = CURL_FORMADD_ILLEGAL_ARRAY ;
 else {
 forms = va_arg ( params , struct curl_forms * ) ;
 if ( forms ) array_state = TRUE ;
 else return_value = CURL_FORMADD_NULL ;
 }
 break ;
 case CURLFORM_PTRNAME : # ifdef CURL_DOES_CONVERSIONS # else current_form -> flags |= HTTPPOST_PTRNAME ;

 else {
 char * name = array_state ? array_value : va_arg ( params , char * ) ;
 if ( name ) current_form -> name = name ;
 else return_value = CURL_FORMADD_NULL ;
 }
 break ;
 case CURLFORM_NAMELENGTH : if ( current_form -> namelength ) return_value = CURL_FORMADD_OPTION_TWICE ;
 else current_form -> namelength = array_state ? ( size_t ) array_value : ( size_t ) va_arg ( params , long ) ;
 break ;
 case CURLFORM_PTRCONTENTS : current_form -> flags |= HTTPPOST_PTRCONTENTS ;
 case CURLFORM_COPYCONTENTS : if ( current_form -> value ) return_value = CURL_FORMADD_OPTION_TWICE ;
 else {
 char * value = array_state ? array_value : va_arg ( params , char * ) ;
 if ( value ) current_form -> value = value ;
 else return_value = CURL_FORMADD_NULL ;
 }
 break ;
 case CURLFORM_CONTENTSLENGTH : if ( current_form -> contentslength ) return_value = CURL_FORMADD_OPTION_TWICE ;
 else current_form -> contentslength = array_state ? ( size_t ) array_value : ( size_t ) va_arg ( params , long ) ;
 break ;
 case CURLFORM_FILECONTENT : if ( current_form -> flags & ( HTTPPOST_PTRCONTENTS | HTTPPOST_READFILE ) ) return_value = CURL_FORMADD_OPTION_TWICE ;
 else {
 const char * filename = array_state ? array_value : va_arg ( params , char * ) ;
 if ( filename ) {
 current_form -> value = strdup ( filename ) ;
 if ( ! current_form -> value ) return_value = CURL_FORMADD_MEMORY ;
 else {
 current_form -> flags |= HTTPPOST_READFILE ;
 current_form -> value_alloc = TRUE ;
 }
 }
 else return_value = CURL_FORMADD_NULL ;
 }
 break ;
 case CURLFORM_FILE : {
 const char * filename = array_state ? array_value : va_arg ( params , char * ) ;
 if ( current_form -> value ) {
 if ( current_form -> flags & HTTPPOST_FILENAME ) {
 if ( filename ) {
 char * fname = strdup ( filename ) ;
 if ( ! fname ) return_value = CURL_FORMADD_MEMORY ;
 else {
 form = AddFormInfo ( fname , NULL , current_form ) ;
 if ( ! form ) {
 Curl_safefree ( fname ) ;
 return_value = CURL_FORMADD_MEMORY ;
 }
 else {
 form -> value_alloc = TRUE ;
 current_form = form ;
 form = NULL ;
 }
 }
 }
 else return_value = CURL_FORMADD_NULL ;
 }
 else return_value = CURL_FORMADD_OPTION_TWICE ;
 }
 else {
 if ( filename ) {
 current_form -> value = strdup ( filename ) ;
 if ( ! current_form -> value ) return_value = CURL_FORMADD_MEMORY ;
 else {
 current_form -> flags |= HTTPPOST_FILENAME ;
 current_form -> value_alloc = TRUE ;
 }
 }
 else return_value = CURL_FORMADD_NULL ;
 }
 break ;
 }
 case CURLFORM_BUFFERPTR : current_form -> flags |= HTTPPOST_PTRBUFFER | HTTPPOST_BUFFER ;
 if ( current_form -> buffer ) return_value = CURL_FORMADD_OPTION_TWICE ;
 else {
 char * buffer = array_state ? array_value : va_arg ( params , char * ) ;
 if ( buffer ) {
 current_form -> buffer = buffer ;
 current_form -> value = buffer ;
 }
 else return_value = CURL_FORMADD_NULL ;
 }
 break ;
 case CURLFORM_BUFFERLENGTH : if ( current_form -> bufferlength ) return_value = CURL_FORMADD_OPTION_TWICE ;
 else current_form -> bufferlength = array_state ? ( size_t ) array_value : ( size_t ) va_arg ( params , long ) ;
 break ;
 case CURLFORM_STREAM : current_form -> flags |= HTTPPOST_CALLBACK ;
 if ( current_form -> userp ) return_value = CURL_FORMADD_OPTION_TWICE ;
 else {
 char * userp = array_state ? array_value : va_arg ( params , char * ) ;
 if ( userp ) {
 current_form -> userp = userp ;
 current_form -> value = userp ;
 }
 else return_value = CURL_FORMADD_NULL ;
 }
 break ;
 case CURLFORM_CONTENTTYPE : {
 const char * contenttype = array_state ? array_value : va_arg ( params , char * ) ;
 if ( current_form -> contenttype ) {
 if ( current_form -> flags & HTTPPOST_FILENAME ) {
 if ( contenttype ) {
 char * type = strdup ( contenttype ) ;
 if ( ! type ) return_value = CURL_FORMADD_MEMORY ;
 else {
 form = AddFormInfo ( NULL , type , current_form ) ;
 if ( ! form ) {
 Curl_safefree ( type ) ;
 return_value = CURL_FORMADD_MEMORY ;
 }
 else {
 form -> contenttype_alloc = TRUE ;
 current_form = form ;
 form = NULL ;
 }
 }
 }
 else return_value = CURL_FORMADD_NULL ;
 }
 else return_value = CURL_FORMADD_OPTION_TWICE ;
 }
 else {
 if ( contenttype ) {
 current_form -> contenttype = strdup ( contenttype ) ;
 if ( ! current_form -> contenttype ) return_value = CURL_FORMADD_MEMORY ;
 else current_form -> contenttype_alloc = TRUE ;
 }
 else return_value = CURL_FORMADD_NULL ;
 }
 break ;
 }
 case CURLFORM_CONTENTHEADER : {
 struct curl_slist * list = array_state ? ( struct curl_slist * ) array_value : va_arg ( params , struct curl_slist * ) ;
 if ( current_form -> contentheader ) return_value = CURL_FORMADD_OPTION_TWICE ;
 else current_form -> contentheader = list ;
 break ;
 }
 case CURLFORM_FILENAME : case CURLFORM_BUFFER : {
 const char * filename = array_state ? array_value : va_arg ( params , char * ) ;
 if ( current_form -> showfilename ) return_value = CURL_FORMADD_OPTION_TWICE ;
 else {
 current_form -> showfilename = strdup ( filename ) ;
 if ( ! current_form -> showfilename ) return_value = CURL_FORMADD_MEMORY ;
 else current_form -> showfilename_alloc = TRUE ;
 }
 break ;
 }
 default : return_value = CURL_FORMADD_UNKNOWN_OPTION ;
 break ;
 }
 }
 if ( CURL_FORMADD_OK != return_value ) {
 FormInfo * ptr ;
 for ( ptr = first_form ;
 ptr != NULL ;
 ptr = ptr -> more ) {
 if ( ptr -> name_alloc ) {
 Curl_safefree ( ptr -> name ) ;
 ptr -> name_alloc = FALSE ;
 }
 if ( ptr -> value_alloc ) {
 Curl_safefree ( ptr -> value ) ;
 ptr -> value_alloc = FALSE ;
 }
 if ( ptr -> contenttype_alloc ) {
 Curl_safefree ( ptr -> contenttype ) ;
 ptr -> contenttype_alloc = FALSE ;
 }
 if ( ptr -> showfilename_alloc ) {
 Curl_safefree ( ptr -> showfilename ) ;
 ptr -> showfilename_alloc = FALSE ;
 }
 }
 }
 if ( CURL_FORMADD_OK == return_value ) {
 post = NULL ;
 for ( form = first_form ;
 form != NULL ;
 form = form -> more ) {
 if ( ( ( ! form -> name || ! form -> value ) && ! post ) || ( ( form -> contentslength ) && ( form -> flags & HTTPPOST_FILENAME ) ) || ( ( form -> flags & HTTPPOST_FILENAME ) && ( form -> flags & HTTPPOST_PTRCONTENTS ) ) || ( ( ! form -> buffer ) && ( form -> flags & HTTPPOST_BUFFER ) && ( form -> flags & HTTPPOST_PTRBUFFER ) ) || ( ( form -> flags & HTTPPOST_READFILE ) && ( form -> flags & HTTPPOST_PTRCONTENTS ) ) ) {
 return_value = CURL_FORMADD_INCOMPLETE ;
 break ;
 }
 else {
 if ( ( ( form -> flags & HTTPPOST_FILENAME ) || ( form -> flags & HTTPPOST_BUFFER ) ) && ! form -> contenttype ) {
 char * f = form -> flags & HTTPPOST_BUFFER ? form -> showfilename : form -> value ;
 form -> contenttype = strdup ( ContentTypeForFilename ( f , prevtype ) ) ;
 if ( ! form -> contenttype ) {
 return_value = CURL_FORMADD_MEMORY ;
 break ;
 }
 form -> contenttype_alloc = TRUE ;
 }
 if ( ! ( form -> flags & HTTPPOST_PTRNAME ) && ( form == first_form ) ) {
 if ( form -> name ) form -> name = memdup ( form -> name , form -> namelength ) ;
 if ( ! form -> name ) {
 return_value = CURL_FORMADD_MEMORY ;
 break ;
 }
 form -> name_alloc = TRUE ;
 }
 if ( ! ( form -> flags & ( HTTPPOST_FILENAME | HTTPPOST_READFILE | HTTPPOST_PTRCONTENTS | HTTPPOST_PTRBUFFER | HTTPPOST_CALLBACK ) ) && form -> value ) {
 form -> value = memdup ( form -> value , form -> contentslength ) ;
 if ( ! form -> value ) {
 return_value = CURL_FORMADD_MEMORY ;
 break ;
 }
 form -> value_alloc = TRUE ;
 }
 post = AddHttpPost ( form -> name , form -> namelength , form -> value , form -> contentslength , form -> buffer , form -> bufferlength , form -> contenttype , form -> flags , form -> contentheader , form -> showfilename , form -> userp , post , httppost , last_post ) ;
 if ( ! post ) {
 return_value = CURL_FORMADD_MEMORY ;
 break ;
 }
 if ( form -> contenttype ) prevtype = form -> contenttype ;
 }
 }
 if ( CURL_FORMADD_OK != return_value ) {
 FormInfo * ptr ;
 for ( ptr = form ;
 ptr != NULL ;
 ptr = ptr -> more ) {
 if ( ptr -> name_alloc ) {
 Curl_safefree ( ptr -> name ) ;
 ptr -> name_alloc = FALSE ;
 }
 if ( ptr -> value_alloc ) {
 Curl_safefree ( ptr -> value ) ;
 ptr -> value_alloc = FALSE ;
 }
 if ( ptr -> contenttype_alloc ) {
 Curl_safefree ( ptr -> contenttype ) ;
 ptr -> contenttype_alloc = FALSE ;
 }
 if ( ptr -> showfilename_alloc ) {
 Curl_safefree ( ptr -> showfilename ) ;
 ptr -> showfilename_alloc = FALSE ;
 }
 }
 }
 }
 while ( first_form ) {
 FormInfo * ptr = first_form -> more ;
 Curl_safefree ( first_form ) ;
 first_form = ptr ;
 }
 return return_value ;
 }