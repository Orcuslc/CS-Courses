#include <stdio.h>
#include <string.h>

#include <unistd.h>
#include <sys/stat.h>

#include "beargit.h"
#include "util.h"

/* Implementation Notes:
 *
 * - Functions return 0 if successful, 1 if there is an error.
 * - All error conditions in the function description need to be implemented
 *   and written to stderr. We catch some additional errors for you in main.c.
 * - Output to stdout needs to be exactly as specified in the function description.
 * - Only edit this file (beargit.c)
 * - You are given the following helper functions:
 *   * fs_mkdir(dirname): create directory <dirname>
 *   * fs_rm(filename): delete file <filename>
 *   * fs_mv(src,dst): move file <src> to <dst>, overwriting <dst> if it exists
 *   * fs_cp(src,dst): copy file <src> to <dst>, overwriting <dst> if it exists
 *   * write_string_to_file(filename,str): write <str> to filename (overwriting contents)
 *   * read_string_from_file(filename,str,size): read a string of at most <size> (incl.
 *     NULL character) from file <filename> and store it into <str>. Note that <str>
 *     needs to be large enough to hold that string.
 *  - You NEED to test your code. The autograder we provide does not contain the
 *    full set of tests that we will run on your code. See "Step 5" in the homework spec.
 */

/* beargit init
 *
 * - Create .beargit directory
 * - Create empty .beargit/.index file
 * - Create .beargit/.prev file containing 0..0 commit id
 *
 * Output (to stdout):
 * - None if successful
 */

int beargit_init(void) {
  fs_mkdir(".beargit");

  FILE* findex = fopen(".beargit/.index", "w");
  fclose(findex);
  
  write_string_to_file(".beargit/.prev", "0000000000000000000000000000000000000000");

  return 0;
}


/* beargit add <filename>
 * 
 * - Append filename to list in .beargit/.index if it isn't in there yet
 *
 * Possible errors (to stderr):
 * >> ERROR: File <filename> already added
 *
 * Output (to stdout):
 * - None if successful
 */

int beargit_add(const char* filename) {
  FILE* findex = fopen(".beargit/.index", "r");
  FILE *fnewindex = fopen(".beargit/.newindex", "w");

  char line[FILENAME_SIZE];
  while(fgets(line, sizeof(line), findex)) {
    strtok(line, "\n");
    if (strcmp(line, filename) == 0) {
      fprintf(stderr, "ERROR: File %s already added\n", filename);
      fclose(findex);
      fclose(fnewindex);
      fs_rm(".beargit/.newindex");
      return 3;
    }

    fprintf(fnewindex, "%s\n", line);
  }

  fprintf(fnewindex, "%s\n", filename);
  fclose(findex);
  fclose(fnewindex);

  fs_mv(".beargit/.newindex", ".beargit/.index");

  return 0;
}


/* beargit rm <filename>
 * 
 * See "Step 2" in the homework 1 spec.
 *
 */

int beargit_rm(const char* filename) {
  /* COMPLETE THE REST */
  FILE* findex = fopen(".beargit/.index", "r");
  FILE* fnewindex = fopen(".beargit/.newindex", "w");
  char line[FILENAME_SIZE];
  int flag = 1;
  while(fgets(line, sizeof(line), findex)) {
    strtok(line, "\n");
    if(strcmp(line, filename) == 0) {
      flag = 0;
    }
    else {
      fprintf(fnewindex, "%s\n", line);
    }
  }
  if(flag == 1) {
    fprintf(stderr, "ERROR: File %s not tracked\n",filename);
    fclose(findex);
    fclose(fnewindex);
    fs_rm(".beargit/.newindex");
    return 3;
  }
  else {
    fclose(findex);
    fclose(fnewindex);
    fs_mv(".beargit/.newindex", ".beargit/.index");
  }
  return 0;
}

/* beargit commit -m <msg>
 *
 * See "Step 3" in the homework 1 spec.
 *
 */

const char* go_bears = "GO BEARS!";

int is_commit_msg_ok(const char* msg) {
  /* COMPLETE THE REST */
  int index = 0;
  while(*msg) {
    if(*msg == *(go_bears+index)) {
      index++;
    }
    else {
      index = 0;
    }
    if(index == 9) {
      return 1;
    }
    msg++;
  }
  return 0;
}

void next_commit_id(char* commit_id) {
  /* COMPLETE THE REST */
  int carry = 1;
  char* original = commit_id;
  while(*commit_id) {
    if(*commit_id == '0') {
      *commit_id = '1';
    }
    if(carry != 0) {
      if(*commit_id == '1') {
        *commit_id = '6';
        carry = 0;
      }
      else if(*commit_id == '6') {
        *commit_id = 'c';
        carry = 0;
      }
      else if(*commit_id == 'c'){
        *commit_id = '1';
        carry = 1;
      }
    }
    commit_id++;
  }
  commit_id = original;
}

char* join(char* a, char* b) {
  char* c = (char*)malloc(strlen(a)+strlen(b)+1);
  char* tmpc = c, *tmpa = a, *tmpb = b;
  while(*a != '\0') {
    *c++ = *a++;
  }
  while(*b != '\0') {
    *c++ = *b++;
  }
  a = tmpa;
  b = tmpb;
  return tmpc;
}

int beargit_commit(const char* msg) {
  if (!is_commit_msg_ok(msg)) {
    fprintf(stderr, "ERROR: Message must contain \"%s\"\n", go_bears);
    return 1;
  }

  char commit_id[COMMIT_ID_SIZE];
  read_string_from_file(".beargit/.prev", commit_id, COMMIT_ID_SIZE);
  next_commit_id(commit_id);

  /* COMPLETE THE REST */
  fs_mkdir(join(".beargit/", commit_id));
  fs_cp(".beargit/.index", join(join(".beargit/", commit_id), "/.index"));
  fs_cp(".beargit/.prev", join(join(".beargit/", commit_id), "/.prev"));

  write_string_to_file(join(join(".beargit/", commit_id), "/.msg"), msg);
  write_string_to_file(".beargit/.prev", commit_id);

  return 0;
}

/* beargit status
 *
 * See "Step 1" in the homework 1 spec.
 *
 */

int beargit_status() {
  /* COMPLETE THE REST */
  FILE* findex = fopen(".beargit/.index", "r");
  char line[FILENAME_SIZE];

  fprintf(stdout, "Tracked files:\n\n");
  int count = 0;
  while(fgets(line, sizeof(line), findex)) {
    strtok(line, "\n");
    fprintf(stdout, "\t%s\n", line);
    count++;
  }
  fprintf(stdout, "\n%d files total\n", count);
  return 0;
}

/* beargit log
 *
 * See "Step 4" in the homework 1 spec.
 *
 */

int beargit_log() {
  /* COMPLETE THE REST */
  char commit_id[COMMIT_ID_SIZE];
  read_string_from_file(".beargit/.prev", commit_id, COMMIT_ID_SIZE);
  const char init_id[COMMIT_ID_SIZE] = "0000000000000000000000000000000000000000";
  if(strcmp(commit_id, init_id) == 0) {
    fprintf(stderr, "%s\n", "ERROR: There are no commits!");
    return 3;
  }
  while(strcmp(commit_id, init_id) != 0) {
    printf("\ncommit %s\n", commit_id);
    char msg[MSG_SIZE];
    read_string_from_file(join(join(".beargit/", commit_id), "/.msg"), msg, MSG_SIZE);
    printf("\t%s\n", msg);
    read_string_from_file(join(join(".beargit/", commit_id), "/.prev"), commit_id, COMMIT_ID_SIZE);
  }
  printf("\n");
  return 0;
}
