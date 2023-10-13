#include <stdio.h>
#include <stdlib.h>

void print_board(int **board, int size);

int **create_board(int size);

void free_board(int **board, int size);

char set_mark(int record);

void move(int **board, int size, int player, int location);

int main(int argc, char *argv[]){
  if(argc != 2){
    printf("Usage: %s mode\n", argv[0]);
    exit(1);
  }

  int **board = create_board(3);

  print_board(board, 3);

  move(board, 3, 0, 4);
  move(board, 3, 1, 2);
  print_board(board, 3);
  
  free_board(board, 3);

  exit(0);
}

char set_mark(int record){
  char mark = '!';

  if(record == 0){
    mark = ' ';
  } else if(record == -1){
    mark = 'O';
  } else if(record == 1){
    mark = 'X';
  } else {
    mark = '?';
  }
  return mark;
}

void print_board(int **board, int size){
  char mark = ' ';
  printf("\n");
  for(int i = 0; i < size; i++){
    for(int j = 0; j < size; j++){
      if(j != 0){
	printf("|");
      }
      mark = set_mark(board[i][j]);
      
      printf("%c",mark);
    }
    if(i!= size - 1){
      printf("\n_____\n");
    }
  }
  printf("\n\n");
  return;

}

int **create_board(int size){
  int **board = malloc(size * sizeof(int*));
  for(int i = 0; i < size; i++){
    board[i] = malloc(size * sizeof(int));
    for(int j = 0; j < size; j++){
      board[i][j] = 0;
    }
  }
  return board;
}

void free_board(int **board, int size){
  for(int i = 0; i < size; i++){
      free(board[i]);
    }
    free(board);
}

void move(int **board, int size, int player, int location){
  int record = 0;
  if(player == 0){
    record = 1;
  } else if(player == 1){
    record = -1;
  } else {
    record = 2;
  }
  int i = location / size;
  int j = location % size;
  board[i][j] = record;
  
}
