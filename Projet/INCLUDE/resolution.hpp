#ifndef RESOLUTION_HPP
#define RESOLUTION_HPP

    #include "matrice.hpp"
    #include <vector>
    #include "parametres.hpp"

    class Resolution
    {
        private:
            std::vector<double> diagonaleL; /**< Vecteur représentant la diagonale de la matrice */
            std::vector<double> surDiagonaleU; /**< Vecteur représentant la sur-diagonale de la matrice */

        public:
            // Constructeur
            Resolution(std::vector<double> b_star, std::vector<double> c_star)
            : diagonaleL(b_star), surDiagonaleU(c_star) {}

            // Méthode pour résoudre le système
            Resolution(Matrice matrice, int taille);

            // getters et setters
            double getDiagonaleL(int i) const { return diagonaleL[i]; }

            double getSurDiagonaleU(int i) const { return surDiagonaleU[i]; }

            void setDiagonaleL(int i, double val) { diagonaleL[i] = val; }

            void setSurDiagonaleU(int i, double val) { surDiagonaleU[i] = val; }

            // Méthodes de décomposition LU
            void decompositionLU(Matrice matrice, int taille);

            // Méthodes de résolution LY = F
            std::vector<double> resoudreLYF(Matrice matrice, int taille);

            // Méthodes de résolution UX = Y
            std::vector<double> resoudreUXY(std::vector<double> Y, int taille);

            // Méthode pour écrire dans un fichier CSV
            void ecrireFichier(std::vector<double> vecteur, std::string nomFichier, std::vector<double> TExacte);

            // Méthode pour calculer la solution exacte
            std::vector<double> solutionExacte();

            // Méthode pour écrire dans un fichier VTK
            void writeVTKFile(std::vector<double> vecteur, std::string fileName);

            // Destructeur
            ~Resolution()
            {
                diagonaleL.clear();
                surDiagonaleU.clear();
            }

    };

#endif
