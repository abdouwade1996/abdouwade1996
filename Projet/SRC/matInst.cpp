#include "../INCLUDE/matInst.hpp"
#include <vector>
#include "../INCLUDE/resolution.hpp"
#include "../INCLUDE/matrice.hpp"

Parametre para("../PARAMETRE/simu.cfg");

// Initialisation des paraètres
double kappaInst = para.kappa;
double hInst = para.Lx / para.M;
double hcInst = para.hc;
double SInst = para.Ly * para.Lz;
double pInst = 2 * (para.Ly + para.Lz);
int MInst = para.M;
double TeInst = para.Te;
double Phi_pInst = para.Phi_p;

// paramètres pour le calcul de la matrice
double rhoIsnt = para.rho;
double CpIsnt = para.Cp;
double TFinal = para.TFinal;
int N = para.N;
int Mx = para.Mx;
int My = para.My;
int Mz = para.Mz;
double dt = TFinal / N;

MatInst::MatInst(std::vector<double> aInst, std::vector<double> bInst, std::vector<double> cInst)
{
    // remplissage des vecteurs a, b et c
    // vecteur a
    for (int i = 1; i < MInst - 1; i++)
    {
        aInst.push_back(-kappaInst / (hInst * hInst));
    }
    aInst.push_back(-kappaInst / hInst);

    // vecteur b
    bInst.push_back(kappaInst / hInst);
    for (int i = 1; i < MInst - 1; i++)
    {
        bInst.push_back(2 * kappaInst / (hInst * hInst) + ((hcInst * pInst) / SInst) + ((rhoIsnt * CpIsnt) / dt));
    }
    bInst.push_back(kappaInst / hInst);

    // vecteur c
    cInst.push_back(-kappaInst / hInst);
    for (int i = 1; i < MInst - 1; i++)
    {
        cInst.push_back(-kappaInst / (hInst * hInst));
    }

    // remplissage des vecteurs diagonale, sousDiagonale et surDiagonale
    for (int i = 0; i < MInst; i++)
    {
        diagInst.push_back(bInst[i]);
        sousDiagInst.push_back(aInst[i]);
        surDiagInst.push_back(cInst[i]);
    }
}

std::vector<std::vector<double>> MatInst::matriceTridiagInst() const
{
    // initialisation de la matrice tridiagonale
    std::vector<std::vector<double>> matrixInst(MInst, std::vector<double>(MInst, 0));

    // remplissage de la matrice tridiagonale
    for (int i = 0; i < MInst; i++)
    {
        matrixInst[i][i] = diagInst[i];
    }
    for (int i = 0; i < MInst - 1; i++)
    {
        matrixInst[i][i + 1] = surDiagInst[i];
    }
    for (int i = 1; i < MInst; i++)
    {
        matrixInst[i][i - 1] = sousDiagInst[i];
    }

    return matrixInst;
}

// Méthode pour calculer juste le F' instationnaire mais pas tout le second membre
std::vector<double> MatInst::FInst() const
{
    // initialisation du vecteur F instationnaire
    std::vector<double> FInst;

    // remplissage du vecteur F instationnaire
    FInst.push_back(Phi_pInst);
    for (int i = 1; i < MInst - 1; i++)
    {
        FInst.push_back((hcInst * pInst * TeInst) / SInst);
    }
    FInst.push_back(0);

    return FInst;
}