#include <iostream>
#include "../INCLUDE/resolution.hpp"
#include <vector>
#include "../INCLUDE/matrice.hpp"
#include <iomanip>
#include <fstream>
#include <sstream>
#include <cmath>

// fonction Affichage pour tester l'affichage de la matrice
void Aff(std::vector<std::vector<double>> matrice)
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

// fonction Affichage pour tester l'affichage du vecteur
void AffVec(std::vector<double> vecteur)
{
    for (int i = 0; i < vecteur.size(); i++)
    {
        std::cout << vecteur[i] << " ";
    }
    std::cout << "\ntaille du vecteur = " << vecteur.size() << std::endl;
}

// INSTATIAION DE LA CLASSE PARAMETRE
Parametre parametre("../PARAMETRE/simu.cfg");

// Initialisation des paramètres
double kappa = parametre.kappa;
double h = parametre.Lx / parametre.M;
double hc = parametre.hc;
double S = parametre.Ly * parametre.Lz;
double p = 2 * (parametre.Ly + parametre.Lz);
int M = parametre.M;
double Te = parametre.Te;
double Phi_p = parametre.Phi_p;
int MxSta = parametre.Mx;
int MySta = parametre.My;
int MzSta = parametre.Mz;
double Lx = parametre.Lx;
double Ly = parametre.Ly;
double Lz = parametre.Lz;

// constructeur
Resolution::Resolution(Matrice matrice, int taille)
{
    std::vector<double> b_star;
    std::vector<double> c_star;

    // Remplissage des vecteurs b_star et c_star
    b_star.push_back(matrice.getDiagonale(0));
    c_star.push_back(matrice.getSurDiagonale(0) / b_star[0]);

    for (int k = 1; k < taille - 1; k++)
    {
        b_star.push_back(matrice.getDiagonale(k) - matrice.getSousDiagonale(k - 1) * c_star[k - 1]);
        c_star.push_back(matrice.getSurDiagonale(k) / b_star[k]);
    }
    b_star.push_back(matrice.getDiagonale(taille - 1) - matrice.getSousDiagonale(taille - 2) * c_star[taille - 2]);

#ifdef DEBUG
    // affichage des vecteurs b_star et c_star
    std::cout << "\nb_star : ";
    AffVec(b_star);

    std::cout << "\nc_star : ";
    AffVec(c_star);
#endif

    // remplissage des diagonales de la matrice L et U
    for (int i = 0; i < taille; i++)
    {
        diagonaleL.push_back(b_star[i]);
    }

    for (int i = 0; i < taille - 1; i++)
    {
        surDiagonaleU.push_back(c_star[i]);
    }

#ifdef DEBUG
    std::cout << "\ndiagonaleL : ";
    AffVec(diagonaleL);

    std::cout << "\nsurDiagonaleU : ";
    AffVec(surDiagonaleU);
#endif
}

// Méthode de décomposition LU
void Resolution::decompositionLU(Matrice matrice, int taille)
{
    // Creation des matrices L et U de taille taille x taille et initialisation à 0
    std::vector<std::vector<double>> L(taille, std::vector<double>(taille, 0));
    std::vector<std::vector<double>> U(taille, std::vector<double>(taille, 0));

    // remplissage de la matrice L
    for (int i = 0; i < taille; i++)
    {
        L[i][i] = diagonaleL[i];
    }
    for (int i = 1; i < taille; i++)
    {
        L[i][i - 1] = matrice.getSousDiagonale(i - 1);
    }

    // remplissage de la matrice U
    for (int i = 0; i < taille; i++)
    {
        U[i][i] = 1;
    }
    for (int i = 0; i < taille - 1; i++)
    {
        U[i][i + 1] = surDiagonaleU[i];
    }

#ifdef DEBUG
    std::cout << "\nMatrice L : " << std::endl;
    Aff(L);

    std::cout << "\nMatrice U : " << std::endl;
    Aff(U);
#endif
}

// Méthode de résolution LY = F
std::vector<double> Resolution::resoudreLYF(Matrice matrice, int taille)
{
    // création du vecteur Y
    std::vector<double> Y;
    Y.push_back(matrice.secondMembre()[0] / diagonaleL[0]);

    for (int k = 1; k < taille; k++)
    {
        Y.push_back((matrice.secondMembre()[k] - matrice.getSousDiagonale(k - 1) * Y[k - 1]) / diagonaleL[k]);
    }

#ifdef DEBUG
    std::cout << "\nVecteur Y : " << std::endl;
    AffVec(Y);
#endif

    return Y;
}

