#define STRING_MAX_LENGTH 4096

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef enum { NULL_, BOOLEAN, INTEGER, FLOAT, STRING, LIST, OBJECT } JsonType;


/* General */

int toString(void* z, char b[]);


/* Null */

typedef struct {
    JsonType type;
} Null;

Null createNull() {
    Null z;
    z.type = NULL_;
    return z;
}

int nullToString(Null* z, char b[]) {
    strcpy(b, "null");
    return 4;
}


/* Boolean */

typedef struct {
    JsonType type;
	int value;
} Boolean;

Boolean createBoolean(int value) {
    Boolean z;
    z.type = BOOLEAN;
	z.value = value;
    return z;
}

int booleanToString(Boolean* z, char b[]) {
	if (z->value) {
		strcpy(b, "true");
		return 4;
	}
	else {
		strcpy(b, "false");
		return 5;
	}
}


/* Integer */

typedef struct {
    JsonType type;
    int value;
} Integer;

Integer createInteger(int value) {
    Integer z;
    z.type = INTEGER;
    z.value = value;
    return z;
}

int integerToString(Integer* z, char b[]) {
    char t[32];
    snprintf(t, 32, "%d", z->value);
    strcpy(b, t);
    return strlen(t);
}


/* Float */

typedef struct {
    JsonType type;
    double value;
} Float;

Float createFloat(double value) {
    Float z;
    z.type = FLOAT;
    z.value = value;
    return z;
}

int floatToString(Float* z, char b[]) {
    char t[32];
    snprintf(t, 32, "%lf", z->value);
    strcpy(b, t);
    return strlen(t);
}


/* String */

typedef struct {
    JsonType type;
    char value[STRING_MAX_LENGTH];
} String;

String createString(const char* value) {
    String z;
    z.type = STRING;
    strcpy(z.value, value);
    return z;
}

int stringToString(String* z, char b[]) {
    int p = 0;
    b[p++] = '"';
    strcpy(b + p, z->value);
    p += strlen(z->value);
    b[p++] = '"';
    b[p] = '\0';
    return p;
}


/* List */

typedef struct {
    JsonType type;
    int length;
    void** items;
} List;

List createList() {
    List z;
    z.type = LIST;
    z.length = 0;
    z.items = NULL;
    return z;
}

void listAdd(List* list, void* z) {
    list->length++;
    list->items = realloc(list->items, list->length * sizeof(void*));
    list->items[list->length - 1] = z;
}

int listToString(List* z, char b[]) {
    int p = 0;
    b[p++] = '[';
    int i;
    for (i = 0; i < z->length; i++) {
        if (i != 0) {
            b[p++] = ',';
            b[p++] = ' ';
        }
        p += toString(z->items[i], b + p);
    }
    b[p++] = ']';
    b[p] = '\0';
    return p;
}


/* Object */

typedef struct {
    JsonType type;
    int length;
    const char** keys;
    void** values;
} Object;

Object createObject() {
    Object z;
    z.type = OBJECT;
    z.length = 0;
    z.keys = NULL;
    z.values = NULL;
    return z;
}

void objectAdd(Object* obj, const char* key, void* z) {
    obj->length++;
    obj->keys = realloc(obj->keys, obj->length * sizeof(void*));
    obj->values = realloc(obj->values, obj->length * sizeof(void*));
    obj->keys[obj->length - 1] = key;
    obj->values[obj->length - 1] = z;
}

void* objectGet(Object* obj, const char* key) {
    void* z = NULL;
    int i;
    for (i = 0; i < obj->length; i++) {
        if (strcmp(obj->keys[i], key) == 0) {
            z = obj->values[i];
            break;
        }
    }
    return z;
}

int objectToString(Object* z, char b[]) {
    int p = 0;
    b[p++] = '{';
    int i;
    for (i = 0; i < z->length; i++) {
        if (i != 0) {
            b[p++] = ',';
            b[p++] = ' ';
        }
        b[p++] = '"';
        strcpy(b + p, z->keys[i]);
        p += strlen(z->keys[i]);
        b[p++] = '"';
        b[p++] = ':';
        b[p++] = ' ';
        p += toString(z->values[i], b + p);
    }
    b[p++] = '}';
    b[p] = '\0';
    return p;
}


/* General */

int toString(void* z, char b[]) {
    switch (*(int*)z) {
        case NULL_:
            return nullToString(z, b);
		case BOOLEAN:
			return booleanToString(z, b);
        case INTEGER:
            return integerToString(z, b);
        case FLOAT:
            return floatToString(z, b);
        case STRING:
            return stringToString(z, b);
        case LIST:
            return listToString(z, b);
        case OBJECT:
            return objectToString(z, b);
    }
}
