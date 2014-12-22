
#ifndef LIBCSV_H__
#define LIBCSV_H__
#include <stdlib.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

#define CSV_MAJOR 0
#define CSV_MINOR 1
#define CSV_RELEASE 0


/* Character values */
#define CSV_TAB    0x09
#define CSV_SPACE  0x20
#define CSV_CR     0x0d
#define CSV_LF     0x0a
#define CSV_COMMA  0x2c
#define CSV_QUOTE  0x22

/**
 
  buffer
  fmt - (from gwan: csv, tsv / text, html, json) 
  
  Table <- Rows <- Cell
  Table <- Columns <- Cell
  
  read data into memory
  or 
  parse and store only pointer/offset in file
*/

typedef struct Cell { 	
	int type; // value, string or maybe currency, time
	// char * key;	
	union {
		int value;   
		char* value;  
		//time_t value;
		//currency_t value;
   }
} Cell

/** line of the CSV as a dynamic array of strings */
typedef struct Row { 
	Cell	**cell; /// cell array
	//char **text;	/// cell array
	size_t size;			/// space allocation (the Max lines)
	size_t length;		/// Number of rows
	int bound[2];	///  Index of the first significant cell width and significant field
} Row; 

Row *new_row(void);				/// создать новую пустую строку
Row *row_add(Row *row,char *s);	/// добавить запись (текст) в конец строки
Row *row_parse(Row *row,char *s,char **saveptr);/// разобрать из текста в соотв. с csvformat
Row *row_clear(Row *row,void (*cb)(char *));	/// очистить строку

char *row_cell(Row *,int);

typedef struct Table {
	Row **row;
	int sz;			/// allocated in row[]
	int len;		/// used in row[]
	int width;		/// ширина таблицы (= макс.ширина строк в row[])
	int height;		/// длина таблицы
	int bound[4];	/// индексы первой значащей ячейки и ширина/длина значащего поля
} Table;

/* xxx_table() - constructors */
Table *new_table(void);
Table *read_table(Table *,FILE *);
Table *parse_table(Table *,char *s,char **saveptr);

/* table_xxx() - methods */
Table *table_add(Table *,Row *);
Row *table_row(Table *,int);
char *table_cell(Table *,int,int);


typedef struct CsvFormat {
	char *fs;	// field separator (default ", and;")
	char *rs;	// record separator (default \ n or \ n \ r)
	int quoting; // framing quotes (default - as it is)
	int omit_trail_cells;	// =1 if you can omit empty cells at the end of lines
	int omit_trail_rows;	// =1 if you can omit the blank lines at the end of the file
} CsvFormat;

extern CsvFormat csvformat;

#define SPACES " \t\v\f\r\n"
#define BLANK " \t\v\f"



