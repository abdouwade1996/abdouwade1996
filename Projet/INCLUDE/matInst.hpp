#ifndef MATINST_HPP
    #define MATINST_HPP
    #include <iostream>
    #include "parametres.hpp"
    #include <vector>
    
    /**
     * @brief The MatInst class represents a tridiagonal matrix.
     * 
     * This class stores the elements of a tridiagonal matrix and provides methods to perform calculations on it.
     */
    class MatInst
    {
    private:
        std::vector<double> sousDiagInst;   // Vector to store the sub-diagonal elements
        std::vector<double> diagInst;       // Vector to store the diagonal elements
        std::vector<double> surDiagInst;    // Vector to store the super-diagonal elements
        int taille;                         // Size of the matrix

    public:
        /**
         * @brief Constructs a MatInst object with the given size.
         * 
         * @param taille The size of the matrix.
         */
        MatInst(int taille) : taille(taille) {}

        /**
         * @brief Constructs a MatInst object with the given vectors of elements.
         * 
         * @param a The vector of sub-diagonal elements.
         * @param b The vector of diagonal elements.
         * @param c The vector of super-diagonal elements.
         */
        MatInst(std::vector<double> a, std::vector<double> b, std::vector<double> c);

        /**
         * @brief Constructs a MatInst object from a matrix represented as a vector of vectors.
         * 
         * @param matriceTridiagInst The matrix represented as a vector of vectors.
         * @param taille The size of the matrix.
         */
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
        /**
         * @brief Returns the size of the matrix.
         * 
         * @return The size of the matrix.
         */
        int getTaille() const { return taille; }

        /**
         * @brief Returns the diagonal element at the specified index.
         * 
         * @param i The index of the diagonal element.
         * @return The diagonal element at the specified index.
         */
        double getDiagInst(int i) const { return diagInst[i]; }

        /**
         * @brief Returns the sub-diagonal element at the specified index.
         * 
         * @param i The index of the sub-diagonal element.
         * @return The sub-diagonal element at the specified index.
         */
        double getSousDiagInst(int i) const { return sousDiagInst[i]; }

        /**
         * @brief Returns the super-diagonal element at the specified index.
         * 
         * @param i The index of the super-diagonal element.
         * @return The super-diagonal element at the specified index.
         */
        double getSurDiagInst(int i) const { return surDiagInst[i]; }

        /**
         * @brief Calculates and returns the tridiagonal matrix represented as a vector of vectors.
         * 
         * @return The tridiagonal matrix represented as a vector of vectors.
         */
        std::vector<std::vector<double>> matriceTridiagInst() const;

        /**
         * @brief Calculates and returns the second member vector.
         * 
         * @return The second member vector.
         */
        std::vector<double> FInst() const;

        /**
         * @brief Destroys the MatInst object and clears the vectors of elements.
         */
        ~MatInst()
        {
            diagInst.clear();
            sousDiagInst.clear();
            surDiagInst.clear();
        }
    };
    
#endif
