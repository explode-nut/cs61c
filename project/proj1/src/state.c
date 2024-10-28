#include "state.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "snake_utils.h"

/* Helper function definitions */
static void set_board_at(game_state_t *state, unsigned int row, unsigned int col, char ch);
static bool is_tail(char c);
static bool is_head(char c);
static bool is_snake(char c);
static char body_to_tail(char c);
static char head_to_body(char c);
static unsigned int get_next_row(unsigned int cur_row, char c);
static unsigned int get_next_col(unsigned int cur_col, char c);
static void find_head(game_state_t *state, unsigned int snum);
static char next_square(game_state_t *state, unsigned int snum);
static void update_tail(game_state_t *state, unsigned int snum);
static void update_head(game_state_t *state, unsigned int snum);

/* Task 1 */
game_state_t *create_default_state() {
  // TODO: Implement this function.
  //创建蛇
  snake_t snake = {2, 2, 2, 4, true};

  //创建返回对象
  game_state_t *game = malloc(sizeof(game_state_t));
  //为蛇分配内存并赋值
  game->snakes = malloc(sizeof(snake_t));
  game->snakes[0] = snake;
  //为游戏界面赋值
  game->board = malloc(18*sizeof(char*));
  for (int i = 0; i < 18; i++) {
    game->board[i] = malloc(21*sizeof(char));
    for (int j = 0; j < 20; j++) {
      game->board[i][j] = ' ';
    }
    game->board[i][20] = '\0';
  }

  //为边界赋值
  for (int i = 0; i < 20; i++) {
    game->board[0][i] = '#';
    game->board[17][i] = '#';
  }
  for (int i = 1; i < 17; i++) {
    game->board[i][0] = '#';
    game->board[i][19] = '#';
  }
  //加入蛇和食物
  game->board[2][9] = '*';
  game->board[2][2] = 'd';
  game->board[2][3] = '>';
  game->board[2][4] = 'D';
  //赋值其他变量
  game->num_rows = 18;
  game->num_snakes = 1;
  
  return game;
}

/* Task 2 */
void free_state(game_state_t *state) {
  // TODO: Implement this function.
  for (int i = 0; i < state->num_rows; i++)
    free(state->board[i]);
  free(state->board);
  free(state->snakes);
  free(state);
  return;
}

/* Task 3 */
void print_board(game_state_t *state, FILE *fp) {
  // TODO: Implement this function.
  for (int i = 0; i < state->num_rows; i++) {
    fprintf(fp, "%s\n", state->board[i]);
  }
  return;
}

/*
  Saves the current state into filename. Does not modify the state object.
  (already implemented for you).
*/
void save_board(game_state_t *state, char *filename) {
  FILE *f = fopen(filename, "w");
  print_board(state, f);
  fclose(f);
}

/* Task 4.1 */

/*
  Helper function to get a character from the board
  (already implemented for you).
*/
char get_board_at(game_state_t *state, unsigned int row, unsigned int col) { return state->board[row][col]; }

/*
  Helper function to set a character on the board
  (already implemented for you).
*/
static void set_board_at(game_state_t *state, unsigned int row, unsigned int col, char ch) {
  state->board[row][col] = ch;
}

/*
  Returns true if c is part of the snake's tail.
  The snake consists of these characters: "wasd"
  Returns false otherwise.
*/
static bool is_tail(char c) {
  // TODO: Implement this function.
  if (c != 'w' && c != 'a' && c != 's' && c != 'd') {
    return false;
  }
  return true;
}

/*
  Returns true if c is part of the snake's head.
  The snake consists of these characters: "WASDx"
  Returns false otherwise.
*/
static bool is_head(char c) {
  // TODO: Implement this function.
  if (c != 'W' && c != 'A' && c != 'S' && c != 'D' && c != 'x') {
    return false;
  }
  return true;
}

/*
  Returns true if c is part of the snake.
  The snake consists of these characters: "wasd^<v>WASDx"
*/
static bool is_snake(char c) {
  // TODO: Implement this function.
  if (!is_head(c) && !is_tail(c) && c != '^' && c != '<' && c != 'v' && c != '>') {
    return false;
  }
  return true;
}

