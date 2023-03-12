// TP5.cpp : définit le point d'entrée de l'application.
//

#include "TP5.h"

using namespace std;

int main(){
	// ----- Déclaration des variables -----

	map<int, tuple<int,int>> mapColis;
	vector<string> listeVilles;
	vector<vector<int>> matriceDistance;
	int capaciteCamion = 0;
	int nombreColisDispo = 0;
	int nombreDeVilles = 0;

	// ----- Introduction -----

	// ----- Question 1 -----
	cout << "\t\t\t\t\tReponse a la question 1 : " << endl;
	cout << "Pour nous la meilleure structure pour resoudre le probleme 1 est une map avec en cle les index (noms) des colis. Et pour le probleme 2 le mieux est d'utiliser des vectors pour les villes et afin de sauvegarder la matrice nous pouvons utiliser un vector de vectors." << endl;
	cout << endl << endl;
	// ----- Fin question 1 -----

	// ----- Question 2 -----
	cout << "\t\t\t\t\tReponse a la question 2 : " << endl;
	ifstream fluxColis("C:/Users/audre/Source/Repos/TP5/infos/5colis30capacite.txt"); //ouverture du ficher des colis
	ifstream fluxVilles("C:/Users/audre/Source/Repos/TP5/infos/4villes.txt"); // ouverture du ficher des villes

	cout << "\t\t\t\t\tProbleme 1 : " << endl << endl;

	if (fluxColis) {

		int element;               //|
		int i = 0;                 //|
		int indice = 0;            //| déclarations de toutes les variables nécéssaires
		int consommation = 0;      //|
		int benefice = 0;          //|
		tuple <int, int> VolBenef; //|

		while (fluxColis >> element) { //tant qu'il y a du texte à lire
			if (nombreColisDispo == 0 && capaciteCamion != 0) {
				nombreColisDispo = element; //objetDisponible prend la deuxieme valeur du fichier
			}
			else if (capaciteCamion == 0) {
				capaciteCamion = element; //capacite prend la premiere valeur du fichier
			}
			else {
				switch (i) { //recupération de l'élément en fonction de là où il doit aller
				case 0: indice = element;
					i++;
					break;
				case 1:
					consommation = element;
					i++;
					break;
				case 2: benefice = element;
					i = 0;
					break;
				}
				if (benefice != 0) {
					VolBenef = make_tuple(consommation, benefice);
					mapColis.insert(pair<int, tuple<int, int>>(indice, VolBenef)); //on insert dans la map les informations qu'on a recolté précédement
					indice = consommation = benefice = 0; //reset de toutes les infos
				}
			}
			
		}
		// Map Colis OK !
		//affichage de la map des colis
		cout << "La camion a une capacite de : " << capaciteCamion;
		cout << "\nLe nombre d'objet disponible est : " << nombreColisDispo << endl;
		map<int, tuple<int,int>>::iterator itr;
		cout << "\nLa map mapColis est :\n";
		cout << "INDEX\tCONSO\tBENEF\n";
		for (itr = mapColis.begin(); itr != mapColis.end(); ++itr) {
			cout << itr->first << '\t' << get<0>(itr->second) << "\t" << get<1>(itr->second)
				<< '\n';
		}
		cout << endl << endl;
	}
	else {
		cout << "ERREUR: Impossible d'ouvrir le fichier en lecture." << endl; //en cas d'erreur d'ouverture du fichier
	}

	cout << "\t\t\t\t\tProbleme 2 : " << endl << endl;

	if (fluxVilles) {

		string nomDeVille = ""; //|
		string element;         //|
		int colonne = 1;        //|  déclaration de toutes les variables nécéssaires 
		int ligne = 0;          //|
		bool init = false;      //|
		

		while (fluxVilles >> element) {//tant qu'il y a quelque chose a lire 
			if (nombreDeVilles == 0) { //nombreDeViles prends la premiere valeur du fichier
				nombreDeVilles = stoi(element);
			}
			else if (listeVilles.size() != nombreDeVilles) { //tant que le nombreDeVilles n'est pas atteint on va ajoute l'element qui est le nom d'une ville au vecteur qui contient toutes les villes 
				listeVilles.push_back(element);
			}
			else if (listeVilles.size() == nombreDeVilles && init == false){ //ici on doit initialiser le vecteur de toute les distance en jouant avec le nombreDeVille
				vector<int> temp;
				temp.assign(nombreDeVilles, 0);
				for (int i = 0; i < nombreDeVilles; i++) {
					matriceDistance.assign(nombreDeVilles, temp);
				}
				init = true;
				matriceDistance.at(0).at(0) = stoi(element); //ajout de la premiere valeur a la matrice
			}
			else {
				matriceDistance.at(ligne).at(colonne) = stoi(element); //on complete le reste de la matrice 
				colonne++;
				if (colonne == 4) {// modulo 4
					colonne = 0;
					ligne++;
				}
			}
		}

		cout << "Le nombre de villes est : " << nombreDeVilles << endl << endl;

		for (auto villes : listeVilles) {
			cout << villes << "  ";
		}

		cout << "\n\nLa matrice des distances est la suivante :" << endl;
		for (int i = 0; i < 4; i++)						// |				
		{												// |
			for (int j = 0; j < 4; j++)					// |
			{											// |
				cout << matriceDistance[i][j] << " ";	// | affichage de la matrice
			}											// |
			cout << endl;								// |
		}												// |
		
	}
	else {
		cout << "ERREUR: Impossible d'ouvrir le fichier en lecture." << endl; //en cas d'erreur d'ouverture du fichier
	}
	// ----- Fin question 2 -----
	
	// ------------------------------------------------------------------------------------------------------------------

	// ----- Question 3 & 4 ----- 

	cout << "\t\t\t\t\tReponse a la question 3 et 4: " << endl;

	cout << "\t\t\t\t\tProbleme 1 : " << endl << endl;

	multimap<float, int> mapColisQ3;			// |
	vector<int> colisDansLeCamion;				// |
												// | 
	float benefvol = 0;							// |
	int benef = 0;								// | Déclaration des variables nécéssaires
	int vol = 0;								// |
	int index = -1;								// |
	int beneficeTotal = 0;						// |

	for (auto itr = mapColis.begin(); itr != mapColis.end(); ++itr) {		// |
		benef = get<1>(itr->second);									// |
		vol = get<0>(itr->second);										// |
		benefvol = static_cast<float>(benef)/static_cast<float>(vol);	// | Création de la mapColisQ3
		mapColisQ3.insert(pair<float, int>(benefvol, itr->first));		// |
	}																	// |


	cout << "Matrice mapColisQ3 (a l'envers):" << endl;
	for (auto iter = mapColisQ3.rbegin(); iter != mapColisQ3.rend(); ++iter) {		// |
		cout << iter -> first << "/" << iter -> second << endl;				// | Affichage de la mapColisQ3
	}																		// |

	cout << endl;

	auto it = mapColisQ3.rbegin();
	
	while(capaciteCamion > 0 && it != mapColisQ3.rend()){	// |
		index = it->second;									// |
		if (capaciteCamion > get<0>(mapColis[index])) {		// |
			capaciteCamion -= get<0>(mapColis[index]);		// |
			colisDansLeCamion.push_back(index);				// |
			++it;											// | Chargement du camion
		}													// |
		else {												// |
			++it;											// |
		}													// |
	}														// |

	cout << "Affichage des colis dans le camion : " << endl;	// |
	for (auto i: colisDansLeCamion) {							// | Affichage du contenu du camion et calcul du bénéfice total
		cout << i << " ";										// |
		beneficeTotal += get<1>(mapColis[i]);					// |
	}															// |

	cout << endl << endl << "Le benefice total sera de : " << beneficeTotal << " euros" << endl;


	// ------------------------------------------------------------------------------------------------------------------

	cout << "\t\t\t\t\tProbleme 2 : " << endl << endl;

	int resteVilles = nombreDeVilles - 1;
	index = 0;
	int distanceInterMin = 1000;
	int distanceMinVoyage = 0;
	int saveIndex = 0;
	vector <int> backupVilleRetour;
	vector <string> listeVilleVoyage;

	while (resteVilles >= 0) {

		distanceInterMin = 1000;

		if (resteVilles == nombreDeVilles - 1) {									// si c'est la premiere itération
						
			listeVilleVoyage.push_back(listeVilles.at(0));

			for (int i = 0; i < nombreDeVilles; i++) {
				backupVilleRetour.push_back(matriceDistance.at(i).at(index));	// enregister les distances dans un vecteur de backup
				
				matriceDistance.at(i).at(index) = 0;							// mettre la colonne de la ville de départ à 0	
			}																	
		}																		
		
		for (auto valeur : matriceDistance.at(index)) {							// |
			if (valeur <= distanceInterMin && valeur != 0) {					// |
				distanceInterMin = valeur;										// | trouver la valeur minimale de la ligne dans distanceInterMid
			}																	// |
		}																		// |


		auto trouverIndexVille = find(matriceDistance.at(index).begin(), matriceDistance.at(index).end(), distanceInterMin);	// | trouver l'index de la ville d'arriver du voyage intermédiaire 
		index = distance(matriceDistance.at(index).begin(), trouverIndexVille);													// |
		
		if (resteVilles == 1) {
			saveIndex = index;
		}

		if (resteVilles == 0) {
			distanceMinVoyage += backupVilleRetour.at(saveIndex);
			listeVilleVoyage.push_back(listeVilles.at(0));
			break;
		}
		
		distanceMinVoyage += distanceInterMin;		//ajouter la distance intermédiaire à la distance totale
		listeVilleVoyage.push_back(listeVilles.at(index));
		

		for (int i = 0; i < matriceDistance.size(); i++) {	// |
			matriceDistance.at(i).at(index) = 0;			// | mettre la colonne de la ville d'arrivée du voyage intermédiaire à 0
		}													// |


		resteVilles--; //reduire le nombre de villes à visiter 
	}

	cout << "La liste des villes que nous allons visiter en prenant le plus court chemin : " << endl;

	for (auto ville : listeVilleVoyage) {
		cout << ville << " ";
	}

	cout << endl << endl;

	cout << "La distance totale du voyage le plus court : " << distanceMinVoyage << endl;
	
	// ----- Fin de la question 3 et 4 -----


	return 0; //fin du main
}



