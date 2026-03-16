TEST_F ( TemplateURLParserTest , InvalidInput ) {
 struct DumbFilter : TemplateURLParser : : ParameterFilter {
 bool KeepParameter ( const std : : string & key , const std : : string & value ) override {
 return true ;
 }
 }
 filter ;
 constexpr char char_data [ ] = R "( < OpenSearchDescription > < Url template = ")R:RRR?>RRR0" type = "application/x-suggestions+json" > < Param name = "name" value = "value" / > < / Url > < / OpenSearchDescription > ) ";
 TemplateURLParser : : Parse ( SearchTermsData ( ) , char_data , arraysize ( char_data ) , & filter ) ;
 }