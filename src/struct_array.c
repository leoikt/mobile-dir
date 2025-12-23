// src: https://stepik.org/lesson/Structures-1443629/step/9?unit=1462430 
/*

struct maybe_int64 {
  int64_t value;
  bool valid;
};

struct maybe_int64 some_int64(int64_t i) {
  return (struct maybe_int64) { i, true };
}

const struct maybe_int64 none_int64 = { 0 };
*/

size_t read_size() { size_t sz = 0; scanf("%zu", &sz); return sz; }

struct array_int {
  int64_t* data;
  size_t size;  // Исправлено: добавлена точка с запятой
};

void array_int_fill( int64_t* array, size_t sz ) {
  for( size_t i = 0; i < sz; i += 1 ) {
    array[i] = read_int64();
  }
}

struct array_int array_int_read() {
  const size_t size = read_size();
  if (size > 0) {
    int64_t* array = malloc( sizeof(int64_t) * size);
    array_int_fill( array, size );
    return (struct array_int) { .data = array, .size = size };
  }
  else return (struct array_int) {0};
}

// returns an error if the index is outside the array
struct maybe_int64 array_int_get( struct array_int a, size_t i ) {
  struct maybe_int64 res = {0};
  if (!a.data || a.size == 0 || i >= a.size)  // Исправлено: i >= a.size вместо i > (size-1)
    res.valid = false;
  else {
    res.value = a.data[i];
    res.valid = true;
  }
  return res;
}

// returns false if the index is outside the array
bool array_int_set( struct array_int a, size_t i, int64_t value ) {
  if (!a.data || a.size == 0 || i >= a.size) return false;  // Исправлено: i >= a.size
  
  a.data[i] = value;
  return true;
}

void array_int_print( struct array_int array ) {
  for (size_t i = 0; i < array.size; i = i + 1) {
    printf("%" PRId64 " " , array_int_get( array, i).value);
  }
}

struct maybe_int64 array_int_min( struct array_int array ) {
  struct maybe_int64 res = {0};
  if (!array.data || array.size == 0) 
    res.valid = false;
  else {
    res.value = array.data[0];
    for (size_t i = 1; i < array.size; i++) {  // Исправлено: array.size вместо size
      if (res.value > array.data[i]) 
        res.value = array.data[i];
    }
    res.valid = true;
  }
  return res;
}

void array_int_free( struct array_int a ) { 
    if ( a.size > 0 ) {
        free(a.data); 
        a.size = 0;
    } 
}
