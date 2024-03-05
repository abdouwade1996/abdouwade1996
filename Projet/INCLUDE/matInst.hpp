#ifndef MATINST_HPP
    #define MATINST_HPP
    #include <iostream>
    #include "parametres.hpp"
    #include <vector>
    
    class MatInst
    {
    private:
        std::vector<double> sousDiagInst;
        std::vector<double> diagInst;     
        std::vector<double> surDiagInst; 
        int taille;                       

    public:
        // Constructeur
        MatInst(int taille) : taille(taille) {}

        MatInst(std::vector<double> a, std::vector<double> b, std::vector<double> c);

        MatInst(std::vector<std::vector<double>> matriceTridiagInst, int taille) : taille(taille)
        {
            for (int i = 0; i < taille; i++)
            {
                diagInst.push_back(matriceTridiagInst[i][i]);
                sousDiagInst.push_back(matriceTridiagInst[i][i - 1]);
                surDiagInst.push_back(matriceTridiagInst[i][i + 1]);
            }
        }

        // getters et setters
        int getTaille() const { return taille; }

        double getDiagInst(int i) const { return diagInst[i]; }

        double getSousDiagInst(int i) const { return sousDiagInst[i]; }

        double getSurDiagInst(int i) const { return surDiagInst[i]; }

        // Méthode pour calculer la matrice tridiagonale
        std::vector<std::vector<double>> matriceTridiagInst() const;

        // Méthode pour calculer le second membre
        std::vector<double> FInst() const;

        // Destructeur
        ~MatInst()
        {
            diagInst.clear();
            sousDiagInst.clear();
            surDiagInst.clear();
        }
    };
    
#endif
