# cjson

**CJSON** is a library to create JSON strings in C. To use it just copy the file **cjson.h** into your project.

### Tutorials

JSON supports a fixed set of elementary datatypes: integer, float, string, boolean, null.
Not all of them are represented in C, this is why it's necessary to create their instances:

    Null n = createNull();
    Boolean b = createBoolean(0);
    Integer d = createInteger(5);
    Float f = createFloat(3.14);
    String s = createString("my string");
    
Also JSON includes complex values: lists and dictionaries, that may contain values of elementary types and complex ones as well.
Here is an example how to create instances of a list and a dictionary:

    List l = createList();
    listAdd(&l, &n); // n in a NULL
    listAdd(&l, &d); // d is an Integer
    
    Object o = createObject();
    objectAdd(&o, "key_null", &n); // n in a NULL
    objectAdd(&o, "key_int", &d); // d is an Integer
    objectAdd(&o, "key_list", &l); // l is a list
    objectAdd(&o, "flt", &f); // f is a Float
    objectAdd(&o, "str", &s); // s is a String
    objectAdd(&o, "bool_field", &b); // b is a Boolean
    
And of course there is a function called `toString` that stringifies any of created above instances:

    char buff[4096];
    toString(&o, buff);
    printf("%s\n", buff);
