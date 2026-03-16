static unsigned acpi_data_len(GArray *table)

{


    assert(g_array_get_element_size(table) == 1);


    return table->len;

}
