#include <assert.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* readline();
char** split_string(char*);

//Define the structs of the 2-sided linked list.
typedef struct singly_linked_list_node_t singly_linked_list_node_t;
typedef struct singly_linked_list_t singly_linked_list_t;

struct singly_linked_list_node_t {
	char *data;
	singly_linked_list_node_t *next;
	singly_linked_list_node_t *prev;

};

struct singly_linked_list_t {
	singly_linked_list_node_t *head;
	singly_linked_list_node_t *tail;
};

//Creates a new&un filled node instance.
singly_linked_list_node_t* create_singly_linked_list_node(char *node_data) {
	if(node_data == NULL) {
		return NULL;
	}
	singly_linked_list_node_t *node = malloc(sizeof(singly_linked_list_node_t));
	if (!node){
		return NULL;
	}
	node->data = node_data;
	node->next = NULL;
	node->prev = NULL;
	return node;
}

//creates new&un-filled list instance.
singly_linked_list_t* create_singly_linked_list (){
	singly_linked_list_t *new_list = malloc(sizeof(singly_linked_list_t));
	if (!new_list){
		return NULL;
	}
	(new_list)->head = NULL;
	(new_list)->tail = NULL;

	return new_list;
}

//the function take new data and existing list, create new node that containing
//the data, and add it to the end of the given list.
void insert_node_into_singly_linked_list(
		singly_linked_list_t *singly_linked_list_t,
		char *node_data) {

	if ( singly_linked_list_t == NULL || node_data == NULL ) {
		return;
	}

	singly_linked_list_node_t *node = create_singly_linked_list_node(node_data);

	if (!(singly_linked_list_t)->head) {
		(singly_linked_list_t)->head = node;
	} else {
		node->prev = (singly_linked_list_t)->tail;
		(singly_linked_list_t)->tail->next = node;
	}

	(singly_linked_list_t)->tail = node;

	return;
}

//The function take pointer to array of pointers and convert it to 2-sided
//linked list.
singly_linked_list_t* convert_to_list(int size_of_list, char** list_elements){

	singly_linked_list_t *new_list = create_singly_linked_list();
	for (int i = 0; i< size_of_list; i++){
		insert_node_into_singly_linked_list(new_list,*(list_elements+i));
	}

	return new_list;
}

//The function free all dynamic allocated memory that used by the given list.
void free_singly_linked_list(singly_linked_list_t *list) {
	if(list == NULL) {
		return;
	}
	singly_linked_list_node_t *head = (list)->head;
	singly_linked_list_node_t *temp_node;
	singly_linked_list_node_t *cursor = head;

	while (cursor) {
		temp_node = cursor;
		cursor = cursor->next;
		free(temp_node);
	}

	free(list);
	return;
}


//The function get data, and search in the given 2-sided linked list
//a node that match it.
singly_linked_list_node_t* list_contains(
		singly_linked_list_node_t *head,
		char *data) {


	if (head == NULL || data == NULL) {
		return NULL;
	}
	for (singly_linked_list_node_t *cursor=head; cursor; cursor=cursor->next) {
		char *tmp_data = cursor->data;

		if(tmp_data ==NULL) {
			return NULL;
		}


		if (!(strcmp(tmp_data,data))) {
			return cursor;
		}
	}
	return NULL;
}


// The function remove a specific node from the given 2-sided linked list.
//the function free the memory that used by the node.
void delete_node(singly_linked_list_node_t *node,singly_linked_list_t *list) {

	singly_linked_list_node_t *temp = node;
	if ((list->head)!=(list->tail)) {
		if (!(list->head)){
			return;
		} else if (list->head == temp) {
			list->head = temp->next;
			(list->head)->prev = NULL;
		} else if ((list->tail) == temp) {
			list->tail = temp->prev;
			(list->tail)->next = NULL;
		} else {
			temp->prev->next = temp->next;
			temp->next->prev = temp->prev;
		}
	} else {
		(list->head) = NULL;
		(list->tail) = NULL;
	}

	free(temp);
	return;

}





// Complete the checkMagazine function below.
void checkMagazine(
		int magazine_count,
		char **magazine,
		int note_count,
		char **note) {

	singly_linked_list_t *map = convert_to_list(magazine_count,magazine);

	if(magazine_count < note_count){
		printf("No");
		free_singly_linked_list(map);
		return;
	}

	for(int i =0; i< note_count; i++){
		singly_linked_list_node_t *tmp = list_contains(((map)->head),*(note+i));
		if(!tmp){
			printf("No");
			free_singly_linked_list(map);
			return;
		}
		delete_node(tmp,map);
	}

	printf("Yes");
	free_singly_linked_list(map);
	return;
}

int main()
{
    char** mn = split_string(readline());

    char* m_endptr;
    char* m_str = mn[0];
    int m = strtol(m_str, &m_endptr, 10);

    if (m_endptr == m_str || *m_endptr != '\0') { exit(EXIT_FAILURE); }

    char* n_endptr;
    char* n_str = mn[1];
    int n = strtol(n_str, &n_endptr, 10);

    if (n_endptr == n_str || *n_endptr != '\0') { exit(EXIT_FAILURE); }

    char** magazine_temp = split_string(readline());

    char** magazine = malloc(m * sizeof(char*));

    for (int i = 0; i < m; i++) {
        char* magazine_item = *(magazine_temp + i);

        *(magazine + i) = magazine_item;
    }

    int magazine_count = m;

    char** note_temp = split_string(readline());

    char** note = malloc(n * sizeof(char*));

    for (int i = 0; i < n; i++) {
        char* note_item = *(note_temp + i);

        *(note + i) = note_item;
    }

    int note_count = n;

    checkMagazine(magazine_count, magazine, note_count, note);

    return 0;
}

char* readline() {
    size_t alloc_length = 1024;
    size_t data_length = 0;
    char* data = malloc(alloc_length);

    while (true) {
        char* cursor = data + data_length;
        char* line = fgets(cursor, alloc_length - data_length, stdin);

        if (!line) {
            break;
        }

        data_length += strlen(cursor);

        if (data_length < alloc_length - 1 || data[data_length - 1] == '\n') {
            break;
        }

        alloc_length <<= 1;

        data = realloc(data, alloc_length);

        if (!line) {
            break;
        }
    }

    if (data[data_length - 1] == '\n') {
        data[data_length - 1] = '\0';

        data = realloc(data, data_length);
    } else {
        data = realloc(data, data_length + 1);

        data[data_length] = '\0';
    }

    return data;
}

char** split_string(char* str) {
    char** splits = NULL;
    char* token = strtok(str, " ");

    int spaces = 0;

    while (token) {
        splits = realloc(splits, sizeof(char*) * ++spaces);

        if (!splits) {
            return splits;
        }

        splits[spaces - 1] = token;

        token = strtok(NULL, " ");
    }

    return splits;
}
