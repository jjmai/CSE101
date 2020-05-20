#include <stdio.h>
#include "Dictionary.h"

int main(int argc, char *argv[]) {
   Dictionary d = newDictionary(1);

   insert(d,"a",NULL);
    insert(d,"z",NULL);
    insert(d,"b",NULL);
    insert(d,"f",NULL);
    insert(d,"m",NULL);
    insert(d,"c",NULL);
    insert(d,"y",NULL);
    insert(d,"a",NULL);
    printDictionary(stdout,d,"post");
     delete(d,"a");
    delete(d,"y");
    printf("\n");
    printDictionary(stdout,d,"post");

}
