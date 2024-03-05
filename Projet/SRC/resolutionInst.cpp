#include "../INCLUDE/resolutionInst.hpp"

#include <vector>
#include <iostream>
#include <iomanip>
#include <vector>
#include <fstream>
#include <cmath>

// fonction Affichage pour tester l'affichage de la matrice
void AfMat(std::vector<std::vector<double>> matrice)
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

// INSTANCIATION DE LA CLASSE PARAMETRE
Parametre par("../PARAMETRE/simu.cfg");

// Initialisation des paramètres
double kappaInsta = par.kappa;
double hInsta = par.Lx / par.M;
double hcInsta = par.hc;
double SInsta = par.Ly * par.Lz;
double pInsta = 2 * (par.Ly + par.Lz);
int MInsta = par.M;
double TeInsta = par.Te;
double Phi_pInsta = par.Phi_p;
double rhoIsnta = par.rho;
double CpIsnta = par.Cp;
double TF = par.TFinal;
int NInsta = par.N;
double deltaT = TF / NInsta;
int MxInsta = par.Mx;
int MyInsta = par.My;
int MzInsta = par.Mz;

// METHODES
ResolutionInst::ResolutionInst(MatInst matInsta, int taille)
{
    std::vector<double> bInstaRes;
    std::vector<double> cInstaRes;
    // remplissage des vecteurs b et c
    // vecteur b
    bInstaRes.push_back(matInsta.getDiagInst(0));
    cInstaRes.push_back(matInsta.getSurDiagInst(0) / bInstaRes[0]);

    for (int k = 1; k < taille - 1; k++)
    {
        bInstaRes.push_back(matInsta.getDiagInst(k) - matInsta.getSousDiagInst(k - 1) * cInstaRes[k - 1]);
        cInstaRes.push_back(matInsta.getSurDiagInst(k) / bInstaRes[k]);
    }
    bInstaRes.push_back(matInsta.getDiagInst(taille - 1) - matInsta.getSousDiagInst(taille - 2) * cInstaRes[taille - 2]);

    // remplissage des vecteurs diagonale de L et surDiagonale de U
    for (int i = 0; i < taille; i++)
    {
        diagInstL.push_back(bInstaRes[i]);
    }
    for (int i = 0; i < taille - 1; i++)
    {
        surDiagInstU.push_back(cInstaRes[i]);
    }
}

// Méthode FactoLU() pour le cas instationnaire
std::vector<MatInst> ResolutionInst::FactoLU(const MatInst &matInsta) const
{
    int taille = MInsta;
    std::vector<std::vector<double>> LInsta(taille, std::vector<double>(taille, 0));
    std::vector<std::vector<double>> UInsta(taille, std::vector<double>(taille, 0));

    // Remplissage de la matrice L
    for (int i = 0; i < MInsta; i++)
    {
        LInsta[i][i] = diagInstL[i];
    }
    for (int i = 1; i < MInsta; i++)
    {
        LInsta[i][i - 1] = matInsta.getSousDiagInst(i - 1);
    }

    // Remplissage de la matrice U
    for (int i = 0; i < MInsta; i++)
    {
        UInsta[i][i] = 1;
    }
    for (int i = 0; i < MInsta - 1; i++)
    {
        UInsta[i][i + 1] = surDiagInstU[i];
    }

    // Création des objets MatInst pour L et U
    MatInst LMatrix(LInsta, MInsta);
    MatInst UMatrix(UInsta, MInsta);

    std::vector<MatInst> LU;
    LU.push_back(LMatrix);
    LU.push_back(UMatrix);

    return LU;
}

// Méthode LYFInst()
std::vector<double> ResolutionInst::LYFInst(std::vector<double> Y, const MatInst &matInsta, int taille, std::vector<double> F) const
{
    // calcul de Y
    Y.push_back(F[0] / diagInstL[0]);

    for (int k = 1; k < taille; k++)
    {
        Y.push_back((F[k] - matInsta.getSousDiagInst(k) * Y[k - 1]) / diagInstL[k]);
    }

    return Y;
}

