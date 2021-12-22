#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define MAX_DATA 512
#define MAX_ROWS 100

struct Address {
	int		id;
	int		set;
	char	name[MAX_DATA];
	char	email[MAX_DATA];
};

struct Database {
	struct Address	rows[MAX_ROWS];
};

struct Connection {
	FILE			*file;
	struct Database	*db;
};

void				die(const char *message);
void				Address_print(struct Address *addr);
void				Address_get(const int id);
void				Address_set(int id, const char *name, const char *email);
void				Address_delete(int id);
void				Database_load(void);
void				Database_write(void);
void				Database_open(char *filename, int mode);
void				Database_close(void);
void				Database_create(void);
void				Database_list(void);

static struct Connection	*g_conn;

int	main(int argc, char *argv[])
{
	if (argc < 3)
		die("USAGE: ex17 <dbfile> <action> [action params]");

	char				*filename = argv[1];
	int					action = argv[2][0];
	int					id = 0;

	Database_open(filename, action);
	if (argc > 3)
		id = atoi(argv[3]);
	if (id >= MAX_ROWS)
		die("There's not that many records.");
	switch (action) {
		case 'c':
			Database_create();
			Database_write();
			break;
		case 's':
			if (argc != 6)
				die("Need id, name, email to set.");
			Address_set(id, argv[4], argv[5]);
			Database_write();
			break;
		case 'g':
			if (argc != 4)
				die("Need an id to get.");
			Address_get(id);
			break;
		case 'd':
			if (argc != 4)
				die("Need an id to delete");
			Address_delete(id);
			Database_write();
			break;
		case 'l':
			Database_list();
			break;
		default:
			die("Invalid action: c=create, g=get, s=set, d=del, l=list");
	}
	
	Database_close();

	return (0);
}

void	die(const char *message)
{
	if (errno) {
		perror(message);
	} else {
		printf("ERROR: %s\n", message);
	}
	Database_close();
	exit(1);
}

void	Address_set(int id, const char *name,
		const char *email)
{
	struct Address	*addr = &g_conn->db->rows[id];

	if (addr->set == 1)
		die("Already set, delete it first.");
	addr->set = 1;
	// WARNING: bug, read the "How To Break It" and fix this
	char	*res = strncpy(addr->name, name, MAX_DATA);
	if (res == NULL)
		die("Name copy failed.");
	res = strncpy(addr->email, email, MAX_DATA);
	if (res == NULL)
		die("Email copy failed.");
	addr->name[MAX_DATA - 1] = '\0';
	addr->email[MAX_DATA - 1] = '\0';
}

void	Address_get(const int id)
{
	struct Address	*addr = &g_conn->db->rows[id];

	if (addr->set == 0)
		die("Id is not set.");
	else
		Address_print(addr);
}

void	Address_print(struct Address *addr)
{
	printf("%d %s %s\n", addr->id, addr->name, addr->email);
}

void	Address_delete(int id)
{
	struct Address	addr = {.id = id, .set = 0};
	g_conn->db->rows[id] = addr;
}

void	Database_open(char *filename, int mode)
{
	g_conn = malloc(sizeof(struct Connection));
	if (g_conn == NULL)
		die("Memory error.");

	g_conn->db = malloc(sizeof(struct Database));
	if (g_conn->db == NULL)
		die("Memory error.");

	if (mode == 'c') {
		g_conn->file = fopen(filename, "w");
	} else {
		g_conn->file = fopen(filename, "r+");

		if (g_conn->file)
			Database_load();
	}

	if (g_conn->file == NULL)
		die("Failed to open the file.");
}

void	Database_close(void)
{
	if (g_conn)
	{
		if (g_conn->db)
			free(g_conn->db);
		if (g_conn->file)
			fclose(g_conn->file);
		free(g_conn);
	}
}

void	Database_load(void)
{
	int		rc = fread(g_conn->db, sizeof(struct Database), 1, g_conn->file);

	if (rc != 1)
		die("Failed to load database.");
}

void	Database_write(void)
{
	rewind(g_conn->file);

	int		rc = fwrite(g_conn->db, sizeof(struct Database), 1, g_conn->file);

	if (rc != 1)
		die("Failed to write.");

	rc = fflush(g_conn->file);
	if (rc == EOF)
		die("Cannot flush database.");
}

void	Database_create(void)
{
	struct Database	*db = g_conn->db;
	struct Address	preset;
	int				id;

	for (id = 0; id < MAX_ROWS; ++id)
	{
		// make a prototype to initialize it
		preset = (struct Address){.id = id, .set = 0};
		// then just assign it
		db->rows[id] = preset;
	}
}

void	Database_list(void)
{
	assert(g_conn->db != NULL);
	struct Database	*db = g_conn->db;
	struct Address	*itr;
	int				id;

	for (id = 0; id < MAX_ROWS; ++id)
	{
		itr = &db->rows[id];
		if (itr->set == 0)
			continue;
		Address_print(itr);
	}
}
