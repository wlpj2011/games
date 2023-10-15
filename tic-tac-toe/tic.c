#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void print_board(int **board, int size); //Prints the current state of the board
int **create_board(int size); //Creates a blank size x size board
void free_board(int **board, int size); //Frees the allocated memory
char set_mark(int record); //Converts an integer board mark to a printable one
void move(int **board, int size, int player, int location); //Makes the given move on the board
int decide_move(int **board, int size, int player); //Decides what move should be made
int player_input(int size); //Gets the players move from stdin
int evaluate_board(int **board, int size); //Decides if the game is over and who has won if so
int play_game(int **board, int size, int player); //Manages the game loop and returns the winner

int main(int argc, char *argv[]){
  if(argc != 2){
    printf("Usage: %s mode\n", argv[0]);
    exit(1);
  }

  int **board = create_board(3);

  system("clear");
  print_board(board, 3);

  sleep(1);
  move(board, 3, 0, 4);
  system("clear");
  print_board(board, 3);

  sleep(1);
  move(board, 3, 1, 2);
  system("clear");
  print_board(board, 3);

  sleep(1);

  free_board(board, 3);

  system("clear");

  /*
  int SIZE = 3;
  int PLAYER = 0;
  int **board = create_board(SIZE);

  system("clear");
  play_game(board, SIZE, PLAYER);
  free_board(board, SIZE);
  system("clear");
  */

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

int decide_move(int **board, int size, int player){
  //put a slowdown here if the AI is fast so player can see board after their move
  return -1;
}

int player_input(int size){

  return -1;
}

int evaluate_board(int **board, int size){

  for (int i = 0; i < size; i++){
    int result_horizontal = 0;
    int result_vertical = 0;
    for (int j = 0; j < size; j++)
    {
      result_horizontal += board[i][j];
      result_vertical += board[j][i];
    }
    if((result_horizontal == 3) || (result_vertical == 3)){
      return 0;
    } else if((result_horizontal == -3) || (result_vertical == -3)){
      return 1;
    }
  }
  int result1 = 0;
  int result2 = 0;
  for (int i = 0; i < size; i++){
    result1 += board[i][i];
    result2 += board[i][size - i - 1];
  }
  if((result1 == 3) || (result2 == 3)){
    return 0;
  } else if((result1 == -3) || (result2 == -3)){
    return 1;
  }
  return -1;
}

int play_game(int **board, int size, int player){
  int current_player = 0;
  while (evaluate_board(board, size) == -1){
    if(current_player == player){
      print_board(board, size);
      move(board, size, current_player, player_input(size));
    }
    else{
      print_board(board, size);
      move(board, size, current_player, decide_move(board, size, current_player));
    }
    current_player = 1 - current_player;
  }
  return evaluate_board(board,size);
}
