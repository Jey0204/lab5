
#include "ModelARX.h"

ModelARX::ModelARX(const std::vector<double> &a, const std::vector<double> &b, unsigned int delay, double sigma)
{
    setWspolczynnikiA(a);
    setWspolczynnikiB(b);
    setOpoznienie(delay);
    setOdchylenieStandardowe(sigma);
}

void ModelARX::setWspolczynnikiA(const std::vector<double> &a)
{
    a_coeffs = a;
    output_buffer.assign(a_coeffs.size(), 0.0);
}

void ModelARX::setWspolczynnikiB(const std::vector<double> &b)
{
    b_coeffs = b;
    input_buffer.assign(b_coeffs.size(), 0.0);
}

void ModelARX::setOpoznienie(int d)
{
    delay = (d <= 0) ? 1 : static_cast<unsigned int>(d);
    delay_buffer.assign(delay, 0.0);
}

void ModelARX::setOdchylenieStandardowe(double s)
{
    sigma = (s < 0.0) ? 0.0 : s;
    dist = std::normal_distribution<double>(0.0, sigma);
}

double ModelARX::symuluj(double u)
{
    // Dodaj zak��cenie
    double noise = (sigma > 0.0) ? dist(gen) : 0.0;

    // Op�nienie wej�cia
    delay_buffer.push_back(u);
    double delayed_u = delay_buffer.front();
    delay_buffer.pop_front();

    // Zaktualizuj bufor wej�ciowy
    input_buffer.push_back(delayed_u);
    if (input_buffer.size() > b_coeffs.size())
        input_buffer.pop_front();

    double y = 0.0;

    // Licznik (B)
    for (size_t i = 0; i < b_coeffs.size(); ++i)
        y += b_coeffs[i] * input_buffer[input_buffer.size() - 1 - i];

    // Mianownik (A)
    for (size_t i = 0; i < a_coeffs.size(); ++i)
        y -= a_coeffs[i] * output_buffer[output_buffer.size() - 1 - i];

    y += noise;

    // Zaktualizowany bufor wyjściowy
    output_buffer.push_back(y);
    if (output_buffer.size() > a_coeffs.size())
        output_buffer.pop_front();

    return y;
}