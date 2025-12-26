struct list {
  int64_t value;
  struct list* next;
};

struct list* node_create( int64_t value ) {
  struct list* node = (struct list*)malloc(sizeof(struct list));
  if (node) {
    node->value = value;
    node->next = NULL;
  }
  return node;
}

