#include "hashset.h"  /* the .h file does NOT reside in /usr/local/include/ADTs */
#include <stdlib.h>
#include <stdio.h>

/* any other includes needed by your code */
#define UNUSED __attribute__((unused))
#define SHIFT 31L 

// added node structure 
typedef struct node {
    struct node *next;
} Node; 



typedef struct s_data {
    /* definitions of the data members of self */
    void (*freeValue)(void *e);
    int (*cmpFxn) (void *first, void *second);
    long changes; //recommended by the book
    long capacity; 
    double loadFactor;
    long (*hashFxn) (void*, long);
    Node **buckets; 

} SData;

/*
 * important - remove UNUSED attributed in signatures when you flesh out the
 * methods
 */

// Helper functions recommended by the Book 

static void purge(SData *st){
    long i; 
    Node *p;
    for(i = 0L; i < st->capacity; i++){ 
        p = st->buckets[i];
        while(p != NULL){
            st->freeValue(st->buckets[i]);
        }
        st->buckets[i] = NULL;
    }
}


// Flesh these functions out

static void s_destroy(const Set *s) {
    /* implement the destroy() method */
    SData *st = (SData *)s->self; 

    purge(st);
    free(st->buckets);
    free(st);
    free((void*)st); // this may not be needed but read book tommorow 04/16/23
}

static void s_clear(const Set *s) {
    /* implement the clear() method */
    SData *st = (SData*)s->self; 

    purge(st);
    st->capacity = 0;
    st->loadFactor = 0.0;
    st->changes = 0; 
    //s_destroy(s);
                    // This needs to be checked once I go back through because I dont belive this
                    // is entirely the correct way to go about this
}

static bool s_add(const Set *s, UNUSED void *member) {
    /* implement the add() method 
    SData *st = (SData*)s->self; 
    if(s_contains(st, member)){
        return false; 
    }else{
        hashFxn(member, st->capacity);
    } */
    return true;
}

static Node *findMember(SData *st, void *member, long *bucket){
    long i = hashFxn(member, st->capacity);
    Node *p; 
    for(p = st->buckets[i]; p != NULL; i++){
        if(cmpFxn(p, member) == 0){
            break;
        }
    }
    return p;
}


static bool s_contains(const Set *s, void *member) {
    /* implement the contains() method */
    SData *st = (SData*)s->self;
    long bucket;

    return (findMember(st, member, &bucket) != NULL); 
}

static bool s_isEmpty(const Set *s) {
    /* implement the isEmpty() method */
    SData *st = (SData*)s->self;
    return (st->capacity == 0L); // check if st->next is equivalent to 0L. If it is then true, else false
}

static bool s_remove(UNUSED const Set *s, UNUSED void *member) {
    /* implement the remove() method */
    return 0;
}

static long s_size(const Set *s) {
    /* implement the size() method */
    SData *st = (SData*)s->self; 
    return st->capacity;
}

static void **s_toArray(UNUSED const Set *s, UNUSED long *len) {
    /* implement the toArray() method */
    return NULL;
}

static const Iterator *s_itCreate(UNUSED const Set *s) {
    /* implement the itCreate() method */
    return NULL;
}

static Set template = {
    NULL, s_destroy, s_clear, s_add, s_contains, s_isEmpty, s_remove,
    s_size, s_toArray, s_itCreate
};

const Set *HashSet(void (*freeValue)(void*), int (*cmpFxn)(void*, void*),
                   long capacity, double loadFactor,
                    long (*hashFxn)(void *m, long N)
                  ) {
    /* construct a Set instance and return to the caller */
    SData *s = (SData*)malloc(sizeof(capacity));

    return s;
}
