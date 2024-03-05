#include <iostream>
#include <fstream>
#include "../INCLUDE/parametres.hpp"

// constructeur
Parametre::Parametre(std::string nomFichier)
{
    std::ifstream fichier(nomFichier);
    if (fichier)
    {
        fichier >> chaine >> Lx >> chaine >> Ly >> chaine >> Lz;
        fichier >> chaine >> M;
        fichier >> chaine >> Phi_p;
        fichier >> chaine >> hc;
        fichier >> chaine >> rho;
        fichier >> chaine >> Cp;
        fichier >> chaine >> kappa;
        fichier >> chaine >> Te;
        fichier >> chaine >> stationary;
        fichier >> chaine >> TFinal;
        fichier >> chaine >> N;
        fichier >> chaine >> Mx >> chaine >> My >> chaine >> Mz;
    }
    else
    {
        std::cout << "ERREUR: Impossible d'ouvrir le fichier en lecture." << std::endl;
    }

    fichier.close();
}