// Méthode pour résoudre UX = Y
std::vector<double> ResolutionInst::UXYInst(std::vector<double> Y, int taille) const
{
    // calcul de X
    std::vector<double> X(taille, 0);
    X[taille - 1] = Y[taille - 1];

    for (int k = taille - 2; k >= 0; k--)
    {
        X[k] = Y[k] - surDiagInstU[k] * X[k + 1];
    }

    return X;
}

// surchage de l'opérateur * entre deux vecteurs
std::vector<double> operator*(const std::vector<double> &a, const std::vector<double> &b)
{
    std::vector<double> res;
    for (int i = 0; i < b.size(); i++)
    {
        res.push_back(a[i] * b[i]);
    }
    return res;
}

// surchage de l'opérateur + entre deux vecteurs
std::vector<double> operator+(const std::vector<double> &a, const std::vector<double> &b)
{
    std::vector<double> res;
    for (int i = 0; i < b.size(); i++)
    {
        res.push_back(a[i] + b[i]);
    }
    return res;
}

// méthode resoudreInst() pour résoudre le système instationnaire
std::vector<std::vector<double>> ResolutionInst::resoudreInst(MatInst matInsta, int taille) const
{
    // initialisation de la solution
    std::vector<double> T0;
    std::vector<std::vector<double>> TInstaRes(NInsta, std::vector<double>(taille, 0));
    for (int i = 0; i < taille; i++)
    {
        T0.push_back(TeInsta);
    }

    // creation du vecteur CFL
    std::vector<double> CFL;
    CFL.push_back(0);
    for (int i = 1; i < taille - 1; i++)
    {
        CFL.push_back((rhoIsnta * CpIsnta) / (deltaT));
    }
    CFL.push_back(0);

#ifdef DEBUG
    // affichage du vecteur CFL
    std::cout << "\nCFL : " << std::endl;
    for (int i = 0; i < taille; i++)
    {
        std::cout << CFL[i] << "\n";
    }
#endif

    // calcul de LU
    std::vector<MatInst> LU = FactoLU(matInsta);

#ifdef DEBUG
    // affichage de la matrice L et U pour vérifier
    std::cout << "\nMatrice L : " << std::endl;
    AfMat(LU[0].matriceTridiagInst());
    std::cout << "\nMatrice U : " << std::endl;
    AfMat(LU[1].matriceTridiagInst());
#endif

    // calcul de T^n+1 en fonction de T^n
    for (int n = 1; n < NInsta; n++)
    {
        // création du vecteur F
        std::vector<double> Y;
        std::vector<double> YInsta;

        // appel de la méthode LYFInst()
        Y = LYFInst(YInsta, LU[0], taille, matInsta.FInst() + CFL * T0);

#ifdef DEBUG
        // affichage de la solution
        std::cout << "\nYInsta : " << std::endl;
        for (int i = 0; i < taille; i++)
        {
            std::cout << Y[i] << "\n";
        }
#endif

        // appel de la méthode UXYInst()
        std::vector<double> X(taille, 0);
        T0 = UXYInst(Y, taille);

#ifdef DEBUG
        // affichage de la solution
        std::cout << "\nT0 : " << std::endl;
        for (int i = 0; i < taille; i++)
        {
            std::cout << T0[i] << " ";
        }
        std::cout << std::endl;
#endif

        // // remplissage de la solution
        for (int i = 0; i < taille; i++)
        {
            TInstaRes[n][i] = T0[i];
        }
    }

#ifdef DEBUG
    // affichage la dernière température
    std::cout << "\nTInstaRes : " << std::endl;
    for (int i = 0; i < taille; i++)
    {
        std::cout << TInstaRes[NInsta - 1][i] << " ";
    }
    std::cout << std::endl;
#endif

    return TInstaRes;
}

