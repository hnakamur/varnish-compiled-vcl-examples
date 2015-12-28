varnish-compiled-vcl-examples
=============================

Example vcl files and compiled C files.

Compilation was done with the command like:

```
varnishd -d -f virtualhost_backend.vcl -C > virtualhost_backend.c 2>&1
```

## Example vcls

* virtualhost_backend.vcl
    * Copied from https://www.varnish-cache.org/docs/trunk/users-guide/vcl-backends.html#backends-and-virtual-hosts-in-varnish
* partition_storage.vcl
    * Copied from http://info.varnish-software.com/blog/partitioning-your-varnish-cache
