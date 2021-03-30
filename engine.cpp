#include "engine.h"

Engine::Engine() {}

Engine::~Engine()
{
}

void Engine::createTask(int rows, int columns)
{
    m_storage.clear();

    MatrixX* matrix = new MatrixX(rows, columns);
    m_storage.setMatrix(matrix);
    m_basis.create(columns);
}

void Engine::setCell(const short row, const short column, std::string value)
{
    m_storage.matrix()->cell(row, column) = num::fromString(value.data());
}

void Engine::setB(const short row, std::string value)
{
    m_storage.matrix()->b(row) = num::fromString(value.data());
}

void Engine::setFCoef(const short column, std::string value)
{
    m_storage.matrix()->fRow(column) = num::fromString(value.data());
}

void Engine::setMax()
{
    m_isMax = true;
}

void Engine::setBasis(int pos, std::string value)
{
    m_basis[pos] = num::fromString(value.data());
}

void Engine::setMethod(int value)
{
    m_method = value;
}

SimplexResult Engine::start()
{
    // Вспомогательные переменные
    short row, column;
    // Приведение исходной матрицы к нормальной форме
    // - Переход к min
    // - Превращение всех свободных членов в положительные
    m_storage.matrix()->toNormalForm();

    switch (m_method) {
    case 0:
        if(m_storage.matrix()->rows() >= m_storage.matrix()->columns()){
            if(!m_storage.setMatrix(m_storage.matrix()->toClearGauss())) return SimplexResult::InconsistentSystem;

            if(m_storage.matrix()->rows() == m_storage.matrix()->columns()){

                m_basis.fill(1);
                // Преобразование методом Гаусса
                if(!m_storage.setMatrix(m_storage.matrix()->toGauss(m_basis))) return SimplexResult::SingularMatrix;
                // Переход к симплекс методу
                m_storage.setMatrix(m_storage.matrix()->toSimplexFromGauss(m_basis));
            }
            else {
                // Преход к методу искусстенного базиса
                m_storage.setMatrix(m_storage.matrix()->toArtificialBasis());
                // Решение методом искуственного базиса
                while(m_storage.matrix()->nextSolveCell(&row, &column)){
                    m_storage.setMatrix(m_storage.matrix()->nextStep(row, column));
                }
                if(m_storage.matrix()->hasNegativeColumn()) return SimplexResult::NoSolution;
                // Переход к симплекс методу
                if(!m_storage.setMatrix(m_storage.matrix()->toSimplexFromArtificialBasis(*m_storage.getMatrix(0)))) return SimplexResult::ArtificialVariablesInBasis;
            }
        }
        else{
            // Преход к методу искусстенного базиса
            m_storage.setMatrix(m_storage.matrix()->toArtificialBasis());
            // Решение методом искуственного базиса
            if(!simplex()) return SimplexResult::NoSolution;
            // Переход к симплекс методу
            if(!m_storage.setMatrix(m_storage.matrix()->toSimplexFromArtificialBasis(*m_storage.getMatrix(0)))) return SimplexResult::ArtificialVariablesInBasis;
        }
    break;
    case 1:
        // Преобразование методом Гаусса
        if(!m_storage.setMatrix(m_storage.matrix()->toGauss(m_basis))) return SimplexResult::SingularMatrix;
        // Переход к симплекс методу
        m_storage.setMatrix(m_storage.matrix()->toSimplexFromGauss(m_basis));
    break;
    case 2:
        //invertBasis();
        // Преобразование методом Гаусса
        if(!m_storage.setMatrix(m_storage.matrix()->toGauss(m_basis))) return SimplexResult::SingularMatrix;
        // Переход к симплекс методу
        m_storage.setMatrix(m_storage.matrix()->toSimplexFromGauss(m_basis));
    break;
    }

    // Симплекс метод
    while(m_storage.matrix()->nextSolveCell(&row, &column)){
        m_storage.setMatrix(m_storage.matrix()->nextStep(row, column));
    }
    if(m_storage.matrix()->hasNegativeColumn()) return SimplexResult::NoSolution;

    return SimplexResult::OK;
}

SimplexResult Engine::changePath(const int index, const short row, const short column)
{
    m_storage.setCursor(index);

    m_storage.setMatrix(m_storage.matrix()->nextStep(row, column));

    if(m_storage.matrix()->getState() == InArtificialBasis){
        if(!simplex()) return SimplexResult::NoSolution;
        if(!m_storage.setMatrix(m_storage.matrix()->toSimplexFromArtificialBasis(*m_storage.getMatrix(0)))) return SimplexResult::ArtificialVariablesInBasis;
    }

    if(!simplex()) return SimplexResult::NoSolution;
    return SimplexResult::OK;
}

MatrixX *Engine::getResult()
{
    return m_storage.matrix();
}

Storage &Engine::getStorage()
{
    return m_storage;
}

Basis &Engine::getBasis()
{
    return m_basis;
}

QString Engine::getResultText(int index, bool type)
{
    QString text;
    std::vector<num> res = m_storage.getMatrix(index)->getResult();
    text += "X = (";
    for(int i = 0; i < int(res.size()) - 1; i++) {
        text += type ? res[i].toString().data() : QString::number(res[i].toDouble());
        text += ", ";
    }

    text += type ? res[res.size() - 1].toString().data() : QString::number(res[res.size() - 1].toDouble());
    text += ")";

    text += "\n";

    text += "f(x) = ";
    num f = -m_storage.getMatrix(index)->f();
    text += type ? f.toString().data() : QString::number(f.toDouble());

    return text;
}

void Engine::invertBasis()
{
    for(int i = 0; i < m_basis.size(); i++){
        if(m_basis[i] == 0) m_basis[i] = 1;
        else m_basis[i] = 0;
    }
}

bool Engine::simplex()
{
    short row, column;

    while(m_storage.matrix()->nextSolveCell(&row, &column)){
        m_storage.setMatrix(m_storage.matrix()->nextStep(row, column));
    }
    if(m_storage.matrix()->hasNegativeColumn()) return false;
    return true;
}