// Méthode de résolution UX = Y
std::vector<double> Resolution::resoudreUXY(std::vector<double> Y, int taille)
{
    // création du vecteur X
    std::vector<double> X(taille, 0);
    X[taille - 1] = Y[taille - 1];

    for (int k = taille - 2; k >= 0; k--)
    {
        X[k] = Y[k] - surDiagonaleU[k] * X[k + 1];
    }

#ifdef DEBUG
    std::cout << "\nVecteur X : " << std::endl;
    AffVec(X);
#endif

    return X;
}

// méthode pour ecrire le fichier csv
void Resolution::ecrireFichier(std::vector<double> vecteur, std::string nomFichier, std::vector<double> TExacte)
{
    std::ofstream fichier(nomFichier, std::ios::out | std::ios::trunc);

    if (fichier)
    {
        // Ecriture de l'entête du fichier
        fichier << "x"
                << ","
                << "numeric"
                << ","
                << "exacte" << std::endl;

        // Ecriture dans le fichier
        for (int i = 0; i < vecteur.size(); i++)
        {
            fichier << i * h << "," << vecteur[i] << "," << TExacte[i] << std::endl;
        }
        fichier.close();

        std::cout << "Ecriture dans le fichier " << nomFichier << " réussie !" << std::endl;
    }
    else
    {
        std::cout << "Erreur à l'ouverture !" << std::endl;
    }
}

// méthode pour implémenter la solution exacte
std::vector<double> Resolution::solutionExacte()
{
    double a = (hc * p) / (kappa * S);
    double b = (Phi_p / kappa) * ((cosh(sqrt(a) * Lx)) / (sqrt(a) * sinh(sqrt(a) * Lx)));

    // création du vecteur solution exacte
    std::vector<double> TExacte;

    for (int i = 0; i < M; i++)
    {
        TExacte.push_back(Te + b * ((cosh(sqrt(a) * (Lx - i * h))) / (cosh(sqrt(a) * Lx))));
    }

#if 0
    std::cout << "\nVecteur solution exacte : " << std::endl;
    AffVec(TExacte);
#endif

    return TExacte;
}

// méthode pour écrire le fichier vtk
void Resolution::writeVTKFile(std::vector<double> vecteur, std::string fileName)
{
    std::ofstream fichier(fileName, std::ios::out | std::ios::trunc);

    if (fichier)
    {
        // Ecriture de l'entête du fichier
        fichier << "# vtk DataFile Version 2.0" << std::endl;
        fichier << "vtk output" << std::endl;
        fichier << "ASCII" << std::endl;
        fichier << "DATASET STRUCTURED_GRID" << std::endl;
        fichier << "DIMENSIONS " << MxSta << " " << MySta << " " << MzSta << std::endl;

        // On declare le nombre de points
        fichier << "POINTS " << MxSta * MySta * MzSta << " float" << std::endl;

        // Ecriture des points
        for (int k = 0; k < MzSta; k++)
        {
            for (int j = 0; j < MySta; j++)
            {
                for (int i = 0; i < MxSta; i++)
                {
                    fichier << i << " " << j << " " << k << std::endl;
                }
            }
        }

        // On commence par une section point data
        fichier << "POINT_DATA " << MxSta * MySta * MzSta << std::endl;

        // On ajoute une section FIELD
        fichier << "FIELD FieldData 1" << std::endl;

        // On ecrit le nom du champ
        fichier << "sol1 " << 1 << " " << MxSta * MySta * MzSta << " float" << std::endl;

        // Enfin, on met la valeur du champ pour chaque point en respectant l’ordre qui a été utilisé précédemment avec le maillage
        int k = 0, xk;
        double a, b;
        double hx = Lx / MxSta;

        for (int i = 0; i < MxSta; i++)
        {
            // localiser xi00 dans le maillage 1d (i.e. trouver k tel que xi00 ∈ [xk, xk+1])
            double xi00 = i * hx;
            for (int j = 0; j < M; j++)
            {
                double xk = j * h;
                if (xi00 >= xk && xi00 <= xk + h)
                {
                    k = j;
                    break;
                }
            }

            // calculer les coefficients de la droite y=ax+b passant par les points (xk, Tk) et (xk+1, Tk+1)
            a = (vecteur[k + 1] - vecteur[k]) / (h);
            b = vecteur[k] - a * k * h;

            // évaluer ˆTi = a xi00 + b
            vecteur[i] = a * xi00 + b;
        }

        // On met la valeur du champ pour chaque point en respectant l’ordre qui a été utilisé précédemment avec le maillage
        for (int k = 0; k < MzSta; k++)
        {
            for (int j = 0; j < MySta; j++)
            {
                for (int i = 0; i < MxSta; i++)
                {
                    fichier << vecteur[i] << std::endl;
                }
            }
        }

        fichier.close();

        std::cout << "Ecriture dans le fichier " << fileName << " réussie !" << std::endl;
    }
    else
    {
        std::cout << "Erreur à l'ouverture !" << std::endl;
    }
}