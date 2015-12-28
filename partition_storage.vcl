vcl 4.0;
import std;

backend default {
    .host = "198.51.100.1";
    .port = "80";
}

sub vcl_recv {
}

sub vcl_backend_response {
    if (bereq.http.host ~ "foo") {
        set beresp.storage_hint = "foo";
        set beresp.http.x-storage = "foo";
    } else if (bereq.http.host ~ "bar") {
        set beresp.storage_hint = "bar";
        set beresp.http.x-storage = "bar";
    } else {
        set beresp.storage_hint = "default";
        set beresp.http.x-storage = "default";
    }
}

sub vcl_deliver {
}
