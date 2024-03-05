#ifndef MATRICE_HPP
#define MATRICE_HPP

    #include <iostream>
    #include "parametres.hpp"
    #include <vector>

    /**
     * @brief Represents a tridiagonal matrix.
     * 
     * This class represents a tridiagonal matrix with a given size.
     * It stores the values of the sub-diagonal, diagonal, and super-diagonal elements.
     * The class provides methods to access and modify the elements of the matrix,
     * as well as methods to calculate the tridiagonal matrix and the right-hand side vector.
     */
    class Matrice
    {
        private:
            std::vector<double> sousDiagonale; /**< Vector representing the sub-diagonal of the matrix. */
            std::vector<double> diagonale;     /**< Vector representing the diagonal of the matrix. */
            std::vector<double> surDiagonale;  /**< Vector representing the super-diagonal of the matrix. */
            int taille;                        

        public:
            /**
             * @brief Constructs a Matrice object with the given size.
             * 
             * @param taille The size of the matrix.
             */
            Matrice(int taille) : taille(taille) {}

            /**
             * @brief Constructs a Matrice object with the given sub-diagonal, diagonal, and super-diagonal vectors.
             * 
             * @param a The sub-diagonal vector.
             * @param b The diagonal vector.
             * @param c The super-diagonal vector.
             */
            Matrice(std::vector<double> a, std::vector<double> b, std::vector<double> c);

            // getters et setters
            int getTaille() const { return taille; }

            double getDiagonale(int i) const { return diagonale[i]; }

            double getSousDiagonale(int i) const { return sousDiagonale[i]; }

            double getSurDiagonale(int i) const { return surDiagonale[i]; }

            void setDiagonale(int i, double val) { diagonale[i] = val; }

            void setSousDiagonale(int i, double val) { sousDiagonale[i] = val; }

            void setSurDiagonale(int i, double val) { surDiagonale[i] = val; }

            /**
             * @brief Calculates the tridiagonal matrix.
             * 
             * @return A 2D vector representing the tridiagonal matrix.
             */
            std::vector<std::vector<double>> matriceTridiagonale() const;

            /**
             * @brief Calculates the right-hand side vector.
             * 
             * @return A vector representing the right-hand side vector.
             */
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