/*
  Converts a character in the snake's body ("^<v>")
  to the matching character representing the snake's
  tail ("wasd").
*/
static char body_to_tail(char c) {
  // TODO: Implement this function.
  switch (c) {
    case '^':
      return 'w';
      break;
    case '<':
      return 'a';
      break;
    case 'v':
      return 's';
      break;
    case '>':
      return 'd';
      break;
  }
  return '?';
}

/*
  Converts a character in the snake's head ("WASD")
  to the matching character representing the snake's
  body ("^<v>").
*/
static char head_to_body(char c) {
  // TODO: Implement this function.
  switch (c) {
    case 'W':
      return '^';
      break;
    case 'A':
      return '<';
      break;
    case 'S':
      return 'v';
      break;
    case 'D':
      return '>';
      break;
  }
  return '?';
}

/*
  Returns cur_row + 1 if c is 'v' or 's' or 'S'.
  Returns cur_row - 1 if c is '^' or 'w' or 'W'.
  Returns cur_row otherwise.
*/
static unsigned int get_next_row(unsigned int cur_row, char c) {
  // TODO: Implement this function.
  if (c == 'v' || c == 's' || c == 'S') {
    return cur_row + 1;
  } else if (c == '^' || c == 'w' || c == 'W') {
    return cur_row - 1;
  }
  return cur_row;
}

/*
  Returns cur_col + 1 if c is '>' or 'd' or 'D'.
  Returns cur_col - 1 if c is '<' or 'a' or 'A'.
  Returns cur_col otherwise.
*/
static unsigned int get_next_col(unsigned int cur_col, char c) {
  // TODO: Implement this function.
  if (c == '>' || c == 'd' || c == 'D') {
    return cur_col + 1;
  } else if (c == '<' || c == 'a' || c == 'A') {
    return cur_col - 1;
  }
  return cur_col;
}

/*
  Task 4.2

  Helper function for update_state. Return the character in the cell the snake is moving into.

  This function should not modify anything.
*/
static char next_square(game_state_t *state, unsigned int snum) {
  // TODO: Implement this function.
  unsigned int cur_row = state->snakes[snum].head_row;
  unsigned int cur_col = state->snakes[snum].head_col;
  char head_sign = get_board_at(state, cur_row, cur_col);
  unsigned int next_row = get_next_row(cur_row, head_sign);
  unsigned int next_col = get_next_col(cur_col, head_sign);

  char res = get_board_at(state, next_row, next_col);;

  return res;
}

/*
  Task 4.3

  Helper function for update_state. Update the head...

  ...on the board: add a character where the snake is moving

  ...in the snake struct: update the row and col of the head

  Note that this function ignores food, walls, and snake bodies when moving the head.
*/
static void update_head(game_state_t *state, unsigned int snum) {
  // TODO: Implement this function.
  unsigned int cur_row = state->snakes[snum].head_row;
  unsigned int cur_col = state->snakes[snum].head_col;
  char head_sign = get_board_at(state, cur_row, cur_col);
  unsigned int next_row = get_next_row(cur_row, head_sign);
  unsigned int next_col = get_next_col(cur_col, head_sign);

  //修改snake_t
  state->snakes[snum].head_row = next_row;
  state->snakes[snum].head_col = next_col;
  //修改board
  set_board_at(state, next_row, next_col, head_sign);
  set_board_at(state, cur_row, cur_col, head_to_body(head_sign));

  return;
}

/*
  Task 4.4

  Helper function for update_state. Update the tail...

  ...on the board: blank out the current tail, and change the new
  tail from a body character (^<v>) into a tail character (wasd)

  ...in the snake struct: update the row and col of the tail
*/
static void update_tail(game_state_t *state, unsigned int snum) {
  // TODO: Implement this function.
  unsigned int cur_row = state->snakes[snum].tail_row;
  unsigned int cur_col = state->snakes[snum].tail_col;
  char tail_sign = get_board_at(state, cur_row, cur_col);
  unsigned int next_row = get_next_row(cur_row, tail_sign);
  unsigned int next_col = get_next_col(cur_col, tail_sign);
  char next = get_board_at(state, next_row, next_col);

  //修改snake_t
  state->snakes[snum].tail_row = next_row;
  state->snakes[snum].tail_col = next_col;
  //修改board
  set_board_at(state, next_row, next_col, body_to_tail(next));
  set_board_at(state, cur_row, cur_col, ' ');


  return;
}

