#include <stdio.h>
#include "cjson.h"


/* main */

int main() {
    Null n = createNull();

    Integer d = createInteger(5);

    Float f = createFloat(3.14);

    String s = createString("my string");

    List l = createList();
    listAdd(&l, &n);
    listAdd(&l, &d);

    Object o = createObject();
    objectAdd(&o, "key_null", &n);
    objectAdd(&o, "key_int", &d);
    objectAdd(&o, "key_list", &l);
    objectAdd(&o, "flt", &f);
    objectAdd(&o, "str", &s);

    char b[4096];
    toString(&o, b);
    printf("%s\n", b);

    return 0;
}
