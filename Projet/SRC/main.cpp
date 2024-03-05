#include <iostream>
#include "../INCLUDE/parametres.hpp"
#include "../INCLUDE/matrice.hpp"
#include "../INCLUDE/resolution.hpp"
#include "../INCLUDE/matInst.hpp"
#include "../INCLUDE/resolutionInst.hpp"
#include <vector>
#include <iomanip>

// fonction Affichage
void afficheMatrice(std::vector<std::vector<double>> matrice)
{
    for (int i = 0; i < matrice.size(); i++)
    {
        for (int j = 0; j < matrice.size(); j++)
        {
            std::cout << std::setw(12) << matrice[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "\ntaille de la matrice = " << matrice.size() << std::endl;
}

// affichage du vecteur
void afficheVecteur(std::vector<double> vecteur)
{
    for (int i = 0; i < vecteur.size(); i++)
    {
        std::cout << vecteur[i] << " ";
    }
    std::cout << "\ntaille du vecteur = " << vecteur.size() << std::endl;
}

int main(int argc, char *argv[])
{
    //lire parametres.cfg à l'exécution
    if (argc < 2)
    {
        std::cout << "Usage: " << argv[0] << " ../PARAMETRE/simu.cfg" << std::endl;
        return 1;
    }
    Parametre param(argv[1]);

#ifdef DEBUG
    std::cout << "M = " << param.M << std::endl;
    std::cout << "N = " << param.N << std::endl;
    std::cout << "Lx = " << param.Lx << std::endl;
    std::cout << "Ly = " << param.Ly << std::endl;
    std::cout << "Lz = " << param.Lz << std::endl;
#endif

    std::cout << "\n::::::::::::::::::::Modéle Stationnaire:::::::::::::::::::\n" << std::endl;
    // Initialisation de la matrice
    std::vector<double> a;
    std::vector<double> b;
    std::vector<double> c;

    Matrice matrice(a, b, c);

    // test de la méthode matriceTridiagonale()
    std::vector<std::vector<double>> matriceTridiagonale = matrice.matriceTridiagonale();

    // test de la méthode secondMembre()
    std::vector<double> secondMembre = matrice.secondMembre();

#ifdef DEBUG
    std::cout << "\nmatrice tridiagonale A :" << std::endl;
    afficheMatrice(matriceTridiagonale);

    std::cout << "\nsecond membre F :" << std::endl;
    afficheVecteur(secondMembre);
#endif

    // test de la méthode resolutionLU()
    Resolution resolution(matrice, param.M);

    // test de la méthode decompositionLU()
    resolution.decompositionLU(matrice, param.M);

    // test de la méthode resoudreLYF()
    std::vector<double> Y = resolution.resoudreLYF(matrice, param.M);

    // test de la méthode resoudreUXY()
    std::vector<double> X = resolution.resoudreUXY(Y, param.M);

    // test de la méthode solutionExacte()
    std::vector<double> solutionExacte = resolution.solutionExacte();

    // test de la méthode ecrireFichier() pour dans le dossier CSV
    resolution.ecrireFichier(X, "../CSV/stationnaire.csv", solutionExacte);

    // test de la méthode writeVTKFile()
    resolution.writeVTKFile(X, "../VTK/stationnaire.vtk");

    std::cout << "\n::::::::::::::::::::Modéle Instationnaire:::::::::::::::::\n" << std::endl;

    // Initialisation de la matrice instationnaire
    std::vector<double> aInst;
    std::vector<double> bInst;
    std::vector<double> cInst;

    MatInst matriceInst(aInst, bInst, cInst);

    // test de la méthode matriceTridiagInst()
    std::vector<std::vector<double>> matriceTridiagonaleInst = matriceInst.matriceTridiagInst();
    #ifdef DEBUG
    afficheMatrice(matriceTridiagonaleInst);
    #endif

    // test de la méthode FInst()
    std::vector<double> FInst = matriceInst.FInst();
    #ifdef DEBUG
    afficheVecteur(FInst);
    #endif

    // test de la méthode matriceTridiagInst()
    ResolutionInst resolutionInst(matriceInst, param.M);

    // test de la méthode decompositionLUInst()
    // resolutionInst.LUInst(matriceInst, param.M);

    // test de la méthode resoudreInst(MatInst matInsta, int taille)
    std::vector<std::vector<double>> TInstaRes = resolutionInst.resoudreInst(matriceInst, param.M);
    // afficheVecteur(YInst);

    // test de la méthode ecritureCSVInst()
    resolutionInst.ecritureCSVInst(TInstaRes, "../CSV/instationnaire.csv");

    

    resolutionInst.VTKParPasDeTemps(TInstaRes, param.N);
    
    
    return 0;
}