static int printHelp ( int argc , char * argv [ ] ) {
 fprintf ( stderr , "Usage: %s [-options] [file_name]\n" "\n" "Read the files specified and\n" "create a binary file [package-name]_[bundle-name]." DATA_TYPE " with the StringPrep profile data\n" "\n" , argv [ 0 ] ) ;
 fprintf ( stderr , "Options:\n" "\t-h or -? or --help print this usage text\n" "\t-v or --verbose verbose output\n" "\t-c or --copyright include a copyright notice\n" ) ;
 fprintf ( stderr , "\t-d or --destdir destination directory, followed by the path\n" "\t-s or --sourcedir source directory of ICU data, followed by the path\n" "\t-b or --bundle-name generate the ouput data file with the name specified\n" "\t-i or --icudatadir directory for locating any needed intermediate data files,\n" "\t followed by path, defaults to %s\n" , u_getDataDirectory ( ) ) ;
 fprintf ( stderr , "\t-n or --normalize turn on the option for normalization and include mappings\n" "\t from NormalizationCorrections.txt from the given path,\n" "\t e.g: /test/icu/source/data/unidata\n" ) ;
 fprintf ( stderr , "\t-m or --norm-correction use NormalizationCorrections.txt from the given path\n" "\t when the input file contains a normalization directive.\n" "\t unlike -n/--normalize, this option does not force the\n" "\t normalization.\n" ) ;
 fprintf ( stderr , "\t-k or --check-bidi turn on the option for checking for BiDi in the profile\n" "\t-u or --unicode version of Unicode to be used with this profile followed by the version\n" ) ;
 return argc < 0 ? U_ILLEGAL_ARGUMENT_ERROR : U_ZERO_ERROR ;
 }