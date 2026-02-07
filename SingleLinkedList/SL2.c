// typedef struct Node
// {
//   /* data */
//   int data;
//   struct Node*next;
// }Node;

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


typedef struct Task{
  int id ;
  char deskripsi[120];
  char prioritas;
}Task;


typedef struct Node 
{
  /* data */
  Task task;
  struct Node *next;

}Node;

Node *head = NULL;

Node* buat_node(int id, const char *desk, int prioritas){
  Node* node_baru = (Node*)malloc(sizeof(Node));

  if(!node_baru){
    fprintf(stderr,"Gagal dalam alokasi untuk memori baru \n" );
    exit(EXIT_FAILURE);
  }


  node_baru -> task.id = id;
  strncpy(node_baru-> task.deskripsi, desk, sizeof(node_baru-> task.deskripsi)-1);
  node_baru-> task.deskripsi[sizeof(node_baru -> task.deskripsi)-1] = '\0';
  node_baru -> task.prioritas = prioritas;


  node_baru -> next = NULL;


  return node_baru;
}


void tambah_task()