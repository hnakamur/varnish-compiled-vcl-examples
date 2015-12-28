vcl 4.0;
import std;

backend foo {
    .host = "198.51.100.1";
    .port = "80";
}
backend bar {
    .host = "198.51.100.2";
    .port = "80";
}

sub vcl_recv {
    if (req.http.host ~ "foo.com") {
        set req.backend_hint = foo;
    } elsif (req.http.host ~ "bar.com") {
        set req.backend_hint = bar;
    }
}

sub vcl_backend_response {
}

sub vcl_deliver {
}
