int path_is_absolute(const char *path)

{

    const char *p;


     

    if (*path == '/' || *path == '\\')

        return 1;


    p = strchr(path, ':');

    if (p)

        p++;

    else

        p = path;


    return (*p == '/' || *p == '\\');


    return (*p == '/');


}
