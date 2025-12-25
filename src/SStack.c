// src: https://stepik.org/lesson/Structures-1443629/step/13?unit=1462430

struct stack {
  size_t count;
  struct array_int data;
};

size_t stack_count( const struct stack* s );
struct stack stack_create( size_t size );
void stack_destroy( struct stack* s );
bool stack_is_full( const struct stack * s);
bool stack_is_empty( const struct stack * s);
bool stack_push( struct stack* s, int64_t value );
struct maybe_int64 stack_pop( struct stack* s );
void stack_print(const struct stack* s);

size_t stack_count( const struct stack* s ) {
  return s ? s->count : 0;
}

struct stack stack_create( size_t size ) {
  struct stack s = {.count = 0, .data.size = 0};
  s.data.data = (int64_t*)malloc(size * sizeof(int64_t));
  if (s.data.data) {
    s.data.size = size;
  }
  return s;
}

void stack_destroy( struct stack* s ) {
  if (s) {
    free(s->data.data);
    s->data.data = NULL;
    s->data.size = 0;
    s->count = 0;
  }
}

bool stack_is_full( const struct stack * s) {
  return s && s->data.data && s->count == s->data.size;
}

bool stack_is_empty( const struct stack * s) {
  return s && s->count == 0;
}

bool stack_push( struct stack* s, int64_t value ) {
  if (s && s->data.data && s->count < s->data.size) {
    s->data.data[s->count++] = value;
    return true;
  } else {
    return false;
  }
}

struct maybe_int64 stack_pop( struct stack* s ) {
  struct maybe_int64 res = {.valid = false};
  if (s && s->data.data && s->count > 0) {
    res.value = s->data.data[s->count - 1];
    res.valid = true;
    s->count--;
  }
  return res;
}

void stack_print( const struct stack* s ) {
  for (size_t i = 0; i < stack_count(s); i = i + 1 ) {
    print_int64( array_int_get( s->data, i).value );
    printf(" ");
  }
}


