sprintf_len(char *string, const char *format, ...)


sprintf_len(va_alist) va_dcl


{

	va_list args;


	va_start(args, format);


	char *string;

	char *format;

	va_start(args);

	string = va_arg(args, char *);

	format = va_arg(args, char *);


	vsprintf(string, format, args);

	return strlen(string);

}
