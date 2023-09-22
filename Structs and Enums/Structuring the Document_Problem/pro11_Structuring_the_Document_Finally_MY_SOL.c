/******
 * Solution Author: Alaa Ashraf Fawzy 
 * Date:            22 September 2023
 * Discription:     "Structuring the Document" problem on Hackerrank is a coding application on [structs and dynamic memory allocation]
 * *****/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define MAX_CHARACTERS 1005
#define MAX_PARAGRAPHS 5

struct word {
    char* data;
};

struct sentence {
    struct word* data;
    int word_count;//denotes number of words in a sentence
};

struct paragraph {
    struct sentence* data  ;
    int sentence_count;//denotes number of sentences in a paragraph
};

struct document {
    struct paragraph* data;
    int paragraph_count;//denotes number of paragraphs in a document
};

struct document get_document(char* text) {

    struct document Doc;
    Doc.paragraph_count=0;
    Doc.data=NULL;

    struct paragraph Para;
    Para.sentence_count=0;
    Para.data=NULL;

    struct sentence Sen;
    Sen.word_count=0;
    Sen.data=NULL;

    struct word Word;
    Word.data=NULL;
    int char_count =0;


    int n_loop=0;
    int i_char=0;
    int j_w=0;
    int k_sen=0; 
    int t_para=0;


    while((*(text+n_loop))!='\0') {
       
        switch (*(text+n_loop)) {
        case ' ':
  
        Word.data[i_char]='\0';
        Sen.word_count++;
        Sen.data=realloc(Sen.data,Sen.word_count*sizeof(struct word));
        Sen.data[j_w]=Word;
        j_w++;
        Word.data=NULL;
        char_count=0;
        i_char=0;

        break;
        case '.':

        Word.data[i_char]='\0';
        Sen.word_count++;
        Sen.data=realloc(Sen.data,Sen.word_count*sizeof(struct word));
        Sen.data[j_w]=Word;
        j_w++;
        Word.data=NULL;
        char_count=0;
        i_char=0;

        Para.sentence_count++;
        Para.data=realloc(Para.data,Para.sentence_count*sizeof(struct sentence));
        Para.data[k_sen]=Sen;
        k_sen++;
        Sen.data=NULL;
        Sen.word_count=0;
        j_w=0;

        if (*(text+n_loop+1)=='\0'){

           
            Doc.paragraph_count++;
            Doc.data = realloc(Doc.data , Doc.paragraph_count*sizeof(struct paragraph));
            Doc.data[t_para] = Para;
            t_para++;
            Para.data=NULL;
            Para.sentence_count=0;
            k_sen=0;
        }

        break;
        case '\n':
        

        Doc.paragraph_count++;
        Doc.data = realloc(Doc.data , Doc.paragraph_count*sizeof(struct paragraph));
        Doc.data[t_para] = Para;
        t_para++;
        Para.data=NULL;
        Para.sentence_count=0;
        k_sen=0;

        break;
        case 'a' ... 'z':
            

            char_count++;
            Word.data=realloc(Word.data,char_count*sizeof(char));
            Word.data[i_char]=text[n_loop];
            i_char++;
            
            
        break;
        case 'A' ... 'Z':

            char_count++;
            Word.data=realloc(Word.data,char_count*sizeof(char));
            Word.data[i_char]=text[n_loop];
            i_char++;
            
        break;
        case '0' ... '9':
            

            char_count++;
            Word.data=realloc(Word.data,char_count*sizeof(char));
            Word.data[i_char]=text[n_loop];
            i_char++;
            
            
        break;
        }

    n_loop++;
    }
    

    return Doc;
}

struct word kth_word_in_mth_sentence_of_nth_paragraph(struct document Doc, int k, int m, int n) {
    return Doc.data[n-1].data[m-1].data[k-1];
}

struct sentence kth_sentence_in_mth_paragraph(struct document Doc, int k, int m) { 
    return Doc.data[m-1].data[k-1];
}

struct paragraph kth_paragraph(struct document Doc, int k) {
    
    return Doc.data[k-1];
}


void print_word(struct word w) {
    printf("%s", w.data);
}

void print_sentence(struct sentence sen) {
    for(int i = 0; i < sen.word_count; i++) {
        print_word(sen.data[i]);
        if (i != sen.word_count - 1) {
            printf(" ");
        }
    }
}

void print_paragraph(struct paragraph para) {
    for(int i = 0; i < para.sentence_count; i++){
        print_sentence(para.data[i]);
        printf(".");
    }
}

void print_document(struct document doc) {
    for(int i = 0; i < doc.paragraph_count; i++) {
        print_paragraph(doc.data[i]);
        if (i != doc.paragraph_count - 1)
            printf("\n");
    }
}

char* get_input_text() {	
    int paragraph_count;
    scanf("%d", &paragraph_count);

    char p[MAX_PARAGRAPHS][MAX_CHARACTERS], doc[MAX_CHARACTERS];
    memset(doc, 0, sizeof(doc));
    getchar();
    for (int i = 0; i < paragraph_count; i++) {
        scanf("%[^\n]%*c", p[i]);
        strcat(doc, p[i]);
        if (i != paragraph_count - 1)
            strcat(doc, "\n");
    }

    char* returnDoc = (char*)malloc((strlen (doc)+1) * (sizeof(char)));
    strcpy(returnDoc, doc);
    return returnDoc;
}

int main() 
{
    char* text = get_input_text();
    struct document Doc = get_document(text);

    int q;
    scanf("%d", &q);

    while (q--) {
        int type;
        scanf("%d", &type);

        if (type == 3){
            int k, m, n;
            scanf("%d %d %d", &k, &m, &n);
            struct word w = kth_word_in_mth_sentence_of_nth_paragraph(Doc, k, m, n);
            print_word(w);
        }

        else if (type == 2) {
            int k, m;
            scanf("%d %d", &k, &m);
            struct sentence sen= kth_sentence_in_mth_paragraph(Doc, k, m);
            print_sentence(sen);
        }

        else{
            int k;
            scanf("%d", &k);
            struct paragraph para = kth_paragraph(Doc, k);
            print_paragraph(para);
        }
        printf("\n");
    }     
}