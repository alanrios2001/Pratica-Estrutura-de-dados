#include <iostream>
#include <sstream>
#include <string>
#include <string.h>
#include <Windows.h>
using namespace std;


class P_Proc {

	int n_lines;
	int text_len;

	//estrutura 1: estrutura a entrada pelos tokens de cada frase
	typedef struct Node_data_length {
		int length;
	}Node_data_length;

	typedef struct Node_data_lines {
		int line;
		struct Node_data_lines* next;
	}Node_data_lines;

	typedef struct Node_data_count {
		int count;
	}Node_data_count;

	typedef struct Node_tokens {
		char text[29];
		struct Node_tokens* next;
		struct Node_data_length* text_length;
		struct Node_data_lines* lines_occ;
		struct Node_data_count* count;
	}Node_tokens;

	//

	//estrutura 2: estrutura com ramo principal com tamanho de cada palavra
	typedef struct Node_tokens_second {
		char token[29];
		Node_tokens_second* next;
	}Node_tokens_second;

	typedef struct Node_lenght_main {
		int token_lenght;
		Node_lenght_main* next;
		Node_tokens_second* tokens_second;
	}Node_lenght;


public:
	Node_tokens* l_token;
	Node_lenght_main* l_lenght;

	void run_debug(void) {
		//debug
		cout << "----------primeira estrutura de dados----------" << endl;
		Node_tokens* head = l_token;
		while (head != NULL) {
			Node_data_lines* head_occ = head->lines_occ;
			cout << "token: " << head->text << endl;
			cout << "	tamanho: " << head->text_length->length << endl;;
			cout << "	ocorrencias: " << head->count->count << endl;
			cout << "	linhas em que ocorre: ";
			while (head_occ != NULL) {
				cout << head_occ->line << " ";
				head_occ = head_occ->next;
			}
			cout << "" << endl;
			head = head->next;
		}
		cout << "----------segunda estrutura de dados----------" << endl;
		Node_lenght_main* head2 = l_lenght;
		while (head2 != NULL) {
			Node_tokens_second* tokens = head2->tokens_second;
			cout << "tamanho da palavra: " << head2->token_lenght << endl;
			cout << "	palavras: ";
			while (tokens != NULL) {
				cout << tokens->token << " ";
				tokens = tokens->next;
			}
			cout << endl;
			head2 = head2->next;
		}
	}



	P_Proc(int n_lines) {
		//system("chcp 1252 > nul");
		SetConsoleCP(1252);
		SetConsoleOutputCP(1252);


		l_token = NULL;
		l_lenght = NULL;

		string text_line;
		string ext_word;
		//ler linhas no input e processar
		for (int i = 0; i <= n_lines; i++) { //"<=" pois o cmd d· double click quando inserir primeiro input
			getline(cin, text_line);
			processar(text_line, i);
		}

		Node_tokens* head = l_token;
		while (head != NULL) {
			if (consulta_2(head->text_length->length) == false) {
				create_new_node_lenght(head->text_length->length, head->text);
			}
			else {
				update_node_lenght(head->text_length->length, head->text);
			}
			head = head->next;
		}
	}


	void processar(string text_line, int line_number) {
		string ext_word;
		int len_count = 0;
		int length = text_line.length();
		char comAcentos[] = "‰·‚‡„ÈÍÎËÌÓÔÏˆÛÙÚı¸˙˚˘Á";
		char semAcentos[] = "aaaaaeeeeiiiiooooouuuuc";

		//percorre todos os caracteres da linha, tokeniza, e deixa palavras padronizadas(minuscula e sem acento)
		for (int j = 0; j < length; j++) {
			if (text_line[j] != ' ' && text_line[j] != ',' && text_line[j] != '.') {
				char caracter = tolower(text_line[j]);

				//trata as palavras acentuadas
				for (int u = 0; u < strlen(comAcentos); u++) {
					if (comAcentos[u] == caracter) {
						caracter = semAcentos[u];
					}
				}

				ext_word = ext_word + caracter;
				len_count += 1;

				//verifica se È o ultimo caracter
				if (j == length - 1) {
					//consulta a ultima palavra da linha, caso ja exista, adiciona o numero da linha apontado pelo token
					if (consulta(ext_word) == true) {
						update_token_node(ext_word, line_number);
						ext_word.clear();
						len_count = 0;
					}
					//caso contrario, outro nÛ È criado
					else {
						create_node(len_count, ext_word, line_number);
						ext_word.clear();
						len_count = 0;
					}
				}
			}
			else {
				//caso encontre qualquer caracter "proibido", a palavra formada È consultada, caso ja exista, adiciona o numero da linha apontado pelo token
				if (consulta(ext_word) == true) {
					update_token_node(ext_word, line_number);
					ext_word.clear();
					len_count = 0;
				}
				//caso contrario, outro nÛ È criado
				else {
					create_node(len_count, ext_word, line_number);
					ext_word.clear();
					len_count = 0;
				}
			}
		}
	}


