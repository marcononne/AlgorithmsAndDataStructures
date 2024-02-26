#include "skiplist.h"

// Compilazione:     make build/main_skiplist
// Esecuzione:       build/main_skiplist <path to dictionary.txt> <path to correctme.txt>

static void read_quote(const char* path_to_dict, const char* path_to_corr_me);
static int find_index_of_first_valid_character(char *word);
static int find_index_to_split_word(char *word);
static SkipList * load_dictionary(const char* path_to_dic);

static void read_quote(const char* path_to_dict, const char* path_to_corr_me) {
   char *read_line_ptr;
   char buffer[1024], word[1024];
   int bufsize = 1024, i, stop, start;
   double time_spent;
   clock_t end, begin = clock();
   SkipList *dictionary = load_dictionary(path_to_dict);
   void* words;
   FILE *quote_ptr;
   

   quote_ptr = fopen(path_to_corr_me, "r");
   if(quote_ptr == NULL) {
      printf("Unable to open the file correctme.txt \n");
      exit(EXIT_FAILURE);
   }
   
   while(fgets(buffer, bufsize, quote_ptr) != NULL) {
      read_line_ptr = buffer;
      while((start = find_index_of_first_valid_character(read_line_ptr)) != -1) {
         read_line_ptr += start;
         stop = find_index_to_split_word(read_line_ptr);
         i=0;
         while(i<stop) {
            word[i] = *read_line_ptr;
            i++;
            read_line_ptr++;
         }
         word[i] = '\0';
         words = searchSkipList(dictionary, word);
         if(words == NULL)
            printf("%s \n", word);
      }
   }
   end = clock();
   time_spent = (double)(end-begin) / CLOCKS_PER_SEC;
   printf("Done in %f seconds \n------------------------------------------\n", time_spent);
   fclose(quote_ptr);
   skiplist_free_memory(dictionary);
}

static SkipList * load_dictionary(const char* path_to_dict) {
	char word[1024];
	FILE *dictionary;
	int words = 0;
   SkipList *dict_list = create_skipList(precedes_node_string);
   clock_t begin, end;
   double time_spent;

	dictionary = fopen(path_to_dict, "r");
	if(dictionary == NULL) {
		printf("Unable to open the file dictionary.txt \n");
      exit(EXIT_FAILURE);
	}

	while(fscanf(dictionary, "%s", word) != EOF) 
		words++;

	rewind(dictionary);
   
   printf("Loading dictionary... \n");
   begin = clock();
	for(int i=0; i<words; i++) {
		fscanf(dictionary, "%s", word);
	   insertSkipList(dict_list, strdup(word));
	}
   end = clock();
   time_spent = (double)(end-begin) / CLOCKS_PER_SEC;
   printf("Done in %f seconds \n------------------------------------------\n", time_spent);
	fclose(dictionary);
   return dict_list;
}
	
static int find_index_of_first_valid_character(char *w) {
	int i=0;
	while(!isalpha(w[i])) {
		if(w[i] == '\0')
			return -1;

		i++;
	}
	return i;
}

static int find_index_to_split_word(char *w) {
	int i=0;
	while(isalpha(w[i]))
		i++;
	return i;
}

int main(int argc, char const *argv[]) {
   if(argc < 3) {
      printf("Usage: ./main <path to dictionary.txt> <path to correctme.txt> \n");
      exit(EXIT_FAILURE);
   }
	read_quote(argv[1], argv[2]);
	return 0;
}
