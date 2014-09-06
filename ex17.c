#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define MAX_DATA 20
#define MAX_ROWS 3

//// DATA STRUCTURES ////

struct Address {
  int id;
  int set;
  char name[MAX_DATA];
  char email[MAX_DATA];
};

struct Database {
  struct Address rows[MAX_ROWS];
};

struct Connection {
  FILE *file;
  struct Database *db;
};

//// FUNCTIONS ////

void
die(const char *message)
// Terminate program with error message
{
  if (errno) {
    perror(message);
  } else {
    printf("ERROR: %s\n", message);
  }

  exit(1);
}

void
Address_print(struct Address *addr)
// Pretty print Address struct
{
  printf("%d %s %s\n",
	 addr->id,
	 addr->name,
	 addr->email
	 );
}

void Database_load(struct Connection *conn)
// Load db file into Database structure at conn->db
{
  int rc = fread(conn->db, sizeof(struct Database), 1, conn->file);
  if (rc != 1) die("Failed to load database.");
}

struct Connection *
Database_open(const char *filename, char mode)
// Create new connection structure
// with allocated memory for database
// fille with data from file
{
  struct Connection *conn = malloc(sizeof(struct Connection));
  if (!conn) die("Memory Error");

  conn->db = malloc(sizeof(struct Database));
  if(!conn->db) die("Memory Error");

  if (mode == 'c') {
    conn->file = fopen(filename, "w");
  } else {
    conn->file = fopen(filename, "r+");

    if (conn->file) {
      Database_load(conn);
    }
  }

  if(!conn->file) die("Faild to open file");

  return conn;
}

void
Database_close(struct Connection *conn)
// Close file descriptors and free memory
{
  if (conn) {
    if (conn->file) fclose(conn->file);
    if (conn->db)   free(conn->db);
    free(conn);
  }
}

void
Database_write(struct Connection *conn)
// write memory representation of db to file
{
  rewind(conn->file);

  int rc = fwrite(conn->db, sizeof(struct Database), 1, conn->file);
  if (rc != 1) die("Failed to write database.");

  rc = fflush(conn->file);
  if (rc == -1) die("Cannot flush database.");
}

void
Database_create(struct Connection *conn)
{
  for(int i = 0; i < MAX_ROWS; i++){
    // make a prototype address
    struct Address addr = { .id = i, .set = 0 };
    // and assign it to the i-th row
    conn->db->rows[i] = addr;
  }
}

void
Database_get(struct Connection *conn, int id)
{
  struct Address *addr = &conn->db->rows[id];

  if(addr->set) {
    Address_print(addr);
  } else {
    // die("Id is not set");
  }
}

void
Database_list(struct Connection *conn)
{
  for(int i=0; i<MAX_ROWS; i++){
    Database_get(conn,i);
  }
}

void
Database_delete(struct Connection *conn, int id)
{
  struct Address addr = {.id = id, .set = 0};
  conn->db->rows[id] = addr;
}

void
Database_set(struct Connection *conn, int id, const char *name, const char *email)
{
  struct Address *addr = &conn->db->rows[id];
  if (addr->set) die("Row %d already set, delete it first.");

  addr->set = 1;

  char *res = strncpy(addr->name, name, MAX_DATA);
  if(!res) die("Name copy failed");

  // manual 0-termination of resulting string
  if (MAX_DATA >0) addr->name[MAX_DATA -1] = '\0';

  res = strncpy(addr->email, email, MAX_DATA);
  if(!res) die("Name copy failed");

  // manual 0-termination of resulting string
  if (MAX_DATA >0) addr->email[MAX_DATA -1] = '\0';
}


int
main(int argc, char * argv[])
{
  if (argc <3) die("USAGE: ex17 <dbfile> <action> [action params]");

  char * filename = argv[1];
  char action = argv[2][0];
  int id = 0;
  if (argc > 3) id = atoi(argv[3]);
  if (id >= MAX_ROWS) die("There's not that many records.");

  struct Connection * conn = Database_open(filename, action);

  switch (action) {
  case 'c':
    Database_create(conn);
    Database_write(conn);
    break;

  case 's':
    Database_set(conn, id, argv[4], argv[5]);
    Database_write(conn);
    break;

  case 'g':
    Database_get(conn, id);
    break;

  case 'l':
    Database_list(conn);
    break;

  case 'd':
    Database_delete(conn, id);
    Database_write(conn);
    break;

  default:
    printf("%c",action);
    die("Invalid action");
  }

  Database_close(conn);
  return 0;
}
