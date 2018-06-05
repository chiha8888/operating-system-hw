#ifndef _BUFFER_H_
#define _BUFFER_H_
#define BUFFER_SIZE 5
typedef int buffer_item;


buffer_item buffer[BUFFER_SIZE];

int insert_item(buffer_item item);
int remove_item(buffer_item *item);
void init();
#endif
