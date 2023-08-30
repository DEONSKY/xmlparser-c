#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"
#include <string.h>

typedef struct Xmlproperty Xmlproperty;

struct Xmlproperty {
    char* key;
    char* value;
    Xmlproperty* next;
};

typedef struct Xmlnode Xmlnode;

struct Xmlnode {
    char* key;
    Xmlproperty* properties;
    struct Xmlnode* children;
    char* string;
    struct Xmlnode* next;
};

typedef struct xml {
    Xmlproperty* prolog;
    Xmlnode* root;
}Xml;

Xml * makexml(){
  Xml * xml = malloc(sizeof(Xml));
  if (!xml) {
    return NULL;
  }
  xml->prolog = NULL;
  xml->root = NULL;
  return xml;
}


Xmlnode * createxmlnode(char* key){
  Xmlnode * newNode = malloc(sizeof(Xmlnode));
  if (!newNode) {
    return NULL;
  }
  newNode->key = key;
  newNode->properties = NULL;
  newNode->children = NULL;
  newNode->string = NULL;
  newNode->next = NULL;
  return newNode;
}

//adds poperty and return referance for optimized add
Xmlnode * addxmlnode(char* key, Xmlnode * list){
  Xmlnode * current = NULL;
  if(list == NULL){
    list = createxmlnode(key);
    return list;
  }
  else {
    current = list; 
    while (current->next!=NULL){
      current = current->next;
    }
    current->next = createxmlnode(key);
    return list;
  }
}

Xmlproperty * createxmlproperty(char* key,char* value){
  Xmlproperty * newProperty = malloc(sizeof(Xmlproperty));
  if (!newProperty) {
    return NULL;
  }
  newProperty->key = key;
  newProperty->value = value;
  newProperty->next = NULL;
  return newProperty;
}

//adds poperty and return newly created properties referance for optimized add
Xmlproperty * addxmlproperty(char* key,char* value, Xmlproperty * list){
  Xmlproperty * current = NULL;
  if(list == NULL){
    list = createxmlproperty(key,value);
    return list;
  }
  else {
    current = list; 
    while (current->next!=NULL){
      current = current->next;
    }
    current->next = createxmlproperty(key,value);
    return current->next;
  }
}

enum categorization{Prolog,Property,ChildrenNode,RootNode,ChildrenString,NotDefined};

int readxml(FILE* file){
    int c;
    char buffer[sizeof(char)*128];
    char* extendedDynamicBuffer;
    size_t n = 0;
    Xml* xml = makexml();
    int deepness = 0;
    enum categorization category = NotDefined;

    if(xml==NULL){
        printf("%s","Problem has been occured while memmory alocation");
        return 0;
    }

    while ((c = fgetc(file)) != EOF) {
        if((char)c == '<'){
            n=0; 
        }
        if(buffer[0]=='<'&&n==1&&(char)c=='?'){
            if(deepness>0){
                printf("syntax error. Prolog cannot inside of the children");
                return 0;
            }
            category = Prolog;
        }

        if(category==Prolog){
            
            
            while ((c = fgetc(file)) != '?') {
                char * key;
                char * val;
                /**/
                if((char)c==' '){
                    n=0;
                    while ((c = fgetc(file)) != '=') {
                      buffer[n++] = (char)c;
                    }
                    key = malloc(sizeof(char)*n);
                    memcpy(key,buffer, n);
                    //xml->prolog = createxmlproperty()
                }

                if((char)c=='\"'){
                    n=0;
                    while ((c = fgetc(file)) != '\"') {
                      buffer[n++] = (char)c;
                    }
                    val = malloc(sizeof(char)*n);
                    memcpy(val, buffer, n);
                    
                }
                xml->prolog = createxmlproperty(key,val);
                
                if(c==EOF){
                    printf("syntax error. Prolog not finished");
                    return 0;
                }
                
            }    

        }
        category= NotDefined;

        buffer[n++] = (char)c;
        if((char)c == '>'){
            printf("%.*s",n,buffer);
        }
        
        //printf("%c", c);
    }

    printf("%s , %s",xml->prolog->key,xml->prolog->value);

}


int main() {
    printf("here");
    FILE *file = fopen("target.xml", "r");
    char *code;
    size_t n = 0;
    int c;

    if (file == NULL) return 0; //could not open file
    fseek(file, 0, SEEK_END);
    long f_size = ftell(file);
    fseek(file, 0, SEEK_SET);
    code = malloc(f_size);
    
    readxml(file);

/*
    while ((c = fgetc(file)) != EOF) {
        code[n++] = (char)c;
        printf("%c", c);
    }

    code[n] = '\0';        
*/
    fclose(file); 
}
