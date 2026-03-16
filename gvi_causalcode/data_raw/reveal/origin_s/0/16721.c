int Curl_FormInit ( struct Form * form , struct FormData * formdata ) {
 if ( ! formdata ) return 1 ;
 form -> data = formdata ;
 form -> sent = 0 ;
 form -> fp = NULL ;
 form -> fread_func = ZERO_NULL ;
 return 0 ;
 }