/* Task 4.5 */
void update_state(game_state_t *state, int (*add_food)(game_state_t *state)) {
  // TODO: Implement this function.
  for (unsigned int i = 0; i < state->num_snakes; i++) {
    char next = next_square(state, i);
    if (is_snake(next) || next == '#') {
      set_board_at(state, state->snakes[i].head_row, state->snakes[i].head_col, 'x');
      state->snakes[i].live = false;
    } else if (next == '*') {
      update_head(state, i);
      add_food(state);
    } else {
      update_head(state, i);
      update_tail(state, i);
    }
  }
  return;
}

/* Task 5.1 */
char *read_line(FILE *fp) {
  // TODO: Implement this function.
    char buff[255]; // 定义字符数组作为缓冲区
    char *line = NULL;

    // 尝试读取一行到缓冲区
    if(fgets(buff, 64, fp) != NULL) {
        line = malloc(strlen(buff) + 1); // 分配足够大小的内存
        if(line != NULL) {
            strcpy(line, buff); // 复制数据
        }
    }

    return line;
}

/* Task 5.2 */
game_state_t *load_board(FILE *fp) {
  // TODO: Implement this function.
  game_state_t *res = NULL;
  char *line;
  unsigned int row = 0;

  while ((line = read_line(fp)) != NULL) {
    //读到空字符立即结束循环
    if (line[0] == '\0') {
      break;
    }
    //readline中使用fgets读取行，遇到换行符会停止读取，这样会多读一行空行
    //因此要将每行最后一个换行符换成空字符防止多一行空行
    if (line[strlen(line) - 1] == '\n') {
      line[strlen(line) - 1] = '\0';
    }
    //第一次读取
    if (row == 0) {
      res = malloc(sizeof(game_state_t));
      if (res == NULL) {
        free(line);
        return NULL;
      }
      res->board = malloc((row + 1) * sizeof(char*));
      if (res->board == NULL) {
        free(line);
        return NULL;
      }
    } else {
      //非第一次读取
      res->board = realloc(res->board, (row + 1) * sizeof(char*));
      if (res->board == NULL) {
        free(res);
        free(line);
        return NULL;
      }
    }
    //line已经被分配内存，不需要重新分配
    res->board[row] = line;
    row++;
  }

  res->num_rows = row;
  //防止错误
  res->snakes = NULL;
  
  return res;
}

/*
  Task 6.1

  Helper function for initialize_snakes.
  Given a snake struct with the tail row and col filled in,
  trace through the board to find the head row and col, and
  fill in the head row and col in the struct.
*/
static void find_head(game_state_t *state, unsigned int snum) {
  // TODO: Implement this function.
  unsigned int i = state->snakes[snum].tail_row;
  unsigned int j = state->snakes[snum].tail_col;
  char sign = get_board_at(state, i, j);
  while (!is_head(sign)) {
    i = get_next_row(i, sign);
    j = get_next_col(j, sign);
    sign = get_board_at(state, i, j);
  }

  state->snakes[snum].head_row = i;
  state->snakes[snum].head_col = j;
  if (sign == 'x') {
    state->snakes[snum].live = false;
  } else {
    state->snakes[snum].live = true;
  }

  return;
}

/* Task 6.2 */
game_state_t *initialize_snakes(game_state_t *state) {
  // TODO: Implement this function.
  unsigned int num_snakes = 0;
  //初始化蛇尾，及找到蛇的数量
  for (unsigned int i = 0; i < state->num_rows; i++) {
    for (unsigned int j = 0; j < strlen(state->board[i]); j ++) {
      if (is_tail(get_board_at(state, i, j))) {
        //第一条蛇
        if (num_snakes == 0) {
          state->snakes = malloc((num_snakes + 1) * sizeof(snake_t));
          if (state->snakes == NULL) {
            return NULL;
          }
        } else {
          state->snakes = realloc(state->snakes, (num_snakes + 1) * sizeof(snake_t));
          if (state->snakes == NULL) {
            return NULL;
          }
        }
        state->snakes[num_snakes].tail_row = i;
        state->snakes[num_snakes].tail_col = j;
        state->snakes[num_snakes].live = true;
        num_snakes++;
      }
    }
  }

  //初始化蛇头
  state->num_snakes = num_snakes;
  for (unsigned int i = 0; i < num_snakes; i++) {
    find_head(state, i);
  }

  return state;
}