	void create_node(int len, string token, int line) {
		Node_tokens* new_node = (Node_tokens*)malloc(sizeof(Node_tokens));
		Node_data_length* token_length = (Node_data_length*)malloc(sizeof(Node_data_length));
		Node_data_count* token_count = (Node_data_count*)malloc(sizeof(Node_data_count));

		token_length->length = len;
		token_count->count = 1;

		strcpy_s(new_node->text, token.c_str());
		new_node->text_length = token_length;
		new_node->count = token_count;
		new_node->lines_occ = create_lines_store_data(line);

		//insere strings em ordem alfabetica
		Node_tokens* head = l_token;
		Node_tokens* head_ant = NULL;
		while (head != NULL) {
			if (token.compare(head->text) < 0) {
				if (head_ant == NULL) {
					new_node->next = l_token;
					l_token = new_node;
					break;
				}
				else {
					new_node->next = head;
					head_ant->next = new_node;
					break;
				}
			}
			head_ant = head;
			head = head->next;

		}

		if (head == NULL) {
			if (head_ant != NULL) {
				head_ant->next = new_node;
				new_node->next = head;
			}
			if (head_ant == NULL) {
				new_node->next = l_token;
				l_token = new_node;
			}
		}
	}

	Node_data_lines* create_lines_store_data(int line) {
		Node_data_lines* l_lines = NULL;
		Node_data_lines* new_node = (Node_data_lines*)malloc(sizeof(Node_data_lines));
		new_node->line = line;
		new_node->next = l_lines;
		l_lines = new_node;
		return l_lines;
	}

	Node_data_lines* get_update_lines_store_data(int line, Node_data_lines* l_lines) {
		Node_data_lines* new_node = (Node_data_lines*)malloc(sizeof(Node_data_lines));
		if (consulta_lines(line, l_lines) == true) {
			return l_lines;
		}
		new_node->line = line;
		new_node->next = l_lines;
		return new_node;
	}

	bool consulta_lines(int line, Node_data_lines* l_lines) {
		Node_data_lines* head = l_lines;
		while (head != NULL && head->line != line) {
			head = head->next;
		}
		if (head == NULL) {
			return false;
		}
		return true;
	}

	void update_token_node(string word, int line) {
		Node_tokens* head = l_token;
		while (head != NULL && head->text != word) {
			head = head->next;
		}
		head->count->count += 1;
		Node_data_lines* new_node = get_update_lines_store_data(line, head->lines_occ);
		head->lines_occ = new_node;

	}


	bool consulta(string palavra) {
		Node_tokens* head = l_token;
		while (head != NULL && head->text != palavra) {
			head = head->next;
		}

		if (head == NULL) {
			return false;
		}
		return true;
	}

	//funcoes 2 estrutura

	bool consulta_2(int num) {
		Node_lenght_main* head = l_lenght;
		while (head != NULL && head->token_lenght != num) {
			head = head->next;
		}

		if (head == NULL) {
			return false;
		}
		return true;
	}

	void create_new_node_lenght(int len, string palavra) {
		Node_tokens_second* l_tokens_second = NULL;
		Node_lenght_main* new_node = (Node_lenght_main*)malloc(sizeof(Node_lenght_main));
		Node_tokens_second* new_node2 = (Node_tokens_second*)malloc(sizeof(Node_tokens_second));
		new_node->token_lenght = len;
		strcpy_s(new_node2->token, palavra.c_str());
		new_node2->next = l_tokens_second;
		l_tokens_second = new_node2;
		new_node->tokens_second = l_tokens_second;
		new_node->next = l_lenght;
		l_lenght = new_node;
	}

