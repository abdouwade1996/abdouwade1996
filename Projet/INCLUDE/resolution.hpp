#ifndef RESOLUTION_HPP
#define RESOLUTION_HPP

#include "matrice.hpp"
#include <vector>
#include "parametres.hpp"

/**
 * @brief Class representing the resolution of a linear system using LU decomposition.
 */
class Resolution
{
private:
    std::vector<double> diagonaleL; /**< Vector representing the diagonal of the matrix */
    std::vector<double> surDiagonaleU; /**< Vector representing the upper diagonal of the matrix */

public:
    /**
     * @brief Constructor for Resolution class.
     * @param b_star Vector representing the diagonal of the matrix.
     * @param c_star Vector representing the upper diagonal of the matrix.
     */
    Resolution(std::vector<double> b_star, std::vector<double> c_star)
        : diagonaleL(b_star), surDiagonaleU(c_star) {}

    /**
     * @brief Method to solve the linear system using LU decomposition.
     * @param matrice The matrix to be decomposed.
     * @param taille The size of the matrix.
     */
    Resolution(Matrice matrice, int taille);

    // getters and setters
    /**
     * @brief Get the value of the diagonal element at index i.
     * @param i The index of the diagonal element.
     * @return The value of the diagonal element at index i.
     */
    double getDiagonaleL(int i) const { return diagonaleL[i]; }

    /**
     * @brief Get the value of the upper diagonal element at index i.
     * @param i The index of the upper diagonal element.
     * @return The value of the upper diagonal element at index i.
     */
    double getSurDiagonaleU(int i) const { return surDiagonaleU[i]; }

    /**
     * @brief Set the value of the diagonal element at index i.
     * @param i The index of the diagonal element.
     * @param val The new value for the diagonal element at index i.
     */
    void setDiagonaleL(int i, double val) { diagonaleL[i] = val; }

    /**
     * @brief Set the value of the upper diagonal element at index i.
     * @param i The index of the upper diagonal element.
     * @param val The new value for the upper diagonal element at index i.
     */
    void setSurDiagonaleU(int i, double val) { surDiagonaleU[i] = val; }

    /**
     * @brief Perform LU decomposition on the given matrix.
     * @param matrice The matrix to be decomposed.
     * @param taille The size of the matrix.
     */
    void decompositionLU(Matrice matrice, int taille);

    /**
     * @brief Solve the equation LY = F for Y.
     * @param matrice The matrix L.
     * @param taille The size of the matrix.
     * @return The solution vector Y.
     */
    std::vector<double> resoudreLYF(Matrice matrice, int taille);

    /**
     * @brief Solve the equation UX = Y for X.
     * @param Y The solution vector Y.
     * @param taille The size of the matrix.
     * @return The solution vector X.
     */
    std::vector<double> resoudreUXY(std::vector<double> Y, int taille);

    /**
     * @brief Write the vector to a CSV file.
     * @param vecteur The vector to be written.
     * @param nomFichier The name of the CSV file.
     * @param TExacte The exact solution vector.
     */
    void ecrireFichier(std::vector<double> vecteur, std::string nomFichier, std::vector<double> TExacte);

    /**
     * @brief Calculate the exact solution vector.
     * @return The exact solution vector.
     */
    std::vector<double> solutionExacte();

    /**
     * @brief Write the vector to a VTK file.
     * @param vecteur The vector to be written.
     * @param fileName The name of the VTK file.
     */
    void writeVTKFile(std::vector<double> vecteur, std::string fileName);

    /**
     * @brief Destructor for Resolution class.
     */
    ~Resolution()
    {
        diagonaleL.clear();
        surDiagonaleU.clear();
    }
};

#endif
