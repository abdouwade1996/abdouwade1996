/**
 * @file resolutionInst.hpp
 * @brief Header file for the ResolutionInst class.
 */

#ifndef __RESOLUTIONINST_HPP__
#define __RESOLUTIONINST_HPP__

#include "matInst.hpp"
#include <vector>
#include "parametres.hpp"

/**
 * @class ResolutionInst
 * @brief Class representing the resolution of an instance.
 */
class ResolutionInst
{
private:
    std::vector<double> diagInstL;    /**< Vector representing the diagonal of the matrix */
    std::vector<double> surDiagInstU; /**< Vector representing the upper diagonal of the matrix */
    int taille;                       /**< Size of the matrix */

public:
    /**
     * @brief Constructor for the ResolutionInst class.
     * @param b_star The vector representing the diagonal of the matrix.
     * @param c_star The vector representing the upper diagonal of the matrix.
     */
    ResolutionInst(std::vector<double> b_star, std::vector<double> c_star)
        : diagInstL(b_star), surDiagInstU(c_star) {}

    /**
     * @brief Constructor for the ResolutionInst class.
     * @param matInst The instance of the MatInst class.
     * @param taille The size of the matrix.
     */
    ResolutionInst(MatInst matInst, int taille);

    // getters and setters
    /**
     * @brief Get the value at the specified index in the diagonal vector.
     * @param i The index.
     * @return The value at the specified index in the diagonal vector.
     */
    double getDiagInstL(int i) const { return diagInstL[i]; }

    /**
     * @brief Get the value at the specified index in the upper diagonal vector.
     * @param i The index.
     * @return The value at the specified index in the upper diagonal vector.
     */
    double getSurDiagInstU(int i) const { return surDiagInstU[i]; }

    /**
     * @brief Get the size of the matrix.
     * @return The size of the matrix.
     */
    int getTaille() const { return taille; }

    /**
     * @brief Set the value at the specified index in the diagonal vector.
     * @param i The index.
     * @param val The value to set.
     */
    void setDiagInstL(int i, double val) { diagInstL[i] = val; }

    /**
     * @brief Set the value at the specified index in the upper diagonal vector.
     * @param i The index.
     * @param val The value to set.
     */
    void setSurDiagInstU(int i, double val) { surDiagInstU[i] = val; }

    // LU decomposition methods
    /**
     * @brief Perform LU decomposition on the given MatInst instance.
     * @param matInsta The MatInst instance.
     * @param MInsta The size of the matrix.
     */
    void LUInst(const MatInst &matInsta, int MInsta);

    // LY = F resolution methods
    /**
     * @brief Solve the equation LY = F for Y.
     * @param Y The vector Y.
     * @param matInsta The MatInst instance.
     * @param taille The size of the matrix.
     * @param F The vector F.
     * @return The solution vector Y.
     */
    std::vector<double> LYFInst(std::vector<double> Y, const MatInst &matInsta, int taille, std::vector<double> F) const;

    // UX = Y resolution methods
    /**
     * @brief Solve the equation UX = Y for X.
     * @param Y The vector Y.
     * @param taille The size of the matrix.
     * @return The solution vector X.
     */
    std::vector<double> UXYInst(std::vector<double> Y, int taille) const;

    // Resolution methods for the instationary system
    /**
     * @brief Solve the instationary system.
     * @param matInsta The MatInst instance.
     * @param taille The size of the matrix.
     * @return The solution matrix.
     */
    std::vector<std::vector<double>> resoudreInst(MatInst matInsta, int taille) const;

    // LU decomposition method
    /**
     * @brief Perform LU decomposition on the given MatInst instance.
     * @param matInsta The MatInst instance.
     * @return The vector of MatInst instances.
     */
    std::vector<MatInst> FactoLU(const MatInst &matInsta) const;

    // CSV writing methods for the instationary case
    /**
     * @brief Write the solution matrix to a CSV file.
     * @param Solve The solution matrix.
     * @param nomFichier The name of the CSV file.
     */
    void ecritureCSVInst(std::vector<std::vector<double>> Solve, std::string nomFichier) const;

    /**
     * @brief Write the solution matrix to a CSV file with flux values.
     * @param Solve The solution matrix.
     * @param nomFichier The name of the CSV file.
     */
    void ecritureCSVFluxInst(std::vector<std::vector<double>> Solve, std::string nomFichier) const;

    /**
     * @brief Write the solution matrix to a VTK file for a specific time step.
     * @param Solve The solution matrix.
     * @param pasDeTemps The time step.
     */
    void VTKParPasDeTemps(std::vector<std::vector<double>> Solve, int pasDeTemps);

    /**
     * @brief Destructor for the ResolutionInst class.
     */
    ~ResolutionInst()
    {
        diagInstL.clear();
        surDiagInstU.clear();
    }
};

#endif