	void update_node_lenght(int len, string palavra) {
		Node_tokens_second* new_node = (Node_tokens_second*)malloc(sizeof(Node_tokens_second));
		strcpy_s(new_node->token, palavra.c_str());

		Node_lenght_main* head = l_lenght;
		while (head->token_lenght != len) {
			head = head->next;
		}

		Node_tokens_second* head_token = head->tokens_second;
		Node_tokens_second* head_ant = NULL;

		while (head_token != NULL) {
			head_ant = head_token;
			head_token = head_token->next;
		}

		head_ant->next = new_node;
		new_node->next = head_token;
	}
	//fim pre processamento

	//funcoes para funcionamento app
	void linhas_da_palavra(string palavra) {
		Node_tokens* head = l_token;
		while (head != NULL && head->text != palavra) {
			head = head->next;
		}

		if (head != NULL) {
			Node_data_lines* head_lines = head->lines_occ;
			while (head_lines != NULL) {
				if (head_lines->next != NULL) {
					cout << head_lines->line << " ";
				}
				else {
					cout << head_lines->line << endl;
				}
				head_lines = head_lines->next;
			}
		}
	}

	void palavras_por_tamanho(int tamanho) {
		Node_lenght_main* head = l_lenght;
		while (head != NULL && head->token_lenght != tamanho) {
			head = head->next;
		}
		if (head != NULL) {
			Node_tokens_second* head_token = head->tokens_second;
			while (head_token != NULL) {
				cout << head_token->token << endl;
				head_token = head_token->next;
			}
		}
	}

	void ocorrencias_palavra(string palavra) {
		Node_tokens* head = l_token;

		while (head != NULL && head->text != palavra) {
			head = head->next;
		}

		if (head == NULL) {
			cout << palavra << " " << 0 << endl;
		}
		else {
			cout << palavra << " " << head->count->count << endl;
		}
	}

	void listar_palavras(){
		Node_tokens* head = l_token;

		while (head != NULL) {
			cout << head->text<<endl;
			head = head->next;
		}
	}

	void comando_o_caso_c(string maior_que, string menor_que) {
		Node_tokens* head = l_token;
		while(head!=NULL){
			if(maior_que.compare(head->text) <= 0 && menor_que.compare(head->text) >= 0){
				cout << head->text<<endl;
			}
			head = head->next;
		}
	}

	void comando_o_caso_d(string maior_que, string menor_que) {
		bool control = true;
		Node_tokens* head_marca = NULL;

		while (control == true) {
			Node_tokens* head = l_token;
			Node_tokens* head_ant = NULL;
			while (head != head_marca) {
				head_ant = head;
				head = head->next;
			}
			head_marca = head_ant;
			if (head_ant != NULL) {
				if (maior_que.compare(head_ant->text) <= 0 && menor_que.compare(head_ant->text) >= 0) {
					cout << head_ant->text << endl;
				}
			}
			if (head_ant == NULL) {
				control = false;
			}

		}
	}
};


class App {

public:

	App() {
		int numero_de_linhas;
		cin >> numero_de_linhas;
		receber_comandos(numero_de_linhas);
	}

	void receber_comandos(int numero_de_linhas) {
		P_Proc texto(numero_de_linhas);
		string comando;
		while (comando != "e") {
			getline(cin, comando);
			if (comando == "l") {
				string palavra;
				getline(cin, palavra);
				texto.linhas_da_palavra(palavra);
				//texto.run_debug();
			}
			if (comando == "x") {
				int tamanho;
				cin>>tamanho;
				texto.palavras_por_tamanho(tamanho);
			}
			if (comando == "n") {
				string palavra;
				getline(cin, palavra);
				texto.ocorrencias_palavra(palavra);
			}
			if (comando == "o") {
				string comando2;
				getline(cin, comando2);
				if (comando2 == "c") {
					string palavra1;
					string palavra2;
					getline(cin, palavra1);
					getline(cin, palavra2);
					texto.comando_o_caso_c(palavra1,palavra2);
				}
				else if (comando2 == "d") {
					string palavra1;
					string palavra2;
					getline(cin, palavra1);
					getline(cin, palavra2);
					texto.comando_o_caso_d(palavra2, palavra1);
				}
			}
			if (comando == "a") {
				texto.listar_palavras();
			}
			if (comando == "debug") {
				texto.run_debug();
			}
		}
	}
};

int main()
{
	App app;
}