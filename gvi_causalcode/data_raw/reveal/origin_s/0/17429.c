size_t Curl_FormReader ( char * buffer , size_t size , size_t nitems , FILE * mydata ) {
 struct Form * form ;
 size_t wantedsize ;
 size_t gotsize = 0 ;
 form = ( struct Form * ) mydata ;
 wantedsize = size * nitems ;
 if ( ! form -> data ) return 0 ;
 if ( ( form -> data -> type == FORM_FILE ) || ( form -> data -> type == FORM_CALLBACK ) ) {
 gotsize = readfromfile ( form , buffer , wantedsize ) ;
 if ( gotsize ) return gotsize ;
 }
 do {
 if ( ( form -> data -> length - form -> sent ) > wantedsize - gotsize ) {
 memcpy ( buffer + gotsize , form -> data -> line + form -> sent , wantedsize - gotsize ) ;
 form -> sent += wantedsize - gotsize ;
 return wantedsize ;
 }
 memcpy ( buffer + gotsize , form -> data -> line + form -> sent , ( form -> data -> length - form -> sent ) ) ;
 gotsize += form -> data -> length - form -> sent ;
 form -> sent = 0 ;
 form -> data = form -> data -> next ;
 }
 while ( form -> data && ( form -> data -> type < FORM_CALLBACK ) ) ;
 return gotsize ;
 }