/*
https://github.com/nektomk/csvcut/blob/master/csvzip.c

Table *tab;
int row,col;
  csvformat.omit_trail_cells=1; 
  csvformat.omit_trail_rows=0; 

tab=read_table(NULL,stdin); 
 	if (tab==NULL) { 
 		fprintf(stderr,"error reading table\n"); 
 		exit(EXIT_FAILURE); 
} 
int colspan,rowspan;
for(row=0;row<tab->width;row++) {
	colspan=0;
	for(col=0;col<tab->height;col++) {
		text=table_cell(tab,col,row);
		colspan++;
	}
	rowspan++;
}

------------
http://gwan.ch/source/sqlite.c
// ----------------------------------------------------------------------------
// pre-defined output formats (TEXT, CSV, JSON, XML)
// ----------------------------------------------------------------------------
typedef struct fmt_s
{
   char *header, *footer,       
        *bol, *eol, // begin and end of line
        *prefix[2], *suffix[2];
}fmt_t;

fmt_t fmt_text = 
{ 
   "", "",
   "\t", "\n",
   {"\t", "\t"},
   {"\t", "\t"}
};

fmt_t fmt_csv = 
{ 
   "", "",
   "", "\n",
   {"", ""},
   {",", ","}
};

http://gwan.com/source/ab.c

http://gwan.ch/api

// a key-value store
typedef struct
{
   char  name[12];  // kv name (optional)
   u32   flags;     // kv flags (optional)
   long  root;      // kv storage
   long  nbr_items; // nbr of items in kv (atomically maintained)
   long  lock;      // global kv lock (not used by G-WAN, only for users)
   void *delfn;     // kv_del() callback (to free memory of custom records)
   void *recfn;     // persistence callback (to format records saved to disk)
   void *pool;      // if specified, used for memory allocations
} kv_t;

// a tuple (key-value, and key-value lengths)
// if(!klen) then kv_add()/kv_get()/kv_del()/kv_do() do klen = strlen(klen);
typedef struct
{
   char *key, *val; // value length limit: available memory
   union {
   u32   flags;   // kv_add() flags: set to zero for compatibility
   u32   in_use;  // if(KV_REFCOUNT) ref_count atomically incr. by kv_get()
   };
   u32   klen;    // key length limit: 4 GB
} kv_item;



---

enum JSN_TYPE
{
   jsn_FALSE = 0, jsn_TRUE, jsn_NULL, jsn_NUMBER, jsn_STRING,
   jsn_NODE, jsn_ARRAY
};

typedef struct jsn_s
{
   struct jsn_s *prev;    // node's prev item (parent if node is 1st child)
   struct jsn_s *next;    // node's next item (list ends with NULL)
   struct jsn_s *child;   // node's child node (NULL if none)
   char         *name;    // node's name
   int           type;    // node's value type (see JSN_TYPE above)
   union {
   char         *string;  // value 'type' == jsn_STRING
   s64           integer; // value 'type' == jsn_INTEGER
   double        real;    // value 'type' == jsn_REAL
   };
   u64           x;       // context
   long          y;       // context
} jsn_t;

https://github.com/wuakitv/playback_handler/blob/master/0.0.0.0_8080/%230.0.0.0/csp/data_uri.c
https://github.com/wuakitv/playback_handler/blob/master/0.0.0.0_8080/%230.0.0.0/csp/fractal.c
https://github.com/wuakitv/playback_handler/blob/master/0.0.0.0_8080/%230.0.0.0/csp/captcha.c
https://github.com/wuakitv/playback_handler/blob/master/0.0.0.0_8080/%230.0.0.0/csp/charts.c
https://github.com/wuakitv/playback_handler/blob/master/0.0.0.0_8080/%230.0.0.0/csp/chart.c

https://github.com/wuakitv/playback_handler/blob/master/0.0.0.0_8080/%230.0.0.0/csp/auth_oauth.c_

https://github.com/wuakitv/playback_handler/blob/master/0.0.0.0_8080/%230.0.0.0/csp/bigtable.c


https://bitbucket.org/xi/libyaml

typedef struct yaml_document_s {

    // The document nodes. 
    struct {
         The beginning of the stack. 
        yaml_node_t *start;
         The end of the stack. 
        yaml_node_t *end;
        The top of the stack. 
        yaml_node_t *top;
    } nodes;
	}
	 // The list of tag directives. 
    struct {
        // The beginning of the tag directives list. 
        yaml_tag_directive_t *start;
        //The end of the tag directives list. 
        yaml_tag_directive_t *end;
    } tag_directives;


*/

struct csv {
	unsigned char * entry_buf;   /* Entry buffer */
	void *pool;      // if specified, used for memory allocations

};


/* Function Prototypes */
int csv_init(struct csv_parser *p, unsigned char options);

int csv_fini(struct csv_parser *p );

void csv_free(struct csv_parser *p);

int csv_error(struct csv_parser *p);

char * csv_strerror(int error);

size_t csv_parse(struct csv_parser  *p );



#ifdef __cplusplus
}
#endif

#endif
