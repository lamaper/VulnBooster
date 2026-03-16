xmlAttrPtr xsltAttrListTemplateProcess ( xsltTransformContextPtr ctxt , xmlNodePtr target , xmlAttrPtr attrs ) {
 xmlAttrPtr attr , copy , last ;
 xmlNodePtr oldInsert , text ;
 xmlNsPtr origNs = NULL , copyNs = NULL ;
 const xmlChar * value ;
 xmlChar * valueAVT ;
 if ( ( ctxt == NULL ) || ( target == NULL ) || ( attrs == NULL ) || ( target -> type != XML_ELEMENT_NODE ) ) return ( NULL ) ;
 oldInsert = ctxt -> insert ;
 ctxt -> insert = target ;
 if ( target -> properties ) {
 last = target -> properties ;
 while ( last -> next != NULL ) last = last -> next ;
 }
 else {
 last = NULL ;
 }
 attr = attrs ;
 do {

 goto next_attribute ;
 }

 goto next_attribute ;
 }

 if ( ( attr -> children -> type != XML_TEXT_NODE ) || ( attr -> children -> next != NULL ) ) {
 xsltTransformError ( ctxt , NULL , attr -> parent , "Internal error: The children of an attribute node of a " "literal result element are not in the expected form.\n" ) ;
 goto error ;
 }
 value = attr -> children -> content ;
 if ( value == NULL ) value = xmlDictLookup ( ctxt -> dict , BAD_CAST "" , 0 ) ;
 }
 else value = xmlDictLookup ( ctxt -> dict , BAD_CAST "" , 0 ) ;
 copy = xmlNewDocProp ( target -> doc , attr -> name , NULL ) ;
 if ( copy == NULL ) {
 if ( attr -> ns ) {
 xsltTransformError ( ctxt , NULL , attr -> parent , "Internal error: Failed to create attribute '{
%s}
%s'.\n" , attr -> ns -> href , attr -> name ) ;
 }
 else {
 xsltTransformError ( ctxt , NULL , attr -> parent , "Internal error: Failed to create attribute '%s'.\n" , attr -> name ) ;
 }
 goto error ;
 }
 copy -> parent = target ;
 if ( last == NULL ) {
 target -> properties = copy ;
 last = copy ;
 }
 else {
 last -> next = copy ;
 copy -> prev = last ;
 last = copy ;
 }
 if ( attr -> ns != origNs ) {
 origNs = attr -> ns ;
 if ( attr -> ns != NULL ) {



 }
 else copyNs = NULL ;
 }
 copy -> ns = copyNs ;
 text = xmlNewText ( NULL ) ;
 if ( text != NULL ) {
 copy -> last = copy -> children = text ;
 text -> parent = ( xmlNodePtr ) copy ;
 text -> doc = copy -> doc ;
 if ( attr -> psvi != NULL ) {
 valueAVT = xsltEvalAVT ( ctxt , attr -> psvi , attr -> parent ) ;
 if ( valueAVT == NULL ) {
 if ( attr -> ns ) {
 xsltTransformError ( ctxt , NULL , attr -> parent , "Internal error: Failed to evaluate the AVT " "of attribute '{
%s}
%s'.\n" , attr -> ns -> href , attr -> name ) ;
 }
 else {
 xsltTransformError ( ctxt , NULL , attr -> parent , "Internal error: Failed to evaluate the AVT " "of attribute '%s'.\n" , attr -> name ) ;
 }
 text -> content = xmlStrdup ( BAD_CAST "" ) ;
 goto error ;
 }
 else {
 text -> content = valueAVT ;
 }
 }
 else if ( ( ctxt -> internalized ) && ( target -> doc != NULL ) && ( target -> doc -> dict == ctxt -> dict ) && xmlDictOwns ( ctxt -> dict , value ) ) {
 text -> content = ( xmlChar * ) value ;
 }
 else {
 text -> content = xmlStrdup ( value ) ;
 }
 if ( ( copy != NULL ) && ( text != NULL ) && ( xmlIsID ( copy -> doc , copy -> parent , copy ) ) ) xmlAddID ( NULL , copy -> doc , text -> content , copy ) ;
 }
 next_attribute : attr = attr -> next ;
 }
 while ( attr != NULL ) ;
 attr = attrs ;
 do {

 xsltApplyAttributeSet ( ctxt , ctxt -> node , ( xmlNodePtr ) attr , NULL ) ;
 }

 xsltApplyAttributeSet ( ctxt , ctxt -> node , ( xmlNodePtr ) attr , NULL ) ;
 }

 }
 while ( attr != NULL ) ;
 ctxt -> insert = oldInsert ;
 return ( target -> properties ) ;
 error : ctxt -> insert = oldInsert ;
 return ( NULL ) ;
 }