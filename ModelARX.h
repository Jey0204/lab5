
#ifndef MODEL_ARX_H
#define MODEL_ARX_H

#include "ObiektSISO.h"
#include <vector>
#include <deque>
#include <random>

/**
 * @author Jessica Adamczyk
 * @class ModelARX
 * @brief Implementacja dyskretnego modelu ARX
 */

class ModelARX : public ObiektSISO
{
public:
    ModelARX(const std::vector<double> &a, const std::vector<double> &b, unsigned int delay = 1, double sigma = 0.0);
    ModelARX() = delete;

    void setWspolczynnikiA(const std::vector<double> &a);
    void setWspolczynnikiB(const std::vector<double> &b);
    void setOpoznienie(int d);
    void setOdchylenieStandardowe(double s);

    double symuluj(double u) override;

private:
    std::vector<double> a_coeffs;
    std::vector<double> b_coeffs;
    unsigned int delay;
    double sigma;

    std::deque<double> input_buffer;
    std::deque<double> delay_buffer;
    std::deque<double> output_buffer;

    std::default_random_engine gen;
    std::normal_distribution<double> dist;
};

#endif
