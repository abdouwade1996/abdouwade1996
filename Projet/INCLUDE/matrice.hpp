#ifndef MATRICE_HPP
#define MATRICE_HPP

    #include <iostream>
    #include "parametres.hpp"
    #include <vector>

    class Matrice
    {
        private:
            std::vector<double> sousDiagonale; /**< Vecteur représentant la sous-diagonale de la matrice. */
            std::vector<double> diagonale;     /**< Vecteur représentant la diagonale de la matrice. */
            std::vector<double> surDiagonale;  /**< Vecteur représentant la sur-diagonale de la matrice. */
            int taille;                        

        public:
            // Constructeur
            Matrice(int taille) : taille(taille) {}

            // Constructeur
            Matrice(std::vector<double> a, std::vector<double> b, std::vector<double> c);

            // getters et setters
            int getTaille() const { return taille; }

            double getDiagonale(int i) const { return diagonale[i]; }

            double getSousDiagonale(int i) const { return sousDiagonale[i]; }

            double getSurDiagonale(int i) const { return surDiagonale[i]; }

            void setDiagonale(int i, double val) { diagonale[i] = val; }

            void setSousDiagonale(int i, double val) { sousDiagonale[i] = val; }

            void setSurDiagonale(int i, double val) { surDiagonale[i] = val; }

            // Méthode pour calculer la matrice tridiagonale
            std::vector<std::vector<double>> matriceTridiagonale() const;

            // Méthode pour calculer le second membre
            std::vector<double> secondMembre() const;

            // Destructeur
            ~Matrice()
            {
                diagonale.clear();
                sousDiagonale.clear();
                surDiagonale.clear();
            }
    };

#endif