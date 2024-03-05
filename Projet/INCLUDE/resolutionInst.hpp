#ifndef __RESOLUTIONINST_HPP__
#define __RESOLUTIONINST_HPP__

#include "matInst.hpp"
#include <vector>
#include "parametres.hpp"

class ResolutionInst
{
private:
    std::vector<double> diagInstL;    /**< Vecteur représentant la diagonale de la matrice */
    std::vector<double> surDiagInstU; /**< Vecteur représentant la sur-diagonale de la matrice */
    int taille;                       /**< Taille de la matrice */

public:
    // Constructeur
    ResolutionInst(std::vector<double> b_star, std::vector<double> c_star)
        : diagInstL(b_star), surDiagInstU(c_star) {}

    ResolutionInst(MatInst matInst, int taille);

    // getters et setters
    double getDiagInstL(int i) const { return diagInstL[i]; }

    double getSurDiagInstU(int i) const { return surDiagInstU[i]; }

    int getTaille() const { return taille; }

    void setDiagInstL(int i, double val) { diagInstL[i] = val; }

    void setSurDiagInstU(int i, double val) { surDiagInstU[i] = val; }

    // Méthodes de décomposition LU
    void LUInst(const MatInst &matInsta, int MInsta);

    // Méthodes de résolution LY = F
    std::vector<double> LYFInst(std::vector<double> Y, const MatInst &matInsta, int taille, std::vector<double> F) const;

    // Méthodes de résolution UX = Y
    std::vector<double> UXYInst(std::vector<double> Y, int taille) const;

    // Méthodes de résolution pour le système instationnaire
    std::vector<std::vector<double>> resoudreInst(MatInst matInsta, int taille) const;

    // Méthode pour la décomposition LU
    std::vector<MatInst> FactoLU(const MatInst &matInsta) const;


    //ecriture csv pour le cas instationnaire
    void ecritureCSVInst(std::vector<std::vector<double>> Solve, std::string nomFichier) const;

    void ecritureCSVFluxInst(std::vector<std::vector<double>> Solve, std::string nomFichier) const;

    void VTKParPasDeTemps(std::vector<std::vector<double>> Solve, int pasDeTemps);

    // Destructeur
    ~ResolutionInst()
    {
        diagInstL.clear();
        surDiagInstU.clear();
    }
};

#endif