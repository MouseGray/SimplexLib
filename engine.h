#ifndef ENGINE_H
#define ENGINE_H

#include "storage.h"
#include "basis.h"

#include <QString>

enum SimplexResult {
    OK,
    SingularMatrix,
    ArtificialVariablesInBasis,
    NoSolution,
    InconsistentSystem
};

class SIMPLEXLIB_EXPORT Engine
{
public:
    Engine();
    ~Engine();
    void createTask(int rows, int columns);
    void setCell(const short row, const short column, std::string value);
    void setB(const short row, std::string value);
    void setFCoef(const short column, std::string value);
    void setMax();
    void setBasis(int pos, std::string value);
    void setMethod(int value);
    /*  codes:
     *  0 - результат найден
     *  1 - матрица по базису вырождена
     *  2 - базис содержит искусственные переменные
     *  3 - решения нет
     */
    SimplexResult start();
    /*  codes:
     *  0 - результат найден
     *  2 - базис содержит искусственные переменные
     *  3 - решения нет
     */
    SimplexResult changePath(const int index, const short row, const short column);

    MatrixX* getResult();
    Storage& getStorage();

    Basis& getBasis();
    QString getResultText(int index, bool type = true);
private:
    void invertBasis();

    bool simplex();

    Storage m_storage;
    int m_method = 0;
    bool m_isMax = false;
    bool m_gomory = true;

    Basis m_basis;
};

#endif // ENGINE_H
