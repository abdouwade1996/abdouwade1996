#ifndef PARAMETRE_HPP
#define PARAMETRE_HPP
#include <string>

class Parametre
{
    public:
        int M; 
        double Cp, rho, Te, hc, kappa, TFinal, N;
        bool stationary;
        double Lx, Ly, Lz, Phi_p, Mx, My, Mz;
        std::string chaine;
        // Constructeur
        Parametre(std::string nomFichier);
};

#endif