// méthode ecritureCSVInst() pour écrire dans un fichier CSV pour le flux constant
void ResolutionInst::ecritureCSVInst(std::vector<std::vector<double>> Solve, std::string nomFichier) const
{
    std::ofstream fichier(nomFichier, std::ios::out | std::ios::trunc);

    if (fichier)
    {
        fichier << "x"
                << ","
                << "t = 15s"
                << ","
                << "t = 30s"
                << ","
                << "t = 60s"
                << ","
                << "t = 90s"
                << ","
                << "t = 150s"
                << ","
                << "t = 210s"
                << std::endl;

        for (int i = 0; i < MInsta; i++)
        {
            fichier << i * hInsta << "," << Solve[15][i] << "," << Solve[30][i] << "," << Solve[60][i] << "," << Solve[90][i] << "," << Solve[150][i] << "," << Solve[210][i] << std::endl;
        }
        fichier.close();

        std::cout << "Ecriture dans le fichier " << nomFichier << " réussie !" << std::endl;
    }
    else
    {
        std::cout << "Erreur lors de l'ouverture du fichier " << nomFichier << std::endl;
    }
}

// méthode VTKParPasDeTemps() pour écrire les fichiers VTK pour chaque pas de temps dans un même dossier
void ResolutionInst::VTKParPasDeTemps(std::vector<std::vector<double>> Solve, int pasDeTemps)
{
    for (int t = 0; t < pasDeTemps; t++)
    {
        std::string nomFichier = "../VTK/INSTATIONNAIRE/masolution" + std::to_string(t) + ".vtk";
        std::ofstream fichier(nomFichier, std::ios::out | std::ios::trunc);

        if (fichier)
        {
            fichier << "# vtk DataFile Version 2.0" << std::endl;
            fichier << "vtk output" << std::endl;
            fichier << "ASCII" << std::endl;
            fichier << "DATASET STRUCTURED_GRID" << std::endl;
            fichier << "DIMENSIONS " << MxInsta << " " << MyInsta << " " << MzInsta << std::endl;
            fichier << "POINTS " << MxInsta * MyInsta * MzInsta << " float" << std::endl;

            // Ecriture des coordonnées des points
            for (int k = 0; k < MzInsta; k++)
            {
                for (int j = 0; j < MyInsta; j++)
                {
                    for (int i = 0; i < MxInsta; i++)
                    {
                        fichier << i << " " << j << " " << k << std::endl;
                    }
                }
            }

            // fichier << "POINT_DATA " << MxInsta * MyInsta * MzInsta << std::endl;
            // fichier << "FIELD FieldData 1" << std::endl;
            // fichier << "sol1 1 " << MxInsta * MyInsta * MzInsta << " float" << std::endl;

            // // Enfin, on met la valeur du champ pour chaque point en respectant l’ordre qui a été utilisé précédemment avec le maillage
            // int k = 0, xk;
            // double a, b;
            // double hx = par.Lx / MxInsta;
            // double hy = par.Ly / MyInsta;
            // double hz = par.Lz / MzInsta;

            // for (int i = 0; i < MxInsta; i++)
            // {
            //     //localisation du point xi00 dans le maillage 1D (i.e. trouver k tel que xi00 ∈ [xk, xk+1])
            //     double xi00 = i * hx;
            //     for (int j = 0; j < MInsta; j++)
            //     {
            //         double xk = j * hInsta;
            //         if (xi00 >= xk && xi00 <= xk + hInsta)
            //         {
            //             k = j;
            //             break;
            //         }
            //     }

            //     // calcul de a et b
            //     double temp = a * xi00 + b;
            //     Solve[t][i] = temp;
            // }

            // // Ecriture des valeurs du champ
            // std::vector<double> temps = {15, 30, 60, 90, 150, 210};

            fichier << "POINT_DATA " << MxInsta * MyInsta * MzInsta << std::endl;
            fichier << "SCALARS sol" << t << " float" << std::endl;
            fichier << "LOOKUP_TABLE default" << std::endl;

            for (int k = 0; k < MzInsta; k++)
            {
                for (int j = 0; j < MyInsta; j++)
                {
                    for (int i = 0; i < MxInsta; i++)
                    {
                        fichier << Solve[t][i + MxInsta * (j + MyInsta * k)] << std::endl;
                    }
                }
            }

            fichier.close();

            if (t == pasDeTemps - 1)
            {
                std::cout << "Ecriture dans le fichier " << nomFichier << " réussie !" << std::endl;
            }
        }

        else
        {
            std::cout << "Erreur lors de l'ouverture du fichier " << nomFichier << std::endl;
        }
    }
}