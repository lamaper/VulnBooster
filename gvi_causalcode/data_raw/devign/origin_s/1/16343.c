static void vnc_client_cache_auth(VncState *client)

{

    if (!client->info) {

        return;

    }


    if (client->tls.session &&

        client->tls.dname) {

        client->info->has_x509_dname = true;

        client->info->x509_dname = g_strdup(client->tls.dname);

    }



    if (client->sasl.conn &&

        client->sasl.username) {

        client->info->has_sasl_username = true;

        client->info->sasl_username = g_strdup(client->sasl.username);

    }


}
