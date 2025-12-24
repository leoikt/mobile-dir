#define SInt64 struct maybe_int64
#define SSzArray struct array_int
#define SSafeVector struct maybe_array_int
#define SMatrix struct array_array_int

/* You can use these functions from previous tasks */
size_t read_size() { size_t i; scanf("%zu", &i); return i; }

void array_int_fill(int64_t* array, size_t sz);

SSzArray array_int_read();
SInt64 array_int_get(SSzArray a, size_t i);
bool array_int_set(SSzArray a, size_t i, int64_t value);
void array_int_print(SSzArray array);
SInt64 array_int_min(SSzArray array);
void array_int_free(SSzArray a);

void array_int_normalize(SSzArray array, int64_t m) {
  for (size_t i = 0; i < array.size; i = i + 1) {
    array.data[i] = array.data[i] - m;
  }
}

/*  ---- maybe int[] ---- */
SSafeVector {
  SSzArray value;
  bool valid;
};

SSafeVector some_array_int(SSzArray array) {
  return (SSafeVector) { array, true };
}
const SSafeVector none_array_int = { {NULL, 0}, false };

/*  ---- int[][] ---- */
SMatrix {
  SSzArray* data;
  size_t size;
};

/*  --- rows ---  */
SSafeVector array_array_int_get_row(SMatrix a, size_t i) {
  if (0 <= i && i < a.size) { return some_array_int(a.data[i]); }
  else { return none_array_int; }
}

bool array_array_int_set_row(SMatrix a, size_t i, SSzArray value) {
  if (0 <= i && i < a.size) {
    a.data[i] = value;
    return true;
  }
  else { return false; }
}

/*  --- get/set ---  */
SInt64 array_array_int_get(SMatrix a, size_t i, size_t j) {
  SInt64 res = {.valid = false};
  if (a.data && i < a.size && a.data[i].data && j < a.data[i].size) {
      res.value = a.data[i].data[j];
      res.valid = true;
  }
  return res;
}

bool array_array_int_set(SMatrix a, size_t i, size_t j, int64_t value) {
  if (a.data && i < a.size && a.data[i].data && j < a.data[i].size) {
    a.data[i].data[j] = value;
    return true;
  }
  return false;
}

/*  --- read/print ---  */
SMatrix array_array_int_read() {
  SMatrix a = {0};
  a.size = read_size();
  a.data = (SSzArray*)malloc(a.size * sizeof(SSzArray));
  if (a.data) {
    for(size_t i = 0; i < a.size; i++) {
      a.data[i] = array_int_read();
    }
  }
  return a;
}

void array_array_int_print(SMatrix array) {
  for (size_t i = 0; i < array.size; i++) {
    array_int_print(array.data[i]);
    putchar('\n');
  }
}

/*  --- min/normalize ---  */
SInt64 array_array_int_min(SMatrix array) {
  SInt64 min = {.valid = false};
  bool found_first = 0;
  for (size_t i = 0; i < array.size; i++) {
    if (array.data[i].size > 0 && array.data[i].data) {
      for (size_t j = 0; j < array.data[i].size; j++) {
        if (!found_first) {
          min.value = array.data[i].data[j];
          min.valid = true;
          found_first = 1;
        } else if (array.data[i].data[j] < min.value) {
          min.value = array.data[i].data[j];
        }
      }
    }
  }
  return min;
}

void array_array_int_normalize(SMatrix array, int64_t m) {
  for (size_t i = 0; i < array.size; i = i + 1) {
    const SSafeVector cur_row = array_array_int_get_row(array, i);
    if (cur_row.valid) {
      array_int_normalize(cur_row.value, m);
    }
  }
}

void array_array_int_free(SMatrix array) {
  if (array.data) {
    for (size_t i = 0; i < array.size; i++) {
      if (array.data[i].data) {
        free(array.data[i].data);
      }
    }
    free(array.data);
  }
}
