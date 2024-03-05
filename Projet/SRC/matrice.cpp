#include <iostream>
#include "../INCLUDE/matrice.hpp"
#include <vector>

Parametre param("../PARAMETRE/simu.cfg");

// Initialisation des paramètres
double kappaSta = param.kappa;
double hSta = param.Lx / param.M;
double hcSta = param.hc;
double SSta = param.Ly * param.Lz;
double pSta = 2 * (param.Ly + param.Lz);
int MSta = param.M;
double TeSta = param.Te;
double Phi_pSta = param.Phi_p;

void afficheVec(std::vector<double> vecteur)
{
    for (int i = 0; i < vecteur.size(); i++)
    {
        std::cout << "vecteur" << i << " = " << vecteur[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "taille du vecteur = " << vecteur.size() << std::endl;
}

Matrice::Matrice(std::vector<double> a, std::vector<double> b, std::vector<double> c)
{
    // remplissage des vecteurs a, b et c
    // vecteur a
    for (int i = 1; i < MSta - 1; i++)
    {
        a.push_back(-kappaSta / (hSta * hSta));
    }
    a.push_back(-kappaSta / hSta);

    // vecteur b
    b.push_back(kappaSta / hSta);
    for (int i = 1; i < MSta - 1; i++)
    {
        b.push_back(2 * kappaSta / (hSta * hSta) + (hcSta * pSta) / SSta);
    }
    b.push_back(kappaSta / hSta);

    // vecteur c
    c.push_back(-kappaSta / hSta);
    for (int i = 1; i < MSta - 1; i++)
    {
        c.push_back(-kappaSta / (hSta * hSta));
    }

#ifdef DEBUG
    std::cout << "a : ";
    afficheVec(a);
    std::cout << "b : ";
    afficheVec(b);
    std::cout << "c : ";
    afficheVec(c);
#endif

    // remplissage des vecteurs diagonale, sousDiagonale et surDiagonale
    for (int i = 0; i < MSta; i++)
    {
        diagonale.push_back(b[i]);
    }
    for (int i = 0; i < MSta; i++)
    {
        sousDiagonale.push_back(a[i]);
    }
    for (int i = 0; i < MSta; i++)
    {
        surDiagonale.push_back(c[i]);
    }
}

std::vector<std::vector<double>> Matrice::matriceTridiagonale() const
{
    // creation de la matrice tridiagonale de taille MxM avec des 0
    std::vector<std::vector<double>> matrice(MSta, std::vector<double>(MSta, 0));

    // remplissage de la matrice tridiagonale
    for (int i = 0; i < MSta; i++)
    {
        matrice[i][i] = diagonale[i];
    }
    for (int i = 0; i < MSta - 1; i++)
    {
        matrice[i][i + 1] = surDiagonale[i];
    }
    for (int i = 1; i < MSta; i++)
    {
        matrice[i][i - 1] = sousDiagonale[i - 1];
    }

    return matrice;
}

std::vector<double> Matrice::secondMembre() const
{
    // creation du vecteur second membre
    std::vector<double> F;

    // remplissage du vecteur second membre
    F.push_back(Phi_pSta);
    for (int i = 1; i < MSta - 1; i++)
    {
        F.push_back(hcSta * pSta * TeSta / SSta);
    }
    F.push_back(0);

    return F;
}