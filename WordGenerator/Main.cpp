#include "TrigrammeGenerator.hpp"

#include <iostream>
#include <fstream>

int main(int argc, char *argv[]) {
	using namespace std;
	//*****************arguments*****************

	if (argc >= 1) {
		for (int i = 0; i < argc; i++) {
			if (strcmp(argv[i], "--help") == 0)
			{
				cout << "Arg 1 : Relative File Path of the name source" << endl;
				cout << "Arg 2 : [Optional] Number of words to generate" << endl;
				cout << "Arg 3 : [Optional; 1+] Precision of the algorithm" << endl;
				return EXIT_SUCCESS;
			}
		}
	}

	if (argc < 2) {
		cerr << "You must enter at least a file path. You can also enter the number of worlds you want to generate." << endl;
		return 0;
	}

	unsigned int nbr = 5;
	unsigned int precision = 2;

	if (argc > 2) {
		if (sscanf_s(argv[2], "%d", &nbr) == EOF || nbr < 0)
		{
			cerr << "Second argument must be a  positive number." << endl;
			nbr = 5;
		}
	}
	if (argc > 3) {
		if (sscanf_s(argv[3], "%d", &precision) == EOF || precision < 2)
		{
			cerr << "Third argument (precision) must be at least 2." << endl;
			precision = 5;
		}
	}

	//*****************traitement*****************

	ifstream fichier(argv[1], ios::in);  // on ouvre le fichier en lecture

	if (fichier)  // si l'ouverture a réussi
	{
		TrigrammeGenerator wg(precision);
		string ligne;
		while (getline(fichier, ligne))  // récupérer tous les mots
		{
			wg.FormatWord(ligne);
			wg.AddWord(ligne);
		}
		fichier.close();  // on ferme le fichier

		for (size_t i = 0; i < nbr; i++)
		{
			//std::cout << wg.ComputeWord() << std::endl;
			std::cout << wg.ComputeWordWithUnsetLength() << std::endl;
		}
	}
	else {
		cerr << "Impossible d'ouvrir le fichier !" << endl;
	}

#if _DEBUG
	std::cin.get();
#endif // DEBUG

	return EXIT_SUCCESS;
}