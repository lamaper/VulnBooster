static void ultag_close ( ULanguageTag * langtag ) {
 if ( langtag == NULL ) {
 return ;
 }
 uprv_free ( langtag -> buf ) ;
 if ( langtag -> variants ) {
 VariantListEntry * curVar = langtag -> variants ;
 while ( curVar ) {
 VariantListEntry * nextVar = curVar -> next ;
 uprv_free ( curVar ) ;
 curVar = nextVar ;
 }
 }
 if ( langtag -> extensions ) {
 ExtensionListEntry * curExt = langtag -> extensions ;
 while ( curExt ) {
 ExtensionListEntry * nextExt = curExt -> next ;
 uprv_free ( curExt ) ;
 curExt = nextExt ;
 }
 }
 uprv_free ( langtag ) ;
 }