#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>

using namespace std;

bool BrainFuck (string & tokens);
int main(int argc, char *argv[]) {
	if (argc < 2) {  
		cerr << "EE: No input file." << endl;  
		return -1;  
	}
	ifstream file_in (argv[1]);  
	string tokens;  
	if (!file_in) {  
		cerr << "EE: Can not open file: " << argv[1] << endl;  
		return -1;  
	} 
	 while (!file_in.eof ()) {  
		string str_tmp;  
		file_in >> str_tmp;  
		tokens.insert (tokens.length (), str_tmp);  
	}  
	file_in.close ();  
	if (!BrainFuck(tokens)) {  
		return -1;  
	}  
  
	return 0;  
}  
bool BrainFuck(string & tokens) {
	int pointer = 0;
	int layer;
	char work[100000];
	layer = 0;
	for (uint32_t location = 0; location < tokens.length (); ++location) {
		if ('[' == tokens[location]) ++layer;
		if (']' == tokens[location]) --layer;
	}
	if (layer < 0) {
		cerr << "EE: Expect token '[' but not found." << endl;
		return false;
	}else if (layer > 0) {
		cerr << "EE: Expect token ']' but not found." << endl;
		return false;
	}
	for (uint32_t location = 0; location < tokens.length (); ++location) {
		switch (tokens[location]) {
		case '<': --pointer;
			if (pointer < 0) pointer = strlen(work);
			break;
		case '>': ++pointer; break;
		case '-': --work[pointer]; break;
		case '+': ++work[pointer]; break;
		case '.': cout << work[pointer]; break;
		case ',': work[pointer] = getch(); break;
		case '[': layer = 1;
			if (work[pointer]) break;
			while (layer) {
					++location;
				if ('[' == tokens[location]) ++layer;
				if (']' == tokens[location]) --layer;
			}
			--location;
			break;
		case ']':
			layer = 1;
			if (!work[pointer]) break;
			while (layer) {
				--location;
				if (']' == tokens[location]) ++layer;
				if ('[' == tokens[location]) --layer;
			}
			break;
		default:
			cerr << endl << "EE: Can not analyze token: "
			<< tokens[location] << endl;
			return false;
		}
	}
	return true;
}